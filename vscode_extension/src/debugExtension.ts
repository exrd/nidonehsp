// vscode拡張
import * as vscode from "vscode";

// 直接インポートするもの
import {
  WorkspaceFolder,
  DebugConfiguration,
  ProviderResult,
  CancellationToken,
} from "vscode";

// その他一般
import * as path from "path";
import * as cp from "child_process";

// ローカル
import * as util from "./util";
import * as task from "./task";

// デバッグコンフィグ
export class DebugConfigurationProvider
  implements vscode.DebugConfigurationProvider {
  // コンテキスト
  private vscontext?: vscode.ExtensionContext;

  // ctor
  public constructor(context: vscode.ExtensionContext) {
    this.vscontext = context;
  }

  // 代入前フック
  public resolveDebugConfiguration(
    folder: WorkspaceFolder | undefined,
    config: DebugConfiguration,
    token?: CancellationToken
  ): ProviderResult<DebugConfiguration> {
    // OSチェック
    if (!util.isStudioSupportedPlatform()) {
      vscode.window.showErrorMessage(
        util.shared.localeString('nidonehsp-env.debugger.resolve.unsupportedPlatform')
      );
      return undefined;
    }

    // 何も入ってないなら今開いているものを自動でターゲットに
    if (!config.program || config.program === "") {
      const editor = vscode.window.activeTextEditor;
      if (editor && editor.document.languageId === "nidonehsp") {
        config.program = "${file}";
      }
    }

    return config;
  }

  // 代入後フック
  public async resolveDebugConfigurationWithSubstitutedVariables(
    folder: WorkspaceFolder | undefined,
    config: DebugConfiguration,
    token?: CancellationToken
  ): Promise<DebugConfiguration | undefined> {
    // スタートアップスクリプトがないならエラー
    if (!config.program) {
      return vscode.window
        .showInformationMessage("Cannot find a startup script to debug")
        .then(() => {
          return undefined;
        });
    }

    // ポート
    if (config.port === undefined) {
      config.port = 9022;
    }

    // cwd
    if (config.cwd === undefined) {
      config.cwd = path.dirname(config.program);
    }

    // プリデバッグコンパイルチェック
    if (config.preDebugCompileCheck === undefined) { config.preDebugCompileCheck = true; }
    if (config.preDebugCompileCheck) {
      const compileTask = task.compileCheckTaskProvider.generateTask({ type: task.compileCheckTaskType, program: config.program }, true);
      if (!compileTask) { return undefined; }
      const compileSuccess = await util.shared.executeTask(compileTask) === 0;
      if (!compileSuccess) {
        vscode.window.showErrorMessage(util.shared.localeString('nidonehsp-env.debugger.resolve.preDebugCompileCheck.failed'));
        util.shared.focusToProblemsView();
        return undefined;
      }
    }

    //consol.log(`nidonehsp-env: resolveDebugConfigurationWithSubstitutedVariables: ${JSON.stringify(config)}`);
    return config;
  }
}

export class DebugAdapterServerDescriptorFactory
  implements vscode.DebugAdapterDescriptorFactory {
  // 裏に存在するデバッグインスタンス
  private _pinstance?: cp.ChildProcessWithoutNullStreams;

  // デバッグセッションの開始
  public createDebugAdapterDescriptor(
    session: vscode.DebugSession,
    executable: vscode.DebugAdapterExecutable | undefined
  ): vscode.ProviderResult<vscode.DebugAdapterDescriptor> {
    // 前回のセッションを閉じる
    this.closeInstance();

    // コンフィグ
    const config = session.configuration;

    const port = config.port as number;

    // インスタンス無いなら作る
    if (!this._pinstance) {
      // ランタイムの決定
      const debugRuntime = config.debuggerRuntime;
      if (!util.shared.ensureLambdaOrShowErrorMessage(() => { util.shared.ensureRuntimeStudioPath(debugRuntime); })) {
        return undefined;
      }
      const studioPath = util.shared.runtimeStudioPath(debugRuntime);

      // コマンド実行
      const debugArgs: string[] = [
        '--mode', 'debugadapter',
        '--startup-script', `${config.program}`,
        '--da-port', `${port}`,
        '--da-logging', `${config.logDebuggerRuntime ? '1' : '0'}`,
      ]
      .concat(util.shared.makeAdditionalIncludePathsArgs())
      .concat(util.shared.makeAdditionalDefineMacrosArgs())
      .map((v) => `"${v.replace(/\"/g, '\\"')}"`);// エスケープ

      this._pinstance = cp.spawn(studioPath, debugArgs, {cwd: config.cwd, shell: true});

      // ロギング
      if (config.logDebuggerRuntime) {
        console.log(`launched ${studioPath} ${debugArgs.join(' ')}`);
      }
      if (this._pinstance && config.logDebuggerRuntime) {
        this._pinstance.stdout.on('data', (data) => {
          console.log(data.toString());
        });
        this._pinstance.stderr.on('data', (data) => {
          console.log(data.toString());
        });
      }
    }

    // そのポートへ
    return new vscode.DebugAdapterServer(port);
  }

  // subscription用
  dispose() {
    this.closeInstance();
  }

  // インスタンスを強制終了
  private closeInstance() {
    if (this._pinstance) {
      if (!this._pinstance.killed) {
        // sigkillの方がいいか？
        this._pinstance.kill();
      }
      this._pinstance = undefined;
    }
  }
}

// アクティベート関数
export function activateDebugExtension(context: vscode.ExtensionContext) {
  // デバッグコンフィグ
  const provider = new DebugConfigurationProvider(context);
  context.subscriptions.push(
    vscode.debug.registerDebugConfigurationProvider("nidonehsp-env", provider)
  );

  // デバッガ
  const factory = new DebugAdapterServerDescriptorFactory();
  context.subscriptions.push(
    vscode.debug.registerDebugAdapterDescriptorFactory("nidonehsp-env", factory)
  );
}

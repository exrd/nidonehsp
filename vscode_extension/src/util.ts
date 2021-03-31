
import * as fs from "fs";
import * as path from "path";
import * as process from "process";

// vscode拡張
import * as vscode from "vscode";

// problemMatcher
export const problemMatcherStudio = '$nidonehsp-env.studio';

// ext
export const osSpecificExecutableExtension = process.platform.startsWith('win') ? '.exe' : '';

// シングルトン
class Shared {
  public initialize(context: vscode.ExtensionContext) {
    this._vscontext = context;

    // initialize locale table
    const defaultLocaleTable = require('../package.nls.json');
    const currentLocale = JSON.parse(process.env.VSCODE_NLS_CONFIG as string).locale;
    let currentLocaleTable = {};
    switch (currentLocale) {
      case 'ja': currentLocaleTable = require('../package.nls.ja.json'); break;
      default: break;
    }
    this._localeTable = Object.assign(defaultLocaleTable, currentLocaleTable);
  }

  public shellQuoted(value: string): vscode.ShellQuotedString {
    return { quoting: vscode.ShellQuoting.Strong, value: value };
  }

  public localeTable() {
    return this._localeTable;
  }

  public localeString(label: string, orLabel: string | undefined = undefined): string {
    return this._localeTable[label] || orLabel || label;
  }

  public ensureLambdaOrShowErrorMessage(lambda: () => void): boolean {
    try {
      lambda();
      return true;
    } catch (e) {
      vscode.window.showErrorMessage(e.message);
      return false;
    }
  }

  public additionalIncludePaths(): string[] {
    const paths: string[] = [];
    const rawPaths: any = this.getConfiguration('runtime.includePath') || [];
    if (typeof(rawPaths) === 'object') {
      for (var k in rawPaths) {
        const path = rawPaths[k];
        if (typeof(path) === 'string') {
          paths.push(path);
        }
      }
    }
    return paths;
  }

  public additionalDefineMacros(): string[] {
    const macros: string[] = [];
    const rawMacros: any = this.getConfiguration('runtime.defineMacro') || [];
    if (typeof(rawMacros) === 'object') {
      for (var k in rawMacros) {
        const macro = rawMacros[k];
        if (typeof(macro) === 'string') {
          macros.push(macro);
        }
      }
    }
    return macros;
  }

  public makeAdditionalIncludePathsArgs(addCommonPath: boolean = true): string[] {
    const args: string[] = [];
    const srcPaths = this.additionalIncludePaths();
    if (addCommonPath) {
      srcPaths.push(path.join(path.dirname(this.runtimeStudioPath()), 'common'));
    }
    for (var k in srcPaths) {
      const srcPath = srcPaths[k];
      args.push('-I');
      args.push(srcPath);
    }
    return args;
  }

  public makeAdditionalDefineMacrosArgs(): string[] {
    const args: string[] = [];
    const srcMacros = this.additionalDefineMacros();
    for (var k in srcMacros) {
      const srcMacro = srcMacros[k];
      args.push('-D');
      args.push(srcMacro);
    }
    return args;
  }

  public runtimeRootPath(prior: string | undefined = undefined): string {
    return prior
      || this.getConfiguration('runtime.runtimeRootPath') as string
      || path.join(this._vscontext?.extensionPath || '', 'bin', 'runtime');
  }

  public ensureRuntimeRootPath(prior: string | undefined = undefined) {
    const path = this.runtimeRootPath(prior);
    if (fs.existsSync(path)) { return; }
    throw new Error(this.localeString('nidonehsp-env.shared.cannotResolveRuntimeRootPath').replace(/\$\{resolvedPath\}/g, path));
  }

  public runtimeStudioPath(prior: string | undefined = undefined): string {
    return prior
      || this.getConfiguration('runtime.studioPath') as string
      || path.join(this._vscontext?.extensionPath || '', 'bin', `n2studio${osSpecificExecutableExtension}`);
  }

  public ensureRuntimeStudioPath(prior: string | undefined = undefined) {
    const path = this.runtimeStudioPath(prior);
    if (fs.existsSync(path)) { return; }
    throw new Error(this.localeString('nidonehsp-env.shared.cannotResolveStudioPath').replace(/\$\{resolvedPath\}/g, path));
  }

  public async executeTask(task: vscode.Task): Promise<number> {
    const resPromise = new Promise<number>(resolve => {
      let taskDisposable = vscode.tasks.onDidEndTaskProcess(ev => {
        if (ev.execution.task !== task) { return; }
        taskDisposable.dispose();
        resolve(ev.exitCode === undefined ? -1 : ev.exitCode);
      });
    });
    await vscode.tasks.executeTask(task);
    return resPromise;
  }

  public executeCommandIfFound(command: string): boolean {
    let found = false;
    vscode.commands.getCommands(true).then((commands: string[]) => {
      if (commands.indexOf(command) >= 0) {
        vscode.commands.executeCommand(command);
        found = true;
      }
    });
    return found;
  }

  public focusToProblemsView(): boolean {
    return this.executeCommandIfFound('workbench.action.problems.focus');
  }

  private getConfiguration(label: string) {
    return vscode.workspace.getConfiguration('nidonehsp-env').get(label);
  }

  private _vscontext: vscode.ExtensionContext | null = null;
  private _localeTable: { [key: string]: string } = {};
};

export const shared = new Shared();// シングルトン化

// 今動いているOSサポートされてる？
export function isStudioSupportedPlatform() {
  return process.platform.startsWith('win');
}

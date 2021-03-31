// vscode
import * as vscode from "vscode";

// local modules
import * as util from "./util";
import * as n2task from "./task";
import * as n2helpview from "./helpView";
import * as n2debug from "./debugExtension";

// activate
export function activate(context: vscode.ExtensionContext) {
  //console.log('"nidonehsp-env" is activated');

  // utilは最初に初期化
  util.shared.initialize(context);

  // syntax features
  /*{
    const selector = {language: 'nidonehsp'};
    const provider = new N2DocumentSemanticTokensProvider();
    const legend = N2DocumentSemanticTokensProvider.semanticTokenLegend();

    context.subscriptions.push(
      vscode.languages.registerDocumentSemanticTokensProvider(
        selector,
        provider,
        legend
      )
    );
  }*/
  // @todo LSP

  // task
  n2task.activateTaskExtension(context);

  // helpview
  n2helpview.activateHelpViewExtension(context);

  // debugger and etc
  n2debug.activateDebugExtension(context);

  // コマンド登録
  context.subscriptions.push(
    vscode.commands.registerCommand("nidonehsp-env.helpview", async () => {
      await n2helpview.helpViewer?.helpViewOpen(vscode.window.activeTextEditor);
    })
  );

  context.subscriptions.push(
    vscode.commands.registerTextEditorCommand(
      "nidonehsp-env.helpviewOnEditor",
      async (textEditor: vscode.TextEditor) => {
        await n2helpview.helpViewer?.helpViewOpen(textEditor);
      }
    )
  );

  context.subscriptions.push(
    vscode.commands.registerCommand("nidonehsp-env.previewActiveScript", async () => {
      const task = n2task.previewTaskProvider.getActiveDocumentTask(true);
      if (task) { vscode.tasks.executeTask(task); }
    })
  );

  context.subscriptions.push(
    vscode.commands.registerCommand("nidonehsp-env.compileCheckActiveScript", async () => {
      const task = n2task.compileCheckTaskProvider.getActiveDocumentTask(true);
      if (!task) { return; }
      const compileSuccess = await util.shared.executeTask(task) === 0;
      if (!compileSuccess) {
        util.shared.focusToProblemsView();
      }
    })
  );

  context.subscriptions.push(
    vscode.commands.registerCommand("nidonehsp-env.buildActiveScript", async () => {
      const task = n2task.buildTaskProvider.getActiveDocumentTask(true);
      if (task) { vscode.tasks.executeTask(task); }
    })
  );

  context.subscriptions.push(
    vscode.commands.registerCommand("nidonehsp-env.exportActiveScript", async () => {
      const task = n2task.exportTaskProvider.getActiveDocumentTask(true);
      if (task) { vscode.tasks.executeTask(task); }
    })
  );
}

// deactivate
export function deactivate() {
  //console.log('"nidonehsp-env" is deactivated');
}

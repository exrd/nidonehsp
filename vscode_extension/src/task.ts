// vscode
import * as path from "path";
import * as vscode from "vscode";

// ローカル
import * as util from "./util";

// 定数
const taskSourceName = 'nidonehsp-env';

// コンパイルチェックタスク
export const compileCheckTaskType = 'nidonehsp-env.compileCheck';

export interface CompileCheckTaskDefinition extends vscode.TaskDefinition {
    type: typeof compileCheckTaskType;
    program: string;
}

export class CompileCheckTaskProvider implements vscode.TaskProvider {
    public provideTasks(): Thenable<vscode.Task[]> | undefined {
        return this.generateTasks();
    }
  
    public resolveTask(task: vscode.Task): vscode.Task | undefined {
        const taskDef: CompileCheckTaskDefinition = <any>task.definition;
        return this.generateTask(taskDef, true);
    }

    public getActiveDocumentTask(isResolve: boolean = false): vscode.Task | undefined {
        if (!vscode.window.activeTextEditor) {
            return undefined;
        }
        return this.generateTask({type: compileCheckTaskType, program: vscode.window.activeTextEditor.document.uri.fsPath}, isResolve);
    }

    private async generateTasks(): Promise<vscode.Task[]> {
        const tasks: vscode.Task[] = [];
        let task: vscode.Task | undefined = undefined;
        if (task = this.getActiveDocumentTask()) {
            tasks.push(task);
        }
        return tasks;
    }

    public generateTask(taskDef: CompileCheckTaskDefinition, isResolve: boolean): vscode.Task | undefined {
        if (isResolve && !this.ensureTaskCondition()) {
            return undefined;
        }
        const studioPath = util.shared.runtimeStudioPath();
        const args: string[] = [
            '--mode', 'compile',
            '--error-dialog', '0',
            '--success-dialog', '0',
            '--startup-script', taskDef.program,
            '--formatted-output', '1',
        ]
        .concat(util.shared.makeAdditionalIncludePathsArgs())
        .concat(util.shared.makeAdditionalDefineMacrosArgs());
        const task = new vscode.Task(
            taskDef,
            vscode.TaskScope.Workspace,
            compileCheckTaskType,
            taskSourceName,
            new vscode.ShellExecution(
                studioPath,
                args.map((arg) => util.shared.shellQuoted(arg)),
                {cwd: path.dirname(taskDef.program)}
            ),
            util.problemMatcherStudio
        );
        //task.group = vscode.TaskGroup.Build;
        return task;
    }

    private ensureTaskCondition(): boolean {
        return util.shared.ensureLambdaOrShowErrorMessage(
            () => { util.shared.ensureRuntimeStudioPath(); }
        );
    }
}

export const compileCheckTaskProvider = new CompileCheckTaskProvider();

// ビルドタスク
export const buildTaskType = 'nidonehsp-env.build';

export interface BuildTaskDefinition extends vscode.TaskDefinition {
    type: typeof buildTaskType;
    program: string;
    outputRootPath: string;
    showDialog: boolean;
}

export class BuildTaskProvider implements vscode.TaskProvider {
    public provideTasks(): Thenable<vscode.Task[]> | undefined {
        return this.generateTasks();
    }
  
    public resolveTask(task: vscode.Task): vscode.Task | undefined {
        const taskDef: BuildTaskDefinition = <any>task.definition;
        return this.generateTask(taskDef, true);
    }

    public getActiveDocumentTask(isResolve: boolean = false): vscode.Task | undefined {
        if (!vscode.window.activeTextEditor) {
            return undefined;
        }
        const docPath = vscode.window.activeTextEditor.document.uri.fsPath;
        let outPath = path.dirname(docPath);
        if ((!outPath || outPath.length <= 0) && vscode.workspace.workspaceFolders?.[0]) {
            outPath =vscode.workspace.workspaceFolders[0].uri.fsPath;
        }
        return this.generateTask({
            type: buildTaskType,
            program: docPath,
            outputRootPath: outPath,
            showDialog: true,
        }, isResolve);
    }

    private async generateTasks(): Promise<vscode.Task[]> {
        const tasks: vscode.Task[] = [];
        let task: vscode.Task | undefined = undefined;
        if (task = this.getActiveDocumentTask(false)) {
            tasks.push(task);
        }
        return tasks;
    }

    public generateTask(taskDef: BuildTaskDefinition, isResolve: boolean): vscode.Task | undefined {
        if (isResolve && !this.ensureTaskCondition()) {
            return undefined;
        }
        const studioPath = util.shared.runtimeStudioPath();
        const showDialog: boolean = taskDef.showDialog === undefined || taskDef.showDialog;
        const args: string[] = [
            '--mode', 'build',
            '--output-root', taskDef.outputRootPath,
            '--error-dialog', showDialog ? '1' : '0',
            '--success-dialog', showDialog ? '1' : '0',
            '--startup-script', taskDef.program,
            '--formatted-output', '1',
        ]
        .concat(util.shared.makeAdditionalIncludePathsArgs())
        .concat(util.shared.makeAdditionalDefineMacrosArgs());
        const task = new vscode.Task(
            taskDef,
            vscode.TaskScope.Workspace,
            buildTaskType,
            taskSourceName,
            new vscode.ShellExecution(
                studioPath,
                args.map((arg) => util.shared.shellQuoted(arg)),
                {cwd: path.dirname(taskDef.program)}
            ),
            util.problemMatcherStudio
        );
        task.group = vscode.TaskGroup.Build;
        return task;
    }

    private ensureTaskCondition(): boolean {
        return util.shared.ensureLambdaOrShowErrorMessage(
            () => {
                util.shared.ensureRuntimeRootPath();
                util.shared.ensureRuntimeStudioPath();
            }
        );
    }
}

export const buildTaskProvider = new BuildTaskProvider();

// エクスポートタスク
export const exportTaskType = 'nidonehsp-env.export';

export interface ExportTaskDefinition extends vscode.TaskDefinition {
    type: typeof exportTaskType;
    program: string;
    targetPlatform: 'auto' | 'native' | 'html';
    outputRootPath: string;
    showDialog: boolean;
}

export class ExportTaskProvider implements vscode.TaskProvider {
    public provideTasks(): Thenable<vscode.Task[]> | undefined {
        return this.generateTasks();
    }
  
    public resolveTask(task: vscode.Task): vscode.Task | undefined {
        const taskDef: ExportTaskDefinition = <any>task.definition;
        return this.generateTask(taskDef, true);
    }

    public getActiveDocumentTask(isResolve: boolean = false): vscode.Task | undefined {
        if (!vscode.window.activeTextEditor) {
            return undefined;
        }
        const docPath = vscode.window.activeTextEditor.document.uri.fsPath;
        let outPath = path.dirname(docPath);
        if ((!outPath || outPath.length <= 0) && vscode.workspace.workspaceFolders?.[0]) {
            outPath =vscode.workspace.workspaceFolders[0].uri.fsPath;
        }
        return this.generateTask({
            type: exportTaskType,
            program: docPath,
            targetPlatform: 'auto',
            outputRootPath: outPath,
            showDialog: true,
        }, isResolve);
    }

    private async generateTasks(): Promise<vscode.Task[]> {
        const tasks: vscode.Task[] = [];
        let task: vscode.Task | undefined = undefined;
        if (task = this.getActiveDocumentTask(false)) {
            tasks.push(task);
        }
        return tasks;
    }

    public generateTask(taskDef: ExportTaskDefinition, isResolve: boolean): vscode.Task | undefined {
        if (isResolve && !this.ensureTaskCondition()) {
            return undefined;
        }
        const studioPath = util.shared.runtimeStudioPath();
        const showDialog: boolean = taskDef.showDialog === undefined || taskDef.showDialog;
        const args: string[] = [
            '--mode', 'export',
            '--export-runtime-root', util.shared.runtimeRootPath(),
            '--output-root', taskDef.outputRootPath,
            '--error-dialog', showDialog ? '1' : '0',
            '--success-dialog', showDialog ? '1' : '0',
            '--startup-script', taskDef.program,
            '--export-platform', taskDef.targetPlatform === 'auto' ? 'html' : taskDef.targetPlatform,
            '--formatted-output', '1',
        ]
        .concat(util.shared.makeAdditionalIncludePathsArgs())
        .concat(util.shared.makeAdditionalDefineMacrosArgs());
        const task = new vscode.Task(
            taskDef,
            vscode.TaskScope.Workspace,
            exportTaskType,
            taskSourceName,
            new vscode.ShellExecution(
                studioPath,
                args.map((arg) => util.shared.shellQuoted(arg)),
                {cwd: path.dirname(taskDef.program)}
            ),
            util.problemMatcherStudio
        );
        task.group = vscode.TaskGroup.Build;
        return task;
    }

    private ensureTaskCondition(): boolean {
        return util.shared.ensureLambdaOrShowErrorMessage(
            () => {
                util.shared.ensureRuntimeRootPath();
                util.shared.ensureRuntimeStudioPath();
            }
        );
    }
}

export const exportTaskProvider = new ExportTaskProvider();


// プレビュータスク
export const previewTaskType = 'nidonehsp-env.preview';

export interface PreviewTaskDefinition extends vscode.TaskDefinition {
    type: typeof previewTaskType;
    program: string;
}

export class PreviewTaskProvider implements vscode.TaskProvider {
    public provideTasks(): Thenable<vscode.Task[]> | undefined {
        return this.generateTasks();
    }
  
    public resolveTask(task: vscode.Task): vscode.Task | undefined {
        const taskDef: PreviewTaskDefinition = <any>task.definition;
        return this.generateTask(taskDef, true);
    }

    public getActiveDocumentTask(isResolve: boolean = false): vscode.Task | undefined {
        if (!vscode.window.activeTextEditor) {
            return undefined;
        }
        return this.generateTask({type: previewTaskType, program: vscode.window.activeTextEditor.document.uri.fsPath}, isResolve);
    }

    private async generateTasks(): Promise<vscode.Task[]> {
        const tasks: vscode.Task[] = [];
        let task: vscode.Task | undefined = undefined;
        if (task = this.getActiveDocumentTask(false)) {
            tasks.push(task);
        }
        return tasks;
    }

    public generateTask(taskDef: PreviewTaskDefinition, isResolve: boolean): vscode.Task | undefined {
        if (isResolve && !this.ensureTaskCondition()) {
            return undefined;
        }
        const studioPath = util.shared.runtimeStudioPath();
        const args: string[] = [
            '--mode', 'preview',
            '--error-dialog', '1',
            '--success-dialog', '0',
            '--startup-script', taskDef.program,
        ]
        .concat(util.shared.makeAdditionalIncludePathsArgs())
        .concat(util.shared.makeAdditionalDefineMacrosArgs());
        const task = new vscode.Task(
            taskDef,
            vscode.TaskScope.Workspace,
            previewTaskType,
            taskSourceName,
            new vscode.ShellExecution(
                studioPath,
                args.map((arg) => util.shared.shellQuoted(arg)),
                {cwd: path.dirname(taskDef.program)}
            ),
            util.problemMatcherStudio
        );
        task.group = vscode.TaskGroup.Test;
        return task;
    }

    private ensureTaskCondition(): boolean {
        return util.shared.ensureLambdaOrShowErrorMessage(
            () => { util.shared.ensureRuntimeStudioPath(); }
        );
    }
}

export const previewTaskProvider = new PreviewTaskProvider();

// アクティブ関数
export function activateTaskExtension(context: vscode.ExtensionContext) {
    // タスクプロバイダーの登録
    context.subscriptions.push(
        vscode.tasks.registerTaskProvider(compileCheckTaskType, compileCheckTaskProvider)
    );
    context.subscriptions.push(
        vscode.tasks.registerTaskProvider(buildTaskType, buildTaskProvider)
    );
    context.subscriptions.push(
        vscode.tasks.registerTaskProvider(exportTaskType, exportTaskProvider)
    );
    context.subscriptions.push(
        vscode.tasks.registerTaskProvider(previewTaskType, previewTaskProvider)
    );
}
// vscode
import * as vscode from "vscode";

import * as path from "path";
import * as fs from "fs";

// plugin
import * as marked from "marked";
import * as sanitizeHtml from "sanitize-html";

// ローカル
import * as util from "./util";

export class HelpViewer {
  // member
  private vscontext: vscode.ExtensionContext;

  private helpViewPanel?: vscode.WebviewPanel = undefined;
  private helpViewDataSet: any = undefined;
  private helpViewDocIndex: any = undefined;
  private helpViewRefIndex: any = undefined;
  private helpViewRefRelationGroups: any = {};
  private helpViewRefHistoryPrev: string[] = [];
  private helpViewRefHistoryNext: string[] = [];
  private helpViewRefHistoryStaging?: string = undefined;

  private helpViewMarkedRenderer?: marked.Renderer;

  private readonly helpViewDescSanitizeHtmlOptions: sanitizeHtml.IOptions = {
    allowedAttributes: Object.assign(sanitizeHtml.defaults.allowedAttributes, {
      table: ["class", "style"],
    }),
  };
  private readonly helpViewCodeSanitizeHtmlOptions: sanitizeHtml.IOptions = {};

  // ctor
  public constructor(context: vscode.ExtensionContext) {
    this.vscontext = context;

    {
      const renderer = new marked.Renderer();
      renderer.table = (header: string, body: string) => {
        if (body) {
          body = "<tbody>" + body + "</tbody>";
        }

        return (
          '<table class="uk-table uk-table-divider table-xsmall n2-siderefdesc-table">\n' +
          "<thead>\n" +
          header +
          "</thead>\n" +
          body +
          "</table>\n"
        );
      };
      this.helpViewMarkedRenderer = renderer;
    }
  }

  // private method
  private helpViewPostMessage(message: string, data: any = null) {
    if (!this.helpViewPanel) {
      return false;
    }
    this.helpViewPanel.webview.postMessage({ command: message, data: data });
    return true;
  }

  private helpViewSubstituteMarkers(desc: string): string {
    return desc
      .replace(
        /\$doc\((.*?)\)/g,
        (_, docName) => {
          const doc = this.helpViewDocIndex && this.helpViewDocIndex[docName];
          return `<span n2trig="selectDoc" n2select="${docName}" style="margin: 0 5px;"><span n2trig="parent" uk-icon="icon: file-text; ratio: 1;"></span><a n2trig="parent">${doc ? doc.summary : docName}</a></span>`;
        }
      )
      .replace(
        /\$ref\((.*?)\)/g,
        '<span n2trig="selectRef" n2select="$1" style="margin: 0 5px;"><span n2trig="parent" uk-icon="icon: link; ratio: 1;"></span><a n2trig="parent">$1</a></span>'
      )
      ;
  }

  private helpViewMergeRawMdLines(lines: any): string{
    const descs: string[] = [];
    if (typeof(lines) === 'object') {
      for (var k in lines) {
        let val = lines[k];
        if (typeof(val) !== 'string') { continue; }

        //console.log(val);
        if (val.endsWith("$")) {
          val = val.replace(/\$$/, "");
        } else {
          val = val.concat("\\");
        }
        descs.push(val);
      }
    }
    return descs.join("\n").replace(/\\$/, "");
  }

  private helpViewCacheDocument(doc: any) {
    if (!doc || doc.cached) {
      return true;
    }

    const cached: any = {};
    try {
      let desc: string | undefined = undefined;
      if (doc.description !== undefined) {
        desc = this.helpViewMergeRawMdLines(doc.description);
      } else if (doc.file !== undefined) {
        desc = fs.readFileSync(path.join(this.vscontext.extensionPath, 'resources', doc.file as string)).toString();
      }
      desc = marked(desc as string, { renderer: this.helpViewMarkedRenderer });
      desc = sanitizeHtml(desc, this.helpViewDescSanitizeHtmlOptions);
      desc = this.helpViewSubstituteMarkers(desc);
      cached.description = desc;
    } catch (e) {
      //console.log(e);
      return false;
    }
    doc.cached = cached;
    return true;
  }

  private helpViewCacheReference(reference: any) {
    if (!reference || reference.cached) {
      return true;
    }

    const cached: any = {};
    try {
      let desc = this.helpViewMergeRawMdLines(reference.description);
      desc = marked(desc, { renderer: this.helpViewMarkedRenderer });
      desc = sanitizeHtml(desc, this.helpViewDescSanitizeHtmlOptions);
      desc = this.helpViewSubstituteMarkers(desc);
      cached.description = desc;

      const examples: any = [];
      for (var k in reference.example || []) {
        const v = reference.example[k];
        let ca = v["code"].join("\n");
        ca = sanitizeHtml(ca, this.helpViewCodeSanitizeHtmlOptions);
        ca = ca.replace(/\n/g, "<br />\n");
        examples.push({ summary: v["summary"], code: ca });
      }
      cached.examples = examples;
    } catch (e) {
      //console.log(e);
      return false;
    }
    reference.cached = cached;
    return true;
  }

  private helpViewSyncPreloadState() {
    this.helpViewPostMessage("preloadState", {
      state: this.helpViewRefIndex ? true : false,
    });
  }

  private helpViewSyncPrevNextButton() {
    this.helpViewPostMessage("prevState", {
      has: this.helpViewRefHistoryPrev.length > 0,
      label: this.helpViewRefHistoryPrev[
        this.helpViewRefHistoryPrev.length - 1
      ],
    });
    this.helpViewPostMessage("nextState", {
      has: this.helpViewRefHistoryNext.length > 0,
      label: this.helpViewRefHistoryNext[0],
    });
  }

  private helpViewSyncContentDocSafe(input: string) {
    const found = this.helpViewDocIndex && this.helpViewDocIndex[input];
    if (!found) {
      return false;
    }

    this.helpViewCacheDocument(found);

    this.helpViewPostMessage("documentDescription", {
      doc: found
    });
    return true;
  }

  private helpViewSyncSearchTarget(input: string) {
    this.helpViewPostMessage("searchTarget", { input: input });
  }

  private helpViewSyncSearchList(input: string) {
    if (!this.helpViewRefIndex) {
      return -1;
    }

    const linput = input.toLowerCase();
    let accepted = 0;
    let wordRefs: any = [];
    for (var k in this.helpViewRefIndex) {
      const wordRef = this.helpViewRefIndex[k];
      const ks = k as string;
      if (
        linput.length <= 0 ||
        ks.includes(linput) ||
        wordRef.summary.includes(linput)
      ) {
        wordRefs.push({ name: wordRef.name, summary: wordRef.summary });
        ++accepted;
      }
    }

    this.helpViewPostMessage("searchList", { wordRefs: wordRefs });
    return accepted;
  }

  private helpViewSyncContentRefSafe(input: string) {
    const linput = input.toLowerCase();

    const found = this.helpViewRefIndex && this.helpViewRefIndex[linput];
    if (!found) {
      return false;
    }

    this.helpViewCacheReference(found);
    const relatedWords: any = {};
    for (var rk in found.relationGroup || {}) {
      var rg = found.relationGroup[rk];
      for (var rc in this.helpViewRefRelationGroups[rg]) {
        if (typeof rc !== "string") {
          continue;
        }
        rc = rc.toLowerCase();
        if (rc === linput) {
          continue;
        }
        const rfound = this.helpViewRefIndex && this.helpViewRefIndex[rc];
        if (!rfound) {
          continue;
        }
        relatedWords[rc] = rfound;
      }
    }

    //console.log(JSON.stringify(relatedWords));
    this.helpViewPostMessage("referenceDescription", {
      wordRef: found,
      relatedWords: relatedWords,
    });
    return true;
  }

  private helpViewDoSearch(input: string, syncSearchTarget: boolean) {
    // ヒストリー処理
    this.helpViewRefHistoryPrev.push(input);
    this.helpViewRefHistoryNext = [];
    // リスト処理
    this.helpViewSyncSearchList(input);
    // 説明処理
    this.helpViewSyncContentRefSafe(input);
    // 検索ボックス
    if (syncSearchTarget) {
      this.helpViewSyncSearchTarget(input);
    }
    // 同期
    this.helpViewSyncPrevNextButton();
  }

  private helpViewReceiveMessage(message: string, data: any) {
    //console.log(`receiveMessage ${message}`);
    switch (message) {
      case "fullsync":
        this.helpViewSyncPreloadState();
        // パネル側が準備できていなかった時用
        if (this.helpViewRefHistoryStaging) {
          const input = this.helpViewRefHistoryStaging;
          // リスト処理
          this.helpViewSyncSearchList(input);
          // 説明処理
          this.helpViewSyncContentRefSafe(input);
          // 検索ボックス
          this.helpViewSyncSearchTarget(input);
        }
      // fallthrough
      case "sync":
        this.helpViewSyncPrevNextButton();
        break;
      case "selectDoc":
        {
          const select = data.select;
          if (typeof select === "string") {
            this.helpViewSyncContentDocSafe(select);
          }
        }
        break;
      case "selectRef":
        {
          const select = data.select;
          if (typeof select === "string") {
            this.helpViewSyncContentRefSafe(select);
          }
        }
        break;
      case "search":
        {
          const input = data.input;
          if (typeof input === "string") {
            this.helpViewDoSearch(input, false);
          }
        }
        break;
      case "searchClear":
        this.helpViewDoSearch("", true);
        break;
      case "copySample":
        {
          let wordName = data.wordName;
          let sampleKey = data.sampleKey;
          if (!wordName || typeof wordName !== "string" || !sampleKey) {
            return;
          }
          if (typeof sampleKey === "string") {
            sampleKey = parseInt(sampleKey);
          }
          if (typeof sampleKey !== "number") {
            return;
          }
          wordName = wordName.toLowerCase();
          const found = this.helpViewRefIndex && this.helpViewRefIndex[wordName];
          if (!found) {
            return false;
          }
          const sample = ((found.example || [])[sampleKey] || {}).code;
          if (!sample) {
            return;
          }
          const ca = sample.join("\n");
          vscode.env.clipboard.writeText(ca as string);
          //vscode.window.showInformationMessage(`Copied sample code for "${wordName}" to the clipboard`);
          vscode.window.setStatusBarMessage(
            util.shared.localeString('nidonehsp-env.helpview.statusbar.copied-samplecode-to-clipboard').replace(/\$\{wordName\}/g, wordName),
            10000
          ); // @todo duration must be customizable as parameter
        }
        break;
    }
  }

  private async helpViewDataInitialize(force: boolean = false) {
    if (!this.helpViewDataSet || force) {
      vscode.window.withProgress(
        {
          location: vscode.ProgressLocation.Notification,
          title: util.shared.localeString('nidonehsp-env.helpview.loading.title'),
          cancellable: true,
        },
        async (progress, token) => {
          // load file
          const dataPath: vscode.Uri = vscode.Uri.file(
            path.join(
              this.vscontext.extensionPath,
              "resources",
              "helpviewdata.json"
            )
          );
          let dataContent: string = "";
          let data: any = undefined;

          try {
            dataContent = await fs.promises.readFile(dataPath.fsPath, "utf8");
            const loaded = JSON.parse(dataContent);
            if (typeof loaded !== "object") {
              throw new Error("helpViewDataSet type mismatch");
            }
            data = loaded;
          } catch (error) {
            this.helpViewDataSet = undefined;
            vscode.window.showInformationMessage(
              `failed loading helpview data (${dataPath.fsPath})`
            );
          }

          if (!data) {
            return;
          }
          if (token.isCancellationRequested) {
            return;
          }

          // indexing
          let docIndexedData: any = {};
          let refIndexedData: any = {};
          const refRelationGroups: any = {};
          try {
            // documents
            for (var key in data["documents"]) {
              if (token.isCancellationRequested) {
                return;
              }
              const skey = key;
              if (typeof skey !== "string") {
                continue;
              }

              var value = data["documents"][key];
              value["name"] = key;
              value["cached"] = undefined;
              docIndexedData[skey] = value;
            }

            // references
            for (var key in data["references"]) {
              if (token.isCancellationRequested) {
                return;
              }
              let skey = key;
              if (typeof skey !== "string") {
                continue;
              }
              skey = skey.toLowerCase();

              var value = data["references"][key];
              value["name"] = key;
              value["cached"] = undefined;
              refIndexedData[skey] = value;

              for (var rk in value["relationGroup"] || {}) {
                var rg = value["relationGroup"][rk];
                if (typeof rg === "string") {
                  if (!refRelationGroups[rg]) {
                    refRelationGroups[rg] = {};
                  }
                  refRelationGroups[rg][skey] = (refRelationGroups[rg][skey] || 0) + 1;
                }
              }
            }
          } catch (e) {
            refIndexedData = undefined;
            vscode.window.showInformationMessage(
              util.shared.localeString('nidonehsp-env.helpview.information.failed-loading-helpview-data').replace(/\$\{fspath\}/g, dataPath.fsPath)
            );
          }
          if (!docIndexedData || !refIndexedData) {
            return;
          }

          // commit
          this.helpViewDataSet = data;
          this.helpViewDocIndex = docIndexedData;
          this.helpViewRefIndex = refIndexedData;
          this.helpViewRefRelationGroups = refRelationGroups;

          // load done
          this.helpViewReceiveMessage("fullsync", {});
        }
      );
    }
  }

  // public
  public async helpViewOpen(textEditor: vscode.TextEditor | undefined) {
    // (re)open webview
    if (this.helpViewPanel) {
      this.helpViewPanel.reveal(vscode.ViewColumn.Two);
    } else {
      // create panel itself
      const panel = vscode.window.createWebviewPanel(
        "nidonehsp-helpview",
        "HelpView",
        vscode.ViewColumn.Two,
        {
          enableScripts: true,
          // extension's installed directory is already added to the resourceRoot
        }
      );

      // determine local plug-in lib root
      const libraryPath = vscode.Uri.file(
        path.join(this.vscontext.extensionPath, "node_modules")
      );
      const libraryUri = panel.webview.asWebviewUri(libraryPath);

      // create panel conent
      this.helpViewPanel = panel;
      this.helpViewPanel.onDidDispose(
        () => {
          this.helpViewPanel = undefined;
        },
        undefined,
        this.vscontext.subscriptions
      );
      this.helpViewPanel.webview.onDidReceiveMessage(
        (message) => {
          this.helpViewReceiveMessage(message.command, message.data);
        },
        undefined,
        this.vscontext.subscriptions
      );

      // load html content
      const htmlPath: vscode.Uri = vscode.Uri.file(
        path.join(this.vscontext.extensionPath, "resources", "html", "helpview.html")
      );
      let panelContent = fs.readFileSync(htmlPath.fsPath, "utf8");
      panelContent = panelContent
      .replace(/\$\(WebviewCspSource\)/g, panel.webview.cspSource)
      .replace(/\$\(LibraryRoot\)/g, libraryUri.toString())
      ;
      panel.webview.html = panelContent;
    }
    // helpview data
    if (!this.helpViewDataSet) {
      await this.helpViewDataInitialize();
    }
    // selected word
    if (textEditor) {
      const wordRange = textEditor.document.getWordRangeAtPosition(
        textEditor.selection.active,
        /(#?)(\w)+(@\w*)?/g
      );
      if (wordRange) {
        const word = textEditor.document
          .getText(wordRange)
          .replace(/@(hsp)?$/i, "");
        this.helpViewRefHistoryStaging = word;
        if (this.helpViewPanel && this.helpViewRefIndex) {
          this.helpViewDoSearch(word, true);
        }
      }
    }
  }
}

export let helpViewer: HelpViewer | undefined = undefined;

// アクティブ関数
export function activateHelpViewExtension(context: vscode.ExtensionContext) {
  // インスタンス作って
  helpViewer = new HelpViewer(context);
}

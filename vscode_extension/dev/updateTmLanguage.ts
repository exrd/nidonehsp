
// resources/nidonehsp.tmLanguage.template.json から
// helpviewdata.jsonとかを統合して
// syntaxes/nidonehsp.tmLanguage.jsonを吐き出す

// あまり依存モジュールを増やしたくないので、テンプレートエンジンは使わない

import * as path from "path";
import * as fs from "fs";

function main() {
    console.log("Begin update tmLanguage.json");

    const rootDir = path.join(__dirname, "../");
    const templateJson = path.join(rootDir, "resources/nidonehsp.tmLanguage.template.json");
    const helpViewJson = path.join(rootDir, "resources/helpviewdata.json");
    const outputJson = path.join(rootDir, "syntaxes/nidonehsp.tmLanguage.json");
    console.log(`
        rootDir = ${rootDir}
        templateJson = ${templateJson}
        helpViewJson = ${helpViewJson}
        outputJson = ${outputJson}
    `);

    let tmLanguage = fs.readFileSync(templateJson).toString();
    const helpViewData = JSON.parse(fs.readFileSync(helpViewJson).toString());

    const builtinFunctions: string[] = [];
    const builtinConstants: string[] = [];
    const builtinVariables: string[] = [];

    for (var k in helpViewData.references) {
        var v = helpViewData.references[k];
        switch (v.type)
        {
        case 'function':
            builtinFunctions.push(k as string);
            break;
        case 'macro':
        case 'constant':
            builtinConstants.push(k as string);
            break;
        case 'systemVariable':
        case 'lexicalVariable':
            builtinVariables.push(k as string);
            break;
        default:
            break;
        }
    }

    tmLanguage = tmLanguage.replace(/\$\{builtinFunctions\}/g, builtinFunctions.join('|').replace(/\@/g, '\\\\\@'));
    tmLanguage = tmLanguage.replace(/\$\{builtinConstants\}/g, builtinConstants.join('|').replace(/\@/g, '\\\\\@'));
    tmLanguage = tmLanguage.replace(/\$\{builtinVariables\}/g, builtinVariables.join('|').replace(/\@/g, '\\\\\@'));

    fs.writeFileSync(outputJson, tmLanguage);

    console.log("End update tmLanguage.json");
}

main();



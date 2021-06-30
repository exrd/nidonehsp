
// ランタイム関連のリソースとか、
// ドキュメントファイルを親ディレクトリからコピーしてくる

import * as path from "path";
import * as fs from "fs";

// tslint:disable-next-line:no-var-requires
const mf = require("mirror-folder");

function main() {
    console.log("Begin update resources");

    const rootDir = path.join(__dirname, "../");
    const srcDir = path.join(rootDir, "../");
    console.log(`
        rootDir = ${rootDir}
        srcDir = ${srcDir}
    `);

    {
        console.log("  Updating documents...");
        var resSrc = path.join(srcDir, "doc");
        var resDst = path.join(rootDir, "resources/doc");
        var opts = {
            watch: false,
            ignore: null,
            keepExisting: false,
          };
        mf(resSrc, resDst, opts, function (err:any) {
            console.log(`directory mirror from(${resSrc}) to(${resDst}) : error(${err})`)
        });
    }

    console.log("End update resources");
}

main();



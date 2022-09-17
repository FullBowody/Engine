const process = require("process");
const fullbowody = require("./build/Release/fullbowody");

fullbowody.extensions_onExtensionUpdate(() => { console.log("extension update"); });
fullbowody.extensions_start();

setInterval(() => {
    console.log(fullbowody.extensions_getExtensions());
}, 500)

setTimeout(() => {
    fullbowody.extensions_stop();
}, 10000);

setTimeout(() => {
    console.log("<= End =>");
    process.exit();
}, 12000);
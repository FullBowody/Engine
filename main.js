const process = require("process");
const fullbowody = require("./build/Release/fullbowody");

console.log("Starting ...");
fullbowody.extensions_start();

fullbowody.extensions_onExtensionUpdate(() => {
    console.log("Extension updated :");
    console.log(fullbowody.extensions_getExtensions());
});

process.on("SIGINT", () => {
    console.log("Exiting...");
    fullbowody.extensions_stop();
    process.exit();
});
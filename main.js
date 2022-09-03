const fullbowody = require("./build/Release/fullbowody.node");

console.log("Available addon functions :")
Object.keys(fullbowody).forEach((key) => {
    console.log("  - "+key);
});

console.log("Calling addon function : [ping]");
console.log(">> "+fullbowody.ping());
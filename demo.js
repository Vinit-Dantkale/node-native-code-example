const findPrimeNative = require("./build/Release/mybinding")

let result

console.time("Native")
result = findPrimeNative(79)
console.timeEnd("Native")
console.log(result)

// util 是一个Node.js 核心模块，提供常用函数的集合，用于弥补核心 JavaScript 的功能 过于精简的不足

const util = require('util');


// util.callbackify
// util.callbackify(original) 将 async 异步函数（或者一个返回值为 Promise 的函数）转换成遵循异常优先的回调风格的函数

async function fn() {
    return 'Hello World';
}

let callbackFunction = util.callbackify(fn);

callbackFunction((err, result) => {
    if (err) {
        throw err;
    } else {
        console.log(result);
    }
});


// util.inherits
// util.inherits(constructor, superConstructor) 是一个实现对象间原型继承的函数
console.log('--------------------------');
function Base() {
    this.name = 'name';
    this.base = 1995;
    this.sayHello = function() {
        console.log('hello ' + this.name);
    }
}

Base.prototype.showName = function() {
    console.log(this.name);
}

function sub() {
    this.name = 'sub';
}

util.inherits(sub, Base);

let baseObj = new Base();
console.log(baseObj);
baseObj.showName();

let subObj = new sub();
console.log(subObj);
console.log(subObj.name);
subObj.showName();


// util.inspect
// util.inspect(object,[showHidden],[depth],[colors]) 是一个将任意对象转换 为字符串的方法，通常用于调试和错误输出。
// 它至少接受一个参数 object，即要转换的对象。showHidden 是一个可选参数，如果值为 true，将会输出更多隐藏信息。
console.log('--------------------------');
function Person() {
    this.name = 'par';
    this.toString = function() {
        return this.name;
    };
}
let obj = new Person();
console.log(util.inspect(obj));
console.log(util.inspect(obj, true));
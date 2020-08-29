// Path内置模块

let path = require('path');


let cache = {};

function testNormalize(key, value) {
    // 将传入的路径转换为标准路径，具体讲的话，除了解析路径中的.与..外，还能去掉多余的斜杠
    cache[path.normalize(key)] = value;
}

testNormalize('foo/bar', 1);
testNormalize('foo/baz//../bar', 2);
console.log(cache);


let pathJoin = "";

function testJoin(...args) {
    // 将传入的多个路径拼接为标准路径
    pathJoin = path.join(...args);

}

testJoin('foo/', 'baz/', '../bar');
console.log(pathJoin);


let pathExtname = "";

function testExtname(fileName) {
    // 得到文件后缀名
    pathExtname = path.extname(fileName);
}

testExtname('foo/bar.js');
console.log(pathExtname);

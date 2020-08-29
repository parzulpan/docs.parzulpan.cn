// Query String
const querystring = require('querystring');


// 这个模块用于实现URL参数字符串与对象的互相转换
let resultR = querystring.parse('foo=bar&baz=qux&baz=quux&corge');
console.log(resultR);

let resultRR = querystring.stringify({
    foo: 'bar',
    baz: [ 'qux', 'quux' ],
    corge: ''
})
console.log(resultRR);

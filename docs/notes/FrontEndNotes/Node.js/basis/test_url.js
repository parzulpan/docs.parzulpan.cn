// URL
let url = require('url')

// 处理HTTP请求时url模块使用率较高，该模块允许解析URL、生成URL以及拼接URL等
let resultP = url.parse('https://www.parzulpan.cn/');
console.log(resultP);

let resultF = url.format({
    protocol: 'https:',
    slashes: true,
    auth: null,
    host: 'www.baidu.com',
    port: null,
    hostname: 'www.baidu.com',
    hash: null,
    search: null,
    query: null,
    pathname: '/',
    path: '/',
    href: 'https://www.baidu.com/'
});
console.log(resultF);

let resultR = url.resolve('https;//www.parzulpan.cn', '/2020/04/04/resume/');
console.log(resultR)
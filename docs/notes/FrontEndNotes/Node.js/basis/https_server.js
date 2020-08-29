// HTTPS

let fs = require('fs');
let https = require('https');


// https模块与http模块极为类似，区别在于https模块需要额外处理SSL证书
// 在服务端模式下，创建一个HTTPS服务器
let options = {
    key: fs.readFileSync('../resources/ssl/default.key'),
    cert: fs.readFileSync('../resources/ssl/default.crt')
};
let server = https.createServer(options, function(request, response) {
    // ...
})


// 在客户端模式下
let optionsC = {
    hostname: 'www.baidu.com',
    port: 443,
    path: '/',
    method: 'GET'
};
let request = https.request(optionsC, function(response) {
    // ...
})
request.end();

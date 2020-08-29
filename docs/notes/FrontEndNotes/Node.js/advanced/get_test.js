// GET请求

let http = require('http');
let url = require('url');
let util = require('util');

http.createServer(function (request, response) {
    response.writeHead(200, {'Content-Type': 'text/plain'});
    // response.end(util.inspect(url.parse(request.url, true)));

    // 解析URL请求
    let params = url.parse(request.url, true).query;
    response.write(`网站名：${params.name}`);
    response.write('\n');
    response.write(`URL: ${params.url}`);
    response.end();

}).listen(8082);













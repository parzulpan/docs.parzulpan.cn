// Express
// 是一个简洁而灵活的 node.js Web应用框架, 提供了一系列强大特性帮助你创建各种Web应用和丰富的HTTP工具
// Express 框架核心特性
// 1. 可以设置中间件来响应 HTTP 请求
// 2. 定义了路由表用于执行不同的 HTTP 请求动作
// 3. 可以通过向模板传递参数来动态渲染 HTML 页面


const express = require('express');
const app = express();

app.get('/', function(request, response) {
    response.send('Hello World by express.');
})

let server = app.listen(2334, 'localhost', function() {
    let host = server.address().address;
    let port = server.address().port;

    console.log(`访问地址: http://${host}:${port}`);
});




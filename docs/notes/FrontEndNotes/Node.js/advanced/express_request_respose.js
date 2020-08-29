// 请求和响应
// Express应用使用回调函数的参数： request 和 response 对象来处理请求和响应的数据

// request 对象表示 HTTP 请求，包含了请求查询字符串，参数，内容，HTTP 头部等属性
// response 对象表示 HTTP 响应，即在接收到请求时向客户端发送的 HTTP 响应数据

// 在HTTP 请求的基本应用中，路由决定了由谁(指定脚本)去响应客户端请求
// 在HTTP请求中，可以通过路由提取出请求的URL以及GET/POST参数
const express = require('express');
let app = express();

// 主页输出 "Hello World"

// GET请求
app.get('/', function(req, res) {
    console.log('主页GET请求');
    // 传送HTTP响应
    res.send('Hello GET');
})

// POST请求
app.post('/', function(req, res) {
    console.log('主页POST请求');
    res.send('Hello POST');
})

// /del_user 页面响应
app.get('/del_user', function(req, res) {
    console.log('/del_user 响应DELETE请求');
    res.send('删除页面');
})

// /list_user 页面GET请求
app.get('/list_user', function (req, res) {
    console.log('/list_user 页面GET请求');
    res.send('用户列表页面');
})

// 对页面 abcd, abxcd, ab123cd, 等响应GET请求
app.get('/ab*cd', function (req, res) {
    console.log('/ab*cd GET请求');
    res.send('正则匹配');
})

let server = app.listen(2335, 'localhost', function() {
    let host = server.address().address;
    let port = server.address().port;
    console.log(`访问地址: http://${host}:${port}`);
});
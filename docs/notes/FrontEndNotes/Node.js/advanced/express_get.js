// GET 方法
const express = require('express');
let app = express();


// 在表单中通过 GET 方法提交两个参数，使用文件内的 process_get 路由器来处理输入
app.use('/resources', express.static('resources'));

app.get('/express_get.html', function(req, res) {
    res.send(__dirname + '/' + 'express_get.html');
})

app.get('/process_get', function(req, res) {
    // 输出JSON格式
    let response = {
        'first_name': req.query.first_name,
        'last_name': req.query.last_name
    };
    console.log(response);
    res.end(JSON.stringify(response));
})

let server = app.listen(2337, 'localhost', function() {
    let host = server.address().address;
    let port = server.address().port;
    console.log(`访问地址: http://${host}:${port}`);
})




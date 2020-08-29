// POST方法

const express = require('express');
const bodyParser = require('body-parser');
let app = express();


// 创建 application/x-www-form-urlencoded 编码解析
let urlEncodeParser = bodyParser.urlencoded({extended: false});

app.use('/resources', express.static('resources'));

app.get('/express_post.html', function(req, res) {
    res.sendFile(__dirname + '/' + 'express_post.html')
})

app.post('/process_post', urlEncodeParser, function(req, res) {
    // 输出JSON格式
    let response = {
        'first_name': req.body.first_name,
        'last_name': req.body.last_name
    };
    console.log(response);
    res.end(JSON.stringify(response));
})

let server = app.listen(2338, 'localhost', function() {
    let host = server.address().address;
    let port = server.address().port;
    console.log(`访问地址: http://${host}:${port}`);
})


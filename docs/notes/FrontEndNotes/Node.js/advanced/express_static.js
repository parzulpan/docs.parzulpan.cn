// 静态文件

// 内置的中间件 express.static 来设置静态文件如：图片， CSS, JavaScript 等

const express = require('express');
const app = express();

app.use('/resources', express.static('resources'));

app.get('/', function(req, res) {
    res.send('Hello World');
})

let server = app.listen(2336, 'localhost', function() {
    let host = server.address().address;
    let port = server.address().port;
    console.log(`访问地址: http://${host}:${port}`);
});
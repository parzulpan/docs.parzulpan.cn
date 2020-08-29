// Cookie管理
const express = require('express');
const cookieParser = require('cookie-parser');
const util = require('util');
const app = express();

app.use(cookieParser());

app.get('/', function(req, res) {
    console.log(`Cookies: ${util.inspect(req.cookies)}`);
})

console.log(`访问地址: http://localhost:2340`);
app.listen(2340, 'localhost');




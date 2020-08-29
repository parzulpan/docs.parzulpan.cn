// 文件上传
const express = require('express');
const app = express();
const fs = require('fs');
const bodyParser = require('body-parser');
const multi = require('multer');


// 创建一个用于上传文件的表单，使用POST方法
app.use('/resources', express.static('resources'));
app.use(bodyParser.urlencoded({extended: false}));
app.use(multi({dest:'/resources'}).array('image'));

app.get('/express_file_upload', function(req, res) {
    res.sendFile(__dirname + '/' + 'express_file_upload.html');
})

app.post('/file_upload', function(req, res) {
    // 上传的文件信息
    console.log(req.files[0]);

    let des_file = './resources/' + req.files[0].originalname;
    fs.readFile(req.files[0].path, function(err, data) {
        fs.writeFile(des_file, data, function(err) {
            if (err) {
                console.log(err);
            } else {
                response = {
                    message: 'File uploaded successfully',
                    filename: req.files[0].originalname
                };
            }
            console.log(response);
            res.end(JSON.stringify(response));
        });
    });
})

let server = app.listen(2339, 'localhost', function() {
    let host = server.address().address;
    let port = server.address().port;
    console.log(`访问地址: http://${host}:${port}`);
})
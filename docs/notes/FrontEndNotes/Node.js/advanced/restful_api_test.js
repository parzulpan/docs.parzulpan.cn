// RESTful API

// REST即表述性状态传递，它是一组架构约束条件和原则，满足这些约束条件和原则的应用程序或设计就是RESTful
// 注意：REST是设计风格而不是标准，它通常基于使用HTTP，URI，和XML以及HTML这些现有的广泛流行的协议和标准，它通常使用 JSON 数据格式

// REST 基本架构的四个方法
// 1. GET -- 用于获取数据
// 2. PUT -- 用于更新或添加数据
// 3. DELETE -- 用于删除数据
// 4. POST -- 用于添加数据

// 基于./resources/restful_users.json创建RESTful API
// 序号	URI	        HTTP方法	   发送内容	       结果
// 1	listUsers	GET	       空	           显示所有用户列表
// 2	addUser	    POST	   JSON字符串	   添加新用户
// 3	deleteUser	DELETE	   JSON字符串	   删除用户
// 4	:id	        GET	       空	           显示用户详细信息
const express = require('express');
const app = express();
const fs = require('fs');

// 显示所有用户列表
app.get('/listUsers', (req, res) => {
    fs.readFile('./resources/restful_users.json', 'utf8', (err, data) => {
        if(err) {
            console.log(`error: ${err}`);
        } else {
            console.log(`data: ${data}`);
            res.end(data);
        }
    });
})

// 添加新用户
let user = {
    "user4": {
        "name": "DDD",
        "password": "password4",
        "profession": "president",
        "id": 4
    }
};
app.get("/addUser", (req, res) => {
    fs.readFile('./resources/restful_users.json', 'utf8', (err, data) => {
        if(err) {
            console.log(`error: ${err}`);
        } else {
            data = JSON.parse(data);
            data["user4"] = user["user4"];
            console.log(`data: ${JSON.stringify(data)}`);
            res.end(JSON.stringify(data));
        }
    });
})

// 显示用户详细信息
app.get('/:id', (req, res) => {
    fs.readFile('./resources/restful_users.json', 'utf8', (err, data) => {
        if(err) {
            console.log(`error: ${err}`);
        } else {
            data = JSON.parse(data);
            let user = data["user" + req.params.id];
            console.log(`user: ${user}`);
            res.end(JSON.stringify(data));
        }
    });
})

// 删除用户
let id = 2;
app.get('deleteUser', (req, res) => {
    fs.readFile('./resources/restful_users.json', 'utf8', (err, data) => {
        if(err) {
            console.log(`error: ${err}`);
        } else {
            data = JSON.parse(data);
            delete data[`user${id}`];
            console.log(`user: ${data}`);
            res.end(JSON.stringify(data));
        }
    });
})


let server = app.listen(2341, 'localhost', function() {
    let host = server.address().address;
    let port = server.address().port;
    console.log(`访问地址: http://${host}:${port}`);
})



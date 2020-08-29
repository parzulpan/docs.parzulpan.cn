// MySQL操作
const mysql = require('mysql');


// 连接数据库
let connection = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password: '123456',
    database: 'nodejs_test'
});
connection.connect();
connection.query('SELECT 1 + 1 AS solution', function(err, results, fields) {
    if(err) {
        console.log(err);
        throw err;
    } else {
        console.log(`THe solution is ${results[0].solution}`);
    }
});
// connection.end();


// 数据库操作(CURD)
// 查询数据
// connection.connect();
let select_sql = 'select * from websites;';
connection.query(select_sql, (err, result) => {
    if (err) {
        console.log(`select error: ${err}`);
    }
    else {
        console.log("-------------select-------------");
        console.log(result);
        console.log("--------------------------------");
    }
});
// connection.end();

// 插入数据
let insert_sql = 'insert into websites(id, name, url, alexa, country) values(0, ?, ?, ?, ?);';
let insert_sql_value = ['baidu', 'https://www.baidu.com', '231', 'CN'];
connection.query(insert_sql, insert_sql_value, (err, result) => {
    if (err) {
        console.log(`insert error: ${err}`);
    } else {
        console.log("-------------insert-------------");
        console.log(result.insertId);
        console.log("--------------------------------");
    }
})

// 更新数据
let update_sql = 'update websites set name = ?, url = ? where id = ?;'
let update_sql_value = ['alibaba', 'https://www.alibaba.com', 6];
connection.query(update_sql, update_sql_value, (err, result) => {
    if (err) {
        console.log(`update error: ${err}`);
    } else {
        console.log("-------------update-------------");
        console.log(result.affectedRows);
        console.log("--------------------------------");
    }
})

// 删除数据
let delete_Sql = 'delete from websites where id = 6;';
connection.query(delete_Sql, (err, result) => {
    if (err) {
        console.log(`delete error: ${err}`);
    } else {
        console.log("-------------delete-------------");
        console.log(result.affectedRows);
        console.log("--------------------------------");
    }
})
connection.end();
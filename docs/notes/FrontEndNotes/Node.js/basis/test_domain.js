// 域
const http = require('http');
const domain = require('domain');


// Node.js提供了domain模块，可以简化异步代码的异常处理
// 简单的讲，一个域就是一个JS运行环境，如果一个异常没有被捕获，将作为一个全局异常被抛出，通过process对象提供了捕获全局异常的方法
process.on('uncaughtException', function(err) {
    console.log('Error: %s', err.message);
});
setTimeout(function() {
    fn();
});
// Error: fn is not defined


// 一个糟糕的代码
function async(request, callback) {
    // Do something.
    asyncA(request, function (err, data) {
        if (err) {
            callback(err);
        } else {
            // Do something
            asyncB(request, function (err, data) {
                if (err) {
                    callback(err);
                } else {
                    // Do something
                    asyncC(request, function (err, data) {
                        if (err) {
                            callback(err);
                        } else {
                            // Do something
                            callback(null, data);
                        }
                    });
                }
            });
        }
    });
}

http.createServer(function (request, response) {
    async(request, function (err, data) {
        if (err) {
            response.writeHead(500);
            response.end();
        } else {
            response.writeHead(200);
            response.end(data);
        }
    });
});

// 改进
// 在每处理一个请求时，使用domain模块创建一个子域（JS子运行环境）
// 在子域内运行的代码可以随意抛出异常，而这些异常可以通过子域对象的error事件统一捕获
function asyncY(request, callback) {
    // Do something.
    asyncA(request, function (data) {
        // Do something
        asyncB(request, function (data) {
            // Do something
            asyncC(request, function (data) {
                // Do something
                callback(data);
            });
        });
    });
}

http.createServer(function (request, response) {
    let d = domain.create();

    d.on('error', function () {
        response.writeHead(500);
        response.end();
    });

    d.run(function () {
        asyncY(request, function (data) {
            response.writeHead(200);
            response.end(data);
        });
    });
});

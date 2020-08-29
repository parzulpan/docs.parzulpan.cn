// v1.0.0

const fs = require('fs');
const path = require('path');
const http = require('http');



let MIME = {
    '.css': 'text/css',
    '.js': 'application/javascript'
};

function combineFiles(pathNames, callback) {
    console.log('开始合并文件...');
    let output = [];

    (function next(i, len) {
        if(i < len) {
            fs.readFile(pathNames[i], function(err, data) {
                if(err) {
                    callback(err);
                } else {
                    output.push(data);
                    next(i + 1, len);
                }
            });
        } else {
            callback(null, Buffer.concat(output));
        }
    })(0, pathNames.length);
}


function parsedURL(root, url) {
    console.log('开始解析URL...');
    let base, pathNames, parts;
    if(url.indexOf('??') === -1) {
        url = url.replace('/', '/??');
    }

    parts = url.split('??');
    base = parts[0];
    pathNames = parts[1].split(',').map(function(value) {
        return path.join(root, base, value);
    })


    return {
        mime: MIME[path.extname(pathNames[0])] || 'text/plain',
        pathNames: pathNames
    };
}


function main(argv) {
    console.log('开始读取配置并创建服务器...');
    let config = JSON.parse(fs.readFileSync(argv[0], 'utf-8'));
    let root = config.root || '.';
    let port = config.port || 80;

    http.createServer(function (request, response) {
        let urlInfo = parsedURL(root, request.url);

        combineFiles(urlInfo.pathNames, function (err, data) {
            if(err) {
                response.writeHead(404);
                response.end(err.message);
            } else {
                response.writeHead(200, {'Content-Type': urlInfo.mime});
                response.end(data);
            }
        });
    }).listen(port);
}

// main(process.argv.slice(2));
main(['./config.json'])

// 使用命令行参数传递JSON配置文件路径，入口函数负责读取并创建服务器
// 入口函数完整描述了程序的运行逻辑，其中解析URL和合并文件的具体实现封装在其他两个函数里
// 解析URL时先将普通URL转换为了文件合并URL，使得两种URL的处理方式可以一致
// 合并文件时使用异步API readFile 读取文件，避免服务器因等待磁盘IO而发生阻塞

// 遍历目录

let fs = require('fs');
let path = require('path');


// 同步遍历
function traverse(dir, callback) {
    fs.readdirSync(dir).forEach(function(file) {
        let pathname = path.join(dir, file);

        if(fs.statSync(pathname).isDirectory()) {
            traverse(pathname, callback);
        } else {
            callback(pathname);
        }
    });
}

traverse('../resources', function(pathname){
    console.log(pathname);
});


// 异步遍历
function traverseAsync(dir, callback, finish) {
    fs.readdir(dir, function(err, files) {
        (function next(i) {
            if(i < files.length) {
                let pathname = path.join(dir, files[i]);

                fs.stat(pathname, function(err, stats) {
                    if(stats.isDirectory()) {
                        traverseAsync(pathname, callback, function() {
                            next(i + 1);
                        });
                    } else {
                        callback(pathname, function() {
                            next(i + 1);
                        });
                    }
                });
            } else {
                finish && finish();
            }
        }(0));
    });
}

traverseAsync('../resources', function(pathname) {console.log(pathname);}, 0);
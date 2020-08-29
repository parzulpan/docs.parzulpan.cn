// 文件拷贝

let fs = require('fs');
let argv = require('argv');


// 小文件拷贝
function small_file_copy(src, dst) {
    // 使用fs.readFileSync从源路径读取文件内容，并使用fs.writeFileSync将文件内容写入目标路径
    fs.writeFileSync(dst, fs.readFileSync(src));
}


// 大文件拷贝
function large_file_copy(src, dst) {
    // 使用fs.createReadStream创建了一个源文件的只读数据流，并使用fs.createWriteStream创建了一个目标文件的只写数据流，
    // 并且用pipe方法把两个数据流连接了起来。连接起来后发生的事情，说得抽象点的话，水顺着水管从一个桶流到了另一个桶。
    fs.createReadStream(src).pipe(fs.createWriteStream(dst));
}



function main() {
    // small_file_copy(argv[0], argv[1]);
    small_file_copy('../resources/test_dst.txt', '../resources/test_dst_copy.txt');
}

// main(process.argv.slice(2));
main();





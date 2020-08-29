// 文本编码
// 在读取不同编码的文本文件时，需要将文件内容转换为JS使用的UTF8编码字符串后才能正常处理
let fs = require('fs');
let iconv = require('iconv-lite');



// BOM的移除
// BOM用于标记一个文本文件使用Unicode编码，其本身是一个Unicode字符（"\uFEFF"），位于文本文件头部
// 在不同的Unicode编码下，BOM字符对应的二进制字节如下：
//     Bytes      Encoding
// ----------------------------
//     FE FF       UTF16BE
//     FF FE       UTF16LE
//     EF BB BF    UTF8
// BOM字符虽然起到了标记文件编码的作用，其本身却不属于文件内容的一部分，但是使用NodeJS读取文本文件时，一般需要去掉BOM
function readText(pathname) {
    let bin = fs.readFileSync(pathname);

    if(bin[0] === 0xEF && bin[1] === 0xBB && bin[2] === 0xBF) {
        bin = bin.slice(3);
    }
    return bin.toString('utf-8');
}

console.log( readText('../resources/test_dst.txt') );


// GBK转UTF-8
// NodeJS支持在读取文本文件时，或者在Buffer转换为字符串时指定文本编码，但遗憾的是，GBK编码不在NodeJS自身支持范围内
// 借助iconv-lite这个三方包来转换编码
function readGBKText(pathname) {
    let bin = fs.readFileSync(pathname);

    return iconv.decode(bin, 'gbk');
}
console.log( readGBKText('../resources/test_dst.txt') );
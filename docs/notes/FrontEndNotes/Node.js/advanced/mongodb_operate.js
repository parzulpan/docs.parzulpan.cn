// MongoDB操作


// 创建数据库，并创建集合
// 需要创建一个 MongoClient 对象，然后配置好指定的 URL 和 端口号
// 如果数据库不存在，MongoDB 将创建数据库并建立连接
const MongoClient = require('mongodb').MongoClient;
let url = 'mongodb://localhost:27017/nodejs_test';

MongoClient.connect(url, {useUnifiedTopology: true}, (err, db) => {
    if (err) {
        console.log(`connect error: ${err}`);
        throw err;
    } else {
        console.log('nodejs_test数据库已创建！');
        console.log('建立连接成功！')

        let nodejs_test = db.db('nodejs_test');
        nodejs_test.createCollection('site', (err, result) => {
            if (err) {
                console.log(`create collection error: ${err}`);
                throw err;
            } else {
                console.log('创建集合成功！')
                // db.close().then(r => console.log(r));
            }
        });


        // 数据库操作(CRUD)
        // 插入数据
        // 连接数据库 nodejs_test 的 site 表，并插入一条数据条数据，使用 insertOne()
        let insertOneObj = {name: 'test', url: 'www.test.cn'};
        // nodejs_test.collection('site').insertOne(insertOneObj, (err, result) => {
        //     if (err) {
        //         console.log(`insertOne error: ${err}`);
        //         throw err;
        //     } else {
        //         console.log('文档插入成功!');
        //         console.log(`内容: ${result}`)
        //     }
        // });
        nodejs_test.collection('site').insertOne(insertOneObj).then((value => console.log('单个文档插入成功！' + '\n' + value)));
        // 插入多条数据
        let insertManyObj = [
            {name: 'parzulpan', url: 'www.parzulpan.cn'},
            {name: 'baidu', url: 'www.baidu.com'}
        ];
        nodejs_test.collection('site').insertMany(insertManyObj).then((value => console.log('多个文档插入成功！' + '\n' + value.name)));


        // 查询数据
        // 使用 find() 来查找数据, find() 可以返回匹配条件的所有数据。 如果未指定条件，find() 返回集合中的所有数据
        // nodejs_test.collection('site').find({}).toArray((err, result) => {
        //         if (err) {
        //             console.log(`find error: ${err}`);
        //             throw err;
        //         } else {
        //             console.log('查询数据成功!');
        //             console.log(`内容: ${result[0].name}`)
        //         }
        // });
        nodejs_test.collection('site').find().toArray().then((result => console.log(result)));


        // 更新数据
        let updateOneObj = {name: 'test'};
        let updateOneObjValue = {$set: {'url': 'www.test4.com'}};
        nodejs_test.collection('site').updateOne(updateOneObj, updateOneObjValue).then((value) => {console.log('单个文档更新成功 ' + value.result.nModified)});
        nodejs_test.collection('site').updateMany(updateOneObj, updateOneObjValue).then((value) => {console.log('多个文档更新成功 ' + value.result.nModified)});


        // 删除数据
        let deleteOneObj = {name: 'test'};
        nodejs_test.collection('site').deleteOne(deleteOneObj).then((value) =>{console.log('单个文档删除成功 ' + value.result.n);})
        nodejs_test.collection('site').deleteMany(deleteOneObj).then((value) =>{console.log('多个文档删除成功 ' + value.result.n);})


        // 排序
        // 使用 sort() 方法，该方法接受一个参数，规定是升序(1)还是降序(-1)
        // 按name字段升序
        let sortObj = {name: 1};
        nodejs_test.collection('site').find().sort(sortObj).toArray().then((result) => {console.log(result);});


        // 查询分页
        // 设置指定的返回条数可以使用 limit() 方法，该方法只接受一个参数，指定了返回的条数
        nodejs_test.collection('site').find().limit(2).toArray().then((result) => {console.log(result);});
        // 要指定跳过的条数，可以使用 skip() 方法
        nodejs_test.collection('site').find().skip(2).limit(2).toArray().then((result) => {console.log(result);});


        // 连接操作
        // mongoDB 不是一个关系型数据库，但可以使用 $lookup 来实现左连接
        // 集合1：orders
        // [
        //     { _id: 1, product_id: 154, status: 1 }
        // ]
        // 集合2：products
        // [
        //   { _id: 154, name: '笔记本电脑' },
        //   { _id: 155, name: '耳机' },
        //   { _id: 156, name: '台式电脑' }
        // ]
        // nodejs_test.collection('orders').aggregate([
        //     { $lookup:
        //             {
        //                 from: 'products',   // 右集合
        //                 localField: 'product_id',   // 左集合join字段
        //                 foreignField: '_id',    // 右集合join字段
        //                 as: 'orderDetails', // 新生成字段(类型array)
        //             }
        //     }
        // ]).toArray().then((result) => {console.log(JSON.stringify(result));})

        // 删除集合
        // 使用 drop() 方法来删除集合
        nodejs_test.collection('site').drop().then((result) => {console.log(result); db.close(true);});


    }
});






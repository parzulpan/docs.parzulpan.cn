//


const server = require('./router_server');
const router = require('./router_router');


server.start(router.route);

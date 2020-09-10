#include <cstdio>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>


// 初始化一个 IPv4 TCP 套接字
int make_socket(uint16_t port) {
    int sock;
    struct sockaddr_in name;

    // 创建字节流类型的 IPv4 socket
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        exit (EXIT_FAILURE);
    }

    // 绑定到 port 和 ip
    name.sin_family = AF_INET;
    name.sin_port = htons(port);    // 指定端口
    name.sin_addr.s_addr = htonl(INADDR_ANY);   // 通配地址

    // 把 IPv4 地址转换成通用地址格式，同时传递长度
    if (bind(sock, (struct sockaddr *) &name, sizeof(name) < 0)) {
        perror("bind");
        exit (EXIT_FAILURE);
    }

    return sock;
}
#include "net.h"

int main() {

    /* 建立套接字 */
    int sockfd = Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    // printf("CC:%d\n",sockfd);

    /* 建立tcp连接 */
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(TCP_SERVER_ADDRESS);
    server_addr.sin_port = htons(TCP_SERVER_PORT);

    Connect(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));

    /* 发送数据 */
    // char *msg = "hello";
    char msg[TCP_BUF_LENGTH];
    while(scanf("%s", msg)!=EOF){
    
    // printf("Send message: %s[%zu bytes]\n", msg, strlen(msg));
    Send(sockfd, msg, strlen(msg), 0);

    char buf[TCP_BUF_LENGTH];
    size_t pkt_len = Recv(sockfd, buf, TCP_BUF_LENGTH, 0);
    buf[pkt_len]='\0';
    printf("%s\n", buf);

    }
    /* 关闭套接字 */
    close(sockfd);

    return 0;
}

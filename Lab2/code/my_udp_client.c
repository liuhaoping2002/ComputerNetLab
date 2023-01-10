#include "net.h"

int main() {

    /* 建立套接字 */
    for(int i=1;i<=10;i++){
    int sockfd = Socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    /* 发送数据 */
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(UDP_SERVER_ADDRESS);
    server_addr.sin_port = htons(UDP_SERVER_PORT);

    char *msg = "hello";
    printf("Send message: %s[%zu bytes]\n", msg, strlen(msg));
    Connect(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
    // Send(sockfd, msg, strlen(msg), 0);
    Sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

    /* 关闭套接字 */
    close(sockfd);
    }
    return 0;
}

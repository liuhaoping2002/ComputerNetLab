#include "net.h"

int main() {

    /* 建立服务端套接字 */
    int server_sockfd = Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    // printf("AA:%d\n",server_sockfd);

    int enable = 1;
    Setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

    /* 绑定端口 */
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(TCP_SERVER_ADDRESS);
    server_addr.sin_port = htons(TCP_SERVER_PORT);

    Bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));

    /* 监听端口 */
    Listen(server_sockfd, CONNECTION_NUMBER);

    /* 建立tcp连接 */
    struct sockaddr_in client_addr;
    unsigned int client_addr_len = sizeof(struct sockaddr_in);
    int client_sockfd = Accept(server_sockfd, (struct sockaddr *)&client_addr, &client_addr_len);
    // printf("SC:%d",client_sockfd);
    printf("Accept client %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    /* 接收数据 */
    char buf[TCP_BUF_LENGTH],msg[TCP_BUF_LENGTH];
    pid_t pid = fork();
    while(1){
        if(pid == 0){
            size_t pkt_len = Recv(client_sockfd, buf, TCP_BUF_LENGTH, 0);
            if (pkt_len > 0) {
            buf[pkt_len] = '\0';
            printf("%s\n", buf);
            // printf("Message received: %s[%zu bytes]\n", buf, pkt_len);
        
            } 
            else {
                printf("Connection closed\n");
                break;
            }
        }
        else{
            scanf("%s", msg);
            // printf("Send message: %s[%zu bytes]\n", msg, strlen(msg));
            Send(client_sockfd, msg, strlen(msg), 0);
        }
    }
    // Send(client_sockfd, buf, strlen(buf), 0);

    /* 关闭套接字 */
    close(client_sockfd);
    close(server_sockfd);

    return 0;
}

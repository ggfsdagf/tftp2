#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 6969 

int main() {
    int server_socket;
    struct sockaddr_in server_addr;

    // 1단계: UDP 소켓 생성 (리눅스 표준)
    server_socket = socket(PF_INET, SOCK_DGRAM, 0);
    if (server_socket < 0) {
        perror("소켓 생성 실패");
        return -1;
    }

    // 2단계: 서버 주소 구조체 설정
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    // 3단계: 포트 바인딩
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("바인딩 실패");
        close(server_socket);
        return -1;
    }

    printf("리눅스 TFTP 서버가 포트 %d에서 대기 중입니다...\n", PORT);

    // 소켓 닫기
    close(server_socket);
    return 0;
}
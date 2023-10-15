
#include <stdio.h>
#include <WinSock2.h>
#define SERVER "127.0.0.1"
#define PORT 8888
#pragma comment(lib,"ws2_32.lib")
int main()
{
	WSADATA w;
	if (WSAStartup(MAKEWORD(2, 3), &w))
	{
		printf("初始化socket错误：");
		return -1;
	}
	
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		printf("创建socket错误.");
		return -1;
	}
	
	struct sockaddr_in addr_in= { AF_INET};
	int rc = bind(sock, (const struct sockaddr*)&addr_in, sizeof(addr_in));
	if (rc)
	{
		printf("绑定失败.");
		return -1;
	}
	addr_in.sin_port = htons(PORT);
	addr_in.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	rc = connect(sock, (const struct sockaddr*)&addr_in, sizeof(addr_in));
	if (rc)
	{
		printf("连接失败.");
		return -1;
	}
	while(1){
		char s[64]={0};
        scanf("%s",s);
        printf("send msg %s to server\n",s);
		send(sock, s, strlen(s), 0);
	}
	return 0;
}
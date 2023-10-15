#include <graphics.h>
#include <stdio.h>
#include <WinSock2.h>
#include <string.h>
#define COL 3
#define RAW 3
#define WIDTH 60
#define SERVER "127.0.0.1"
#define PORT 8888
#pragma comment(lib,"ws2_32.lib")
void setMsg(int x, int y);
static SOCKET sock;

int connect_server()
{
	WSADATA w;
	if (WSAStartup(MAKEWORD(2, 3), &w))
	{
		printf("初始化socket错误：");
		return -1;
	}
	
	sock = socket(AF_INET, SOCK_STREAM, 0);
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
}

void draw_circle(int x, int y)
{
	int raw, col;
	col = x/WIDTH;
	raw = y/WIDTH;
	ege_fillellipse((col*WIDTH), (raw*WIDTH), WIDTH,WIDTH);
	printf("POS:%d,%d\n",col,raw);
	setMsg(col,raw);
}

void setMsg(int x, int y)
{
	char buf[1024]={0};
	sprintf(buf,"{\"client\":\"tim\",\"pos\":\"%d,%d\"}",x,y);
	if(sock > 0)
		send(sock,buf,strlen(buf),0);
}

void handle_msg()
{
	char buffer[1024]={0};
	int x,y;
	if(sock<=0){
		return;
	}
	recv(sock, buffer, sizeof(buffer), 0);
	if(strncmp(buffer,"win",3)== 0){
		xyprintf(0,0,"你赢了！");
	}
	else if(strncmp(buffer,"lose",4)== 0){
		xyprintf(0,0,"你输了.");
	}
	else if(sscanf(buffer,"%d,%d",&x,&y)==2){
			ege_fillellipse((x*WIDTH), (y*WIDTH), WIDTH,WIDTH);
	}
}

int main()
{
	int width = RAW*WIDTH;
	int height = COL*WIDTH;
#ifdef MANUAL_MODE
		initgraph(width, height,INIT_RENDERMANUAL);
#else
		initgraph(width, height);
#endif
	color_t color;
	setbkcolor(WHITE);
	color_t darkColor  = EGEARGB(0xF0, 134, 34, 34);
	color_t lightColor = EGEARGB(0xF0, 216, 216, 216);
	mouse_msg msg;
	//color_t lightColor =WHITE;
	ege_enable_aa(true);
	int i;
	for(i = 0; i < RAW; i++) {
		for(int j = 0;j <= COL; j++){
			color = darkColor;
			if((i+j)%2){
				color = lightColor;
			}
			setfillcolor(color);
			ege_fillrect(i*WIDTH,j*WIDTH,(i+1)*WIDTH,(j+1)*WIDTH,NULL);
		}	
		
	}
	connect_server();
	while(!keystate(key_enter)){
		msg = getmouse();
		int x,y;
		if( msg.is_down()){
			mousepos(&x, &y);
			setfillcolor(BLACK);
			draw_circle(x,y);
		}
		//handle_msg();
#ifdef MANUAL
		delay_fps(60);
#endif
	}
	getch();
	return 0;
}


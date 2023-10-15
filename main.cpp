//#define SHOW_CONSOLE
#include <graphics.h>					//包含EGE的头文件
#include <stdint.h>
#include <stdio.h>
#include "my_win.h"
#define BGCOLOR(_r,_g,_b) EGERGB((_r),(_g),(_b))
typedef struct MYRGB{
	uint8_t r_color = 0;
	uint8_t g_color = 0;
	uint8_t b_color = 0;
}my_rgb;

my_rgb rgb_color{0,0,0};
void set_color_up(uint8_t index)
{
	if(rgb_color.r_color <= (0xff-index)){
		rgb_color.r_color+=index;
		return;
	}
	if(rgb_color.g_color <= (0xff-index)){
		rgb_color.g_color+=index;
		return;
	}
	if(rgb_color.b_color  <= (0xff-index)){
		rgb_color.b_color+=index;
		return;
	}
}
void set_color_down(uint8_t index)
{
	if(rgb_color.b_color >= index){
		rgb_color.b_color-=index;
		return;
	}
	if(rgb_color.g_color >= index){
		rgb_color.g_color-=index;
		return;
	}
	if(rgb_color.r_color >= index){
		rgb_color.r_color-=index;
		return;
	}
}
int key_handler(int key_status)
{
	if(key_status == key_up){
		set_color_up(1);
	}
	else if(key_status == key_down){
		set_color_down(1);
	}
	else if(key_status == key_right) {
		set_color_up(10);
	}
	else if(key_status == key_left) {
		set_color_down(10);
	}
	return 0;
}


int main()
{
	char buf1[32];
	char buf2[32];
	char buf3[32];
	key_msg msg;
	//setinitmode(0, 100, 100);
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	setcaption("RGB背景调节");
	setbkcolor(BLACK);
	msg = getkey();
	while(!keystate(key_enter)) {

		setbkcolor(BGCOLOR(rgb_color.r_color, rgb_color.g_color,rgb_color.b_color));

		sprintf(buf1,"r:%d",rgb_color.r_color);
		sprintf(buf2,"g:%d",rgb_color.g_color);
		sprintf(buf3,"b:%d",rgb_color.b_color);
		outtextxy(CONVERT_X_POS(0), CONVERT_Y_POS(0),buf1);
		outtextxy(CONVERT_X_POS(0), CONVERT_Y_POS(18),buf2);
		outtextxy(CONVERT_X_POS(0), CONVERT_Y_POS(36),buf3);
		
		if(kbmsg())
		{
			msg = getkey();
			if(msg.msg== key_msg_up)
				key_handler(msg.key);
		}
	}
	closegraph();
	return 0;
}

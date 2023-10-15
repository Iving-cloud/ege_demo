//直线绘制
#include <graphics.h>
#include <stdio.h>
#include <string.h>
#include "my_win.h"
typedef struct line_pos_s{
	int x;
	int y;
}line_pos_t;
line_pos_t line_pos[2];


int main()
{
	memset(line_pos,0,sizeof(line_pos));
	line_pos_t *p=line_pos;
	initgraph(WINDOW_WIDTH,WINDOW_HEIGHT);
	setbkcolor(WHITE);
	mouse_msg msg;
	setcolor(BLACK);
	ege_enable_aa(true);
	while(KEY_END){
		//while (mousemsg())
		{
			msg = getmouse();
			if( msg.is_down()){
				mousepos(&p->x, &p->y);
				if(p == &line_pos[1]){
					ege_line(line_pos[0].x,line_pos[0].y,line_pos[1].x,line_pos[1].y);
					memset(line_pos,0,sizeof(line_pos));
					p = &line_pos[0];
					continue;
				}
				p++;
			}
			
		}

	}
	getch();
	return 0;
}

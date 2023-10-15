#include <graphics.h>
#include <math.h>
#include <stdio.h>
void drawGrid(int width, int height, int totalRow, int totalCol);
void positionOffset(int key, int* xOffset, int* yOffset);
bool PositionIsValid(int totalRow, int totalCol, int row, int col);
void drawCircle(float x, float y, float radius);
bool keyIsPressed[256] = { false };
int main()
{	
	const int winWidth = 600;
	const int COL_NUM = 7, ROW_NUM = COL_NUM;
	initgraph(winWidth, winWidth, INIT_RENDERMANUAL);
	ege_enable_aa(true);
	setbkcolor(EGERGB(0xFF, 0xFF, 0xFF));
	setfont(20, 0, "SimSun");
	settextjustify(RIGHT_TEXT, TOP_TEXT);
	setbkmode(TRANSPARENT);
	int curRow = ROW_NUM / 2, curCol = COL_NUM / 2;
	for (; is_run(); delay_fps(60)) 
	{
		while (kbmsg()) 
		{
			key_msg msg = getkey();
			if (msg.msg == key_msg_down) {// 按键按下
				if (!keyIsPressed[msg.key]) {//按键按下时处理
					int colOffset = 0, rowOffset = 0;
					positionOffset(msg.key, &colOffset, &rowOffset);
					int rowNext = curRow + rowOffset, colNext = curCol + colOffset;// 位置有效则移动至下一个位置
					if (PositionIsValid(ROW_NUM, COL_NUM, rowNext, colNext)) {
						curRow = rowNext;
						curCol = colNext;
					}//按键按下，记录按键已变为按下状态
						keyIsPressed[msg.key] = true;
				} 
				else if (msg.msg == key_msg_up) {// 按键抬起，记录按键已变为松开状态
					keyIsPressed[msg.key] = false;
				}
			}
			cleardevice();
			drawGrid(winWidth, winWidth, ROW_NUM, COL_NUM);
			float radius = (float)winWidth / (2.0f * COL_NUM);
			float x = winWidth * ((float)curCol / COL_NUM) + radius;
			float y = winWidth * ((float)curRow / ROW_NUM) + radius;
			drawCircle(x, y, radius);
			setcolor(BLACK);
			xyprintf(winWidth, 0, "当前位置：(%d, %d)", curRow, curCol);
		}
    }
	return 0;
}

// 绘制网格

void drawGrid(int width, int height, int totalRow, int totalCol)
{
	setlinestyle(DASHED_LINE, 0, 1);
	setcolor(EGERGB(0xC0, 0xC0, 0xC0));
	for (int i = 1; i < totalCol; i++) {
		int x = (int)roundf((float)width * i / totalCol);
		line(x, 0, x, height);
	}
	for (int i = 1; i < totalRow; i++) {
		int y = (int)roundf((float)height * i / totalRow);
		line(0, y, width, y);
	}
}

//绘制圆
void drawCircle(float x, float y, float radius)
{
	setfillcolor(EGEACOLOR(0xFF, 0xA0D8EF));
	ege_fillellipse(x - radius, y - radius, 2 * radius, 2 * radius);
	setlinestyle(SOLID_LINE, 0, 2);
	setcolor(BLACK);
	ege_ellipse(x - radius, y - radius, 2 * radius, 2 * radius);
}

void positionOffset(int key, int* xOffset, int* yOffset)
{
	int dx = 0, dy = 0;
	switch (key) {
		case 'A': 
		case key_left:	
			dx = -1;	
			break;	//左移
            printf("左移");
			case 'W': 
			case key_up:		
				dy = -1;	
				break;	//上移
			case 'D': 
			case key_right:	
				dx =  1;	
				break;	//右移
			case 'S': 
			case key_down:	
				dy =  1;	
				break;	//下移
			default:  break;	//其他键不移动
	}
	*xOffset = dx;
	*yOffset = dy;
}

bool PositionIsValid(int totalRow, int totalCol, int row, int col)
{
	return (0 <= row) && (row < totalRow) && (0 <= col) && (col < totalCol);
}
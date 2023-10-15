#include <graphics.h>

int main()
{
	int gridWidth = 64, gridNum = 10;
	int width = gridWidth * gridNum;
	int height = 240;
	
	initgraph(width, height, INIT_RENDERMANUAL);	//初始化窗口
	
	setbkcolor(WHITE);						//设置窗口背景色为白色
	
	//这些是直接复制过来RGB颜色值
	color_t rgbColors[10] = {
		0x7400b8, 0x6930c3, 0x5e60ce, 0x5390d9, 0x4ea8de,
		0x48bfe3, 0x56cfe1, 0x64dfdf, 0x72efdd, 0x80ffdb,
	};
	
	//画10个填充矩形，每个填充矩形的颜色定义在RgbColors数组中
	for (int i = 0; i < gridNum; i++)
	{
		//设置对应的填充颜色
		setfillcolor(rgbColors[i]);
		
		//画个填充矩形
		bar(i * gridWidth, 0, (i + 1) * gridWidth, height);
	}
	
	getch();
	
	closegraph();
	
	return 0;
}


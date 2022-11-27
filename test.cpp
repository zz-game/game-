#include <graphics.h>

int main(void)
{
	initgraph(640, 480, INIT_RENDERMANUAL);
	setbkcolor(EGERGB(0xFF, 0xFF, 0xFF));
	setcolor(BLACK);
	setbkmode(TRANSPARENT);
	setfont(16, 0, "黑体");

	//开启抗锯齿
	ege_enable_aa(true);

	const int speed = 2;			//速度常量
	int r = 80;						//半径
	int cx = r, cy = r;				//圆心
	int dx = speed, dy = speed;		//x, y方向上分速度
	int alpha = 0, da = 1;			//alpha为当前alpha值，da为alpha变化增量
	int colH = 0;					//HSV颜色中的H值（色调）

	for (; is_run(); delay_fps(60))
	{
		//位置更新
		cx += dx;
		cy += dy;

		//碰撞检测
		if (cx - r <= 0) dx = speed;				//碰左
		if (cy - r <= 0) dy = speed;				//碰上
		if (cx + r >= getwidth() - 1) dx = -speed;	//碰右
		if (cy + r >= getheight() - 1) dy = -speed; //碰下

		// 改变alpha值，参数范围为 0 ~ 0xFF(255)
		alpha += da;
		if (alpha <= 0) da = 1;
		if (alpha >= 0xFF) da = -1;

		if (++colH > 360)
			colH = 0;

		color_t color = HSVtoRGB(colH, 1, 1);

		cleardevice();
	
		setfillcolor(EGEACOLOR(alpha, color));			//设置颜色
		ege_fillellipse(cx - r, cy - r, 2 * r, 2 * r);	//绘制小球 
		xyprintf(0, 0, "FPS:%.3f", getfps());			//显示帧率
	}
	
	closegraph();

	return 0;
}
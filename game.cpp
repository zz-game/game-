#include<bits/stdc++.h>
#include<graphics.h>
#include"object.h"
#include"draw.h"
/*************************************************
初始化部分
**************************************************/
void init()
{
    initgraph(1000,1000,INIT_RENDERMANUAL);
	setbkcolor(EGERGB(0xFF, 0xFF, 0xFF));
	setcolor(BLACK);
	setbkmode(TRANSPARENT);
	setfont(16, 0, "黑体");
    Player.init();
    objlist.push_back(&Player);
    //先这样看看
    object *ground1=new object(-505,0,1,1010,44,"image/ground.png");
    objlist.push_back(ground1);
}

/*************************************************
主函数部分
**************************************************/
long long getCurrentTime()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
int main()
{
    init();
    long long timelast,timenow=getCurrentTime(),timegap;
    for(;is_run();delay_fps(300))
    {
        timelast=timenow;
        timenow=getCurrentTime();
        timegap=timenow-timelast;
        int listsize=objlist.size();
        for(int i=0;i<listsize;i++)
        {
            (*objlist[i]).fall(timegap);
            (*objlist[i]).move(timegap);
        }
        keymovement();
        draw();
        xyprintf(0,0,"timegap:%.3lld velx:%lf vely:%lf on:%d",timegap,Player.velx,Player.vely,Player.ongroud());
        xyprintf(0,20,"touch:%d",Player.touch(*objlist[1]));
    }
    closegraph();
    return 0;
}
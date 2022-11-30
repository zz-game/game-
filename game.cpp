#include<bits/stdc++.h>
#include<graphics.h>
#include"object.h"
#include"player.h"
#include"keymovement.h"
#include"draw.h"
#include"init.h"
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
    for(;gameruning;delay_fps(180))
    {
        timelast=timenow;
        timenow=getCurrentTime();
        timegap=timenow-timelast;
        keymovement();
        int listsize=objlist.size();
        for(int i=0;i<listsize;i++)
        {
            (*objlist[i]).fall(timegap);
            (*objlist[i]).move(timegap);
        }
//      draw();
        draw(-600,-600,1200,1200);
        xyprintf(0,0,"timegap:%.3lld velx:%lf vely:%lf on:%d",timegap,Player.velx,Player.vely,Player.ongroud());
        xyprintf(0,20,"touch:%d posx:%d posy:%d keyl:%d keyr:%d",Player.touch(*objlist[1]),Player.posx,Player.posy,Player.keyl,Player.keyr);
    }
    closegraph();
    return 0;
}
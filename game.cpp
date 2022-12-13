#include<bits/stdc++.h>
#include<graphics.h>
#include"gameover.h"
#include"time.h"
#include"object.h"
#include"player.h"
#include"enemy.h"
#include"sword.h"
#include"keymovement.h"
#include"draw.h"
#include"getmap.h"
#include"init.h"
/*************************************************
主函数部分
**************************************************/
int main()
{
    init();
    for(;gameruning;delay_fps(180))
    {
        timelast=timenow;
        timenow=getCurrentTime();
        timegap=timenow-timelast;
        keymovement();
        Player.doublejumpck();
        Sword.swordmovement();
        int listsize;
        listsize=bullist.size();
        for(int i=0;i<listsize;i++)
        {
            if(bullist[i]->disapper())
            {
                bullist.erase(bullist.begin()+(i--));
                listsize--;
            }
        }
        listsize=enmlist.size();
        for(int i=0;i<listsize;i++)
        {
            enmlist[i]->AI();
        }
        listsize=objlist.size();
        for(int i=0;i<listsize;i++)
        {
            if(objlist[i]->neederase)
            {
                objlist[i]->del();
                delete objlist[i];
                objlist.erase(objlist.begin()+(i--));
                listsize--;
                continue;
            }
            objlist[i]->fall();
            objlist[i]->move();
        }
//      draw();
        draw(-180,-2000,10000,3000);
        xyprintf(0,0,"timegap:%.3lld velx:%lf vely:%lf on:%d",timegap,Player.velx,Player.vely,Player.ongroud());
        xyprintf(0,20,"touch:%d posx:%d posy:%d keyl:%d keyr:%d",Player.touch(*objlist[1]),Player.posx,Player.posy,Player.keyl,Player.keyr);
    }
    gameover();
    getch();
    closegraph();
    return 0;
}
#include<bits/stdc++.h>
#include<graphics.h>
/*************************************************
物理引擎部分
**************************************************/
class object
{
    public:
        int posx,posy;//左上角坐标
        bool fixed;
        double velx=0,vely=0;//x向右为正，y向下为正（图片显示形式
        int sizex,sizey;//碰撞箱视为矩形（后面也许会改
        bool keyl=0,keyr=0;//为了player
        PIMAGE img;
        void move(long long timegap);//按速度移动 时间单位：毫秒
        void velchange();//速度碰撞归零
        bool touch(object f);//两个物品是否有部分重叠
        bool inside(int x,int y);//点是否在碰撞箱内
        bool ongroud();//物品是否直接或间接摆在地上
        void fall(long long timegap);//随重力下落
        object(int x,int y,bool f,int sx,int sy,std::string file);//！！！！注意
        object();
};
object::object()
{

}
object::object(int x,int y,bool f,int sx,int sy,std::string file)
{
    posx=x;posy=y;fixed=f;sizex=sx;sizey=sy;
    img=newimage();
    getimage(img,"image/ground.png");
}
bool object::inside(int x,int y)
{
    return x>=posx&&x<posx+sizex&&y>=posy&&y<posy+sizey;
}
bool object::touch(object f)
{
    return inside(f.posx,f.posy)
    ||inside(f.posx,f.posy+f.sizey-1)
    ||inside(f.posx+f.sizex-1,f.posy)
    ||inside(f.posx+f.sizex-1,f.posy+f.sizey-1)
    ||f.inside(posx,posy)
    ||f.inside(posx+sizex-1,posy)
    ||f.inside(posx,posy+sizey-1)
    ||f.inside(posx+sizex-1,posy+sizey-1);
}
const int movegap=1;//！！！！！随便设的
std::vector<object*> objlist;//所有物品列表
void object::velchange()
{
    int signx=velx==0?0:(velx>0?1:-1),signy=vely==0?0:(vely>0?1:-1);
    int listsize=objlist.size();
    object tem=*this;
    tem.posx+=signx*movegap;
    for(int i=0;i<listsize;i++)
        if(objlist[i]!=this)
        if(tem.touch(*objlist[i]))
        {
            if(signx)keyr=0;
            else keyl=0;
            velx=0;
            break;
        }
    tem.posx-=signx*movegap;
    tem.posy+=signy*movegap;
    for(int i=0;i<listsize;i++)
        if(objlist[i]!=this)
        if(tem.touch(*objlist[i]))
        {
            vely=0;
            break;
        }
}
void object::move(long long timegap)
{
    if(fixed)return;
    int aimposx=posx+velx*timegap,aimposy=posy+vely*timegap;
    int signx=velx==0?0:(velx>0?1:-1),signy=vely==0?0:(vely>0?1:-1);
    int listsize=objlist.size();
    object tem=*this;
    bool fla=1;
    while(fla&&posx!=aimposx)
    {
        tem.posx=std::min(signx*(tem.posx+signx*movegap),signx*aimposx)*signx;
        for(int i=0;i<listsize;i++)
            if(tem.touch(*objlist[i]))
            if(objlist[i]!=this)
            {
                fla=0;
                break;
            }
        if(fla)*this=tem;
    }
    fla=1;
    while(fla&&posy!=aimposy)
    {
        tem.posy=std::min(signy*(tem.posy+signy*movegap),signy*aimposy)*signy;
        for(int i=0;i<listsize;i++)
            if(tem.touch(*objlist[i]))
            if(objlist[i]!=this)
            {
                fla=0;
                break;
            }
        if(fla)*this=tem;
    }
    velchange();
}
bool object::ongroud()
{
    if(fixed)return 1;
    object tem=*this;
    tem.posy+=movegap;
    int listsize=objlist.size();
    bool fla=0;
    for(int i=0;i<listsize;i++)
        if(objlist[i]!=this)
        if((*objlist[i]).touch(tem))
        {
            fla|=(*objlist[i]).ongroud();
            if(fla)break;
        }
    return fla;
}
const double gal=0.001;//重力加速度！！！！要调整
void object::fall(long long timegap)
{
    if(ongroud())return;
    vely+=gal*timegap;
}
/*************************************************
玩家部分
**************************************************/
class player : public object
{
    public:
        void velset(int op);//0上1左2右
        void velunset(int op);
        void init();
};
player Player;
const double movevel=0.1,jumpvel=0.7;//！！！！随便设的
void player::velset(int op)
{
    if(op)
    {
        if(op==1)
        {
            if(!keyl)keyl=1,velx-=movevel;
        }
        else 
        {
            if(!keyr)keyr=1,velx+=movevel;
        }
    }
    else
        if(ongroud())
            vely-=jumpvel;
}
void player::velunset(int op)
{
    if(op==1)
    {
        if(keyl)keyl=0,velx+=movevel;
    }
    else
    {
        if(keyr)keyr=0,velx-=movevel;
    }
}
void player::init()
{
    fixed=0;
    posx=0;posy=-100;
    sizex=24;sizey=51;
    img=newimage();
    getimage(img,"image/player.png");
}
/*************************************************
按键部分
**************************************************/
void keymovement()
{
    while(kbmsg())
    {
        key_msg k=getkey();
        if(k.msg==key_msg_down)
        {
            switch(k.key)
            {
                case 'a':
                case 'A':
                    Player.velset(1);
                    break;
                case 'd':
                case 'D':
                    Player.velset(2);
                    break;
                case 'w':
                case 'W':
                    Player.velset(0);
                    break;
                /*
                case key_esc:
                    return;
                */
            }
        }
        if(k.msg==key_msg_up)
        {
            switch(k.key)
            {
                case 'a':
                case 'A':
                    Player.velunset(1);
                    break;
                case 'd':
                case 'D':
                    Player.velunset(2);
                    break;
            }
        }
    }
}
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
    object *ground1=new object(-100,0,1,335,44,"image/ground.png");
    objlist.push_back(ground1);
}
/*************************************************
绘图部分
**************************************************/
int pyx=500,pyy=500;
void draw()
{
    cleardevice();
    int listsize=objlist.size();
    for(int i=0;i<listsize;i++)
    {
        putimage((*objlist[i]).posx+pyx,(*objlist[i]).posy+pyy,(*objlist[i]).img);
    }
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
/*************************************************
物理引擎部分
**************************************************/
class object
{
    public:
        int posx,posy;//左上角坐标
        bool fixed;//浮空
        double velx=0,vely=0;//速度 x向右为正，y向下为正（图片显示形式
        int sizex,sizey;//碰撞箱视为矩形（后面也许会改
        bool peng=1;//是否具有碰撞箱（sword）

        float centerx=0,centery=0;//旋转中心（一个0~1之间的数）
        double rad=0;//旋转角度（弧度制）

        bool keyl=0,keyr=0;//为了player
        bool neederase=0;//是否需要擦除
        PIMAGE img;
        void move();//按速度移动 时间单位：毫秒
        void velchange();//速度碰撞归零
        bool touch(object f);//两个物品是否有部分重叠
        bool inside(int x,int y);//点是否在碰撞箱内
        bool ongroud();//物品是否直接或间接摆在地上
        void fall();//随重力下落
        double distance(object f);//两个物品的距离
        void del();//析构函数
        object(int x,int y,bool f,int sx,int sy,LPCSTR file);
        object();
};
object::object()
{
    img=newimage();
    getimage(img,"",2,2);
}
object::object(int x,int y,bool f,int sx,int sy,LPCSTR file):posx(x),posy(y),fixed(f),sizex(sx),sizey(sy)
{
    img=newimage();
    getimage(img,file,sx,sy);
}
void object::del()
{
    delimage(img);
    // std::cout<<1;
}
bool object::inside(int x,int y)
{
    int centerposx=sizex*centerx+posx,centerposy=sizey*centery+posy;//旋转中心坐标
    int x0=(x-centerposx)*cos(rad)-(y-centerposy)*sin(rad)+centerposx;
    int y0=(x-centerposx)*sin(rad)+(y-centerposy)*cos(rad)+centerposy;//考虑旋转
    x=x0;y=y0;
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
        if(objlist[i]!=this&&objlist[i]->peng)
        if(tem.touch(*objlist[i]))
        {
            if(signx>0)keyr=0;
            else keyl=0;
            velx=0;
            break;
        }
    tem.posx-=signx*movegap;
    tem.posy+=signy*movegap;
    for(int i=0;i<listsize;i++)
        if(objlist[i]!=this&&objlist[i]->peng)
        if(tem.touch(*objlist[i]))
        {
            vely=0;
            break;
        }
}
void object::move()
{
//if(fixed)return;
    int signx=velx==0?0:(velx>0?1:-1),signy=vely==0?0:(vely>0?1:-1);
    int aimposx=posx+(int)(std::fabs(velx)*timegap)*signx,aimposy=posy+(int)(std::fabs(vely)*timegap)*signy;//注意向零取整问题
    int listsize=objlist.size();
    object tem=*this;
    bool fla=1;
    while(fla&&posx!=aimposx)
    {
        tem.posx=std::min(movegap,signx*(aimposx-posx))*signx+posx;
        for(int i=0;i<listsize;i++)
            if(objlist[i]!=this&&objlist[i]->peng)
            if(tem.touch(*objlist[i]))
            {
                fla=0;
                break;
            }
        if(fla)*this=tem;
    }
    fla=1;
    while(fla&&posy!=aimposy)
    {
        tem.posy=std::min(movegap,signy*(aimposy-posy))*signy+posy;
        for(int i=0;i<listsize;i++)
            if(objlist[i]!=this&&objlist[i]->peng)
            if(tem.touch(*objlist[i]))
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
        if(objlist[i]!=this&&objlist[i]->peng)
        if((*objlist[i]).touch(tem))
        {
            fla|=(*objlist[i]).ongroud();
            if(fla)break;
        }
    return fla;
}
const double gal=0.001;//重力加速度！！！！要调整
void object::fall()
{
    if(ongroud())return;
    vely+=gal*timegap;
}
double object::distance(object f)
{
    double dx=(posx+sizex/2.0)-(f.posx+f.sizex/2.0),dy=(posy+sizey/2.0)-(f.posy+f.sizey/2.0);
    return sqrt(dx*dx+dy*dy);
}
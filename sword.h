class sword : public object
{
    public:
        int pyx=10,pyy=40;//相对player偏移（佩刀位置
        double radspeed=0.01;//旋转速度
        long long time;//开始旋转时刻
        long long radtime=300;//旋转时长
        void swordmovement();
        void init();
}Sword;
void sword::init()
{
    img=newimage();
    getimage(img,"image/sword.png");
    sizex=8;sizey=50;
    centerx=0.5f;centery=0.9f;
    peng=0;
}
void sword::swordmovement()
{
    posx=Player.posx+pyx;
    posy=Player.posy+pyy;
    if(timenow-time>radtime)
    {
        rad=0;
        return;
    }
    rad=radspeed*(timenow-time)*(-Player.toword);
}
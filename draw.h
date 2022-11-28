/*************************************************
绘图部分
**************************************************/
int pyx=500,pyy=500;//画面移动偏移值
void draw()//无限制
{
    cleardevice();
    pyx=500-Player.posx;
    pyy=500-Player.posy;
    int listsize=objlist.size();
    for(int i=0;i<listsize;i++)
    {
        putimage((*objlist[i]).posx+pyx,(*objlist[i]).posy+pyy,(*objlist[i]).img);
    }
}
void draw(int XU,int YL,int Xsiz,int Ysiz)//传入限制区域左上坐标和大小，需要限制显示区域大小大于1000*1000
{
    cleardevice();
    pyx=500-Player.posx-Player.sizex/2.0;
    pyy=500-Player.posy-Player.sizey/2.0;
    pyx=std::min(pyx,-XU);
    pyx=std::max(pyx,1000-XU-Xsiz);
    pyy=std::min(pyy,-YL);
    pyy=std::max(pyy,1000-YL-Ysiz);
    int listsize=objlist.size();
    for(int i=0;i<listsize;i++)
    {
        putimage((*objlist[i]).posx+pyx,(*objlist[i]).posy+pyy,(*objlist[i]).img);
    }
}
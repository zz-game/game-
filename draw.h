/*************************************************
绘图部分
**************************************************/
int pyx=500,pyy=500;//画面移动偏移值
void draw()
{
    cleardevice();
    int listsize=objlist.size();
    for(int i=0;i<listsize;i++)
    {
        putimage((*objlist[i]).posx+pyx,(*objlist[i]).posy+pyy,(*objlist[i]).img);
    }
}
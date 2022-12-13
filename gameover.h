/*************************************************
游戏结束界面
**************************************************/
bool gameruning=1;
void gameover()
{
    setfont(200, 0, "黑体");
    outtextxy(50,150,"GAME OVER");
    setfont(30, 0, "黑体");
    outtextxy(400,400,"press any key to exit");//中文不知道为什么有乱码
    Sleep(1000);
    flushkey();
}
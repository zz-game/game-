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
    object *ground1=new object(-300,0,1,300,80,"image/sth_ground 300,80.png");
    objlist.push_back(ground1);
    object *ground2=new object(10,80,1,300,80,"image/sth_ground 300,80.png");
    objlist.push_back(ground2);
}
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
    enemy *enemy1=new enemy(300,-500,"image/player.png");
    enmlist.push_back(enemy1);
    objlist.push_back(enemy1);
    Player.init();
    objlist.push_back(&Player);
    //先这样看看
    object *ground1=new object(-300,0,1,300,80,"image/sth_ground 300,80.png");
    objlist.push_back(ground1);
    object *ground2=new object(10,80,1,300,80,"image/sth_ground 300,80.png");
    objlist.push_back(ground2);
    object *ground3=new object(320,0,1,300,80,"image/sth_ground 300,80.png");
    objlist.push_back(ground3);
    timenow=getCurrentTime();
}
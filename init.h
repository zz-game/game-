/*************************************************
初始化部分
**************************************************/
char imag[100];
void init()
{
    initgraph(1000,1000,INIT_RENDERMANUAL);
	setbkcolor(EGERGB(0xFF, 0xFF, 0xFF));
	setcolor(BLACK);
	setbkmode(TRANSPARENT);
	setfont(16, 0, "黑体");
    freopen("map.txt","r",stdin);
    int Px,Py;
    scanf("%d%d",&Px,&Py);
    Player.init(Px,Py);
    objlist.push_back(&Player);
    char id[10];
    while(~scanf("%s",id))
    {
        if(!strcmp(id,"ground"))
        {
            int PosX,PosY,Fixed,SizeX,SizeY;
            scanf("%d%d%d%d%d%s",&PosX,&PosY,&Fixed,&SizeX,&SizeY,imag);
            object *gro=new object(PosX,PosY,Fixed,SizeX,SizeY,imag);
            objlist.push_back(gro);
        }
        else if(!strcmp(id,"enemy"))
        {
            int PosX,PosY;
            scanf("%d%d%s",&PosX,&PosY,imag);
            enemy *enm=new enemy(PosX,PosY,imag);
            enmlist.push_back(enm);
            objlist.push_back(enm);
        }
    }
    Sword.init();
    objlist.push_back(&Sword);
    freopen("CON","r",stdin);
    // enemy *enemy1=new enemy(300,-500,"image/player.png");
    // enmlist.push_back(enemy1);
    // objlist.push_back(enemy1);
    // objlist.push_back(&Player);
    // Sword.init();
    // objlist.push_back(&Sword);
    // //先这样看看
    // object *ground1=new object(-300,0,1,300,80,"image/sth_ground 300,80.png");
    // objlist.push_back(ground1);
    // object *ground2=new object(10,80,1,300,80,"image/sth_ground 300,80.png");
    // objlist.push_back(ground2);
    // object *ground3=new object(320,0,1,300,80,"image/sth_ground 300,80.png");
    // objlist.push_back(ground3);
    timenow=getCurrentTime();
}
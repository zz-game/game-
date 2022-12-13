/*************************************************
导入地图部分
**************************************************/
char imag[100];
void getmap(char x[])
{
    freopen(x,"r",stdin);
    int Px,Py;
    scanf("%d%d",&Px,&Py);
    Player.init(Px,Py);
    objlist.push_back(&Player);
    char id[10];
    while(~scanf("%s",id))
    {
        if(id[0]=='#')
        {
            std::string use_less;
            std::getline(std::cin,use_less);
            continue;
        }
        if(!strcmp(id,"ground"))
        {
            int PosX,PosY,SizeX,SizeY;
            scanf("%d%d%d%d%s",&PosX,&PosY,&SizeX,&SizeY,imag);
            object *gro=new object(PosX,PosY,1,SizeX,SizeY,imag);
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
        else if(!strcmp(id,"box"))
        {
            int PosX,PosY,SizeX,SizeY;
            scanf("%d%d%d%d%s",&PosX,&PosY,&SizeX,&SizeY,imag);
            object *gro=new object(PosX,PosY,0,SizeX,SizeY,imag);
            objlist.push_back(gro);
        }
    }
    freopen("CON","r",stdin);
}
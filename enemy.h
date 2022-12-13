/*************************************************
子弹部分
**************************************************/
constexpr double bulvel=0.5;//子弹速度
constexpr int bulsize=5;
class bullet : public object //子弹
{
    public:
    int Sposx,Sposy;//开始的地方(左上角)
    double maxdis;
    bool disapper();//是否消失函数（改为假的子弹）（消失返回1）
    bullet();
    bullet(int,int,double);
};
std::vector<bullet*> bullist;//子弹列表
bullet::bullet(){}
bullet::bullet(int posX,int posY,double MaxDis):object(posX,posY,1,bulsize,bulsize,"image/bullet.png"),Sposx(posX),Sposy(posy),maxdis(MaxDis){}
bool bullet::disapper()
{
    int listsize=objlist.size();
    object tem(posx-1,posy-1,0,sizex+2,sizey+2,"");//！！！！这种写法可能有问题，不过问题不大，先不管
    for(int i=0;i<listsize;i++)
    {
        if(objlist[i]!=this&&tem.touch(*objlist[i]))
        {
            if(objlist[i]==&Player)gameruning=0;//击杀玩家
            tem.del();
            return neederase=1;
        }
    }
    tem.del();
    int X=posx-Sposx,Y=posy-Sposy;
    if(sqrt(X*X+Y*Y)>maxdis)
    {
        return neederase=1;
    }
    return 0;
}
/*************************************************
敌人部分
**************************************************/
double seer=200,shotr=400;//警戒范围和射击范围半径
double firetime=2000;//开枪间隔时间
double enmvel=0.11;//敌人移速
class enemy : public object
{
    public:
    long long lasttime;
    void fire();//开枪
    bool seen();//是否看到玩家
    void AI();//行动 只需要调用这个就行了
    enemy();
    enemy(int x,int y,LPCSTR file);
};
enemy::enemy(){}
enemy::enemy(int x,int y,LPCSTR file):object(x,y,0,24,51,file){}
std::vector<enemy*> enmlist;//敌人列表
bool enemy::seen()
{
    int X=Player.posx+Player.sizex/2,Y=Player.posy+Player.sizey/2;
    if(distance(Player)>seer)
        return 0;
    int signx=(X>posx)-(X<posx+sizex),signy=(Y>posy)-(Y<posy+sizey);//[-1,1] n Z;（1右下，-1左上）
    bullet virbul(posx+sizex*(1+signx)/2.0+2*signx-bulsize*(1-signx)/2+2*signy,posy+sizey*(1+signy)/2.0+2*signy-bulsize*(1-signy)/2+2*signx,seer);//测试是否看得见使用的物品
    virbul.velx=(X-(virbul.posx+virbul.sizex/2))/virbul.distance(Player)/10;
    virbul.vely=(Y-(virbul.posy+virbul.sizex/2))/virbul.distance(Player)/10;
    while((!virbul.neederase)&&virbul.distance(Player)>sqrt(Player.sizex*Player.sizex+Player.sizey*Player.sizey)/2.0+5)
    {
        int vsignx=(virbul.velx>0)-(virbul.velx<0),vsigny=(virbul.vely>0)-(virbul.vely<0);
        int aimposx=virbul.posx+(int)(std::fabs(virbul.velx)*100)*vsignx,aimposy=virbul.posy+(int)(std::fabs(virbul.vely)*100)*vsigny;
        bool fla=1;
        int listsize=objlist.size();
        bullet tem=virbul;
        while((fla&&virbul.posx!=aimposx)&&virbul.distance(Player)>sqrt(Player.sizex*Player.sizex+Player.sizey*Player.sizey)/2.0+5)
        {
            tem.posx=std::min(movegap,vsignx*(aimposx-virbul.posx))*vsignx+virbul.posx;
            for(int i=0;i<listsize;i++)
                if(tem.touch(*objlist[i])&&objlist[i]->peng)
                {
                    fla=0;
                    break;
                }
            if(fla)
                virbul=tem;
        }
        fla=1;
        while((fla&&virbul.posy!=aimposy)&&virbul.distance(Player)>sqrt(Player.sizex*Player.sizex+Player.sizey*Player.sizey)/2.0+5)
        {
            tem.posy=std::min(movegap,vsigny*(aimposy-virbul.posy))*vsigny+virbul.posy;
            for(int i=0;i<listsize;i++)
                if(tem.touch(*objlist[i])&&objlist[i]->peng)
                {
                    fla=0;
                    break;
                }
            if(fla)
                virbul=tem;
        }
        virbul.velchange();
        virbul.disapper();
    }
    virbul.del();
    if(virbul.distance(Player)<=sqrt(Player.sizex*Player.sizex+Player.sizey*Player.sizey)/2.0+5)
        return 1;
    return 0;
}
void enemy::fire()
{
    bullet *Bul;
    int X=Player.posx+Player.sizex/2,Y=Player.posy+Player.sizey/2;
    int signx=(X>posx)-(X<posx+sizex),signy=(Y>posy)-(Y<posy+sizey);//[-1,1] n Z;（1右下，-1左上）
    Bul=new bullet(posx+sizex*(1+signx)/2-bulsize*(1-signx)/2+signx,posy+sizey*(1+signy)/2-bulsize*(1-signy)/2+signy,shotr);
    Bul->velx=(X-Bul->posx)/Bul->distance(Player)*bulvel;
    Bul->vely=(Y-Bul->posy)/Bul->distance(Player)*bulvel;
    objlist.push_back(Bul);
    bullist.push_back(Bul);
}
void enemy::AI()
{
    if(seen())
    {
        if(timenow-lasttime>firetime)
        {
            lasttime=timenow;
            fire();
        }
        int X=Player.posx+Player.sizex/2,Y=Player.posy+Player.sizey/2;
        int signx=(X>posx)-(X<posx+sizex),signy=(Y>posy)-(Y<posy+sizey);//[-1,1] n Z;（1右下，-1左上）
        posx-=10*signx;
        if(ongroud())
            velx=-signx*enmvel;
        else
            velx=0;
        posx+=10*signx;
    }
    else
        velx=0;
}
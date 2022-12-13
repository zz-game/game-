/*************************************************
玩家部分
**************************************************/
class player : public object
{
    public:
        double movevel=0.2,jumpvel=0.7;//！！！！随便设的
        bool doublejump=1;//二段跳
        double toword=1;//朝向，向右为1，左为-1
        void doublejumpck();
        void velset(int op);//0上1左2右
        void velunset(int op);
        void init(int,int);
}Player;
void player::doublejumpck()
{
    if(doublejump)return;
    if(ongroud())doublejump=1;
}
void player::velset(int op)
{
    if(op)
    {
        if(op==1)
        {
            toword=-1;
            if(!keyl)keyl=1,velx-=movevel;
        }
        else 
        {
            toword=1;
            if(!keyr)keyr=1,velx+=movevel;
        }
    }
    else
        if(ongroud())
            vely-=jumpvel;
        else
            if(doublejump)
            {
                doublejump=0;
                vely=-jumpvel;
            }
}
void player::velunset(int op)
{
    if(op==1)
    {
        if(keyl)keyl=0,velx+=movevel;
    }
    else
    {
        if(keyr)keyr=0,velx-=movevel;
    }
}
void player::init(int X=0,int Y=-1000)
{
    fixed=0;
    posx=X;posy=Y;
    sizex=24;sizey=51;
    img=newimage();
    getimage(img,"image/player.png");
}
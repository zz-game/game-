/*************************************************
玩家部分
**************************************************/
class player : public object
{
    public:
        void velset(int op);//0上1左2右
        void velunset(int op);
        void init();
};
player Player;
const double movevel=0.2,jumpvel=0.7;//！！！！随便设的
void player::velset(int op)
{
    if(op)
    {
        if(op==1)
        {
            if(!keyl)keyl=1,velx-=movevel;
        }
        else 
        {
            if(!keyr)keyr=1,velx+=movevel;
        }
    }
    else
        if(ongroud())
            vely-=jumpvel;
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
void player::init()
{
    fixed=0;
    posx=0;posy=-100;
    sizex=24;sizey=51;
    img=newimage();
    getimage(img,"image/player.png");
}
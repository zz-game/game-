/*************************************************
按键部分
**************************************************/
void keymovement()
{
    while(kbmsg())
    {
        key_msg k=getkey();
        if(k.msg==key_msg_down)
        {
            switch(k.key)
            {
                case 'a':
                case 'A':
                    Player.velset(1);
                    break;
                case 'd':
                case 'D':
                    Player.velset(2);
                    break;
                case 'w':
                case 'W':
                    Player.velset(0);
                    break;
                /*
                case key_esc:
                    return;
                */
            }
        }
        if(k.msg==key_msg_up)
        {
            switch(k.key)
            {
                case 'a':
                case 'A':
                    Player.velunset(1);
                    break;
                case 'd':
                case 'D':
                    Player.velunset(2);
                    break;
            }
        }
    }
}
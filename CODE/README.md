# BLDC FOC Control


Position_IRn
    if(position1_flag_set)
    {
        oldtime = newtime;
        newtime=gettime(motor1)
        clear_timer()
        set_timer_IT(newtime)
    }
    if(newtime>oldtime)
    {
        if(position2_flag_set)
        {
            stop_motor2
        }
    }
    else 
    {
        if(position2_flag_set)
        {
            start_motor1
        }
    }



Timer_IRn
    if(newtime>oldtime)
    {
        start_motor2
    }
    {
        stop_motor1
    }


git config --global --unset http.proxy 
git config --global --unset https.proxy


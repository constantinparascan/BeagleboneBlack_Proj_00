
#include<iostream>
#include<unistd.h> //for usleep

#include "SS_Server_GPIO.h"

using namespace std;
using namespace exploringBB;

int main(void)
{
    
    SS_Server_GPIO* GPIO_Server = SS_Server_GPIO::SS_Server_GPIO_GetInstance();
    
    
    GPIO_Server->SS_Server_GPIO_Connect_MessageQueue();
    
    
    
    while(1)
    {
        GPIO_Server->SS_Server_GPIO_Get_Message();
    }
    
    
    return 0;
}
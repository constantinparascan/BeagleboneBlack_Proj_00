#include "SS_Server_GPIO.h"

#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace exploringBB;

int main(void)
{
    
    int n_msgid;
    int status;
    struct GPIO_msg_st myData;
    
    n_msgid = msgget((key_t)GPIO_COM_KEY_T_RECEIVE, 0666 | IPC_CREAT);
    
    
    if( n_msgid == -1 )
    {
        perror("ERROR 001: cannot initiate communication queue - key cannot be created");
        
    }
    
    
    unsigned int nIdx = 0;
    while(1)
    {
       myData.my_msg_type = 1; 
       myData.GPIO_command[0] = nIdx;
       myData.GPIO_command[1] = nIdx;
       myData.GPIO_command[2] = nIdx;
       myData.GPIO_command[3] = nIdx;
       myData.GPIO_command[4] = nIdx;
       myData.GPIO_command[5] = nIdx;
       myData.GPIO_command[6] = nIdx;
       myData.GPIO_command[7] = nIdx;
       myData.GPIO_command[8] = nIdx;
       myData.GPIO_command[9] = nIdx;
       
       nIdx ++;
        
       status = msgsnd(n_msgid, (void *)&myData, GPIO_COM_DATA_LENGTH, 0);  
       
       if(status == -1)
       {
           perror("\n Error ... cannot send message ... ");
           
           exit(0);
       }
       else
       {
           printf("\n Sending message ID = %d", nIdx);
       }
    }
    
    
    return 0;
}
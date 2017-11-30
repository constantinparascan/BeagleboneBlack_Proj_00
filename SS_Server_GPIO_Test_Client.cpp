#include "SS_Server_GPIO.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>

using namespace std;
using namespace exploringBB;

int main(void)
{
    
    int n_msgid;
    int status;
    
    int ncommand = 0;
    
    struct GPIO_msg_st myData;
    
    n_msgid = msgget((key_t)GPIO_COM_KEY_T_RECEIVE, 0666 /*| IPC_CREAT*/);
    
    
    if( n_msgid == -1 )
    {
        perror("ERROR 001: cannot initiate communication queue - key cannot be created");
        
    }
    
    
    printf("\n Command list: 10");
    printf("\n Command list: 15");
    printf("\n Command list: 20");
    printf("\n Command list: 30");
    
    
    unsigned int nIdx = 0;
    while(1)
    {
        
       printf("\n >>> Command: ");
       scanf("%d", &ncommand);
       
       switch(ncommand)
       {
           case 10:
           {
               
                myData.my_msg_type = 1; 
                myData.GPIO_command[0] = 0x10;
                myData.GPIO_command[1] = 10;
                myData.GPIO_command[2] = 1;
                myData.GPIO_command[3] = 2;
                myData.GPIO_command[4] = 3;
                myData.GPIO_command[5] = 4;
                myData.GPIO_command[6] = 5;
                myData.GPIO_command[7] = 6;
                myData.GPIO_command[8] = 7;
                myData.GPIO_command[9] = 8;
               
               break;
           }

           
           case 15:
           {
               
                myData.my_msg_type = 1; 
                myData.GPIO_command[0] = 0x15;
                myData.GPIO_command[1] = 15;
                myData.GPIO_command[2] = 1;
                myData.GPIO_command[3] = 2;
                myData.GPIO_command[4] = 3;
                myData.GPIO_command[5] = 4;
                myData.GPIO_command[6] = 5;
                myData.GPIO_command[7] = 6;
                myData.GPIO_command[8] = 7;
                myData.GPIO_command[9] = 8;
               
               break;
           }
           
           
           case 20:
           {
               
                myData.my_msg_type = 1; 
                myData.GPIO_command[0] = 0x20;
                myData.GPIO_command[1] = 20;
                myData.GPIO_command[2] = 1;
                myData.GPIO_command[3] = 2;
                myData.GPIO_command[4] = 3;
                myData.GPIO_command[5] = 4;
                myData.GPIO_command[6] = 5;
                myData.GPIO_command[7] = 6;
                myData.GPIO_command[8] = 7;
                myData.GPIO_command[9] = 8;
               
               break;
           }           
           
           
           
           case 30:
           {
               
                myData.my_msg_type = 1; 
                myData.GPIO_command[0] = 0x30;
                myData.GPIO_command[1] = 30;
                myData.GPIO_command[2] = 1;
                myData.GPIO_command[3] = 2;
                myData.GPIO_command[4] = 3;
                myData.GPIO_command[5] = 4;
                myData.GPIO_command[6] = 5;
                myData.GPIO_command[7] = 6;
                myData.GPIO_command[8] = 7;
                myData.GPIO_command[9] = 8;
               
               break;
           }           
           
       }
/*        
        
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
  */      
       status = msgsnd(n_msgid, (void *)&myData, sizeof(myData.GPIO_command), IPC_NOWAIT);  
       
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
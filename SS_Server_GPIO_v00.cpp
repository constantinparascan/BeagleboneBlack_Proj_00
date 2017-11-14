
#include <stdio.h>

#include "library/gpio/GPIO.h"


#include "SS_Server_GPIO.h"

namespace exploringBB 
{
    

    
    
SS_Server_GPIO *SS_Server_GPIO::s_Server_GPIO_Instance = NULL_PTR_GPIO;
 
    

void SS_Server_GPIO::SS_Server_GPIO_Connect_MessageQueue(void)
{
    int n_msgid;
    
    
    /*
     *  Receive queue 
     */
    
    n_msgid = msgget((key_t)GPIO_COM_KEY_T_RECEIVE, 0666 | IPC_CREAT);
    
    if( n_msgid == -1 )
    {
        perror("ERROR 001: cannot initiate communication queue RX - key cannot be created");
        
        comm_error = true;
    }
    else
    {
        comm_msgid_rx = n_msgid;
        
        comm_error = false;
    }
}


void SS_Server_GPIO::SS_Server_GPIO_Get_Message(void)
{
    int status;
    
    
    /* read from the queue */
    if( comm_msgid_rx != -1 )
    {
        status = msgrcv(comm_msgid_rx, (void *)&comm_msgData, GPIO_COM_DATA_LENGTH, 0, 0);
        
        /* a valid message has been extracted from the queue ? */
        if( status != -1 )
        {
            /*
             *  Process message ... 
             * 
             */
            
            printf("\n >>> Message received %d %d %d %d %d %d %d %d %d %d \n", comm_msgData.GPIO_command[0],
                comm_msgData.GPIO_command[1], comm_msgData.GPIO_command[2], comm_msgData.GPIO_command[3],
                comm_msgData.GPIO_command[4], comm_msgData.GPIO_command[5], comm_msgData.GPIO_command[6],
                comm_msgData.GPIO_command[7], comm_msgData.GPIO_command[8], comm_msgData.GPIO_command[9]);
        }
    }
}

    
}

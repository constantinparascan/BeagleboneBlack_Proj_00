
#include <stdio.h>

#include "library/gpio/GPIO.h"


#include "SS_Server_GPIO.h"
using namespace std;

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


/*
 *  This function is used to decode the command ...
 * 
 */
void SS_Server_GPIO::SS_Server_GPIO_Process_Message(void)
{
    unsigned char nPinIdLocal = 0;
    
    switch(comm_msgData.GPIO_command[0])
    {
      
        /* 
         * Request PIN LOCK ...
         */
        case 0x10:
        {
            /* 
             * check to see if the Application ID is in valid range...  
             */
            if( ( comm_msgData.GPIO_command[0] > 0x00 ) && ( comm_msgData.GPIO_command[0] < 0xFF ) && 
              ( comm_msgData.GPIO_command[1] < DEVICE_MAX_IO_PINS ) )
            {
                PIN_Server_Prop[ comm_msgData.GPIO_command[1] ].b_isPinLocked = GPIO_TRUE;
                
                PIN_Server_Prop[ comm_msgData.GPIO_command[1] ].n_ProcessOwner = comm_msgData.GPIO_command[0];
                PIN_Server_Prop[ comm_msgData.GPIO_command[1] ].n_CountAliveness = DEVICE_MAX_ALIVE_MISSING_UNTIL_UNLOCK;
            }
            
            break;
        }
            

        /* 
         * Request PIN UNLOCK ...
         */
        case 0x15:
        {
            /* 
             * check to see if the Application ID is in valid range...  
             */
            if( ( comm_msgData.GPIO_command[0] > 0x00 ) && ( comm_msgData.GPIO_command[0] < 0xFF ) &&
                ( comm_msgData.GPIO_command[1] < DEVICE_MAX_IO_PINS ) )
            {
                PIN_Server_Prop[ comm_msgData.GPIO_command[1] ].b_isPinLocked = GPIO_FALSE;
                PIN_Server_Prop[ comm_msgData.GPIO_command[1] ].n_CountAliveness = DEVICE_ALIVE_COUNTER_STOPPED;
            }
            
            break;
        }
            
            
            
        /* 
         * Request PIN Configuration ...
         */
        case 0x20:
        {

            /* 
             * check to see if the Application ID is in valid range...  
             */
            if( ( comm_msgData.GPIO_command[0] > 0x00 ) && ( comm_msgData.GPIO_command[0] < 0xFF ) &&
                ( comm_msgData.GPIO_command[1] < DEVICE_MAX_IO_PINS ) )
              {
                  /* 
                   * check to see if we are allowed to change the configurations ... 
                   */
                  
                   nPinIdLocal = comm_msgData.GPIO_command[1];
                  
                   if( ( PIN_Server_Prop[ nPinIdLocal ].b_isPinLocked != GPIO_TRUE ) || 
                     ( ( PIN_Server_Prop[ nPinIdLocal ].b_isPinLocked == GPIO_TRUE )  && 
                       ( PIN_Server_Prop[ nPinIdLocal ].n_ProcessOwner == comm_msgData.GPIO_command[0] ) ) )
                     {
                        /* 
                         *  prepare to reconfigure pin ... 
                         */
                        
                        if( BoardPIN[ nPinIdLocal ] == NULL_PTR_GPIO )
                        {
                            BoardPIN[ nPinIdLocal ] = new GPIO ( nPinIdLocal );
                        }
                            
                        BoardPIN[ nPinIdLocal ]->setDirection( (DIRECTION)comm_msgData.GPIO_command[2] );
                            
                        BoardPIN[ nPinIdLocal ]->setValue( (VALUE)comm_msgData.GPIO_command[3] );
                    }
              }
                
            break;
        }
        
        /* 
         * Request PIN Digital Output Value ...
         */
        case 0x30:
        {

            /* 
             * check to see if the Application ID is in valid range...  
             */
            if( ( comm_msgData.GPIO_command[0] > 0x00 ) && ( comm_msgData.GPIO_command[0] < 0xFF ) &&
                ( comm_msgData.GPIO_command[1] < DEVICE_MAX_IO_PINS ) )
              {
                  /* 
                   * check to see if we are allowed to change the configurations ... 
                   */
                  
                   nPinIdLocal = comm_msgData.GPIO_command[1];
                  
                   if( ( PIN_Server_Prop[ nPinIdLocal ].b_isPinLocked != GPIO_TRUE ) || 
                     ( ( PIN_Server_Prop[ nPinIdLocal ].b_isPinLocked == GPIO_TRUE )  && 
                       ( PIN_Server_Prop[ nPinIdLocal ].n_ProcessOwner == comm_msgData.GPIO_command[0] ) ) )
                     {
                        /* 
                         *  prepare to reconfigure pin ... 
                         */
                        
                        if( BoardPIN[ nPinIdLocal ] != NULL_PTR_GPIO )
                        {
                            BoardPIN[ nPinIdLocal ]->setValue( (VALUE)comm_msgData.GPIO_command[2] );
                        }
                    }
              }
                
            break;
        }
        
        
    }
    
}

}// namespace exploringBB 

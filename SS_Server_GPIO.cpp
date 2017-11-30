
#include <stdio.h>
#include <sys/msg.h>

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
    
    n_msgid = msgget((key_t)GPIO_COM_KEY_T_RECEIVE, 0666 | IPC_CREAT );
    
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
        
        printf("\n\n\n\n Call msgrcv ... ");
        status = msgrcv(comm_msgid_rx, (void *)&comm_msgData, sizeof(comm_msgData.GPIO_command), 0, /*IPC_NOWAIT*/0);
        printf("\n msgrcv received a message ... ");
        
        /* a valid message has been extracted from the queue ? */
        if( status != -1 )
        {
            /*
             *  Process message ... 
             * 
             */
            
            printf("\n >>> Message received %X %d %d %d %d %d %d %d %d %d \n", (unsigned char)comm_msgData.GPIO_command[0],
                (unsigned char)comm_msgData.GPIO_command[1], (unsigned char)comm_msgData.GPIO_command[2], 
                (unsigned char)comm_msgData.GPIO_command[3], (unsigned char)comm_msgData.GPIO_command[4], 
                (unsigned char)comm_msgData.GPIO_command[5], (unsigned char)comm_msgData.GPIO_command[6],
                (unsigned char)comm_msgData.GPIO_command[7], (unsigned char)comm_msgData.GPIO_command[8], 
                (unsigned char)comm_msgData.GPIO_command[9]);
            
            /* process newly rceived message ...  */
            printf("\n >>> start preocessing ... ");
            SS_Server_GPIO_Process_Message();
            printf("\n >>> end preocessing ... ");
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
    
    
    printf("\n >> Process command value %X", (unsigned char)comm_msgData.GPIO_command[0]);
    
    switch((unsigned char)comm_msgData.GPIO_command[0])
    {
      
        /* Skip command ... */
        case 0xFF:
        {
            /*  ... Skip ... */
            
            printf(" \n\n Skip ... ");
            
            break;
        }
        
        /* 
         * Request PIN LOCK ...
         */
        case 0x10:
        {
            
            printf("\n Case 0x10 ... ");
            /* 
             * check to see if the Application ID is in valid range...  
             */
            
            if( (unsigned char)comm_msgData.GPIO_command[1] < DEVICE_MAX_IO_PINS )
            {
                /*
                
                PIN_Server_Prop[ (unsigned char)comm_msgData.GPIO_command[1] ].b_isPinLocked = GPIO_TRUE;
                
                PIN_Server_Prop[ (unsigned char)comm_msgData.GPIO_command[1] ].n_ProcessOwner = (unsigned char)comm_msgData.GPIO_command[0];
                PIN_Server_Prop[ (unsigned char)comm_msgData.GPIO_command[1] ].n_CountAliveness = DEVICE_MAX_ALIVE_MISSING_UNTIL_UNLOCK;
                */
            }
            
            printf("\n >>> command 0x10 ");
            
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
                /*
                PIN_Server_Prop[ comm_msgData.GPIO_command[1] ].b_isPinLocked = GPIO_FALSE;
                PIN_Server_Prop[ comm_msgData.GPIO_command[1] ].n_CountAliveness = DEVICE_ALIVE_COUNTER_STOPPED;
                */
            }
            
            printf("\n >>> command 0x15 ");
            
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
                  
                   /*
                   if( ( PIN_Server_Prop[ nPinIdLocal ].b_isPinLocked != GPIO_TRUE ) || 
                     ( ( PIN_Server_Prop[ nPinIdLocal ].b_isPinLocked == GPIO_TRUE )  && 
                       ( PIN_Server_Prop[ nPinIdLocal ].n_ProcessOwner == comm_msgData.GPIO_command[0] ) ) )
                     {
                        /* 
                         *  prepare to reconfigure pin ... 
                         */
                    /*    
                        if( BoardPIN[ nPinIdLocal ] == NULL_PTR_GPIO )
                        {
                            BoardPIN[ nPinIdLocal ] = new GPIO ( nPinIdLocal );
                        }
                            
                        BoardPIN[ nPinIdLocal ]->setDirection( (GPIO::DIRECTION)comm_msgData.GPIO_command[2] );
                            
                        BoardPIN[ nPinIdLocal ]->setValue( (GPIO::VALUE)comm_msgData.GPIO_command[3] );
                    }
                    */
              }
              
            printf("\n >>> command 0x20 ");
                
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
                  
                   /*
                   if( ( PIN_Server_Prop[ nPinIdLocal ].b_isPinLocked != GPIO_TRUE ) || 
                     ( ( PIN_Server_Prop[ nPinIdLocal ].b_isPinLocked == GPIO_TRUE )  && 
                       ( PIN_Server_Prop[ nPinIdLocal ].n_ProcessOwner == comm_msgData.GPIO_command[0] ) ) )
                     {
                        /* 
                         *  prepare to reconfigure pin ... 
                         */
                    /*    
                        if( BoardPIN[ nPinIdLocal ] != NULL_PTR_GPIO )
                        {
                            BoardPIN[ nPinIdLocal ]->setValue( (GPIO::VALUE)comm_msgData.GPIO_command[2] );
                        }
                    }
                    */
              }
                
            printf("\n >>> command 0x30 ");
                
            break;
        }
        
        default:
        {
            /* invalid command */
            
            printf("\n Default reached !!!");
            
            break;
        }
        
    }
    
    /* next command will be " skip " ... */
    comm_msgData.GPIO_command[0] = 0xFF;

    
}

}// namespace exploringBB 

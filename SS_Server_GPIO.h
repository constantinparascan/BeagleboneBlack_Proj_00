#ifndef __SS_SERVER_GPIO_H__
#define __SS_SERVER_GPIO_H__



#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "library/gpio/GPIO.h"



#define GPIO_COM_DATA_LENGTH (10)
#define GPIO_COM_KEY_T_RECEIVE       (872354)
#define GPIO_COM_KEY_T_SEND          (872355)

#define NULL_PTR_GPIO (0)
#define GPIO_TRUE  (1)
#define GPIO_FALSE (0)

#define DEVICE_MAX_IO_PINS (100)
#define DEVICE_MAX_ALIVE_MISSING_UNTIL_UNLOCK  (10)
#define DEVICE_ALIVE_COUNTER_STOPPED           (0xFF)


namespace exploringBB 
{

/*
 *  communication message type
 * 
 *  msg_type - 0x10 - pin request LOCK
 *                  command [ xx yy]
 *                              xx - Applicaton ID -> 1 .. 0xFE
 *                              yy - Pin ID -> 0 .. DEVICE_MAX_IO_PINS
 * 
 *             0x15 - pin request UNLOCK
 *                  command [ xx yy ]
 *                              xx - Applicaton ID -> 1 .. 0xFE
 *                              yy - Pin ID -> 0 .. DEVICE_MAX_IO_PINS
 *
 *             0x20 - pin configuration request
 *                  command [ xx yy zz pp ]
 *                              xx - Applicaton ID -> 1 .. 0xFE
 *                              yy - Pin ID -> 0 .. DEVICE_MAX_IO_PINS
 *                              zz - Pin type { 1 - input, 2 - output }
 *                              pp - Initial pin state { 0 - Low, 1 = high }
 * 
 *             0x30 - pin OUTPUT Value
 *                  command [ xx yy zz ]
 *                              xx - Application ID -> 1 .. 0xFE
 *                              yy - Pin ID -> 0 .. DEVICE_MAX_IO_PINS
 *                              zz - Pin Output value { 0 - Low, 1 = high }
 * 
 *             0x40 - pin INPUT Value
 * 
 *           - 0x85 - Application Allive
 */
struct GPIO_msg_st 
{
    long int my_msg_type;
    
    char GPIO_command[ GPIO_COM_DATA_LENGTH ]; 
};    
    
/*
 *  PIN property structure ... this keeps all the pin server
 *                             attributes.
 */
typedef struct GPIO_PIN_Server_Prop
{
    unsigned int b_isPinLocked : 1;
    
    unsigned int b_isApplicationAlive : 1;    
    unsigned char n_CountAliveness;
    
    unsigned char n_ProcessOwner;
    
}T_GPIO_PIN_Server_Prop;


/* singletone class ... */

class SS_Server_GPIO
{
    
private:

    /* Communication part ... shall be moved to a different class ??
     */
    key_t comm_key;
    bool  comm_error;
    int   comm_msgid_tx;
    int   comm_msgid_rx;
    struct GPIO_msg_st comm_msgData;
    
    
    
    
    /*
        Supported pin list ...
        
        ..
        ..
        ..
     */
    
    /*
     *  All the IO pins that the device supports ...
     */
    GPIO *BoardPIN[DEVICE_MAX_IO_PINS];    
    
    /* 
     *  Pin properties ... 
     */
    T_GPIO_PIN_Server_Prop PIN_Server_Prop[DEVICE_MAX_IO_PINS];


    static SS_Server_GPIO *s_Server_GPIO_Instance;
    
private:
    
        SS_Server_GPIO()
        {
            s_Server_GPIO_Instance = NULL_PTR_GPIO;
            
            /* communication status on init phase ... */
            comm_key   = -1;
            comm_msgid_tx = -1;
            comm_msgid_rx = -1;
            comm_error = true;
            
            /* all GPIO pins are not yet configured ... */
            for (int nindex = 0; nindex < DEVICE_MAX_IO_PINS; nindex ++)
            {
                BoardPIN[nindex] = (GPIO *)NULL_PTR_GPIO;
            }
        }
      
      
public:
    
        static SS_Server_GPIO* SS_Server_GPIO_GetInstance() 
        {
            if(s_Server_GPIO_Instance == NULL_PTR_GPIO)
            {
                s_Server_GPIO_Instance = new SS_Server_GPIO; 
                
                /* create new communication key ... */
                
                /*
                comm_key = ftok("SS_Server_GPIO.c", 'b');
                
                if(comm_key == -1)
                {
                    perror("ERROR 001: cannot initiate communication queue - key cannot be created");
                    
                    comm_error = true;
                }
                else
                    comm_error = false;
                
                */
                
                

                /* communication status on init phase ... */
                /* ... cannot be done inside static member ... !!!!
                comm_key   = -1;
                comm_msgid = -1;
                comm_error = true;
                */
            }
                
                
            return s_Server_GPIO_Instance;
            
        }
        
        
        
        
        void SS_Server_GPIO_SetPinConfig(int nThreadID, unsigned short nPinID, unsigned int nPinConfig) {};
        
        void SS_Server_GPIO_SetPinLock(int nThreadID, unsigned short nPinID) {};
        
        
        
        void SS_Server_GPIO_Connect_MessageQueue(void);
        
        void SS_Server_GPIO_Get_Message(void);
        
        void SS_Server_GPIO_Process_Message(void);
};


}


#endif /* SS_SERVER_GPIO_H__ */

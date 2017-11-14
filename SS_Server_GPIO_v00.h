#ifndef __SS_SERVER_GPIO_H__
#define __SS_SERVER_GPIO_H__



#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>



#define GPIO_COM_DATA_LENGTH (10)
#define GPIO_COM_KEY_T_RECEIVE       (872354)
#define GPIO_COM_KEY_T_SEND          (872355)

#define NULL_PTR_GPIO (0)



namespace exploringBB 
{

/*
 *  communication message type
 */
struct GPIO_msg_st 
{
    long int my_msg_type;
    
    char GPIO_command[ GPIO_COM_DATA_LENGTH ]; 
};    
    



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

    int ThreadIDLock[50];
    

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
        
        
        
        
        void SS_Server_GPIO_SetPinConfig(int nThreadID, unsigned short nPinID, unsigned int nPinConfig);
        
        void SS_Server_GPIO_SetPinLock(int nThreadID, unsigned short nPinID);
        
        
        
        void SS_Server_GPIO_Connect_MessageQueue(void);
        
        void SS_Server_GPIO_Get_Message(void);
};


}


#endif /* SS_SERVER_GPIO_H__ */

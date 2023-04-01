
#ifndef __IPC_CALL_ARG__
#define IPC_SERVER_REGISTER         0
#define IPC_CLIENT_CONNECT          1
#define IPC_CLIENT_CLOSE            2
#define IPC_SERVER_CLOSE            3            
#define MAX_SERVER_NAME_LENGTH      64
//FIXME: Need to record which key assigned to which client or not?
struct server_register_arg 
{
    char server_name[MAX_SERVER_NAME_LENGTH];
    unsigned int size;
};

struct client_connect_arg
{
    char server_name[MAX_SERVER_NAME_LENGTH];
};

struct client_close_arg
{
    char server_name[MAX_SERVER_NAME_LENGTH];
    unsigned int shm_key;
};

struct server_close_arg
{
    char server_name[MAX_SERVER_NAME_LENGTH];
    long identifier;
};

#define __IPC_CALL_ARG__
#endif
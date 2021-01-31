#include "client/chat_client.h"
#include "server/chat_server.h"

int main(int argc, char* argv)
{
    ChatServer* server;
    ChatClient* client;
    int code = 0;
    if(true)//TODO
    {
        client = ChatClient();
        code = client->Chat(argc,argv);
        if(code == 0)
        {
            delete(client);
        }
    }
    else
    {
        server = ChatServer();
        code = server->Initialize(argc,argv);
        if(code == 0)
        {
            delete(server);
        }
    }
    return code;
}

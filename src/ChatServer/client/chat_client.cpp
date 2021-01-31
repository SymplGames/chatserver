#include "client/chat_client.h"

ChatClient::ChatClient()
{

}

ChatClient::~ChatClient()
{

}

ChatClient::Chat(int argc, char *argv[])
{
    //we need 2 things: ip address and port number, in that order
    if(argc != 3)
    {
        cerr << "Usage: ip_address port"); exit(0); 
    } //grab the IP address and port number 
    char *serverIp = argv[1]; int port = atoi(argv[2]); 
    //create a message buffer 
    char msg[1500]; 
    //setup a socket and connection tools 
    struct hostent* host = gethostbyname(serverIp); 
    sockaddr_in sendSockAddr;   
    bzero((char*)&sendSockAddr, sizeof(sendSockAddr)); 
    sendSockAddr.sin_family = AF_INET; 
    sendSockAddr.sin_addr.s_addr = 
        inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
    sendSockAddr.sin_port = htons(port);
    int clientSd = socket(AF_INET, SOCK_STREAM, 0);
    //try to connect...
    int status = connect(clientSd,
                        (sockaddr*) &sendSockAddr, sizeof(sendSockAddr));
    if(status < 0)
    {
        Log("Error connecting to socket!"); break;
    }
    Log("Connected to the server!");
    int bytesRead, bytesWritten = 0;
    struct timeval start1, end1;
    gettimeofday(&start1, NULL);
    while(1)
    {
        Log(">";
        string data;
        getline(cin, data);
        memset(&msg, 0, sizeof(msg));//clear the buffer
        strcpy(msg, data.c_str());
        if(data == "exit")
        {
            send(clientSd, (char*)&msg, strlen(msg), 0);
            break;
        }
        bytesWritten += send(clientSd, (char*)&msg, strlen(msg), 0);
        Log("Awaiting server response...");
        memset(&msg, 0, sizeof(msg));//clear the buffer
        bytesRead += recv(clientSd, (char*)&msg, sizeof(msg), 0);
        if(!strcmp(msg, "exit"))
        {
            Log("Server has quit the session");
            break;
        }
        Log("Server: " << msg);
    }
    gettimeofday(&end1, NULL);
    close(clientSd);
    Log("********Session********");
    Log("Bytes written: " << bytesWritten << 
    " Bytes read: " << bytesRead);
    Log("Elapsed time: " << (end1.tv_sec- start1.tv_sec) 
    << " secs");
    Log("Connection closed");
    return 0;    
}
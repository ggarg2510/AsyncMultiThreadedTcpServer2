#include "myserver.h"

MyServer::MyServer(QObject *parent):
    QTcpServer(parent)
{

}

void MyServer::StartServer()
{
    if(listen(QHostAddress::Any, 1234))
    {
        qDebug() << "Listening";
    }
    else
    {
        qDebug() << "Server couldn't started";
    }
}

void MyServer::incomingConnection(int handle)
{
    MyClient *client = new MyClient(this);
    client->SetSocket(handle);
}

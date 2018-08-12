#include "myclient.h"

MyClient::MyClient(QObject *parent) : QObject(parent)
{
    QThreadPool::globalInstance()->setMaxThreadCount(3);
}

void MyClient::SetSocket(int Descriptor)
{
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    socket->setSocketDescriptor(Descriptor);
    qDebug()<<Descriptor <<" client Connected";

}

void MyClient::connected()
{
    qDebug()<<"client Connected event";

}
void MyClient::disconnected()
{
    qDebug()<<"client Disconnected event";
}
void MyClient::readyRead()
{
    qDebug()<< socket->readAll();

    MyTask *myTask= new MyTask();
    myTask->setAutoDelete(true);
    connect(myTask, SIGNAL(Result(int)), this, SLOT(TaskResult(int)),Qt::QueuedConnection);
    QThreadPool::globalInstance()->start(myTask);
}
void MyClient::TaskResult(int Number)
{
    //
    QByteArray Buffer;
    Buffer.append("\r\nTask Result = ");
    Buffer.append(QString::number(Number));

    socket->write(Buffer);
//    qDebug() << Number;
}

#include "mytask.h"

MyTask::MyTask()
{

}

void MyTask::run()
{
    //time consumer

    qDebug() << "Task Started";
    int iNumber=0;
    for(int i = 0; i<10000000; i++)
    {/*
        for(int h = 0; h<10000000; h++)
        {

        }*/
         iNumber += i;
    }
    qDebug() << "Task Done";
    emit Result(iNumber);
}

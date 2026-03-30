#include <mqueue.h>
#include <cstring>
#include <iostream>
#include <unistd.h>

void receiver() {
    mqd_t mq = mq_open("/my_queue", O_CREAT | O_RDONLY, 0666, nullptr); //both recv and send create the queue (will be ignored if already exists) so that either can be launched first

    struct mq_attr attr;
    mq_getattr(mq, &attr);

    char* buffer = new char[attr.mq_msgsize];
    //mq_receive is a blocking function such that program will hang until it reads a value from the queue.
    mq_receive(mq, buffer, attr.mq_msgsize, nullptr); //for loop can be added but exit condition must be met, otherwise message queue will exist in system as a file.
                                                      //Not necessarily a bad thing to have the queue exist as a file in the OS that can be accessed at any time but must be done with caution.
    std::cout << "Received: " << buffer << std::endl;

    delete[] buffer;

    mq_close(mq);
    mq_unlink("/my_queue");
}

int main(int argc, char* argv[]){
    receiver();
    return 0;
}
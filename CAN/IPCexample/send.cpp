#include <mqueue.h>
#include <cstring>
#include <iostream>
#include <unistd.h>


int main(int argc, char* argv[]){
    mqd_t mq = mq_open("/my_queue", O_CREAT | O_WRONLY, 0666, nullptr); //both recv and send create the queue (will be ignored if already exists) so that either can be launched first

    const char* msg = "Hello via message queue!";
    mq_send(mq, msg, strlen(msg) + 1, 0);
    mq_close(mq);
    return 0;
}
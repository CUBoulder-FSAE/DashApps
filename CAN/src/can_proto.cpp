#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/socket.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define ConcurrentQueue moodycamel::ConcurrentQueue

int recieve_can(ConcurrentQueue<can_frame>& recieve_queue, int& sock){ //switch to message passing for IPC instead of concurrentqueue
    //have loop run and check for recieved can frames
    struct can_frame frame;

    ssize_t nbytes = read(sock, &frame, sizeof(struct can_frame));

    if (nbytes < 0) {
            perror("can raw socket read");
            return 1;
    }

    /* paranoid check ... */
    if (nbytes < sizeof(struct can_frame)) {
            fprintf(stderr, "read: incomplete CAN frame\n");
            return 1;
    }

    //push can frame to shared memory
}

void main(){
    ConcurrentQueue<can_frame> receive_queue;
    ConcurrentQueue<can_frame> send_queue;

   // pthread_t recieve_thread, send_thread;

    //define socket
    sockaddr_can addr;
    struct ifreq ifr;    
    int sock = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    strcpy(ifr.ifr_name, "can0" );
    ioctl(sock, SIOCGIFINDEX, &ifr);
    //interface index must be 0 to recieve CAN frames from all CAN inputs
    memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    bind(sock, (struct sockaddr *)&addr, sizeof(addr));


    int one; //will be other thread handling can messages
    while(/*interupt*/ true){ //main loop will take data and format to send out as CAN frame

    }
}
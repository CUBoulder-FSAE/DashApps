#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <cstdint>
#include <zmq.hpp>
#include <iostream>

#define SOCKET_PATH "ipc:///tmp/buffdash"
#define print std::cout

int main(int argc, char* argv[]){
    //define can socket
    sockaddr_can can_addr;
    struct ifreq ifr;    
    int sock = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    strcpy(ifr.ifr_name, "vcan0" );

    ioctl(sock, SIOCGIFINDEX, &ifr);
    //interface index must be 0 to recieve CAN frames from all CAN inputs
    can_addr.can_family = AF_CAN;
    can_addr.can_ifindex = ifr.ifr_ifindex;
    bind(sock, (struct sockaddr *)&can_addr, sizeof(can_addr));
//==============================================================
    zmq::context_t context{1};
    zmq::socket_t socket{context, zmq::socket_type::pub};
    socket.bind(SOCKET_PATH);

    while(/*interupt*/ true){ //main loop will take data and format to send out as CAN frame
        struct can_frame frame;

        ssize_t nbytes = read(sock, &frame, sizeof(struct can_frame));

        if (nbytes < 0) {
                perror("can raw socket read");
                continue;
        }

        // paranoid check
        if (nbytes < sizeof(struct can_frame)) {
                fprintf(stderr, "read: incomplete CAN frame\n");
                continue;
        }
        //below outputs the data encoded into the can frame (assuming the original data was standard int)
        // if desired, a specific can frame can be sent as a shutdown signal and break the while loop
        // for(int i=0;i<(int)frame.len;i++){
        //     print<<(int)frame.data[i]<<" ";
        // }
        // print<<std::endl;
        socket.send(zmq::buffer(&frame, sizeof(frame)), zmq::send_flags::none);
    }
    return 0;
}
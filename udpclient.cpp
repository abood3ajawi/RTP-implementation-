#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
#include <sys/types.h>
#include "CImg.h"
using namespace std;
using namespace cimg_library;
struct RTPPacket {
    uint8_t version;         // RTP version (2 bits)
    uint8_t padding;         // Padding (1 bit)
    uint8_t extension;       // Extension (1 bit)
    uint8_t CSRCCount;       // CSRC count (4 bits)
    uint8_t marker;          // Marker (1 bit)
    uint8_t payloadType;     // Payload type (7 bits)
    uint16_t sequenceNumber;    // Sequence number (16 bits)
    uint32_t timeStamp;      // Timestamp (32 bits)
    uint32_t SSRC;           // SSRC (32 bits)
    //there is no CSRC list
    //uint32_t CSRC[1];
    char payload[12288];
};
int main() {
    // Create a UDP socket
    cout<<"hello";
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    ssize_t bytes_received;
    CImgDisplay disp;
    // Set the server address and port
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(10000);

    // Send a message to the server
    sendto(sockfd, "start", 5, 0,
           (struct sockaddr *)&server_addr, sizeof(server_addr));

    socklen_t server_addr_len = sizeof(server_addr);


    char name[1024*100];
    char buffer[sizeof(struct RTPPacket)];
    for (int i = 1; i <= 500; i++) {

        sprintf(name, "testvid/image%03d.jpg", i);
        cout<<111111;
        struct RTPPacket packet;
        bytes_received = recvfrom(sockfd, &packet, sizeof(packet), 0,
                            (struct sockaddr *)&server_addr, &server_addr_len);

        if (bytes_received < 0) {
            break;
        }
        cout<<packet.version;
        std::ofstream image_file(name, std::ios::binary);


        image_file.write(packet.payload, sizeof(packet.payload));
        memset(buffer, 0, sizeof(struct RTPPacket));
        image_file.close();

    }
    for (int i = 1; i <=500 ; ++i) {
        sprintf(name, "testvid/image%03d.jpg", i);
        CImg<unsigned char> img(name);
        disp.display(img);
        usleep(30000);

    }
//    close(sockfd);
    return 0;
}

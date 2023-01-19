#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
#include <sys/types.h>


using namespace std;
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
    //uint32_t CSRC[1];        // CSRC list (32 bits each)
    char payload[12288] ;
};
int main() {
    // Create a UDP socket
    cout<<"start";
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    cout<<"hello";
    ssize_t bytes_sent;

    // Bind the socket to the server address and port
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(10000);
    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    cout<<"hello";

    // Wait for a client to send a message
        cout<<"hello1";
        char initialConnection[10];
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        ssize_t num_bytes = recvfrom(sockfd, initialConnection, sizeof(initialConnection), 0,
                                     (struct sockaddr *)&client_addr, &client_addr_len);
    char buffer[12288];
    // Read the image data and send it to the client
    for(int i=1;i<=500;i++) {
        ifstream fp;
        char name[1000];

        sprintf(name, "vid/image%03d.jpg", i);
        // sprintf(name1, "test/image%03d.jpg", i);

        fp.open(name, ios::binary);
        if (!fp) {
            cout<<"fiald";
            perror("fopen");
            return 1;
        }
        fp.read(buffer, sizeof(buffer));
        cout<<buffer;
        struct RTPPacket packet ;
        packet.version = 2;
        packet.padding = 0 ;
        packet.extension = 0;
        packet.extension = 0;
        packet.marker=0;
        packet.payloadType = 26,
        packet.sequenceNumber =static_cast<uint16_t>(i);
        packet.timeStamp = static_cast<uint32_t>(i);
        packet.SSRC = 0;
        //strcpy( packet.payload, buffer );
        for (int j = 0; j < 12288; ++j) {
            packet.payload[j] = buffer[j];
            cout<<buffer[j];
        }
        cout<<buffer<<endl;
        cout<<packet.payload<<endl;

        bytes_sent =sendto(sockfd, &packet, sizeof (packet), 0, (struct sockaddr *)&client_addr, client_addr_len);

        cout<<bytes_sent;
        memset(buffer, 0, sizeof(buffer));
        cout<<endl<<bytes_sent<<endl;
        fp.close();
    }


        close(sockfd);
    return 0;
}

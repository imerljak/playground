#include <UIPEthernet.h>

#define ONE_SECOND 1000

EthernetServer server = EthernetServer(80);

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);

    uint8_t mac[6] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
    IPAddress ip(192, 168, 1, 24);

    Ethernet.begin(mac, ip);

    server.begin();
}

void loop() {
    size_t size;

    // put your main code here, to run repeatedly
    if(EthernetClient client = server.available()) {
        Serial.println("Online..");

        while((size = client.available()) > 0) {
            uint8_t* msg = (uint8_t*)malloc(size);
            size = client.read(msg, size);
            Serial.write(msg, size);
            free(msg);
        }

        client.println("<h1>Hello world!</h1>");
        client.stop();
    } else {
        Serial.println("Offline...");
        delay(ONE_SECOND);
    }
}
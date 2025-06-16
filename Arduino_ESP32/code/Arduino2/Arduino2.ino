#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(4, 5); // CE, CSN pins

const byte address[6] = "00001";
char receivedData[32] = "";
char replyData[] = "Hello from ESP32!";

void setup() {
  Serial.begin(9600);
  Serial.println("ESP32 Receiver Starting...");

  if (!radio.begin()) {
    Serial.println("NRF24L01+ not responding");
    while (1);
  }

  radio.openWritingPipe(address); // for reply
  radio.openReadingPipe(1, address); // Pipe 1 for incoming data
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_2MBPS);

  radio.startListening();
}

void loop() {
  if (radio.available()) {
    radio.read(&receivedData, sizeof(receivedData));
    Serial.print("Received: ");
    Serial.println(receivedData);

    // Short delay to ensure Arduino switches to RX
    delay(10);

    radio.stopListening(); // Switch to transmit
    bool ok = radio.write(&replyData, sizeof(replyData));
    if (ok) {
      Serial.println("Replied successfully!");
    } else {
      Serial.println("Reply failed.");
    }
    radio.startListening(); // Back to listening
  }
}

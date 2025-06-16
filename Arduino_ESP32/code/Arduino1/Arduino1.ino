#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN pins

const byte address[6] = "00001";
char dataToSend[] = "Hello from Arduino!";
char replyData[32] = "";

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino Sender Starting...");

  if (!radio.begin()) {
    Serial.println("NRF24L01+ not responding");
    while (1);
  }

  radio.openWritingPipe(address);
  radio.openReadingPipe(1, address); // Pipe 1 for responses
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_2MBPS);

  radio.stopListening(); // Start in TX mode
}

void loop() {
  Serial.print("Sending: ");
  Serial.println(dataToSend);

  bool ok = radio.write(&dataToSend, sizeof(dataToSend));
  if (ok) {
    Serial.println("Sent successfully. Switching to receive mode.");

    radio.startListening(); // Listen for reply

    unsigned long startTime = millis();
    bool timeout = false;

    while (!radio.available()) {
      if (millis() - startTime > 2000) { // 2-second timeout
        timeout = true;
        break;
      }
    }

    if (timeout) {
      Serial.println("No reply, timeout.");
    } else {
      radio.read(&replyData, sizeof(replyData));
      Serial.print("Received reply: ");
      Serial.println(replyData);
    }

    radio.stopListening(); // Go back to transmit mode
  } else {
    Serial.println("Sending failed.");
  }

  delay(2000); // 2 seconds between cycles
}

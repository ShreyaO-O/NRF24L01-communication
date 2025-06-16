#include <SPI.h>
#include <RF24.h>
 
RF24 radio(9, 10);  // CE, CSN
 
const byte address[][6] = {"1Node", "2Node"}; // Two pipes
 
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setRetries(15, 15);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(76);
  radio.enableDynamicPayloads();
}
 
void loop() {
  // --- Send Message to Pi ---
  radio.openWritingPipe(address[0]);
  radio.stopListening();
 
  const char text[] = "Hello RPi!";
  bool result = radio.write(&text, sizeof(text));
  if (result)
    Serial.println("Sent to Pi: Hello RPi!");
  else
    Serial.println("Send failed");
 
  delay(10); // Wait before listening
 
  // --- Wait for Response from Pi ---
  radio.openReadingPipe(1, address[1]);
  radio.startListening();
 
  unsigned long start_time = millis();
  bool timeout = false;
 
  while (!radio.available()) {
    if (millis() - start_time > 1000) {
      timeout = true;
      break;
    }
  }
 
    if (!timeout) {
    char received[32] = {0};  // Clear buffer
    radio.read(&received, radio.getDynamicPayloadSize());  // Read only what's received
    Serial.print("Received from Pi: ");
    Serial.println(received);
  } else {
    Serial.println("No response from Pi.");
  }
 
  delay(2000);
}

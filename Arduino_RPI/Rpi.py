
from RF24 import RF24, RF24_PA_LOW, RF24_1MBPS
import time
 
radio = RF24(22, 0)  # CE=GPIO22, CSN=SPI0.0
 
pipes = [b"1Node", b"2Node"]
 
if not radio.begin():
    print("\nNRF init failed")
    exit(1)
 
radio.setPALevel(RF24_PA_LOW)
radio.setDataRate(RF24_1MBPS)
radio.setChannel(76)
radio.enableDynamicPayloads()
 
radio.openReadingPipe(1, pipes[0])
radio.openWritingPipe(pipes[1])
radio.startListening()
 
print("\nListening for NRF24L01 messages...")
 
while True:
    if radio.available():
        received_payload = radio.read(32)
        message = received_payload.decode('utf-8', errors='ignore')
        print("\nReceived from Arduino:", message)
 
        # Respond back
        radio.stopListening()
        response = "\nAck from Pi"
        radio.write(response.encode('utf-8'))
        print("\nSent:", response)
        radio.startListening()
 
    time.sleep(0.1)

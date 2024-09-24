#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to enable it
#endif

BluetoothSerial SerialBT;

// Define the touch sensor pin
#define TOUCH_PIN 4  // Using touch sensor pin T0 (GPIO 4)

void setup() {
  Serial.begin(115200); // Start serial communication at 115200 baud
  SerialBT.begin("ESP32test"); // Initialize Bluetooth with the name "ESP32test"
  Serial.println("Bluetooth device is ready to pair.");
}

void loop() {
  // Read the touch sensor value
 if (SerialBT.available()) {
  char incomingChar[100];
  int len = SerialBT.readBytesUntil('\n', incomingChar, sizeof(incomingChar) - 1);
  incomingChar[len] = '\0';       // Read the incoming character
  Serial.print("Received via Bluetooth: ");  // Print to serial monitor
  Serial.println(incomingChar);
}
/*else if (Serial.available())
{
   char outgoingChar = Serial.read(); // Read from serial monitor
    SerialBT.write(outgoingChar); // Send the data to the phone via Bluetooth
   Serial.print("Sent via Bluetooth: "); 
    Serial.println(outgoingChar);
}*/

else
{
  int touchValue = touchRead(TOUCH_PIN);

// Send the touch sensor value via Bluetooth to the connected mobile device
SerialBT.print("Touch sensor value: ");
SerialBT.println(touchValue);

// Also print it to the serial monitor for debugging
Serial.print("Touch sensor value: ");
Serial.println(touchValue);

// Add a small delay for a readable output
delay(1000);  // 1-second delay}

}
}


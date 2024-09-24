#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to enable it
#endif

BluetoothSerial SerialBT;//creatint instance of bluethoothserial

// Define the touch sensor pin
#define TOUCH_PIN 4  // Using touch sensor pin T0 (GPIO 4)

char incomingChar[100];

void read_funtion();
void write_funtion();
void read_touchSensor_value();

void setup() {
  Serial.begin(115200); // Start serial communication at 115200 baud
  SerialBT.begin("ESP32test"); // Initialize Bluetooth with the name "ESP32test"
  Serial.println("Bluetooth device is ready to pair.");
}
void loop() {
  if (SerialBT.available()) {
    read_funtion();
    write_funtion();
  } else {
    read_touchSensor_value();
  }
}
void read_funtion() {

  int len = SerialBT.readBytesUntil('\n', incomingChar, sizeof(incomingChar) - 1);
  incomingChar[len] = '\0';  // Read the incoming character
}
void write_funtion()  //printing the received msg from mobile to serial monitor
{
  Serial.print("Received via Bluetooth from mobile: ");  // Print to serial monitor
  Serial.println(incomingChar);
}
void read_touchSensor_value() {
  int touchValue = touchRead(TOUCH_PIN);
  SerialBT.print("Touch sensor value: ");  // Send the touch sensor value via Bluetooth to the connected mobile device
  SerialBT.println(touchValue);
  Serial.print("Touch sensor value: ");  // Also print it to the serial monitor for debugging
  Serial.println(touchValue);
  // Add a small delay for a readable output
  delay(1000);  // 1-second delay}
}

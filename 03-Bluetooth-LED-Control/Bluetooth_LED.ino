#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// GPIO pins
#define LIVING_LIGHT 25
#define FAN 26
#define BEDROOM_LIGHT 27

void setup() {

  Serial.begin(115200);

  // Configure pins
  pinMode(LIVING_LIGHT, OUTPUT);
  pinMode(FAN, OUTPUT);
  pinMode(BEDROOM_LIGHT, OUTPUT);

  // Turn everything OFF initially
  digitalWrite(LIVING_LIGHT, LOW);
  digitalWrite(FAN, LOW);
  digitalWrite(BEDROOM_LIGHT, LOW);

  // Start Bluetooth
  SerialBT.begin("ESP32_Home_Automation");

  Serial.println("================================");
  Serial.println(" ESP32 HOME AUTOMATION SYSTEM");
  Serial.println("================================");
  Serial.println("Bluetooth Device:");
  Serial.println("ESP32_Home_Automation");
  Serial.println("System Ready!");
}

void loop() {

  if (SerialBT.available()) {

    String command = SerialBT.readStringUntil('\n');

    command.trim();

    Serial.print("Command received: ");
    Serial.println(command);


    // -------------------------
    // LIVING ROOM LIGHT
    // -------------------------

    if (command == "LIGHT_ON") {

      digitalWrite(LIVING_LIGHT, HIGH);

      SerialBT.println("Living Room Light: ON");
      Serial.println("Living Room Light: ON");
    }

    else if (command == "LIGHT_OFF") {

      digitalWrite(LIVING_LIGHT, LOW);

      SerialBT.println("Living Room Light: OFF");
      Serial.println("Living Room Light: OFF");
    }


    // -------------------------
    // FAN
    // -------------------------

    else if (command == "FAN_ON") {

      digitalWrite(FAN, HIGH);

      SerialBT.println("Fan: ON");
      Serial.println("Fan: ON");
    }

    else if (command == "FAN_OFF") {

      digitalWrite(FAN, LOW);

      SerialBT.println("Fan: OFF");
      Serial.println("Fan: OFF");
    }


    // -------------------------
    // BEDROOM LIGHT
    // -------------------------

    else if (command == "BEDROOM_ON") {

      digitalWrite(BEDROOM_LIGHT, HIGH);

      SerialBT.println("Bedroom Light: ON");
      Serial.println("Bedroom Light: ON");
    }

    else if (command == "BEDROOM_OFF") {

      digitalWrite(BEDROOM_LIGHT, LOW);

      SerialBT.println("Bedroom Light: OFF");
      Serial.println("Bedroom Light: OFF");
    }


    // -------------------------
    // ALL DEVICES
    // -------------------------

    else if (command == "ALL_ON") {

      digitalWrite(LIVING_LIGHT, HIGH);
      digitalWrite(FAN, HIGH);
      digitalWrite(BEDROOM_LIGHT, HIGH);

      SerialBT.println("All Devices: ON");
      Serial.println("All Devices: ON");
    }

    else if (command == "ALL_OFF") {

      digitalWrite(LIVING_LIGHT, LOW);
      digitalWrite(FAN, LOW);
      digitalWrite(BEDROOM_LIGHT, LOW);

      SerialBT.println("All Devices: OFF");
      Serial.println("All Devices: OFF");
    }


    // -------------------------
    // UNKNOWN COMMAND
    // -------------------------

    else {

      SerialBT.println("Unknown command!");
      Serial.println("Unknown command!");
    }
  }
}
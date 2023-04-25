#define voltageSenorPinBatt A0
#define currentSensorPinBatt A1
#define voltageSenorPinSolar A2
#define DIGITAL_IN_PIN 11
#define DIGITAL_IN_PIN2 13
#define BUTTON_PIN 12

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoMqttClient.h>
#include <SPI.h>
#include <WiFiNINA.h>

char ssid[] = "RONG-404";
char pass[] = "1234567890";   // network password (use for WPA, or use as key for WEP)

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "192.168.2.2";
int port            = 1883;
const char topic[]  = "BattVolt";
const char topic1[] = "BattAmp";
const char topic2[] = "SolarVolt";
const char topic3[] = "EnableButton";
bool enable         = false;
bool autoS          = true;

//set interval for sending messages (milliseconds)
const long interval = 2 * 1000;
unsigned long previousMillis = 0;
int count = 0;
const float SENSOR_SENSITIVITY = 0.185; // replace with the sensitivity of the sensor being used
const float TIME_INTERVAL = 1000; // replace with the time interval between readings, in milliseconds

// Set the LCD address to 0x27 in PCF8574 by NXP and Set to 0x3F in PCF8574A by Ti
LiquidCrystal_I2C lcd(0x27, 16, 3);

//icon for battery
byte battery[8] = {
  0b01110,
  0b11011,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b11111
};

// icon for power
byte energy[8] = {
  0b00010,
  0b00100,
  0b01000,
  0b11111,
  0b00010,
  0b00100,
  0b01000,
  0b00000
};

// icon for battery charge
byte charge[8] = {
  0b01010,
  0b11111,
  0b10001,
  0b10001,
  0b10001,
  0b01110,
  0b00100,
  0b00100,
};

byte not_charge[8] = {
  0b00000,
  0b10001,
  0b01010,
  0b00100,
  0b01010,
  0b10001,
  0b00000,
  0b00000,
};


void setup() {
    // Setup Serial Monitor
    Serial.begin(9600);
    
    lcd.begin();
    lcd.createChar(0, battery);
    lcd.createChar(1, charge);
    lcd.createChar(2, not_charge);
    lcd.createChar(3, energy);
    lcd.home();

    // attempt to connect to Wifi network:
    lcd.setCursor(0, 0);
    lcd.print("Connecting: ");
    lcd.setCursor(12, 0);
    lcd.print(ssid);

    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
        lcd.setCursor(0, 1);
        lcd.print("Connection Failed!");
        Serial.print(".");
        delay(5000);
    }
    
    lcd.setCursor(0, 1);
    lcd.print("You're connected to the network");

    Serial.println("You're connected to the network");
    Serial.println();

    lcd.setCursor(0, 0);
    lcd.print("Connecting to the MQTT broker: ");
    lcd.print(broker);

    Serial.print("Attempting to connect to the MQTT broker: ");
    Serial.println(broker);

    while (!mqttClient.connect(broker, port)) {
        lcd.setCursor(0, 1);
        lcd.print("MQTT connection failed!");
        Serial.print("MQTT connection failed! Error code = ");
        Serial.println(mqttClient.connectError());
    }

    lcd.setCursor(0, 1);
    lcd.print("You're connected to the MQTT broker!");
    Serial.println("You're connected to the MQTT broker!");
    Serial.println();

    pinMode(DIGITAL_IN_PIN, OUTPUT);
    pinMode(DIGITAL_IN_PIN2, OUTPUT);

    mqttClient.onMessage(onMqttMessage);
    mqttClient.subscribe(topic3);

    Serial.print("Subscribing to topic: ");
    Serial.println(topic3);
    Serial.println();

    // clear the LCD
    lcd.setCursor(0, 0);
    lcd.print("                                               ");
    lcd.setCursor(0, 1);
    lcd.print("                                               ");
    lcd.setCursor(0, 2);
    lcd.print("                                               ");
    lcd.setCursor(0, 3);
    lcd.print("                                               ");
}

float votlMeasure(int Pin) {
    float R1 = 30000.0;
    float R2 = 7500.0;
    float adc_voltage = 0.0;
    float ref_voltage = 5.0;
    int adc_value = 0;

    adc_value = analogRead(Pin);  
    adc_voltage  = (adc_value * ref_voltage) / 1024.0; 

    return adc_voltage / (R2/(R1+R2)); 
}

float measureEnergy(int pin) {
  float energy = 0.0;
  for (int i = 0; i < 10; i++) {
    // Read voltage from sensor and convert to current using sensor sensitivity
    float voltage = analogRead(pin) * (5.0 / 1024.0);
    float current = (voltage / SENSOR_SENSITIVITY) - 2.5;
    
    // Calculate energy consumption and add to total energy
    energy += current * voltage * (TIME_INTERVAL / 3600.0);
    
    // Wait for next measurement
    delay(1000);
  }
  return energy;
}

void loop() {
    mqttClient.poll();

    float battVoltSens = votlMeasure(voltageSenorPinBatt);
    float battAmpConsumption = (measureEnergy(currentSensorPinBatt)) < 0 ? 0.0 : measureEnergy(currentSensorPinBatt);
    float solarVoltSens = votlMeasure(voltageSenorPinSolar);

    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        // save the last time a message was sent
        previousMillis = currentMillis;

        mqttClient.beginMessage(topic);
        mqttClient.print(battVoltSens);
        mqttClient.endMessage();

        mqttClient.beginMessage(topic1);
        mqttClient.print(battAmpConsumption);
        mqttClient.endMessage();

        mqttClient.beginMessage(topic2);
        mqttClient.print(solarVoltSens);
        mqttClient.endMessage();
    } 


    if(autoS == false) {
        if(enable) {
            digitalWrite(DIGITAL_IN_PIN , HIGH);
        } else {
            digitalWrite(DIGITAL_IN_PIN , LOW);
        }
    } else {
        if (solarVoltSens > 11.0) {
            lcd.setCursor(0, 0);
            lcd.print("Charge State: ");
            lcd.setCursor(15, 0);
            lcd.write(1);
            digitalWrite(DIGITAL_IN_PIN , HIGH);

        } else {
            lcd.setCursor(0, 0);
            lcd.print("Charge State: ");
            lcd.setCursor(15, 0);
            lcd.write(2);
            digitalWrite(DIGITAL_IN_PIN , LOW);
        }
    }

    if(solarVoltSens > 14 && solarVoltSens >= 5) {
        digitalWrite(DIGITAL_IN_PIN2, HIGH);
    } else {
        digitalWrite(DIGITAL_IN_PIN2, LOW);
    }

    if (battVoltSens < 0){
        battVoltSens = 0;
    }

    lcd.setCursor(0, 1);
    lcd.print("Battary: ");
    lcd.setCursor(15, 1);
    lcd.print((int(battVoltSens) * 100 ) / 14);
    lcd.print("%");

    // lcd.setCursor(0, 2);
    // lcd.print("Power Amp: ");
    // lcd.setCursor(15, 2);
    // lcd.print(int(battAmpConsumption));
    // lcd.print("W");

    if (solarVoltSens < 0){
        solarVoltSens = 0;
    }

    lcd.setCursor(0, 2);
    lcd.print("Solar: ");
    lcd.setCursor(15, 2);
    lcd.print((int(solarVoltSens) * 100 ) / 20);
    lcd.print("%");


    }

void onMqttMessage(int messageSize) {
    char message[messageSize + 1];
    int index = 0;
    
    // read the message into a buffer
    while (mqttClient.available()) {
        message[index] = mqttClient.read();
        index++;
    }
    
    // add a null terminator to the end of the buffer
    message[messageSize] = '\0';

    // print the complete message
    Serial.print("Received message: ");
    Serial.println(message);

    if (strstr(message, "on") != NULL) {
        Serial.println("The message contains the word 'on'");
        autoS = false;
        enable = true;
    } else if (strstr(message, "off") != NULL) {
        Serial.println("The message contains the word 'off'");
        autoS = false;
        enable = false;
    } else if (strstr(message, "auto") != NULL) {
        Serial.println("The message contains the word 'auto'");
        autoS = true;
        enable = false;
    } else {
        Serial.println("The message does not contain any of the keywords");
    }
}
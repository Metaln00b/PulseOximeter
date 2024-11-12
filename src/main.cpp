#include <Arduino.h>
#include <HardwareSerial.h>

#define RX_PIN 16
#define TX_PIN 17
#define MSG_LENGTH 17

HardwareSerial MySerial(2);
void parseAndPrint(uint8_t buffer[]);

void setup()
{
    Serial.begin(115200);
    MySerial.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);
}

void loop()
{
    uint8_t buffer[MSG_LENGTH];
    
    if (MySerial.available() > 0)
    {
        MySerial.readBytes(buffer, MSG_LENGTH);
        parseAndPrint(buffer);
    }
    yield();
}

void parseAndPrint(uint8_t buffer[])
{
    if (buffer[0] == 0xFF && 
        buffer[1] == 0xFF &&
        buffer[8] == 0x00 &&
        buffer[11] == 0x00 &&
        buffer[12] == 0x00 &&
        buffer[13] == 0x00 &&
        buffer[14] == 0x00)
    {
        // for (int i = 0; i < MSG_LENGTH; i++)
        // {
        //     if (i == 0) { Serial.print("RAW:"); }
        //     Serial.print(buffer[i], HEX);
        //     Serial.print(" ");
        //     if (i == MSG_LENGTH - 1) { Serial.println(); }
        // }
        uint8_t data1 = buffer[3];
        uint8_t data2 = buffer[4];
        uint8_t data3 = buffer[6];
        uint8_t data4 = buffer[7];
        uint8_t spo2 = buffer[15];
        uint8_t pulse = buffer[16];

        Serial.print("SpO²:");
        Serial.print(spo2);
        Serial.print(",");
        Serial.print("PRbpm:");
        Serial.print(pulse);
        Serial.print(",");
        Serial.print("Data1:");
        Serial.print(data1);
        Serial.print(",");
        Serial.print("Data2:");
        Serial.print(data2);
        Serial.print(",");
        Serial.print("Data3:");
        Serial.print(data3);
        Serial.print(",");
        Serial.print("Data4:");
        Serial.print(data4);
        Serial.println("");
    }
}
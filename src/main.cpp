#include <Arduino.h>
#include <arduino_secrets.h>
#include <MQTT.h>
#include <WiFi.h>

#include <ArduinoJson.h>

// The MQTT topics that this device should publish/subscribe
#define AWS_IOT_PUBLISH_TOPIC "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"

MQTTClient client = MQTTClient(256);

bool connectWifi()
{

    //char ssid[] = WIFI_SSID;   // your network SSID (name)
    //char pass[] = WIFI_PASSWORD;   // your network password (use for WPA, or use as key for WEP)
    int status = WL_IDLE_STATUS; // the WiFi radio's status

    // check for the WiFi module:
    if (WiFi.status() == WL_NO_MODULE)
    {
        Serial.println("Communication with WiFi module failed!");
        // don't continue
        while (true)
            ;
    }

    String fv = WiFi.firmwareVersion();
    Serial.print("Wifi Firmware: ");
    Serial.println(fv);

    if (fv < WIFI_FIRMWARE_LATEST_VERSION)
    {
        Serial.print("Expected Firnwmare version:");
        Serial.println(WIFI_FIRMWARE_LATEST_VERSION);
        Serial.println("Please upgrade the firmware");
    }

    // attempt to connect to WiFi network:
    while (status != WL_CONNECTED)
    {
        Serial.print("Attempting to connect to WPA SSID: ");
        Serial.println(WIFI_SSID);
        // Connect to WPA/WPA2 network:
        status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    }
    return true;
}

void printMacAddress(byte mac[])
{
    for (int i = 5; i >= 0; i--)
    {
        if (mac[i] < 16)
        {
            Serial.print("0");
        }
        Serial.print(mac[i], HEX);
        if (i > 0)
        {
            Serial.print(":");
        }
    }
    Serial.println();
}

void printCurrentWifi()
{
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print the MAC address of the router you're attached to:
    byte bssid[6];
    WiFi.BSSID(bssid);
    Serial.print("BSSID: ");
    printMacAddress(bssid);

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.println(rssi);

    // print the encryption type:
    byte encryption = WiFi.encryptionType();
    Serial.print("Encryption Type:");
    Serial.println(encryption, HEX);
    Serial.println();
}

void setup()
{

    Serial.begin(9600);
    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    connectWifi();
}

void loop()
{
    delay(1000);
    Serial.println("Wifi status: ");
    printCurrentWifi();
}
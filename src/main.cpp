#include <Arduino.h>

#include <WiFi.h>

const char* ssid = "Sbr";
const char* password = "sa222222";

WiFiServer server(5000);
WiFiClient client;

String message = "";

void setup() {
    Serial.begin(115200);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    Serial.println(WiFi.localIP());
    pinMode(15, OUTPUT);

    server.begin();
}

void loop() {

    if (!client || !client.connected()) {
        client = server.available();
    }

    if (client && client.connected()) {

        while (client.available()) {
            char c = client.read();

            if (c == '\n') {
                message.trim();

                Serial.println(message);

                // Process command
                if (message == "ON") {
                    client.println("OUTPUT ON");
                    digitalWrite(15, HIGH);

                }
                else if (message == "OFF") {
                    client.println("OUTPUT OFF");
                    digitalWrite(15, LOW);

                }
                else {
                    client.println("UNKNOWN COMMAND");
                }

                message = "";
            }
            else {
                message += c;
            }
        }
    }
}
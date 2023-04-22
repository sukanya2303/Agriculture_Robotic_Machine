// WeMos D1 Thingspeak

// shraddhavp253@gmail.com
// robot@23
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

#include <ESP8266WiFi.h>

// replace with your channel’s thingspeak API key and your SSID and password
String apiKey = "UX90ZLWP4EID4ZX1";
const char* server = "api.thingspeak.com";

const char* ssid = "Kokaniii";
const char* password = "123456789";

int data_flag = 0;

WiFiClient client;

void setup()
{
  lcd.begin();
  // turn on LCD backlight
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("  Agricultural  ");
  lcd.setCursor(0, 1);
  lcd.print("Robotic  Machine");
  delay(5000);
  lcd.setCursor(0, 0);
  lcd.print("   Project by   ");
  lcd.setCursor(0, 1);
  lcd.print(" Sukanya Kokani ");
  delay(5000);
  lcd.setCursor(0, 0);
  lcd.print(" Shraddha Patil ");
  lcd.setCursor(0, 1);
  lcd.print("  Kirti Dhotre  ");
  delay(5000);
  lcd.clear();

  Serial.begin(115200);
  delay(10);
  WiFi.begin(ssid, password);
  //  Serial.println();
  //  Serial.println();
  //  Serial.print("Connecting to ");
  //  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    //    Serial.print(".");
  }
  //  Serial.println("");
  //  Serial.println("WiFi connected");
  lcd.setCursor(0, 0);
  lcd.print(" WiFi connected ");
  lcd.setCursor(0, 1);
  lcd.print(ssid);
  delay(5000);
}

void loop()
{
  int sensorValue = analogRead(A0);
  int SenP = map(sensorValue, 0, 1023, 0, 100);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Soil  Moisture ");
  lcd.setCursor(0, 1);
  lcd.print(sensorValue);
  lcd.setCursor(6, 1);
  lcd.print("| ");
  lcd.print(SenP);lcd.print("%");
  //  Serial.print(sensorValue);
  //  Serial.println(SenP);
  //  Serial.println();
  delay(10);

  if (client.connect(server, 80))
  {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(sensorValue);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
  }
  client.stop();
  // thingspeak needs at least a 15 sec delay between updates
  // 20 seconds to be safe
  delay(20000);
} 

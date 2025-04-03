#include <SPI.h>
#include <MFRC522.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN  D8  //D2
#define RST_PIN D3  //D1
#define led D4

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD address 0x3F, 16x2 display

/* Set these to your desired credentials. */
const char *ssid = "INFINITY°_5GHz";
const char *password = "Sarat3214";
const char* device_token  = "80ab5096e20a57dc";
//************************************************************************
String URL = "https://rfid.pingayush.in/getdata.php"; // Server URL
String getData, Link;
String OldCardID = "";
unsigned long previousMillis = 0;
//************************************************************************
void setup() {
  delay(1000);
  Serial.begin(115200);
  SPI.begin();  // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
  //---------------------------------------------
  connectToWiFi();

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  pinMode(led, OUTPUT);
  
  // Welcome Message
  lcd.setCursor(0, 0);
  lcd.print("Welcome to RFID");
  lcd.setCursor(0, 1);
  lcd.print("Attendance System");
  delay(2000);
  lcd.clear();
}

//************************************************************************
void loop() {
  // Reconnect if Wi-Fi is disconnected
  if (!WiFi.isConnected()) {
    connectToWiFi();
  }

  // Reset OldCardID every 15 seconds
  if (millis() - previousMillis >= 15000) {
    previousMillis = millis();
    OldCardID = "";
  }
  
  lcd.setCursor(0, 0);
  lcd.print("Scan your card...");
  delay(50);

  // Look for a new card
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  
  // Select the card
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Read Card ID
  String CardID = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    CardID += mfrc522.uid.uidByte[i];
  }

  if (CardID == OldCardID) {
    return;
  } else {
    OldCardID = CardID;
  }

  // Clear LCD and display "Processing..."
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Processing...");
  delay(1000);

  // Send the scanned Card ID
  SendCardID(CardID);
  delay(1000);
}

//************send the Card UID to the website*************
void SendCardID(String Card_uid) {
  Serial.println("Sending the Card ID");
  
  if (WiFi.isConnected()) {
    HTTPClient http;
    WiFiClientSecure client;
    client.setInsecure(); // Bypass SSL certificate verification

    // Prepare GET request
    getData = "?card_uid=" + String(Card_uid) + "&device_token=" + String(device_token);
    Link = URL + getData;
    http.begin(client, Link);

    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS); // Follow redirects
    
    int httpCode = http.GET();
    String payload = http.getString();

    Serial.println(httpCode);   // Print HTTP return code
    Serial.println(Card_uid);   // Print Card ID
    Serial.println(payload);    // Print response

    lcd.clear();

    if (httpCode == 200) {
      if (payload.substring(0, 5) == "login") {
        String user_name = payload.substring(5);
        lcd.setCursor(0, 0);
        lcd.print(user_name);
        digitalWrite(led, HIGH);
        lcd.setCursor(0, 1);
        lcd.print("Welcome, Enter!");
        delay(200);
        digitalWrite(led, LOW);
        delay(200);
        digitalWrite(led, HIGH);
        delay(200);
        digitalWrite(led, LOW);
        delay(200);
        digitalWrite(led, HIGH);
        delay(200);
        digitalWrite(led, LOW);
        delay(200);
        digitalWrite(led, HIGH);
        delay(200);
        digitalWrite(led, LOW);
        delay(200);
      }
      else if (payload.substring(0, 6) == "logout") {
        String user_name = payload.substring(6);
        lcd.setCursor(0, 0);
        lcd.print(user_name);
        lcd.setCursor(0, 1);
        lcd.print("Logout, Have a Nice Day!");
      }
      else {
        lcd.setCursor(0, 0);
        lcd.print("Unknown Card");
      }
    } else {
      lcd.setCursor(0, 0);
      lcd.print("Error Sending ID");
    }
    
    delay(2000);
    lcd.clear();
  }
}

//********************connect to the WiFi******************
void connectToWiFi() {
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConnected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  delay(1000);
}

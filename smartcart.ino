#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
const char* ssid = "Gokul";
const char* password = "gokulaprasad2004";
 
FirebaseData firebaseData;
FirebaseAuth firebaseAuth;
FirebaseConfig firebaseConfig;
 
#define FIREBASE_HOST "https://smart-cart-189d3-default-rtdb.firebaseio.com/"
#define FIREBASE_API_KEY "AIzaSyAzPGTKuJ4bzN6Ihvz9q5D1GHjJpOZE5yY"
#define FIREBASE_USER_EMAIL "test@gmail.com"
#define FIREBASE_USER_PASS "test@123"
 
#define SS_PIN D4
#define RST_PIN D3
 
MFRC522 rfid(SS_PIN, RST_PIN);
 
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire,
OLED_RESET);
 
const unsigned long idleTimeThreshold = 5000;
unsigned long lastOperationTime = 0;
 
void displayIdleScreen() {
display.clearDisplay();
display.setTextSize(2); // Larger text
display.setTextColor(WHITE);
display.setCursor(0, (SCREEN_HEIGHT - 16) / 2); 
display.println("CartSense");
display.display();
}
 
void setup() {
Serial.begin(115200);

 if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
Serial.println(F("SSD1306 allocation failed"));
for (;;);
}
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(0, 0);
display.println("Initializing...");
display.display();
 
WiFi.begin(ssid, password);
Serial.print("Connecting to WiFi...");
display.println("Connecting WiFi...");
display.display();
 
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("\nWiFi connected!");
display.clearDisplay();
display.setCursor(0, 0);
display.println("WiFi Connected!");
display.display();
 
firebaseConfig.database_url = FIREBASE_HOST;
firebaseConfig.api_key = FIREBASE_API_KEY;
 
firebaseAuth.user.email = FIREBASE_USER_EMAIL;
firebaseAuth.user.password = FIREBASE_USER_PASS;
 
Firebase.begin(&firebaseConfig, &firebaseAuth);
Firebase.reconnectWiFi(true);
 
 
SPI.begin();
rfid.PCD_Init();
 
display.println("Setup Completed!");
display.display();
delay(2000);
lastOperationTime = millis(); 
}
void loop() {
if (millis() - lastOperationTime > idleTimeThreshold) {
displayIdleScreen();
}
 
if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
return;
}
lastOperationTime = millis(); // Reset idle timer
 
String rfidUID = "";
for (byte i = 0; i < rfid.uid.size; i++) {
rfidUID += String(rfid.uid.uidByte[i], HEX);
}
 
Serial.print("Scanned RFID: ");
Serial.println(rfidUID);
 
display.clearDisplay();
display.setTextSize(1); // Smaller text
display.setCursor(0, 0);
display.println("RFID Scanned:");
display.println(rfidUID);
display.display();
 
String productPath = "/Products/" + rfidUID;
 
if (Firebase.get(firebaseData, productPath)) {
if (firebaseData.dataType() == "json") {
Serial.println("Product found!");
Serial.println(firebaseData.jsonString());
 
display.println(firebaseData.jsonString());
display.display();
} else {
Serial.println("No product data found.");
display.println("No Data Found!");
display.display();
}
} else {
Serial.println("Product Not Found");
display.println("Product Not Found");
display.display();
}
String scannedRFIDPath = "/ScannedRFID/" + rfidUID;
if (Firebase.set(firebaseData, scannedRFIDPath, "Scanned")) {
Serial.println("RFID stored successfully.");
display.println("RFID Stored!");
display.display();
} else {
Serial.println("Failed to store RFID.");
display.println("Store Failed!");
display.display();
}
delay(2000);
}

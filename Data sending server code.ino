#include "Nextion.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ArduinoJson.h>

// Declare your Nextion button objects for page 1
NexButton b0 = NexButton(0, 1, "b0");
NexButton b1 = NexButton(0, 2, "b1");
NexButton b2 = NexButton(0, 3, "b2");
NexButton b3 = NexButton(0, 4, "b3");
NexButton b4 = NexButton(0, 5, "b4");
NexButton b5 = NexButton(0, 6, "b5");
NexButton b6 = NexButton(0, 7, "b6");
NexButton b7 = NexButton(0, 8, "b7");
NexButton b8 = NexButton(0, 9, "b8");
NexButton b9 = NexButton(0, 10, "b9"); 
NexButton b10 = NexButton(0, 11, "b10"); // OK Button
NexButton b11 = NexButton(0, 12, "b11"); // backspace
NexButton b12 = NexButton(0, 15, "b12"); // delete entered value
NexButton b13 = NexButton(0, 21, "b13"); // backslash

NexTouch *nex_listen_list[] = {
  &b0, &b1, &b2, &b3, &b4, &b5, &b6, &b7, &b8, &b9, 
  &b10, &b11, &b12, &b13, 
  NULL
};

// Variable to store the entered number
String enteredNumber = "";

// Callback functions for button press events
void b0PopCallback(void *ptr) { enteredNumber += "1"; Serial.println("Button 1 pressed"); }
void b1PopCallback(void *ptr) { enteredNumber += "2"; Serial.println("Button 2 pressed"); }
void b2PopCallback(void *ptr) { enteredNumber += "3"; Serial.println("Button 3 pressed"); }
void b3PopCallback(void *ptr) { enteredNumber += "4"; Serial.println("Button 4 pressed"); }
void b4PopCallback(void *ptr) { enteredNumber += "5"; Serial.println("Button 5 pressed"); }
void b5PopCallback(void *ptr) { enteredNumber += "6"; Serial.println("Button 6 pressed"); }
void b6PopCallback(void *ptr) { enteredNumber += "7"; Serial.println("Button 7 pressed"); }
void b7PopCallback(void *ptr) { enteredNumber += "8"; Serial.println("Button 8 pressed"); }
void b8PopCallback(void *ptr) { enteredNumber += "9"; Serial.println("Button 9 pressed"); }
void b9PopCallback(void *ptr) { enteredNumber += "0"; Serial.println("Button 0 pressed"); }
void b10PopCallback(void *ptr) {  // OK Button
  Serial.print("OK Button pressed, entered number: "); 
  Serial.println(enteredNumber); 
  String formattedDate = getFormattedDateTime();
  sendDataToAPI(enteredNumber, formattedDate); 
  enteredNumber = ""; // Reset entered number after processing
}
void b11PopCallback(void *ptr) { // Backspace
  if (enteredNumber.length() > 0) {
    enteredNumber.remove(enteredNumber.length() - 1);
    Serial.print("Backspace pressed, new number: ");
    Serial.println(enteredNumber);
  }
}
void b12PopCallback(void *ptr) { // Delete entered value
  enteredNumber = "";
  Serial.println("Delete pressed, entered number cleared");
}
void b13PopCallback(void *ptr) { Serial.println("Button b13 pressed"); } // Backslash (Functionality to be defined)

// Function to process the entered number
void processEnteredNumber(String number) {
  // Implement your function to handle the entered number here
  Serial.print("Processing number: ");
  Serial.println(number);
}

// WiFi credentials
const char* ssid = "Elconics";
const char* password = "Elconics@123";

// API endpoint
const char* serverName = "https://api.dev.antzsystems.com/api/v1/iot/update/egg/weight";

// NTP client settings
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 0, 60000); // Update every minute

String getFormattedDateTime() {
  time_t rawTime = timeClient.getEpochTime();
  struct tm *timeInfo;
  char buffer[30];
  
  timeInfo = gmtime(&rawTime); // Get the time in UTC
  strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%SZ", timeInfo); // Format time as ISO 8601
  
  return String(buffer);
}

void setup(void) {    
  Serial.begin(115200);
  
  // Initialize UART2 for communication with Nextion
  Serial2.begin(9600, SERIAL_8N1, 16, 17); // Change 16, 17 to your UART2 TX, RX pins
  
  // Initialize the Nextion display using UART2
  nexInit();
  
  // Attach the callback functions to the button objects
  b0.attachPop(b0PopCallback);
  b1.attachPop(b1PopCallback);
  b2.attachPop(b2PopCallback);
  b3.attachPop(b3PopCallback);
  b4.attachPop(b4PopCallback);
  b5.attachPop(b5PopCallback);
  b6.attachPop(b6PopCallback);
  b7.attachPop(b7PopCallback);
  b8.attachPop(b8PopCallback);
  b9.attachPop(b9PopCallback);
  b10.attachPop(b10PopCallback);
  b11.attachPop(b11PopCallback);
  b12.attachPop(b12PopCallback);
  b13.attachPop(b13PopCallback);
 
  // Initialize WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");

  // Initialize NTP client
  timeClient.begin();
  timeClient.update();
}

void loop(void) {   
  // Listen for touch events
  nexLoop(nex_listen_list);
}

void sendDataToAPI(String enteredNumber, String eventDate) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    // Prepare JSON payload
    StaticJsonDocument<200> doc;
    doc["egg_code"] = enteredNumber; // Use entered number as egg_code
    
    JsonObject weight = doc.createNestedObject("weight");
    weight["value"] = 15.2; // Example weight value
    weight["event_date"] = eventDate; // Use current time from NTP server

    JsonObject length = doc.createNestedObject("length");
    length["value"] = 12.3; // Example length value
    length["event_date"] = eventDate; // Use current time from NTP server

    JsonObject width = doc.createNestedObject("width");
    width["value"] = 45.6; // Example width value
    width["event_date"] = eventDate; // Use current time from NTP server

    String requestBody;
    serializeJson(doc, requestBody);

    Serial.print("Sending JSON Payload: ");
    Serial.println(requestBody); // Print the JSON payload

    int httpResponseCode = http.POST(requestBody);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
}

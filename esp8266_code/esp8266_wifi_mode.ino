#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define trigPin1 D1
#define echoPin1 D2

#define trigPin2 D5
#define echoPin2 D6

WiFiServer server(80);  // Create a web server on port 80

// Set your WiFi credentials
const char* ssid = "";         // 👈 your Wi-Fi name
const char* password = "";        // 👈 your Wi-Fi password

long duration1, distance1;
long duration2, distance2;

void setup() {
  Serial.begin(115200);  // Ensure baud rate matches in the serial monitor
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {  // Try for 20 seconds
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if(WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi");
    Serial.println(WiFi.localIP());  // Print the IP address
  } else {
    Serial.println("\nFailed to connect to WiFi. Check your credentials.");
    return;
  }
  
  // Initialize sensor pins
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  server.begin();  // Start the server
}

void loop() {
  WiFiClient client = server.available();  // Listen for incoming clients
  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();
    
    // Handle request for /data endpoint
    if (request.indexOf("GET /data") >= 0) {  
      int detected1 = detect(trigPin1, echoPin1);  // Sensor 1
      int detected2 = detect(trigPin2, echoPin2);  // Sensor 2
      String response = "{\"sensor1\":" + String(detected1) + ",\"sensor2\":" + String(detected2) + "}";
      
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: application/json");
      client.println("Connection: close");
      client.println();
      client.println(response);  // Send the sensor data in JSON format
    }
    
    delay(1);  // Give the client time to receive the response
  }
}

int detect(int trigPin, int echoPin) {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 20000);  // Timeout after 20ms
  distance = duration * 0.034 / 2;  // Calculate distance
  
  if (distance > 0 && distance < 20) {
    return 1;  // Object detected
  }
  return 0;  // No object detected
}
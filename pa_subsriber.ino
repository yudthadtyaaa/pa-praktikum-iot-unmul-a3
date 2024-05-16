#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>

// WiFi and MQTT server details
const char* ssid = "akbar";
const char* password = "12345678";
const char* mqtt_server = "broker.hivemq.com";

// Pin definitions
const int trigPin = D1;   // Pin Trig sensor ultrasonik
const int echoPin = D2;   // Pin Echo sensor ultrasonik
const int servoPin = D8;  // Pin kontrol servo
const int ledPin = D0;    // Pin kontrol LED

WiFiClient espClient;
PubSubClient client(espClient);
Servo myservo;  // Object to control the servo

long duration;
int distance;
int safetyDistance;
bool isOpen = false;  // Track the state of the servo

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// Function to handle incoming MQTT messages
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received [");
  Serial.print(topic);
  Serial.print("] ");
  String data = ""; // Variable to store received data
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    data += (char)payload[i]; // Store char array into string
  }
  Serial.println();

  if (strcmp(topic, "ultrasonic/full") == 0 && data == "Sampah Penuh") {
    digitalWrite(ledPin, HIGH); // Turn on the LED
    delay (5000);
    digitalWrite(ledPin, LOW);
  } else {
    int command = data.toInt(); // Convert string to int
    if (command == 1) { // Command to open the lid
      myservo.write(90); // Move servo to open position
      if (!isOpen) {  // Check if the servo was previously closed
        isOpen = true;  // Update the state
        client.publish("ultrasonic/akses", "akses terbuka");  // Publish the state to the topic
      }
    } else if (command == 0) { // Command to close the lid
      myservo.write(0); // Move servo to closed position
      if (isOpen) {  // Check if the servo was previously open
        isOpen = false;  // Update the state
        client.publish("ultrasonic/akses", "akses tertutup");  // Publish the state to the topic
      }
    }
    else {
      client.publish("ultrasonic/akses","Masukkan 0 (tutup) atau 1(Buka)!");
      }
    }
  }

// Function to reconnect to the MQTT broker
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe("ultrasonic/akses");
      client.subscribe("ultrasonic/full"); // Subscribe to the topic for full bin notification
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(trigPin, OUTPUT);     // Initialize ultrasonic sensor Trig pin
  pinMode(echoPin, INPUT);      // Initialize ultrasonic sensor Echo pin
  pinMode(ledPin, OUTPUT);      // Initialize LED pin
  myservo.attach(servoPin);     // Attach the servo to the control pin

  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883); // Setup initial connection to MQTT server
  client.setCallback(callback); 
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Ultrasonic sensor and servo control code
  digitalWrite(trigPin, LOW);
  delay(1000);
  digitalWrite(trigPin, HIGH);
  delay(1000);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  safetyDistance = distance;
  
  if (safetyDistance <= 5) {
    if (!isOpen) {  // Check if the servo was previously closed
      myservo.write(90); // Move servo to open position if distance is <= 5 cm
      isOpen = true;  // Update the state
      client.publish("ultrasonic/akses", "akses terbuka");  // Publish the state to the topic
    }
  } else {
    if (isOpen) {  // Check if the servo was previously open
      myservo.write(0);  // Move servo to closed position if distance is > 5 cm
      isOpen = false;  // Update the state
      client.publish("ultrasonic/akses", "akses tertutup");  // Publish the state to the topic
    }
  }
  
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(500); // Delay to prevent rapid reading
}

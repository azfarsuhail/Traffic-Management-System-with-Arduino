#define trigPin1 D1
#define echoPin1 D2

#define trigPin2 D5
#define echoPin2 D6

long duration1, distance1;
long duration2, distance2;

void setup() {
  Serial.begin(9600);
  
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
}

void loop() {
  // --- Sensor 1 ---
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH, 20000); // timeout after 20ms
  distance1 = duration1 * 0.034 / 2;

  if (distance1 > 0 && distance1 < 20) {
    Serial.println("Sensor 1: Object Detected");
  } else {
    Serial.println("Sensor 1: No Object Detected");
  }

  // --- Sensor 2 ---
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH, 20000);
  distance2 = duration2 * 0.034 / 2;

  if (distance2 > 0 && distance2 < 20) {
    Serial.println("Sensor 2: Object Detected");
  } else {
    Serial.println("Sensor 2: No Object Detected");
  }

  delay(1000);
}
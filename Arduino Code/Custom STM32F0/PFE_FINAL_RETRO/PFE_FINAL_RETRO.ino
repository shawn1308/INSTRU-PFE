
const int LedPin = PA4;
const int buzzerPin = PA0;
bool buzzon = false;
const int melody[] = {262, 294, 330, 349, 349, 330};

const int noteDurations[] = {100, 100, 100, 100, 100, 100};

void setup() {
  pinMode(LedPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  while (Serial.available() == 0) {
    // Do nothing and keep waiting
    digitalWrite(LED_BUILTIN,HIGH);
  }
  digitalWrite(LED_BUILTIN,LOW);
}

void loop() {
  if (Serial.available() > 0) {
    // Read the incoming byte
    String data = Serial.readStringUntil('\n');
    int intValue = data.toInt();
    if(intValue == 1){
      digitalWrite(LedPin, LOW);
    }else if(intValue == 2){
      digitalWrite(LedPin, HIGH);
    }else if(intValue == 3){
      buzzon = true;
    }else if(intValue == 4){
      buzzon = false;
    }
    Serial.print("Received integer: ");
    Serial.println(intValue);
    clearSerialBuffer();
  }
  if(buzzon){
    for (int i = 0; i < sizeof(melody) / sizeof(int); i++) {
      tone(buzzerPin, melody[i], noteDurations[i]);
      delay(noteDurations[i] * 1.30);
    }
  }
}

void clearSerialBuffer() {
  while (Serial.available() > 0) {
    Serial.read(); // Read and discard any remaining data in the buffer
  }
}
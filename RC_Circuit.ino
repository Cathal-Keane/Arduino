float lastReading;
unsigned long time;

void setup() {
     Serial.begin(9600);
     lastReading = analogRead(A5)*5/1024.;
   }
    void loop() {
    while (fabs(analogRead(A5)*5/1024. - lastReading) < 0.1) {
      time = micros();
    }
    for (int i = 0; i < 500; i++) {  /* This takes 500 voltage points and plots them */
      unsigned long now = micros();
      Serial.print(now - time);
      Serial.print(" ");
      float currentReading = analogRead(A5)*5/1024.;
      Serial.println(currentReading);
    }
    while (1) {
      // do nothing
    }
  }

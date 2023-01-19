/*
Arduino Nano

External Clock Input A7
CV Inputs  A0-A5
6 Gate Outputs D2-D7

Output bandwidth follows clock input bandwidth
Does not need regular clock source, any signal crossing 1v will work.
Each channel generates clocked gates based on the input mixer and thresholds set below.
*/
  int OutPins[] = {2, 3, 4, 5, 6, 7};
  int CVinPins[] = {A0, A1, A2, A3, A4, A5};
  int ClockPin = A7;

  const int CVThreshold = 200; 
  const int ClockThreshold = 200; 

  int CVin = 0;
  int Channel = 0;
  int ClockPinStatus = 0;

  bool ClockState = LOW;
  bool PrevClockState = LOW; 
  bool ChSet[] = {LOW, LOW, LOW, LOW, LOW, LOW};
  bool OutStatus[] = {LOW, LOW, LOW, LOW, LOW, LOW};

void setup() {
  for (Channel = 0; Channel < 6; Channel++) {
    pinMode(OutPins[Channel], OUTPUT); 
  }
}

void loop() {
  for (Channel = 0; Channel < 6; Channel++) { 
    CVin = analogRead(Channel);
    if (CVin > CVThreshold) {ChSet[Channel] = HIGH; } 
  }
  ClockPinStatus = analogRead(ClockPin);
  if (ClockPinStatus > ClockThreshold) {ClockState = HIGH; }
  if (ClockPinStatus <= ClockThreshold) {ClockState = LOW; }

  if (ClockState == LOW && PrevClockState == HIGH) {  
    PrevClockState = LOW; 
    for (Channel = 0; Channel < 6; Channel++) { 
      if (OutStatus[Channel] == HIGH) {
        digitalWrite(OutPins[Channel], LOW );
        OutStatus[Channel] = LOW;
      }
    }
  }
  
  if (ClockState == HIGH && PrevClockState == LOW) {  
    PrevClockState = HIGH;
    for (Channel = 0; Channel < 6; Channel++) { 
      if (ChSet[Channel] == HIGH) {
        digitalWrite(OutPins[Channel], HIGH );
        OutStatus[Channel] = HIGH; 
        ChSet[Channel] = LOW;
      }
    }
  }
  delay(0); 
}

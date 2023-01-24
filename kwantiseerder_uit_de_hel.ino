/*
Arduino Nano

1 External Clock Input A7
6 Channel Inputs 
6 Offset Pots
Channel Inputs + Pots mixed and sent to A0-A5
6 Channel Outputs D2-D7

Output bandwidth follows clock input bandwidth
Does not need regular clock source, any signal that crosses threshold will work - Default 1v
Each channel generates clocked gates based on the input mixer, offset pot and threshold - Default 2.5v
*/
  int OutPins[] = {2, 3, 4, 5, 6, 7};
  int CVinPins[] = {A0, A1, A2, A3, A4, A5};
  int ClockPin = A7;

  const int CVThreshold = 511; 
  const int ClockThreshold = 204; 

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
    CVin = analogRead(CVinPins[Channel]);
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

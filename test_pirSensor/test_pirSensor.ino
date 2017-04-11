int pirSensor = 7;
int led = 13;
int count = 0;

void triggerLed(int temps_ences){
  digitalWrite(led, HIGH);
  delay(temps_ences); //ms
  digitalWrite(led, LOW);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(pirSensor, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(pirSensor) == HIGH){
    triggerLed(500);
    count += 1;
    Serial.print("Detectat "+String(count)+"\n");
    delay(1500);
  }
}

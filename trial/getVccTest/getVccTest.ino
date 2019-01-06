void setup() {
  
  Serial.begin(9600);
  ADC_MODE(ADC_VCC);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(ESP.getVcc());
  delay(1);
}

#define trig 9 
#define echo 10
#define led 12
void setup() {
  Serial.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(led,OUTPUT);
}

void loop() {
   digitalWrite(trig,LOW);
   delayMicroseconds(2);
   digitalWrite(trig,HIGH);
   delayMicroseconds(10);
   digitalWrite(trig,LOW);
   unsigned long duration = pulseIn(echo,HIGH,38000);
   
   if (duration == 0){
    Serial.println("NO OBJECT IN RANGE :");
    digitalWrite(led,LOW);
    return;
   }
   
   float distance = (duration*0.034)/2;
   
   if(distance <= 10)
   {
      digitalWrite(led,HIGH);
   }
   else
   {
      digitalWrite(led,LOW);
   }  
   Serial.print("Distance ="); Serial.print(distance); Serial.println("cm");
   delay(400);
}

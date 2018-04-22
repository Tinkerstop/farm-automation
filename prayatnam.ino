int temp=0,i=0;
int moisture = A0 , k=0;
int MoistureTreshold1 = 700;
int MoistureTreshold2 = 500;
int led=13.,Fan=3;
char str[15];
void setup()
{
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.println("AT+CNMI=2,2,0,0,0");
  delay(500);
  Serial.println("AT+CMGF=1");
  delay(1000);
  digitalWrite(13, LOW);
  digitalWrite(3, LOW);
}
void loop()
 { if(temp==1)
  {
    check();
    temp=0;
    i=0;
    delay(1000);
  }
  int analogSensor = analogRead(moisture);                                                
  if (analogSensor > MoistureTreshold1 && k==0)
   SendMessage1();  
  if (analogSensor < MoistureTreshold2 && k==1 )
   SendMessage2();
 }
 void serialEvent() 
 {
  while(Serial.available()) 
  {
    if(Serial.find("#A."))
    {
      digitalWrite(led, HIGH);
      delay(700);
      digitalWrite(led, LOW);
      while (Serial.available()) 
      {
      char inChar=Serial.read();
      str[i++]=inChar;
      if(inChar=='*')
      {
        temp=1;
        return;
      } 
      } 
    }
   }
 }
 void check()
{ if(!(strncmp(str,"all on",6)))
 {
  digitalWrite(Fan , HIGH);
  delay(200);
  Serial.println("AT+CMGF=1");    
  delay(1000);
  Serial.println("AT+CMGS=\"+919908866990\"\r");
  delay(1000);
  Serial.println("Motor on");
  delay(100);
  Serial.println((char)26);
  delay(1000);
 }

 else if(!(strncmp(str,"all off",7)))
 {
  digitalWrite(Fan , LOW);
  delay(200);
  Serial.println("AT+CMGF=1");    
  delay(1000);
  Serial.println("AT+CMGS=\"+919908866990\"\r");
  delay(1000);
  Serial.println("Motor off");
  delay(100);
  Serial.println((char)26);
  delay(1000);
 }
}
 void SendMessage1()
{
  Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(100);  // Delay of 1000 milli seconds or 1 second
  Serial.println("AT+CMGS=\"+919908866990\"\r"); // Replace x with mobile number
  delay(300);
  Serial.println("The moisture level in soil is not adequate.");// The SMS text you want to send
  delay(300);
  k=1;
  motoron();
}
void SendMessage2()
{
  Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(100);  // Delay of 1000 milli seconds or 1 second
  Serial.println("AT+CMGS=\"+919908866990\"\r"); // Replace x with mobile number
  delay(300);
  Serial.println("The moisture level in soil is adequate.");// The SMS text you want to send
  delay(300);
  k=0;
  motoroff();
}
void motoron()
{
  digitalWrite(3,HIGH);
  delay(1000);
  Serial.println("Motor is on.");// The SMS text you want to send
  delay(100);
  Serial.println((char)26);// ASCII code of CTRL+Z
  delay(100);
  Serial.println("AT+CMGD=1,4"); 
  delay(100);
}

void motoroff()
{
  digitalWrite(3, LOW);
  delay(1000);
  Serial.println("Motor is off.");// The SMS text you want to send
  delay(100);
  Serial.println((char)26);// ASCII code of CTRL+Z
  delay(100);
  Serial.println("AT+CMGD=1,4"); 
  delay(100);
 }

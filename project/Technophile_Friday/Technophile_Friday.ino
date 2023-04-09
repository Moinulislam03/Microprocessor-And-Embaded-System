#include <SoftwareSerial.h> 
float temp1,hum1;
#include <dht.h>
#define Relay1 7
#define Relay2 8
#define Relay3 10  //LED1

#define DHTPIN 6     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);


#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance;


const int Relay4 = 11; // LED2 
const int ldrPin = A0; // analog pin 0


int sensorPin = A1; 
int mois1;  
int limit = 300; 

void setup(){
  
 Serial.begin(9600);  // We are starting our communication with the serial port.
  Serial.println("Started");
  dht.begin();

pinMode(22,OUTPUT);
 pinMode(24,OUTPUT);
pinMode(26,OUTPUT);
pinMode(28,OUTPUT);



pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);

pinMode(Relay1, OUTPUT);
pinMode(Relay2, OUTPUT);
pinMode(Relay3, OUTPUT);
pinMode(Relay4, OUTPUT); // Here LED is determined as an ouput or an indicator.

pinMode(ldrPin, INPUT); 

}

void loop()
{
 
temp1= dht.readTemperature();
  
    Serial.print("temperature1 = ");
    Serial.print(temp1); 
     Serial.println("C  ");
   
    delay(200);
  
  

if ((temp1)<22) 
{
    digitalWrite(Relay1,LOW);
    digitalWrite(Relay2,LOW);
     Serial.print("Both Fan Off ");
    
  }
  else
  {
    digitalWrite(Relay1,HIGH);
    
        if ((temp1)>25) 
        {
             digitalWrite(Relay2,HIGH);
             Serial.print("Fan 2 On ");
        }
        else
        {
            digitalWrite(Relay2,LOW);
        }
  }




digitalWrite(trigPin, LOW);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  if(distance < 15)
  {
     digitalWrite(Relay3, HIGH); 
  }
  else
  {
     digitalWrite(Relay3, LOW); 
  }
  

int ldrStatus = analogRead(ldrPin);

if (ldrStatus < 1011) {

digitalWrite(Relay4, HIGH); // If LDR senses darkness led pin high that means led will glow.

Serial.print("Darkness over here,turn on the LED : ");

Serial.println(ldrStatus);

} else {

digitalWrite(Relay4, LOW); // If LDR senses light led pin low that means led will stop glowing.

Serial.print("There is sufficeint light , turn off the LED : ");

Serial.println(ldrStatus);
 }
delay(5000);

}

 

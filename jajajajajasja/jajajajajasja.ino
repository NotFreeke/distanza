#include <SPI.h>
#include <WiFiNINA.h>
#include <Wire.h>

char ssid[] = Freeke; 
char pass[] = t3eru8yen; 
//int keyIndex = 0;          

int status = WL_IDLE_STATUS;
char server[40] = "nascob.com";   
String path = "/finger/ardu.php?battito=";

WiFiSSLClient client;

void setup() {  
  Serial.begin(115200);
  Serial.println("Initializing...");

  while (!Serial) {
    delay(1);
  }

  //connessione al hotspot
    
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!\nSTOPPED");    
    while (true);
  }

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);    
    status = WiFi.begin(ssid, pass);
    delay(5000);
  }
  Serial.println("Connected to wifi");

  pinMode(pinTrigger, OUTPUT);
  pinMode(pinEcho, INPUT);
  //servo.attach(SERVO);

  Serial.println("Sensore Ultrasuoni: ");
  
}


void loop() {

  int sat = 0;

    digitalWrite(pinTrigger, LOW);
    digitalWrite(pinTrigger, HIGH);

    delayMicroseconds(10);

    digitalWrite(pinTrigger,LOW);


    long durata = pulseIn(pinEcho, HIGH);
    long distanza = durata/58.31;

    Serial.print("distanza: ");

    if( durata > 38000 ){
      Serial.println("Fuori portata");
    }
    else{ 
      Serial.print(distanza); 
      Serial.println(" cm");
    }


 
  if (client.connect(server, 443)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.print("GET ");
    client.print(path);
    client.print(distanza);
    client.print("-");
    client.print(sat);
    client.println(" HTTP/1.1");
    client.println("Host: "+String(server));
    client.println("Connection: close");
    client.println();

  }
}

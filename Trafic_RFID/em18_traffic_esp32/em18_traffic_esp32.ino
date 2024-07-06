#include <WiFi.h>
#define NAME "TrafficManagement"
#define PASS "00000000"
const char* host = "192.168.95.184";

const int MQ135pin = A4;  //GPIO32

int redLed_A = 12;
int yellowLed_A = 14;
int greenLed_A = 27;

int redLed_B = 26;
int yellowLed_B = 25;
int greenLed_B = 33;


int buzzer = 35;
int buttonPin = 13; //push button

String data1 = "NA";
String inst = "";




WiFiClient client;
void setup() {

  Serial.begin(9600);

  pinMode(MQ135pin,INPUT);
  pinMode(redLed_A, OUTPUT);
  pinMode(yellowLed_A, OUTPUT);
  pinMode(greenLed_A, OUTPUT);

  pinMode(redLed_B, OUTPUT);
  pinMode(yellowLed_B, OUTPUT);
  pinMode(greenLed_B, OUTPUT);


  pinMode(buzzer, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);



  while (!Serial) continue;

  WiFi.mode(WIFI_STA);

  WiFi.begin(NAME, PASS);


  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP ahddress: ");
  Serial.println(WiFi.localIP());
  delay(200);


}

void loop() {

  int buttonValue = digitalRead(buttonPin);
  int rawValue = analogRead(MQ135pin);
  int co2=map(rawValue,0,4095,0,1024);
  //Serial.println(buttonValue);

  if (Serial.available())
  {
    //digitalWrite(led, HIGH);
    digitalWrite(buzzer, HIGH);
    while (Serial.available() > 0)
    {
      delay(3);
      char data = Serial.read();
      data1 += data;

    }

  } else {
    //digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
  }

  //delay(200);

  //Serial.println(data1);
  if (client.connect(host, 9091))
  {
    // Serial.print("Connected to: ");
    // Serial.println(host);



    client.println((String)buttonValue+ "#" +(String)co2+ "#" +data1 );
    //delay(200);
    data1 = "";


    /* Wait for data for 5 seconds at most before timing out */
    unsigned long timeout = millis();
    while (client.available() == 0)
    {
      if (millis() - timeout > 5000)
      {
        //   Serial.println("Timeout to server!");
        break;
      }
    }

    /* Read in the data in the stream */
    while (client.available() > 0)
    {


      inst = client.readStringUntil('\n');
      Serial.println(inst);

      //int stringLength = inst.length();
      String ins_1 = inst.substring(0, 1);
      String ins_2 = inst.substring(1, 2);
      String ins_3 = inst.substring(2, 3);
      String ins_4 = inst.substring(3, 4);
      String ins_5 = inst.substring(4, 5);
      String ins_6 = inst.substring(5, 6);



     if (ins_1 == "a") {
        
        //Serial.println("redled ON");
        digitalWrite(redLed_A, HIGH);
      
      } else{
        
        //Serial.println("redled OFF");
        digitalWrite(redLed_A, LOW);
      }

      if (ins_2 == "c") {
        //Serial.println("greenled ON");
        digitalWrite(yellowLed_A, HIGH);
      } else {
        
        //Serial.println("greenled OFF");
        digitalWrite(yellowLed_A, LOW);
      }

      if (ins_3 == "e") {
        
        digitalWrite(greenLed_A, HIGH);
      } else{
        
        digitalWrite(greenLed_A, LOW);
      }

      if (ins_4 == "g") {
        
        digitalWrite(redLed_B, HIGH);
      } else{
        
        digitalWrite(redLed_B, LOW);
      }

      if (ins_5 == "i") {
        
        digitalWrite(yellowLed_B, HIGH);
      }  {
        
        digitalWrite(yellowLed_B, LOW);
      }

      if (ins_6 == "k") {
        
        digitalWrite(greenLed_B, HIGH);
      } else {
        
        digitalWrite(greenLed_B, LOW);
      }


    }
    client.stop();
  }
  else
  {

    client.stop();
  }
  //delay(200);
  inst = "";

}

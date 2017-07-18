#include <VirtualWire.h>
byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message

int rightmot_pin7 =7;
int rightmot_pin6=6;
int leftmot_pin5=5;
int leftmot_pin4=4;
int ledPin=13;//led on pin 13 is ON except when bot is stationary

void setup()
{
 Serial.begin(9600);//Initialise the serial connection debugging

  pinMode(ledPin,OUTPUT);
  pinMode(rightmot_pin7,OUTPUT);
  pinMode(rightmot_pin6,OUTPUT);
  pinMode(leftmot_pin5,OUTPUT);
  pinMode(leftmot_pin4,OUTPUT);

 vw_setup(2000); // Bits per sec
 vw_rx_start(); // Start the receiver
}
void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
  int i;

  //Serial.print("Got: ");//debugging
  
  for (i = 0; i < buflen; i++)
  {
     // Serial.print(buf[i],HEX);//You may also use integer values debugging
      //Serial.print(' ');// debugging

          if (buf[i]==0x73)//Stationary
          {
            digitalWrite(rightmot_pin7,LOW);
            digitalWrite(rightmot_pin6,LOW);
            digitalWrite(leftmot_pin5,LOW);
            digitalWrite(leftmot_pin4,LOW);
  
            Serial.println("Stationary");
            digitalWrite(ledPin,LOW);
          }
          else
          {
            if(buf[i]==0x66)//Forward
            {
              digitalWrite(rightmot_pin7,HIGH);
              digitalWrite(rightmot_pin6,LOW);
              digitalWrite(leftmot_pin5,HIGH);
              digitalWrite(leftmot_pin4,LOW);
              Serial.println("Forward");
              digitalWrite(ledPin,HIGH);
            }
          
            if (buf[i]==0x61)//Backward
            {
              digitalWrite(rightmot_pin7,LOW);
              digitalWrite(rightmot_pin6,HIGH);
              digitalWrite(leftmot_pin5,LOW);
              digitalWrite(leftmot_pin4,HIGH);
              Serial.println("Backward");
              digitalWrite(ledPin,HIGH);
          }
          
            if (buf[i]==0x72)//Right 
            {
              digitalWrite(rightmot_pin7,LOW);
              digitalWrite(rightmot_pin6,LOW);
              digitalWrite(leftmot_pin5,HIGH);
              digitalWrite(leftmot_pin4,LOW);
              Serial.println("Right");
              digitalWrite(ledPin,HIGH);
            }
          
            if (buf[i]==0x6C)//Left 
            {
              digitalWrite(rightmot_pin7,HIGH);
              digitalWrite(rightmot_pin6,LOW);
              digitalWrite(leftmot_pin5,LOW);
              digitalWrite(leftmot_pin4,LOW);
              Serial.println("Left");
              digitalWrite(ledPin,HIGH);
            }
           }   
    }
    //Serial.print("\n");// debugging
        }
        //delay(1000);
}

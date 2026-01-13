
#include <ESP8266WiFi.h>
const char WiFiPassword[] = "123123123";
const char AP_NameChar[] = "HedyMCU1" ;

WiFiServer server(80);

String request = "";

int LED_Pin0 = D0;
int LED_Pin1 = D1;
int LED_Pin2 = D2;
int LED_Pin3 = D3;
int LED_Pin4 = D4;
int LED_Pin5 = D5;
int LED_Pin6 = D6;
//int LED_Pin7 = D7;
int LED_Pin8 = D8;  

int flag = 0;

const int analogPin = A0; // ESP8266 Analog Pin ADC0 = A0
int sensorNewValue = 0;  // value read from the pot
int sensorOldValue = 0;

#include <FastLED.h>
#define LED_PIN     D7
#define NUM_LEDS    6 //1
#define BRIGHTNESS  200
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];


void setup()
{
  Serial.begin(115200);
  pinMode(LED_Pin0, OUTPUT);
  pinMode(LED_Pin1, OUTPUT);
  pinMode(LED_Pin2, OUTPUT);
  pinMode(LED_Pin3, OUTPUT);
  pinMode(LED_Pin4, OUTPUT);
  pinMode(LED_Pin5, OUTPUT);
  pinMode(LED_Pin6, OUTPUT);
  //pinMode(LED_Pin7, OUTPUT);
  pinMode(LED_Pin8, OUTPUT);
  
  WiFi.disconnect();
  boolean conn = WiFi.softAP(AP_NameChar, WiFiPassword);
  server.begin();

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  delay(1000);

  leds[0] =CRGB::Blue;
    FastLED.show();
} 

void loop()
{
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client)  {
    return;
  }

  // Read the first line of the request
  request = client.readStringUntil('\r');
  
/////////////led0/////////////
   if( request.indexOf("D0HIGH") > 0 )  
   {
    digitalWrite(LED_Pin0, HIGH);
    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
    Serial.println("LED0 ON");
   }
   if  ( request.indexOf("D0LOW") > 0 ) 
   {
    digitalWrite(LED_Pin0, LOW);
    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
    Serial.println("LED0 OFF");
   }
/////////////////////////////

/////////////led1/////////////
   if( request.indexOf("D1HIGH") > 0 )  
   {
    digitalWrite(LED_Pin1, HIGH);
    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
    Serial.println("LED1 ON");
   }
   if  ( request.indexOf("D1LOW") > 0 ) 
   {
    digitalWrite(LED_Pin1, LOW);
    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
    Serial.println("LED1 OFF");
   }
/////////////////////////////

/////////////led2/////////////
   if( request.indexOf("D2HIGH") > 0 )  
   {
    digitalWrite(LED_Pin2, HIGH);
    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
    Serial.println("LED2 ON");
   }
   if  ( request.indexOf("D2LOW") > 0 ) 
   {
    digitalWrite(LED_Pin2, LOW);
    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
    Serial.println("LED2 OFF");
   }
/////////////////////////////

/////////////led3/////////////
   if( request.indexOf("D3HIGH") > 0 )  
   {
    digitalWrite(LED_Pin3, HIGH);
    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
    Serial.println("LED3 ON");
   }
   if  ( request.indexOf("D3LOW") > 0 ) 
   {
    digitalWrite(LED_Pin3, LOW);
    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
    Serial.println("LED3 OFF");
   }
/////////////////////////////

/////////////led4/////////////
   if( request.indexOf("D4HIGH") > 0 )  
   {
    digitalWrite(LED_Pin4, HIGH);
    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
    Serial.println("LED4 ON");
   }
   if  ( request.indexOf("D4LOW") > 0 ) 
   {
    digitalWrite(LED_Pin4, LOW);
    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
    Serial.println("LED4 OFF");
   }
/////////////////////////////

/////////////led5/////////////
   if( request.indexOf("D5HIGH") > 0 )  
   {
    digitalWrite(LED_Pin5, HIGH);
    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
    Serial.println("LED5 ON");
   }
   if  ( request.indexOf("D5LOW") > 0 ) 
   {
    digitalWrite(LED_Pin5, LOW);
    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
    Serial.println("LED5 OFF");
   }
/////////////////////////////

/////////////led6/////////////
   if( request.indexOf("D6HIGH") > 0 )  
   {
    digitalWrite(LED_Pin6, HIGH);
    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
    Serial.println("LED6 ON");
   }
   if  ( request.indexOf("D6LOW") > 0 ) 
   {
    digitalWrite(LED_Pin6, LOW);
    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
    Serial.println("LED6 OFF");
   }
/////////////////////////////

/////////////led7/////////////
   if( request.indexOf("D7HIGH") > 0 )  
   {
    //digitalWrite(LED_Pin7, HIGH);
    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
    Serial.println("LED7 ON");
   }
   if  ( request.indexOf("D7LOW") > 0 ) 
   {
    //digitalWrite(LED_Pin7, LOW);
    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
    Serial.println("LED7 OFF");
   }
/////////////////////////////

/////////////led8/////////////
   if( request.indexOf("D8HIGH") > 0 )  
   {
    digitalWrite(LED_Pin8, HIGH);
    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
    Serial.println("LED8 ON");
   }
   if  ( request.indexOf("D8LOW") > 0 ) 
   {
    digitalWrite(LED_Pin8, LOW);
    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
    Serial.println("LED8 OFF");
   }
/////////////////////////////


 
  if( request.indexOf("ADCREAD") > 0 )
  {
    readA0();
    client.println("HTTP/1.1 200 OK\r\n");
    client.println(sensorNewValue);
    client.flush();
    Serial.println(sensorNewValue);
  }
  
//////////leds////////////

  if  ( request.indexOf("BLUE") > 0 ) 
   {
    leds[5] =CRGB::Blue;
    FastLED.show();
    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
   }
   if  ( request.indexOf("RED") > 0 ) 
   {
    leds[0] =CRGB::Red;
    FastLED.show();
    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
   }
   if  ( request.indexOf("GREEN") > 0 ) 
   {
    leds[0] =CRGB::Green;
    FastLED.show();
    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
   }
   if  ( request.indexOf("YELLOW") > 0 ) 
   {
    leds[0] =CRGB::Yellow;
    FastLED.show();
    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
   }
   if  ( request.indexOf("PURPLE") > 0 ) 
   {
    leds[0] =CRGB::Purple;
    FastLED.show();
    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
   }
   if  ( request.indexOf("OFF") > 0 ) 
   {
    leds[0] =CRGB::Black;
    FastLED.show();
    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
   }
  
  delay(5);

} 

void readA0()
{
  sensorOldValue = sensorNewValue;
  sensorNewValue = analogRead(A0);          // read the analog in value
  if(sensorOldValue != sensorNewValue)
  {
    Serial.println(sensorNewValue);
    //client.println(sensorNewValue); 
    //client.flush();   
    delay(200);            
  }
}

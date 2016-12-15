#include <DHT.h>
#include <ESP8266WiFi.h> 

const char* ssid = "thsensor_setup";
const char* password = "424242";
 
#define DHTPIN 13   
#define SLEEP_TIME 300

#define SENSOR_NO 0

//#define SERIAL_LOG 1

String apiKey = "4YT5N1ICRGVKEUVA";
const char* server = "api.thingspeak.com";
 
DHT dht(DHTPIN, DHT22);
WiFiClient client;  
 
void setup() {                
}
 
 
void loop() {
#ifdef SERIAL_LOG
  Serial.begin(115200);
#endif

  //digitalWrite(12, HIGH);
  //delay(3000);
  pinMode(A0, INPUT);
  dht.begin();
  WiFi.begin(ssid, password);
 
#ifdef SERIAL_LOG  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
#endif
   
  WiFi.begin(ssid, password);
   
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
#ifdef SERIAL_LOG  
    Serial.print(".");
#endif
  }

#ifdef SERIAL_LOG  
  Serial.println("");
  Serial.println("WiFi connected");
#endif
   
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
#ifdef SERIAL_LOG  
    Serial.println("Failed to read from DHT sensor!");
#endif
    h = 0;
    t = 0;
  }

  unsigned a0 = analogRead(A0);
  float v = (float)a0 * 5.54 / 1000.0;
 
  if (client.connect(server,80)) {  //   "184.106.153.149" or api.thingspeak.com
    String t_channel = String("field") + String(SENSOR_NO*3+1);
    String h_channel = String("field") + String(SENSOR_NO*3+2);
    String v_channel = String("field") + String(SENSOR_NO*3+3);
    String postStr = "";
           postStr += ("&" + t_channel + "=" + String(t));
           postStr += ("&" + h_channel + "=" + String(h));
           postStr += ("&" + v_channel + "=" + String(v));
           postStr += "\r\n\r\n";
 
     client.print("POST /update HTTP/1.1\n"); 
     client.print("Host: api.thingspeak.com\n"); 
     client.print("Connection: close\n"); 
     client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n"); 
     client.print("Content-Type: application/x-www-form-urlencoded\n"); 
     client.print("Content-Length: "); 
     client.print(postStr.length()); 
     client.print("\n\n"); 
     client.print(postStr);
           
#ifdef SERIAL_LOG  
     Serial.print("Temperature: ");
     Serial.print(t);
     Serial.print(" degrees Celcius, Humidity: "); 
     Serial.print(h);
     Serial.print("%, Input voltage: ");
     Serial.print(v);
     Serial.println("");
#endif
  }
  client.stop();
  // digitalWrite(12, LOW);

  ESP.deepSleep(1000*1000*SLEEP_TIME, WAKE_RF_DEFAULT);
   
}


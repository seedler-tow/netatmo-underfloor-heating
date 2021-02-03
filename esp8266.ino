
#include <ESP8266WiFi.h>
#include <WiFiManager.h>         // https://github.com/tzapu/WiFiManager
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>   
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>



// Auxiliar variables to store the current output state
String output0State = "off";

// Assign output variables to GPIO pins
const int output0 = 0;




const char *host = "[YOUR WEBSITE RUNNING THE PHP SCRIPT]";
String line;
static int relayOn = 0;
float temp, set_temp;
bool anti;
float last_temp, last_set_temp;
bool last_anti;

void setup() {
  Serial.begin(115200);
  
  // Initialize the output variables as outputs
pinMode(output0, OUTPUT);

  // Set output to HIGH to make sure relay is open if network connection fails
  digitalWrite(output0, HIGH);

  // WiFiManager
  // Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  
  // Uncomment and run it once, if you want to erase all the stored information
  //wifiManager.resetSettings();

  //define timeout for wifiManager portal in case of power or wifi failure
wifiManager.setConfigPortalTimeout(180);

  // fetches ssid and pass from eeprom and tries to connect
  // if it does not connect it starts an access point with the specified name
  // here  "AutoConnectAP"
  // and goes into a blocking loop awaiting configuration. Read more about how to configure wifiManager at https://www.instructables.com/Introduction-Library-WifiManager-for-Esp8266/
  
    if(!wifiManager.autoConnect("AutoConnectAP"))WiFi.mode(WIFI_STA);
  
  // if you get here you have connected to the WiFi
  Serial.println("Connected.");
  
}


int getTemperature(){
  
  WiFiClient client;
  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, 80))
  {
    Serial.println("connected]");

// send request to php site

    Serial.println("[Sending a request]");
    String url = "[LOCATION OF YOUR PHP FILE. FOR EXAMPLE /index.php]";
    client.print(String("GET /") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
               "Connection: close\r\n" +
                "\r\n"
                );

    Serial.println("[Response:]");

// retrieve current temperature   
    client.find("actuele temperatuur ");
    String temptemp = String(client.readStringUntil(','));
    
// converting String to float

temp = atof( temptemp.c_str() );
    
    Serial.print("actuele temperatuur ");
    Serial.println(temp);

// retrieve set temperature
    client.find("ingestelde temperatuur ");
    String tempset_temp = String(client.readStringUntil(','));

// converting String to float

 set_temp = atof( tempset_temp.c_str() );
    
    Serial.print("ingestelde temperatuur ");
    Serial.println(set_temp);

    client.find("anticipating? ");
    String tempanti = String(client.readStringUntil('.'));

    // converting String to bool
    if (tempanti=="1"){
      anti=true;
    }
    else{
      anti=false;
    }
    
    Serial.print("anticiperen? ");
    Serial.println(anti);

    client.stop();
    Serial.println("\n[Disconnected]");
  }
  else
  {
    Serial.println("connection failed!]");
    client.stop();
    Serial.println("Relay On");
    digitalWrite(output0, HIGH);
    delay(3000);
    ESP.restart();
  }  
}

void loop(){

int ret = getTemperature();

//sometimes I got an error and then it gave 0 for temp or set_temp. After I improved the conversion from String to float I think it didn't happen anymore, but to be save I left the code below in the script
if (temp==0||set_temp==0){
  temp=last_temp;
  set_temp=last_set_temp;
  anti=last_anti;
}

          Serial.println("Temperature: ");
          Serial.println(temp);
          Serial.println("Set Temperature: ");
          Serial.println(set_temp);

          if(set_temp >= temp ||anti == true ) {
            Serial.println("Relay On");
            digitalWrite(output0, HIGH);
          }
          else {
           Serial.println("Relay Off");
           digitalWrite(output0, LOW);
          }
          
        delay(10000);
        
last_temp=temp;
last_set_temp=set_temp;
last_anti=anti;
}
   
      
   
  

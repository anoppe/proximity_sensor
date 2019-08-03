#include <ESP8266Influxdb.h>
#include <ESP8266WiFi.h>

const char* ssid = "<SSID>";
const char* password = "<WIFI_PWD>";

const char *INFLUXDB_HOST = "<INFLUX_HOST>";
const uint16_t INFLUXDB_PORT = 8086;

const char *DATABASE = "<DB_NAME>";
const char *DB_USER = "<DB_USER>";
const char *DB_PASSWORD = "<DB_PWD>";

WiFiClient espClient;
Influxdb* influxdb;

int lastState = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);   

    setup_wifi();
//  resolve_mdns_host("mac-mini");
  
  influxdb = new Influxdb(INFLUXDB_HOST, INFLUXDB_PORT);
  influxdb->opendb(DATABASE, DB_USER, DB_PASSWORD);

}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());  
}


void loop() {
  // put your main code here, to run repeatedly:
  int reading = digitalRead(D2);
  
  if (reading == 0 && lastState == 1) {
    String data = "p1-readings waterConsumed=1";
    Serial.println(data);
    influxdb->write(data);
    //Serial.println(influxdb.rep
    Serial.println(influxdb->response() == DB_SUCCESS ? "HTTP write success" : "Writing failed");
    delay(1000);
  } else {
    delay(100);  
  }
  
  lastState = reading;
  
}

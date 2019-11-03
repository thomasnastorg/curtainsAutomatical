


#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <TimeLib.h>


#ifndef STASSID
#define STASSID "your-ssid"
#define STAPSK  "your-password"
#endif


// connetion au wifi
const char* host = "test";
const char* ssid = "Route_TN";
const char* password = "1234567890";

// connetion a la base de donnée
IPAddress server_addr(192, 168, 1, 107); // IP of the MySQL *server* here
char user[] = "arduino";              // MySQL user login username
char pass[] = "Arduino2000";        // MySQL user login password

char INSERT_DATA[] = "INSERT INTO home.plant (id,Humidity,Nom_de_la_plante) VALUES (NULL,%d,'%s')" ;
char query[128];

/*IPAddress timeServer(213, 162, 48, 4); // ntp.accelance.net
  const int timeZone = 1;     // Central European Time*/


/*WiFiUDP Udp;
  unsigned int localPort = 8888;  // local port to listen for UDP packets*/
WiFiClient client;
MySQL_Connection conn((Client *)&client);
MySQL_Cursor cur = MySQL_Cursor(&conn);

void setup() {
  Serial.begin(115200);
  Serial.println("Booting");
  Serial.print(host);
  Serial.print(" is Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }


  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  //MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  //ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  /*Serial.print("IP number assigned by DHCP is ");
  Serial.println(WiFi.localIP());
  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(Udp.localPort());
  Serial.println("waiting for sync");
  setSyncProvider(getNtpTime);*/


}
//time_t prevDisplay = 0; // when the digital clock was displayed

void loop() {
  int Humidity_sonde = analogRead(0);

  Serial.println("connection a la base de donnee");

  if (conn.connect(server_addr, 30306, user, pass)) {
    delay(1000);
    // You would add your code here to run a query once on startup.


    Serial.println(Humidity_sonde);

    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);

    sprintf(query, INSERT_DATA, Humidity_sonde, "citronnier");

    cur_mem->execute(query);

    delete cur_mem;
    Serial.println("Recording data.");

    conn.close();
    delay(1800000);
  }
}
/*void digitalClockDisplay() {
  // digital clock display of the time
  Serial.print(hour());
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.print(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(".");
  Serial.print(month());
  Serial.print(".");
  Serial.print(year());
  Serial.println();
  }

  void printDigits(int digits) {
  // utility for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
  }

  -------- NTP code ----------

  const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
  byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

  time_t getNtpTime()
  {
  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  Serial.println("Transmit NTP Request");
  sendNTPpacket(timeServer);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      Serial.println("Receive NTP Response");
      Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }
  Serial.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
  }

  // send an NTP request to the time server at the given address
  void sendNTPpacket(IPAddress &address)
  {
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
  }*/

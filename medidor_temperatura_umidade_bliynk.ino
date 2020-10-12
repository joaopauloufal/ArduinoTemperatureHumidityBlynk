#define BLYNK_PRINT Serial

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <dht.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


char auth[] = "5548751974124a1b985ca443d7aa1a30";

char ssid[] = "Roteador Intelbras Sala";
char pass[] = "admin@ud&";

#define EspSerial Serial
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
BlynkTimer timer;
dht DHT;


void setup() {

  Serial.begin(115200);
  delay(10);

  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  lcd.begin(16,2);

  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("Iniciando...");

  Blynk.begin(auth, wifi, ssid, pass);

  lcd.clear();

  timer.setInterval(2000L, sendTemperaturaUmidade);

}

void loop() {

  Blynk.run(); //INICIALIZA O BLYNK
  timer.run(); //INICIALIZA O TIMER

}


void sendTemperaturaUmidade(){

  DHT.read22(A1);
  
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("Temp.:");
  lcd.setCursor(7,0);
  lcd.print(DHT.temperature, 1);
  lcd.setCursor(12,0);
  lcd.print("*C");
  
  lcd.setCursor(0,1);
  lcd.print("Umidade:");
  lcd.setCursor(9,1);
  lcd.print(DHT.humidity, 1);

  lcd.setCursor(13,1);
  lcd.print("%");

  Blynk.virtualWrite(1, DHT.temperature); //ENVIA AO WIDGET GAUGE (PINO VIRTUAL 1) O VALOR DA TEMPERATURA
  Blynk.virtualWrite(2, DHT.humidity); //ENVIA AO WIDGET GAUGE (PINO VIRTUAL 2) O VALOR DA UMIDADE
  
}


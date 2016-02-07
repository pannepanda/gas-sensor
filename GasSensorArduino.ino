// Arduino script for DIY gas sensor with MQ-2 and MQ-9 sensors 

// LCD initialization 
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5,4,3,2); 
// connect LCD to (RS, E, D4, D5, D6, D7)
// connect R/W and VSS to GND; VDD to 5V; V0 to (Rs) and GND, 

// Gas sensor constants
int const gasPinQ2 = A1; // reading Q2 value
int const gasPinQ9 = A2; // reading Q9 value 
int gasValQ2 = 0; // initialise Q2
int gasValQ9 = 0; // initialise Q9
int concQ2; 
int concQ9; 

// Datalogger constants
 #include <SPI.h>
 #include <SD.h>
 const int chipSelect = 10; // was pin 4
// MOSI pin 11; MISO pin 12; CLK pin 13; CS pin 4 (or 10)

void setup()
{
  lcd.begin(16, 2);
  lcd.print("Gas sensor starting!"); //print to LCD
  
  Serial.begin(9600); // Set serial baud rate to 9600 bps
  pinMode(10, OUTPUT); // make sure that the default chip select pin is set to output
}

void loop()
{
lcd.clear();

// Read MQ2
gasValQ2 = analogRead(gasPinQ2); 
concQ2 = map(gasValQ2, 0, 1023, 0, 100);
Serial.print("\n Elapsed time: "); Serial.print(millis()/60000,DEC); Serial.print(" min + "); Serial.print(millis()/1000-millis()/60000*60,DEC); Serial.print(" s \n");
Serial.print(" MQ2 value: "); Serial.print(gasValQ2,DEC); Serial.print("; "); Serial.print((int)concQ2,DEC); Serial.print(" % \n"); // Print the value to serial port
lcd.setCursor(0, 0); lcd.print("Time: "); lcd.print(millis()/60000,DEC); lcd.print("min "); lcd.print(millis()/1000-millis()/60000*60,DEC); lcd.print("s"); 
lcd.setCursor(0, 1); lcd.print("MQ2 "); lcd.print(concQ2); lcd.print("% "); 

// Read MQ9
gasValQ9 = analogRead(gasPinQ9); 
concQ9 = map(gasValQ9, 0, 1023, 0, 100);
Serial.print(" MQ9 value: "); Serial.print(gasValQ9,DEC);  Serial.print("; "); Serial.print((int)concQ9,DEC); Serial.print(" % \n"); 
lcd.print("MQ9 "); lcd.print(concQ9); lcd.print("%"); 

// Datalogging
if (!SD.begin(chipSelect)) {
  String dataString = "";
  dataString = String(millis()/6e4); dataString += "min, MQ2: "; dataString += String(concQ2);
  dataString += "%, MQ9: "; dataString += String(concQ9); dataString += "%, ";

// writing onto mircoSD 
File dataFile = SD.open("GasLog.txt", FILE_WRITE);
    if (dataFile) {
  dataFile.println(dataString);
  dataFile.close();
  Serial.println(dataString); }  
    else {
    Serial.println("error opening file"); 
  }
}

delay(1000);
}

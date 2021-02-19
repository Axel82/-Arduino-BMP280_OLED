#include <Wire.h>
#include <String.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// BMP280 sensor
Adafruit_BMP280 myBmp280;
int Bmp280Temperature = 0;
int Bmp280PressureHpa = 0;
int Bmp280Altitude = 0;

// OLED screen
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define SCREEN_ID 0x3C  // OLED display adress
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

 
void setup()
{
  // Init serial port
  Serial.begin(9600);
  Serial.println(F("BMP280 & OLED"));

   // BMP opening test
  if (!myBmp280.begin())
  {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
    }

    // OLED opening test
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ID))
    {
      Serial.println(F("Could not find a valid OLED screen, check wiring!"));
      while (1);
      }
      else
      {
        // Defaults settings
        display.clearDisplay();
        display.setTextSize(1);             // The fontsize
        display.setTextColor(WHITE);        // Draw white text
        } 
}
 
void loop()
{
  Serial.println(F("New scan"));
  
  // BMP get datas
  Bmp280Temperature = myBmp280.readTemperature();
  Bmp280PressureHpa = myBmp280.readPressure() / 100;
  Bmp280Altitude = myBmp280.readAltitude(1017);
  
  // OLED display 
  PrintOledScreen();
  
  // Break
  delay(2000);
}

void PrintOledScreen()
{
  Serial.println(F("New OLED print"));
  
  display.clearDisplay();
  
  display.setCursor(0, 0);           // Start at top-left corner
  display.print("BMP280 + OLED");       //the text

  // Temperature display
  display.setCursor(0, 8);
  display.print("Temp : ");
  display.setCursor(42, 8);
  display.print(Bmp280Temperature);
  display.setCursor(70, 8);
  display.print("C");

  // Pressure display
  display.setCursor(0, 16);
  display.print("Pres : ");
  display.setCursor(42, 16);
  display.print(Bmp280PressureHpa);
  display.setCursor(70, 16);
  display.print("hPa");  

  // Altitude display
  display.setCursor(0, 24);
  display.print("Alt  : ");
  display.setCursor(42, 24);
  display.print(Bmp280Altitude);
  display.setCursor(70, 24);
  display.print("m");  

  display.display();                  //call to display
}

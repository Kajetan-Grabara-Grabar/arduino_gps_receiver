// //YWROBOT
// //Compatible with the Arduino IDE 1.0
// //Library version:1.1
// #define second_int_value 1000
// #define red_button 2
// #define blue_button 3
// #include <LiquidCrystal_I2C.h>
// #include <SoftwareSerial.h>
// #include <TinyGPS++.h>

// LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// const char build_number[16]="Build nr <<<s<build_id>>>>";    //build number variable for CI pipeline
// const char build_branch[16]="<<s<<build_branch>>>>"; //git branch variable for CI pipeline

// long set_time_in_seconds;
// bool end_of_a_game = false;
// SoftwareSerial ss(4, 3);
// TinyGPSPlus gps;
// void start_screen(){
//     lcd.init();                      // initialize the lcd 
//     lcd.backlight();    // backlight on
//     lcd.setCursor(0,0);
//     lcd.print(build_number);
//     lcd.setCursor(0,1);
//     lcd.print(build_branch);
//     delay(second_int_value);
// }
// void setup()
// {
//     ss.begin(9600);
//     start_screen();
// }

// void loop()
// {
//     while (ss.available() > 0){
//         // get the byte data from the GPS
//         // char gpsData[16] = ss.read();
//         lcd.clear();
//         lcd.setCursor(0,0);
//         gps.encode(ss.read());
//         lcd.print(gps.location.lng(), 6);
//         if (gps.location.isUpdated()){
//             lcd.clear();
//             // lcd.setCursor(0,0);
//             // lcd.print(gps.location.lat(), 6);
//             lcd.setCursor(0,1);
//             lcd.print(gps.location.lng(), 6);
//         }
//             delay(second_int_value);
//     }
// }
/*
 * Rui Santos 
 * Complete Project Details https://randomnerdtutorials.com
 */
 
#define second_int_value 1000
#define red_button 2
#define blue_button 3
#include <LiquidCrystal_I2C.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

const char build_number[16]="Build nr <<<<build_id>>>>";    //build number variable for CI pipeline
const char build_branch[16]="<<<<build_branch>>>>"; //git branch variable for CI pipeline

void start_screen(){
    lcd.init();                      // initialize the lcd 
    lcd.backlight();    // backlight on
    lcd.setCursor(0,0);
    lcd.print(build_number);
    lcd.setCursor(0,1);
    lcd.print(build_branch);
    delay(second_int_value);
}
void setup(){
  Serial.begin(9600);
  ss.begin(GPSBaud);
  start_screen();
}

void loop(){
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
        lcd.clear();
        Serial.print("Latitude= "); 
        Serial.print(gps.location.lat(), 6);
        Serial.print(" Longitude= "); 
        Serial.println(gps.location.lng(), 6);
        lcd.setCursor(0,0);
        double firstline = gps.location.lat();
        lcd.print(gps.location.lat(),6);
        lcd.setCursor(0,1);
        double secondine = gps.location.lng();
        lcd.print(gps.location.lng(),6);
        delay(second_int_value);
    }
  }
}
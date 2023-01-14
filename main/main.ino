#define second_int_value 1000
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
void decimalToDMS(double decimalDegrees) {
    int degrees = (int)decimalDegrees;
    double minutesAndSeconds = (decimalDegrees - degrees) * 60;
    int minutes = (int)minutesAndSeconds;
    double seconds = (minutesAndSeconds - minutes) * 60;
    lcd.print(degrees);
    lcd.print('°');
    lcd.print(minutes);
    lcd.print("'");
    lcd.print(seconds,4);
    lcd.print("''");
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
        lcd.setCursor(0,0);
        decimalToDMS(gps.location.lat());
        lcd.setCursor(0,1);
        decimalToDMS(gps.location.lng());
        delay(10000);
    }
  }
}
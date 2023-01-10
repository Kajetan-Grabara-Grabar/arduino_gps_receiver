//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#define second_int_value 1000
#define red_button 2
#define blue_button 3
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

const char build_number[16]="Build nr <<<<build_id>>>>";    //build number variable for CI pipeline
const char build_branch[16]="<<<<build_branch>>>>"; //git branch variable for CI pipeline

long set_time_in_seconds;
bool end_of_a_game = false;
SoftwareSerial ss(4, 3);
void start_screen(){
    lcd.init();                      // initialize the lcd 
    lcd.backlight();    // backlight on
    lcd.setCursor(0,0);
    lcd.print(build_number);
    lcd.setCursor(0,1);
    lcd.print(build_branch);
    delay(second_int_value);
}
void setup()
{
    ss.begin(9600);
    start_screen();
}

void loop()
{
    while (ss.available() > 0){
        // get the byte data from the GPS
        byte gpsData = ss.read();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(gpsData);
        delay(second_int_value);
    }
}
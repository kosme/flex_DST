
#include <Wire.h>
#include "RTClib.h"
#include "flex_DST.h"

RTC_DS1307 rtc; // clock object

// Several examples according to different DST configurations
flex_DST dst_rtc(1,4,5,10); // DST object starting the first SUNDAY in April and ending the last SUNDAY in October
// flex_DST dst_rtc(1,10,4,3); // DST object starting the first SUNDAY in October and ending the fourth SUNDAY in March
// flex_DST dst_rtc(1,5,3,5,10); // DST object starting the FRIDAY before the last SUNDAY in March and ending the last SUNDAY in October
// flex_DST dst_rtc(2,5,3,5,10); // DST object starting the last FRIDAY in April and ending the last FRIDAY in October
// flex_DST dst_rtc(3,21,3,21,9) // DST object starting March 21st and ending September 21st

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  Wire.begin();
  rtc.begin();

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(__DATE__, __TIME__));
    // DST? If we're in it, let's subtract an hour from the RTC time to keep our DST calculation correct. This gives us
    // Standard Time which our DST check will add an hour back to if we're in DST.
    DateTime standardTime = rtc.now();
    if (dst_rtc.checkDST(standardTime) == true) { // check whether we're in DST right now. If we are, subtract an hour.
      standardTime = standardTime.unixtime() - 3600;
    }
    rtc.adjust(standardTime);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  DateTime standardTime = rtc.now();

  Serial.println("Standard Time");
  printTheTime(standardTime);

  DateTime theTime = dst_rtc.calculateTime(standardTime); // takes into account DST

  Serial.println("time adjusted for Daylight Saving Time");
  printTheTime(theTime);

  delay(2000);

}


// print time to serial
void printTheTime(DateTime theTimeP) {
  Serial.print(theTimeP.year(), DEC);
  Serial.print('/');
  Serial.print(theTimeP.month(), DEC);
  Serial.print('/');
  Serial.print(theTimeP.day(), DEC);
  Serial.print(' ');
  Serial.print(theTimeP.hour(), DEC);
  Serial.print(':');
  Serial.print(theTimeP.minute(), DEC);
  Serial.print(':');
  Serial.print(theTimeP.second(), DEC);
  Serial.println();
}

# flex_DST
This algorithm is programmed to observe Daylight Saving Time based on a configuration given on the constructor. Since the rules for DST vary by country and territory, one can define the specific rules for any place.

requires [RTClib](https://github.com/adafruit/RTClib/)

Function to figure out if we're in Daylight Saving Time, then adding an hour if we are in DST.
Adapted from Andy Doro's library
https://github.com/andydoro/DST_RTC

https://en.wikipedia.org/wiki/Daylight_saving_time_by_country
This method doesn't check whether its 2am or not when the time change officially occurs.

The constructor receives the following parameters:

## flex_DST(uint8_t irregularity, uint8_t startDay, uint8_t startMonth, uint8_t endDay, uint8_t endMonth)

### irregularity
  (optional) A number that chooses the kind of DST configuration desired
  0   Sunday to Sunday. This is the default and this parameter can be ommited in most cases
  1   Friday to Sunday
  2   Friday to Friday
  3   Specific begining and end dates

### startDay
  (compulsory) Specifies which day the DST begins

  1   First Sunday/Friday of the month
  2   Second Sunday/Friday of the month
  3   Third Sunday/Friday of the month
  4   Fourth Sunday/Friday of the month
  5   Last Sunday/Friday of the month

  In the case of irregularity equal to 3, this parameter represents the exact day to begin the DST.

### startMonth
  (compulsory) Specifies the month in which DST begins (1-12)

### endDay
  (compulsory) Same arguments as startDay

### endMonth
  (compulsory) Same arguments as startMonth


## boolean flex_DST::checkDST(DateTime RTCTime)
  Returns whether the given date is within the DST


## DateTime calculateTime(DateTime RTCTime)
  Checks if a given DateTime is within the DST and adjusts it accordingly

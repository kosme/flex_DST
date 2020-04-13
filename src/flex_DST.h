#include <Arduino.h>
#include "RTClib.h"

class flex_DST
{
  public:
    flex_DST(uint8_t beginSunday, uint8_t beginMonth, uint8_t endSunday, uint8_t endMonth);
    /*
    Irregularities account for DST schedules that don't begin/end on a Sunday
    Irregularity  / Meaning
      0             DST begins and ends on a Sunday (Most of the world)
      1             DST begins on a Friday and ends on a Sunday (Israel)
      2             DST begins and ends on a Friday (Jordan, Syria)
      3             DST begins and ends on specific dates (Iran, Western Sahara)
    */
    flex_DST(uint8_t irregularity, uint8_t beginDay, uint8_t beginMonth, uint8_t endDay, uint8_t endMonth);
    boolean checkDST(DateTime RTCTime);
    DateTime calculateTime(DateTime RTCTime);

  private:
    uint8_t _irregularity;
    uint8_t _beginDay;
    uint8_t _beginMonth;
    uint8_t _endDay;
    uint8_t _endMonth;
    boolean _isLastSunday(uint8_t month, int previousSunday);
    uint8_t _daysInMonth(uint8_t month);
};

/*
    Function to figure out if we're in Daylight Saving Time, then adding an hour if we are in DST.
    Adapted from Andy Doro's library
    https://github.com/andydoro/DST_RTC
    This algorithm is programmed to observe Daylight Saving Time based on a configuration given on the constructor.
    Since the rules for DST vary by country and territory, one can define the specific rules for any place.

    https://en.wikipedia.org/wiki/Daylight_saving_time_by_country
    This method doesn't check whether its 2am or not when the time change officially occurs.
    This could be more accurate at the expense of being more complicated.

    First   1
    Second  2
    Third   3
    Fourth  4
    Last    5
*/

#include "flex_DST.h"

flex_DST::flex_DST(uint8_t beginSunday, uint8_t beginMonth, uint8_t endSunday, uint8_t endMonth)
{
  flex_DST(0, beginSunday, beginMonth, endSunday, endMonth);
}

flex_DST::flex_DST(uint8_t irregularity, uint8_t beginDay, uint8_t beginMonth, uint8_t endDay, uint8_t endMonth)
{
  _irregularity = irregularity & 0x03;
  _beginDay = beginDay;
  _beginMonth = beginMonth;
  _endDay = endDay;
  _endMonth = endMonth;
}

uint8_t flex_DST::_daysInMonth(uint8_t month){ //DST never begins / ends in February so it is not considered
  if(month < 8){
    return(month % 2 ? 31 : 30);
  } else {
    return(month % 2 ? 30 : 31);
  }
}

boolean flex_DST::_isLastSunday(uint8_t month, int previousSunday){
  return(previousSunday + 7 > _daysInMonth(month));
}

boolean flex_DST::checkDST(DateTime RTCTime)
{
  uint8_t currentDay = RTCTime.day();
  uint8_t currentMonth = RTCTime.month();
  uint8_t currentDOW = RTCTime.dayOfTheWeek();
  int previousSunday = currentDay - currentDOW;
  if(_beginMonth < _endMonth){ //Northern Hemisphere
    if((currentMonth > _beginMonth) && (currentMonth < _endMonth)){
      return true;
    }
  } else {
    if((currentMonth > _beginMonth) || (currentMonth < _endMonth)){
      return true;
    }
  }
  if(currentMonth == _beginMonth){
    if(_irregularity == 0){
      return(previousSunday > ( 7 * (_beginDay - 1)));
    } else if(_irregularity < 3){ //begins on Friday
      previousSunday = currentDay + 2 - ((currentDOW + 2) % 7);
      if(_beginDay < 5){
        return(previousSunday > ( 7 * (_beginDay - 1)));
      } else {
        return _isLastSunday(currentMonth, previousSunday);
      }
    } else {
      return currentDay >= _beginDay;
    }
  } else if(currentMonth == _endMonth){
    if(_irregularity < 2){
      if(_endDay < 5){
        return(previousSunday < (7 * (_endDay - 1)) + 1);
      } else {
        return !_isLastSunday(currentMonth, previousSunday);
      }
    } else if(_irregularity == 2){
      previousSunday = currentDay + 2 - ((currentDOW + 2) % 7);
      if(_endDay< 5){
        return(previousSunday < ( 7 * (_endDay - 1)) + 1);
      } else{
        return !_isLastSunday(currentMonth, previousSunday);
      }
    } else {
      return currentDay < _endDay;
    }
  } else {
    return false;
  }
}

DateTime flex_DST::calculateTime(DateTime RTCTime)
{
  return(checkDST(RTCTime) ? RTCTime.unixtime() + 3600 : RTCTime);
}

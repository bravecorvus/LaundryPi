#include <time.h>
#include <stdio.h>

class timeConversion{
	int year; /**< year for this timeConversion */
	int month; /**< month for this timeConversion */
	int day; /**< day for this timeConversion */
	int hours; /**< hours for this timeConversion */
	int minutes; /**< minutes for this timeConversion */
	int seconds; /**< seconds for this timeConversion */
public:
/** 1-argument constructor
	@param time Time for this timeConversion, to convert into human readable format*/
	timeConversion(time_t time);
/** 0-argument constructor
	@default values are set to create a human readable time*/
	timeConversion();
/** 1-argument constructor
	@param param ConvertedTime, copy into a new timeConversion object*/
	timeConversion(const timeConversion& param);
/** obtain time state variable
	@return The location of the state variable time for this timeConversion */
	char* getTime();
/** obtain year state variable
	@return The value of the state variable year for this timeConversion */
	int getYear();
/** obtain month state variable
	@return The value of the state variable month for this timeConversion */
	int getMonth();
/** obtain day state variable
	@return The value of the state variable day for this timeConversion */
	int getDay();
/** obtain minutes state variable
	@return The value of the state variable minutes for this timeConversion */
	int getMinutes();
/** obtain seconds state variable
	@return The value of the state variable seconds for this timeConversion */
	int getSeconds();
/** 1-argument method which sets year state variable based on parameter int y
	@return nothing */
	void setYear(int y);
/** 1-argument method which sets month state variable based on parameter int m
	@return nothing */
	void setMonth(int m);
/** 1-argument method which sets day state variable based on parameter int d
	@return nothing */
	void setDay(int d);
/** 1-argument method which sets hour state variable based on parameter int h
	@return nothing */
	void setHour(int h);
/** 1-argument method which sets minute state variable based on parameter int m
	@return nothing */
	void setMinute(int m);
/** 1-argument method which sets seconds state variable based on parameter int s
	@return nothing */
	void setSeconds(int s);
};
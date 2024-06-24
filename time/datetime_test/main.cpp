#include "Poco/LocalDateTime.h"
#include "Poco/DateTime.h"
#include "Poco/Timespan.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeParser.h"
#include "Poco/Timezone.h"
#include <iostream>


using Poco::LocalDateTime;
using Poco::DateTime;
using Poco::DateTimeFormat;
using Poco::DateTimeFormatter;
using Poco::DateTimeParser;
using Poco::Timespan;
using Poco::Timestamp;
#include <iostream>
#include <string>
#include <vector>
using namespace std;


using Poco::LocalDateTime;
using Poco::Timestamp;
using Poco::DateTime;
using Poco::Timezone;

#include <qapplication.h>
#include <qtextcodec.h>

void timestamp_test()
{
	cout << "------------------------------------------------------------" << endl;
	cout << "                       Timestamp Test                       " << endl;
	cout << "------------------------------------------------------------" << endl;

	//-------------------------------------------------------------
	//						Init
	//-------------------------------------------------------------
	//1 Default init
	Timestamp now;
	printf("Now is %lld\n",now.epochMicroseconds());
	
	//2 Init by Int64 value
	time_t c_time = time(NULL);
	Timestamp current1 = (double)c_time*1000000;
	printf("Now current1 is %lld\n",current1.epochMicroseconds());

	//3 Init by another obj
	Timestamp current2 = current1;
	printf("Now current2 is %lld\n",current2.epochMicroseconds());

	//4 Init by time_t
	Timestamp current3 = Timestamp::fromEpochTime(c_time);
	printf("Now current3 is %lld\n",current2.epochMicroseconds());


	//-------------------------------------------------------------
	//						   Elapsed
	//-------------------------------------------------------------

	//Elaspsed time
	for(int i=0; i < 100000; i++);
	Timestamp::TimeDiff diff = now.elapsed();
	printf("Elapsed millsec is %lld\n",diff);

	//-------------------------------------------------------------
	//						 Timevalue operation
	//-------------------------------------------------------------

}

void datetime_test()
{
	cout << "------------------------------------------------------------" << endl;
	cout << "                       Datetime Test                        " << endl;
	cout << "------------------------------------------------------------" << endl;
	Timestamp now;
	DateTime dt = now;

	//dt.makeUTC();
	string gmt_string  = DateTimeFormatter::format(dt,DateTimeFormat::SORTABLE_FORMAT);
	cout << "GMT time is \t" << gmt_string << endl;


	dt.makeLocal(Timezone::tzd());
	string local_string  = DateTimeFormatter::format(dt,DateTimeFormat::SORTABLE_FORMAT);
	cout << "Date time is \t" << local_string << endl;

	DateTime utcdt = now;
	//注意此处给出了时区的话，如果是makeutc时间，是减去不是加上
	utcdt.makeUTC(Timezone::tzd());
	string utc_string = DateTimeFormatter::format(utcdt,DateTimeFormat::SORTABLE_FORMAT);
	cout << "UTC time is \t" << utc_string << endl;
}


void localdatetime_test()
{
	cout << "------------------------------------------------------------" << endl;
	cout << "                  LocalDatetime Test                        " << endl;
	cout << "------------------------------------------------------------" << endl;
	Timestamp tt ;
	DateTime dt = tt;
	LocalDateTime bj_ldt(Timezone::tzd,dt);
	LocalDateTime lon_ldt(0,dt);

	string bj_string = DateTimeFormatter::format(bj_ldt,DateTimeFormat::SORTABLE_FORMAT);
	string lon_string = DateTimeFormatter::format(lon_ldt,DateTimeFormat::SORTABLE_FORMAT);
	cout << "Beijin: \t" << bj_string << endl;
	cout << "London: \t" << lon_string << endl;
}

void timezone_test()
{
	cout << "------------------------------------------------------------" << endl;
	cout << "                       Timezone Test                        " << endl;
	cout << "------------------------------------------------------------" << endl;

	//---------------------------------------
	// Timezone 函数都为static，可以直接使用
	//---------------------------------------

	//Timezone print
	cout << "Timezone: " << Timezone::name() << "Standard Name:" << Timezone::standardName() <<"  Timediff:" << Timezone::tzd() << endl;
	// 夏令时
	cout << "Dist: " << Timezone::dstName << " Dis: " << Timezone::dst() << endl; 
}


void timespan_test()
{
	cout << "------------------------------------------------------------" << endl;
	cout << "                       Timespan Test                        " << endl;
	cout << "------------------------------------------------------------" << endl;	
	
	//DateTime 使用
	Timespan sp1;
	DateTime d1(2024,1,1);
	DateTime d2(2024,6,1);

	sp1 = d2.timestamp() - d1.timestamp();
	cout << " Time span day " << sp1.days() << endl;

	Timespan sp2 = d2 - d1;
	
	//LocalDateTime 使用
	LocalDateTime ldt1(2024,1,1);
	LocalDateTime ldt2(2024,2,2);
	Timespan sp3 = ldt2 - ldt1;


}

void timeformat_paraser_test()
{
	cout << "------------------------------------------------------------" << endl;
	cout << "                      Timeformat Test                       " << endl;
	cout << "------------------------------------------------------------" << endl;	
	Timespan sp1;
	Timestamp tt ;
	DateTime dt = tt;
	dt.makeLocal(Timezone::tzd());
	
	//生成指定时间的字符串
	string format1 = DateTimeFormatter::format(dt,DateTimeFormat::SORTABLE_FORMAT);
	cout << "Sortable format: \t\t"  << format1 << endl;
	string fromat2 = DateTimeFormatter::format(dt,DateTimeFormat::HTTP_FORMAT);
	cout << "Http format: \t\t"  << fromat2 << endl;
	string fromat3 = DateTimeFormatter::format(dt,DateTimeFormat::ISO8601_FORMAT);
	cout << "ISO8601 format: \t\t" << fromat3 << endl;
	string fromat4 = DateTimeFormatter::format(dt,DateTimeFormat::ISO8601_FRAC_FORMAT);
	cout << "ISO8601_FRAC format: \t\t"<< fromat4 << endl;
	string fromat5 = DateTimeFormatter::format(dt,DateTimeFormat::RFC1036_FORMAT);
	cout << "RFC1036 format: \t\t"<< fromat5 << endl;
	string fromat6 = DateTimeFormatter::format(dt,DateTimeFormat::RFC1123_FORMAT);
	cout << "RFC1123 format: \t\t" << fromat6 << endl;
	string fromat7 = DateTimeFormatter::format(dt,DateTimeFormat::RFC850_FORMAT);
	cout << "RFC850 format: \t\t"<< fromat7 << endl;
	string fromat8 = DateTimeFormatter::format(dt,DateTimeFormat::RFC822_FORMAT);
	cout << "RFC822 format: \t\t" << fromat8 << endl;

	//解析指定格式的字符串时间
	DateTime new_dt;
	int tzd;
	DateTimeParser::parse(DateTimeFormat::SORTABLE_FORMAT, format1, dt, tzd);
	dt.makeLocal(tzd);

	cout << "Year:" << new_dt.year() << " Month:" << new_dt.month() << " Day:" << new_dt.day() << " Hour:" << new_dt.hour() << " Min:" << new_dt.minute() << " Sec:" << new_dt.second() << endl;
	
}


int main(int argc, char** argv)
{
	timestamp_test();
	datetime_test();
	localdatetime_test();
	timezone_test();
	timespan_test();
	timeformat_paraser_test();

	return 0;
}

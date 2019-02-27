#include <iostream>
#include <stdio.h>



class weather_msg
{

    public:	
	int message_code;
#define GET_BY_CITY_NAME 1
#define GET_BY_CITY_ID 2 
#define GET_BY_LON_LAT 3
#define GET_BY_ZIP_CODE 4
		
		int getCurrentTemp(int city_id)
		{
			std::cout<< "Server: get by city ID\n";
		}
		int getCurrentTemp(float lon, float lat)
		{
			std::cout<< "Server: get by LON LAT\n";
		}
#if 0
		int getCurrentTemp(string city_name)
		{
			std::cout<< "Server: get by city name\n";
		}
		int getCurrentTemp(string zip_code, int const)
		{
			std::cout<< "Server: get by ZIP CODE\n";
		}
#endif	
}weather_msg_t;
		
		
	


#include <iostream>
#include <stdio.h>



class weather_msg
{

    public:	
	int message_code;
	enum query_type{ 
		GET_BY_CITY_ID=1, 
		GET_BY_LON_LAT,
		GET_BY_CITY_NAME,
		GET_BY_ZIP_CODE
	};
	int city_id;
	float lon;
	float lat;
	std::string city_name;
	char zip_code[10];
	int getCurrentTemp(int city_id);
	int getCurrentTemp(float lon, float lat);
	int getCurrentTemp(std::string city_name);
	int getCurrentTemp(char zip_code[]);
}weather_msg_t;
		
		
	


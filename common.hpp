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
	int getCurrentTemp(int city_id, std::string *output_buf);
	int getCurrentTemp(float lon, float lat, std::string *output_buf);
	int getCurrentTemp(std::string city_name, std::string *output_buf);
	int getCurrentTemp(char zip_code[], std::string *output_buf);
}weather_msg_t;
		
		
	


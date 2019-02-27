#include <iostream>



Class Weather_msg
{

	private:
		int message_code;
#define GET_BY_CITY_NAME 1
#define GET_BY_CITY_ID 2 
#define GET_BY_LON_LAT 3
#define GET_BY_ZIP_CODE 4
	public:
		int getCurrentTemp(string city_name)
		{
			cout<< "Server: get by city name\n";
		}
		
		int getCurrentTemp(int city_id)
		{
			cout<< "Server: get by city ID\n";
		}
		int getCurrentTemp(float lon, flot lat)
		{
			cout<< "Server: get by LON LAT\n";
		}
		int getCurrentTemp(string zip_code, int const)
		{
			cout<< "Server: get by ZIP CODE\n";
		}
	
}
		
		
	


#include <iostream>
#include <string>
#include <fstream>
#include <common.hpp>
#include <unistd.h>


using namespace std;

int json_curl_main(std::string query);
class server_class {

	std::string appid;
public:
	void getAppId(std::string *appid){
		//TODO Read from file sometime
#if 0 
	     std::ifstream fs
	     fs.open("appid.txt", std::fstream::in);
	     if (!fd) {
		     std::cout << "Error reading appid file\n";
		     appid->assign(" ");
		     return;
	     }
	     fd.seekg(0, fd.end);
	     int len = fd.tellg();
	     char *app = new char[len];
	     fd.read(app, len);
	     std::cout << "appid " << app << std::endl;
	     appid->assign(app); 
	     delete[] app;
#endif
	     appid->assign("9ed0909d64301bdbfd30f7a8d1b7df88");
	     return;

	}

}server_class_t;

	
	int weather_msg::getCurrentTemp(int city_id)
	{
		std::cout<< "Server: get by city ID\n";
		server_class server_app;
		std::string appid, query_url;
	        char buf[100];	
		server_app.getAppId(&appid);
		sprintf(buf, "id=%d&&appid=%s", \
				city_id,appid.c_str());
		query_url.assign(buf);
		json_curl_main(query_url);
		
	}
	int weather_msg::getCurrentTemp(float lon, float lat)
	{
		std::cout<< "Server: get by LON LAT\n";
		server_class server_app;
		std::string appid, query_url;
	        char buf[100];	
		server_app.getAppId(&appid);
		sprintf(buf, "lon=%f&lat=%f&&appid=%s", \
				lon, lat, appid.c_str());
		query_url.assign(buf);
		json_curl_main(query_url);
	}
	int weather_msg::getCurrentTemp(std::string city_name)
	{
		std::cout<< "Server: get by city name\n";
		server_class server_app;
		std::string appid, query_url;
	        char buf[100];	
		server_app.getAppId(&appid);
		sprintf(buf, "q=%s&&appid=%s", \
				city_name.c_str(),appid.c_str());
		query_url.assign(buf);
		json_curl_main(query_url);
	}
	int weather_msg::getCurrentTemp(char zip_code[])
	{
		std::cout<< "Server: get by ZIP CODE\n";
		server_class server_app;
		std::string appid, query_url;
	        char buf[100];	
		server_app.getAppId(&appid);
		sprintf(buf, "zip=%s&&appid=%s", \
				zip_code,appid.c_str());
		query_url.assign(buf);
		std::cout<< buf << "\nServer " <<query_url.c_str() << std::endl;
		json_curl_main(query_url);
	}

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <curl/curl.h>
#include <json/value.h>
#include <fstream>
#include <json/reader.h>

#define URL_STATIC "api.openweathermap.org/data/2.5/weather?"


static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}



std::string curl_function(std::string query)
{
  CURL *curl;
  CURLcode res;
  std::string readBuffer;
  std::string appid;
  std::string url = URL_STATIC;
  appid.assign(query.c_str());
  curl = curl_easy_init();
  if(curl) {
   
    curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_ANY);
    curl_easy_setopt(curl, CURLOPT_AUTOREFERER , 1); 
    url.append(appid);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_USERAGENT,  "TEST");
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    
    curl_easy_cleanup(curl);

    std::cout << url.c_str() << "\n\n\n"  << readBuffer  << std::endl;
  }
  return readBuffer;
}

char * json_curl_main(std::string query)
{
    std::string readBuffer, temp_buf;
    Json::Reader reader;
    Json::Value val_field;
    float temp;
    std::string cityname;
    int rc = 0;
    readBuffer = curl_function(query);
    rc = reader.parse(readBuffer, val_field);
    temp = val_field["main"]["temp"].asFloat();
    cityname = val_field["name"].asString();
    char *output_buf = new char[50];
    memset((void *)output_buf, '\0', 50);
    if (temp == 0.0) {
    	sprintf(output_buf, 
		"Error: Data for requested input - NOT FOUND\n");  
    } else { 
    	sprintf(output_buf, "%s - %f", cityname.c_str(), temp);
    }	
    std::cout <<"Server: Send output**\n" << output_buf << std::endl;		    
    return output_buf;

}

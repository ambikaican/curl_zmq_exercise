#include <iostream>
#include <string>
#include <curl/curl.h>


static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main(int argc, char*argv[])
{
  CURL *curl;
  CURLcode res;
  std::string readBuffer;
  std:: string url; 
  //Format "api.openweathermap.org/data/2.5/weather?zip=08820&mode=xml&appid=9ed0909d64301bdbfd30f7a8d1b7df88";
  if (argc == 2) 
  {
	url.assign(argv[1]);
  } else {
	std::cout << "Input url\n";
	return -1;
  }
  curl = curl_easy_init();
  if(curl) {
   
    curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_ANY);
    curl_easy_setopt(curl, CURLOPT_AUTOREFERER , 1); 


    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_USERAGENT,  "TEST");
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    
    curl_easy_cleanup(curl);

    std::cout << readBuffer << std::endl;
  }
  return 0;
}


#include<iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

struct AccessRoutes {
	// curl handler and curl code for sending request and checking responses
	CURL *easyHandle;							  
	CURLcode curlRes;
	std::string res;

	AccessRoutes() {
		/* In windows, this will init the winsock stuff */
		curl_global_init(CURL_GLOBAL_ALL);
					
		// initialize curl handler
		easyHandle = curl_easy_init();
		curlRes = CURLE_OK;
	}

	~AccessRoutes() {
		// Clean up curl handler
		if (easyHandle) {
			curl_easy_cleanup(easyHandle);
		}
		// clean up global init
		curl_global_cleanup();
	}

	// callback function for curl
	static size_t writeCallback(char* resPtr, size_t size, size_t nmemb, std::string* myData) {
		myData->append(resPtr, size * nmemb); // appends the respons to myData pointer
		return size * nmemb;// returns number of bytes written 					
	}
};

int main() {
	// strings for storing responses and URL
	std::string res, 
		URL = "https://hackdiversity.xyz/api/test/mockRoutes",
		START_URL = "https://hackdiversity.xyz/api/start-session";

	AccessRoutes* accessRoutes = new AccessRoutes();

	// Create json header fields
	json jsonPostData;
	jsonPostData["firstName"] = "Yelsin";
	jsonPostData["lastName"] = "Sepulveda";
	std::cout << "post headers: " << jsonPostData << std::endl;
	std::string postData = jsonPostData.dump(4);

	if (accessRoutes->easyHandle) {
		// get session_id
		
		// get routes using session_id

		// filter and sort routes
		
		
	}
	delete accessRoutes;
	accessRoutes = nullptr;
	
	std::cin.get();

	return 0;
}
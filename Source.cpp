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
	
	json getAuthHeader(std::string url, std::string postData) {
		// clear reponse from last call if any
		res.clear();
		
		// call post function to url using postData as header/post content
		return curlPost(url, postData);		 
	}
	
	json curlPost(std::string url, std::string postData) {
		json jsonRes;

		// set option for curl
		curl_easy_setopt(easyHandle, CURLOPT_URL, url.c_str());					// set url
		curl_easy_setopt(easyHandle, CURLOPT_POST, 1L);							// set option to post
		curl_easy_setopt(easyHandle, CURLOPT_POSTFIELDS, postData.c_str());		// set contents of post
		curl_easy_setopt(easyHandle, CURLOPT_WRITEFUNCTION, writeCallback);		// set callback function
		curl_easy_setopt(easyHandle, CURLOPT_WRITEDATA, &res );					// set callback datatype 

		// Set Content-Type header to application/json
		struct curl_slist* headers = nullptr;
		headers = curl_slist_append(headers, "Content-Type: application/json");
		curl_easy_setopt(easyHandle, CURLOPT_HTTPHEADER, headers);				// set header content/type

		// perform curl call and store response
		curlRes = curl_easy_perform(easyHandle);

		// check if call was succesfull
		if (curlRes != CURLE_OK) { 
			std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(curlRes) << std::endl;
		}
		else {		// if so, print and return
			jsonRes = json::parse(res);				
			std::cout << jsonRes.dump(4) << std::endl;
		}
		// Clean up the headers list 
		curl_slist_free_all(headers);
		return jsonRes;
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
		json authHeaderJson = accessRoutes->getAuthHeader(START_URL, postData); // get session-id
		std::cout << "session_id: " << authHeaderJson["session_id"] << std::endl;
		
		// get routes using session_id

		// filter and sort routes
		
		
	}
	delete accessRoutes;
	accessRoutes = nullptr;
	
	std::cin.get();

	return 0;
}
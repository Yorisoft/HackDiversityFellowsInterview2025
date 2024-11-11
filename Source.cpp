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
	
	json getRoutes(std::string url, json authHeader) {
		// clear reponse from last call if any
		res.clear();

		// call get function to url using postData as header/post content
		return curlGet(url, authHeader);
	}
	
	json submitResult(std::string url, std::string postData, json authHeader) {
		
		json jsonRes;

		// clear reponse from last call if any
		res.clear();

		// Extract session_id and create the header string 
		std::string sessionId = authHeader["session_id"].get<std::string>(); 
		std::string sessionHeader = "Authorization: Bearer " + sessionId;
		std::cout << "sessionHeader: " << sessionHeader << std::endl;

		//std::cin.get();

		// set option for curl
		curl_easy_setopt(easyHandle, CURLOPT_URL, url.c_str());					// set url
		curl_easy_setopt(easyHandle, CURLOPT_POST, 1L);							// set option to post
		curl_easy_setopt(easyHandle, CURLOPT_POSTFIELDS, postData.c_str());		// set contents of post
		curl_easy_setopt(easyHandle, CURLOPT_WRITEFUNCTION, writeCallback);		// set callback function
		curl_easy_setopt(easyHandle, CURLOPT_WRITEDATA, &res );					// set callback datatype 

		// Set Content-Type header to application/json
		struct curl_slist* headers = nullptr;
		headers = curl_slist_append(headers, "Content-Type: application/json");
		headers = curl_slist_append(headers, sessionHeader.c_str());
		curl_easy_setopt(easyHandle, CURLOPT_HTTPHEADER, headers);				// set header content/type

		// perform curl call and store response
		curlRes = curl_easy_perform(easyHandle);

		// check if call was succesfull
		if (curlRes != CURLE_OK) { 
			std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(curlRes) << std::endl;
		}
		else {		// if so, print and return
			jsonRes = json::parse(res);				
			std::cout << "this is submitMockResponse res: " <<  jsonRes.dump(4) << std::endl;
		}
		// Clean up the headers list 
		curl_slist_free_all(headers);
		return jsonRes;

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

	json curlGet(std::string url, json authHeader) {
		json jsonRes;
		
		// Extract session_id and create the header string 
		std::string sessionId = authHeader["session_id"].get<std::string>(); 
		std::string sessionHeader = "Authorization: Bearer " + sessionId;
		std::cout << "sessionHeader: " << sessionHeader << std::endl;

		// set option for curl
		curl_easy_setopt(easyHandle, CURLOPT_URL, url.c_str());
		curl_easy_setopt(easyHandle, CURLOPT_HTTPGET, 1L);							// set option to post	
		curl_easy_setopt(easyHandle, CURLOPT_WRITEFUNCTION, writeCallback);
		curl_easy_setopt(easyHandle, CURLOPT_WRITEDATA, &res );

		// Set the authorization header 
		struct curl_slist* headers = nullptr; 
		headers = curl_slist_append(headers, sessionHeader.c_str());
		curl_easy_setopt(easyHandle, CURLOPT_HTTPHEADER, headers);

		// perform curl call and store response
		curlRes = curl_easy_perform(easyHandle);

		if (curlRes != CURLE_OK) {					// check if call was succesfull
			std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(curlRes) << std::endl;
		}
		else {
			jsonRes = json::parse(res);				// turn res into json obj
			std::cout << jsonRes.dump(4) << std::endl;
		}

		// Clean up the headers list 
		curl_slist_free_all(headers);
		return jsonRes;
	}
};

int main() {
	// strings for storing responses and URL
	 const std::string
		START_URL = "https://hackdiversity.xyz/api/start-session",
		MOCK_ROUTE_URL = "https://hackdiversity.xyz/api/test/mockRoutes",
		MOCK_SUBMIT_URL = "https://hackdiversity.xyz/api/test/submit-sorted-routes",
		ROUTE_URL = "https://hackdiversity.xyz/api/navigation/routes",
		SUBMIT_URL = "https://hackdiversity.xyz/api/navigation/sorted_routes";

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
		
		// get MOCK routes using session_id
		json routes = accessRoutes->getRoutes(ROUTE_URL, authHeaderJson);
		
		// filter and sort routes
		// create new json array to hold filtered value
		json filteredRoutes = json::array();
		
		std::cin.get();

		//for each entry in routes that is true, add to filteredRoutes
		for (json& route : routes) {
			if (route["accessible"] == true) {
				filteredRoutes.push_back(route);
			}
		}
		std::cout << "Filtered routes by accessible equals true: " << filteredRoutes.dump(4) << std::endl;

		int minIndex, minValue;
		//sort routes by distance. going with selection sort
		for (int i = 0; i < filteredRoutes.size() - 1; i++) {
			// keep track of the part of the array thats yet to be sorted. Starting at 0. this will me minIndex.
			// As i moves through the array, everything before i should be in order. 
			// Not checking the last element, inner loop will check the last two element and order them.
			minIndex = i;
			for (int j = i + 1; j < filteredRoutes.size(); j++) {
				// if we find an element that is less than filteredRoutes[minIndex], 
				// make minIndex = the index of that element.
				if (filteredRoutes[j]["distance"] < filteredRoutes[minIndex]["distance"]) {
					minIndex = j;
				}
			}
			//swap element at index i with element at index minIndex
			json temp = filteredRoutes[i];
			filteredRoutes[i] = filteredRoutes[minIndex];
			filteredRoutes[minIndex] = temp;
		}
		std::cout << "Sorted routes by distance in accending order: " << filteredRoutes.dump(4) << std::endl;
		
		// submit result to mock-submit-endpoint
		json mockSumbmissionResults = accessRoutes->submitResult(SUBMIT_URL, filteredRoutes.dump(), authHeaderJson);
	}
	// clean up
	delete accessRoutes;
	accessRoutes = nullptr;
	
	// pause terminal before close 
	std::cin.get();

	return 0;
}
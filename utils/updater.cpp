//
// Created by matis on 02/07/2023.
//

#include "../common.h";
#include <iostream>
#include <curl/curl.h>
#include <string>
#include <cstring>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>

struct UpdateInfo {
    std::string version;
    std::string lien;
    std::string informations;
};

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response) {
    size_t totalSize = size * nmemb;
    response->append((char*)contents, totalSize);
    return totalSize;
}

std::string PerformGETRequest(const std::string& url) {
    std::string response;
    CURL* curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "Erreur lors de la requête HTTP : " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    return response;
}

void update() {

}

void reinstall() {

}

void forceReinstall() {

}

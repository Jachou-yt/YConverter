#include <iostream>
#include <string>
#include <exception>
#include <Windows.h>
#include "json.cpp"
#include <conio.h>

std::string GetCurrentDirectory()
{
    char buffer[MAX_PATH];
    GetModuleFileNameA(nullptr, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");

    return std::string(buffer).substr(0, pos);
}


int main() {
    std::string url;
    bool logs = false;

    if (!initiated()) {
        createJson();

        std::cout << "Json file created" << std::endl;
    }

    std::string file = "info.json";

    if (!fileContainsCharacter(file) || jsonIsNull()) {
        initJson();
    }

    std::cout << "Please enter youtube URL : ";
    std::getline(std::cin, url);

    if (url.find(url) == std::string::npos) {
        std::cout << "Invalid URL" << std::endl;
        return 0;
    } else {
        std::cout << "Valid URL" << std::endl;
    }

    std::ifstream jsonFile(file);

    if (!jsonFile.is_open()) {
        std::cerr << "The file can't be open." << std::endl;
        return 0;
    }

    std::string jsonContent((std::istreambuf_iterator<char>(jsonFile)), std::istreambuf_iterator<char>());

    jsonFile.close();

    nlohmann::json jsonObj = nlohmann::json::parse(jsonContent);

    std::string destination = jsonObj["destination"];


    if (destination.find(destination) == std::string::npos) {
        std::cout << "Invalid file destination" << std::endl;
        return 0;
    } else {
        std::cout << "Valid file destination" << std::endl;
    }

    std::string verboseString = jsonObj["verbose"];
    std::string path = jsonObj["path"];
    bool verbose;

    if (verboseString == "true") {
        verbose = true;
    } else {
        verbose = false;
    }

    // Download the video
    try {
        if (verbose) {
            std::cout << "Downloading..." << std::endl;
            std::string command = path + "/yt-dlp_min.exe --verbose --ignore-errors -o \"" + destination + "/%(title)s.%(ext)s\" " + url;
            system(command.c_str());
        } else {
            std::cout << "Downloading..." << std::endl;
            std::string command = path + "/yt-dlp_min.exe --ignore-errors -o \"" + destination + "/%(title)s.%(ext)s\" " + url;
            system(command.c_str());
        }
    } catch (std::exception& e) {
        std::cout << "Error : " << e.what() << std::endl;
    }

    std::cout << "Download completed" << std::endl;

    return 0;
}

#include <iostream>
#include <string>
#include <exception>
#include <Windows.h>

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

    std::cout << "Please enter youtube URL : ";
    std::getline(std::cin, url);

    // Check if the URL is valid
    if (url.find(url) == std::string::npos) {
        std::cout << "Invalid URL" << std::endl;
        return 0;
    } else {
        std::cout << "Valid URL" << std::endl;
    }

    // File destination
    std::string destination;
    std::cout << "Please enter a file destination : ";
    std::getline(std::cin, destination);

    // Check if the file destination is valid
    if (destination.find(destination) == std::string::npos) {
        std::cout << "Invalid file destination" << std::endl;
        return 0;
    } else {
        std::cout << "Valid file destination" << std::endl;
    }

    std::string verbose;
    std::cout << "Do you want to see the logs ? (y/n) : ";
    std::getline(std::cin, verbose);

    if (verbose == "y") {
        logs = true;
    } else if (verbose == "n") {
        logs = false;
    } else {
        std::cout << "Invalid answer" << std::endl;
        return 0;
    }

    // Download the video
    try {
        if (logs) {
            std::cout << "Downloading..." << std::endl;
            std::string command = GetCurrentDirectoryA() + "/yt-dlp_min.exe --verbose --ignore-errors -o \"" + destination + "/%(title)s.%(ext)s\" " + url;
            system(command.c_str());
        } else {
            std::cout << "Downloading..." << std::endl;
            std::string command = GetCurrentDirectoryA() + "/yt-dlp_min.exe --ignore-errors -o \"" + destination + "/%(title)s.%(ext)s\" " + url;
            system(command.c_str());
        }
    } catch (std::exception& e) {
        std::cout << "Error : " << e.what() << std::endl;
    }

    std::cout << "Download completed" << std::endl;

    return 0;
}

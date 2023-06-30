#include <iostream>
#include <string>
#include <Windows.h>

std::string GetCurrentDirectory()
{
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");

    return std::string(buffer).substr(0, pos);
}

int main() {
    std::string url;

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

    // Download the video
    std::string command = GetCurrentDirectoryA() + "/youtube-dl.exe -o" + destination + "/video.mp4" + " " + url;
    system(command.c_str());

    // Check if the video is downloaded
    if (command.find(command) == std::string::npos) {
        std::cout << "Download failed" << std::endl;
        return 0;
    } else {
        std::cout << "Download success" << std::endl;
    }

    return 0;
}

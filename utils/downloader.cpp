//
// Created by matis on 01/07/2023.
//

#include <iostream>
#include <thread>
#include <string>

void downloadVideo(const std::string& path, const std::string& destination, const std::string& url, bool verbose) {
    std::string command = path + "/yt-dlp_min.exe --ignore-errors -o \"" + destination + "/%(title)s.%(ext)s\" " + url;
    if (verbose) {
        std::cout << "Downloading..." << std::endl;
        command += " --verbose";
        system(command.c_str());
    } else {
        std::cout << "Downloading..." << std::endl;
        system(command.c_str());
    }
}

void downloadMultipleVideo(const std::string& path, const std::string& destination, std::string urls[], int length, bool verbose) {
    for (int i = 0; i < length; i++) {
        downloadVideo(path, destination, urls[i], verbose);
    }
}
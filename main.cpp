#include <iostream>
#include <string>
#include <exception>
#include <Windows.h>
#include <conio.h>
#include "json.cpp"

std::string GetCurrentDirectory()
{
    char buffer[MAX_PATH];
    GetModuleFileNameA(nullptr, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");

    return std::string(buffer).substr(0, pos);
}


int main() {
    std::string choice;
    std::string url;

    /*
     * Json file content
     */
    std::string destination;
    std::string path;
    std::string verboseString;
    bool verbose;

    std::cout << " __    __  ____                                                __                     \n"
                 "/\\ \\  /\\ \\/\\  _`\\                                             /\\ \\__                  \n"
                 "\\ `\\`\\\\/'/\\ \\ \\/\\_\\    ___     ___     __  __     __    _ __  \\ \\ ,_\\     __    _ __  \n"
                 " `\\ `\\ /'  \\ \\ \\/_/_  / __`\\ /' _ `\\  /\\ \\/\\ \\  /'__`\\ /\\`'__\\ \\ \\ \\/   /'__`\\ /\\`'__\\\n"
                 "   `\\ \\ \\   \\ \\ \\L\\ \\/\\ \\L\\ \\/\\ \\/\\ \\ \\ \\ \\_/ |/\\  __/ \\ \\ \\/   \\ \\ \\_ /\\  __/ \\ \\ \\/ \n"
                 "     \\ \\_\\   \\ \\____/\\ \\____/\\ \\_\\ \\_\\ \\ \\___/ \\ \\____\\ \\ \\_\\    \\ \\__\\\\ \\____\\ \\ \\_\\ \n"
                 "      \\/_/    \\/___/  \\/___/  \\/_/\\/_/  \\/__/   \\/____/  \\/_/     \\/__/ \\/____/  \\/_/ \n"
                 "                                                                                      \n"
                 "                                                                                      \n"
                 "" << std::endl;

    if (!initiated()) {
        createJson();

        std::cout << "Json file created" << std::endl;
    }

    std::string file = "info.json";

    if (!fileContainsCharacter(file) || jsonIsNull()) {
        initJson();
    }

    while (true) {
        std::cout << "[1] Download a video" << std::endl;
        std::cout << "[2] Modify json information" << std::endl;
        std::cout << "[3] Exit" << std::endl;
        std::cout << "Choice : ";
        std::getline(std::cin, choice);

        if (choice == "1") {
            std::cout << "Enter the URL of the video : ";
            std::getline(std::cin, url);

            if (url.find(url) == std::string::npos) {
                std::cout << "Invalid URL" << std::endl;
                return 0;
            } else {
                std::cout << "Valid URL" << std::endl;

                std::ifstream jsonFile(file);

                if (!jsonFile.is_open()) {
                    std::cerr << "The file can't be open." << std::endl;
                    return 0;
                }

                std::string jsonContent((std::istreambuf_iterator<char>(jsonFile)), std::istreambuf_iterator<char>());

                jsonFile.close();

                nlohmann::json jsonObj = nlohmann::json::parse(jsonContent);

                destination = jsonObj["destination"];


                if (destination.find(destination) == std::string::npos) {
                    std::cout << "Invalid file destination" << std::endl;
                    std::cout << "Please modify the json file" << std::endl;
                    std::cout << "Press any key to continue..." << std::endl;
                    getch();
                } else {
                    std::cout << "Valid file destination" << std::endl;
                }

                verboseString = jsonObj["verbose"];
                path = jsonObj["path"];

                if (verboseString == "true") {
                    verbose = true;
                } else {
                    verbose = false;
                }

                // Download the video
                try {
                    std::string command = path + "/yt-dlp_min.exe --ignore-errors -o \"" + destination + "/%(title)s.%(ext)s\" " + url;

                    if (verbose) {
                        std::cout << "Downloading..." << std::endl;
                        command = command + " --verbose";
                        system(command.c_str());
                    } else {
                        std::cout << "Downloading..." << std::endl;
                        system(command.c_str());
                    }
                } catch (std::exception& e) {
                    std::cout << "Error : " << e.what() << std::endl;
                    std::cout << "Press any key to continue..." << std::endl;
                    getch();
                }

                std::cout << "Download completed in the folder " + destination << std::endl;
                std::cout << "Press any key to continue..." << std::endl;
                getch();

            }

        } else if (choice == "2") {
            std::cout << "Change the directoy wehre the videos are downloaded : ";
            std::getline(std::cin, destination);

            std::cout << "Change the path of YConverter : ";
            std::getline(std::cin, path);

            std::cout << "Do you want to see the download progression ? (y/n) : ";
            std::getline(std::cin, verboseString);

            if (verboseString == "y") {
                verboseString = "true";
            } else {
                verboseString = "false";
            }

            modify(path, destination, verboseString);
        } else if (choice == "3") {
            return 0;
        } else {
            std::cout << "Invalid choice" << std::endl;
        }
    }
}

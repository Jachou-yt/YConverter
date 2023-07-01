#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include "utils/json.cpp"
#include "utils/downloader.cpp"
#include "utils/updater.cpp"


std::string GetCurrentDirectory()
{
    std::string buffer(MAX_PATH, '\0');
    GetModuleFileNameA(nullptr, &buffer[0], MAX_PATH);
    std::string::size_type pos = buffer.find_last_of("\\/");
    std::string currentDirectory = buffer.substr(0, pos);

    return currentDirectory;
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

    std::string logo =
            " __    __  ____                                                __                     \n"
            "/\\ \\  /\\ \\/\\  _`\\                                             /\\ \\__                  \n"
            "\\ `\\`\\\\/'/\\ \\ \\/\\_\\    ___     ___     __  __     __    _ __  \\ \\ ,_\\     __    _ __  \n"
            " `\\ `\\ /'  \\ \\ \\/_/_  / __`\\ /' _ `\\  /\\ \\/\\ \\  /'__`\\ /\\`'__\\ \\ \\ \\/   /'__`\\ /\\`'__\\\n"
            "   `\\ \\ \\   \\ \\ \\L\\ \\/\\ \\L\\ \\/\\ \\/\\ \\ \\ \\ \\_/ |/\\  __/ \\ \\ \\/   \\ \\ \\_ /\\  __/ \\ \\ \\/ \n"
            "     \\ \\_\\   \\ \\____/\\ \\____/\\ \\_\\ \\_\\ \\ \\___/ \\ \\____\\ \\ \\_\\    \\ \\__\\\\ \\____\\ \\ \\_\\ \n"
            "      \\/_/    \\/___/  \\/___/  \\/_/\\/_/  \\/__/   \\/____/  \\/_/     \\/__/ \\/____/  \\/_/ \n"
            "                                                                                      \n"
            "                                                                                      \n";

    std::cout << logo << std::endl;

    if (!initiated()) {
        createJson();

        std::cout << "Json file created" << std::endl;
    }

    std::string file = "info.json";

    if (!fileContainsCharacter(file) || jsonIsNull()) {
        initJson();
    }

    std::ifstream jsonFile(file);

    if (!jsonFile.is_open()) {
        std::cerr << "The file can't be open." << std::endl;
        return 0;
    }

    std::string jsonContent((std::istreambuf_iterator<char>(jsonFile)), std::istreambuf_iterator<char>());

    jsonFile.close();

    nlohmann::json jsonObj = nlohmann::json::parse(jsonContent);

    destination = jsonObj["destination"];

    verboseString = jsonObj["verbose"];
    path = jsonObj["path"];

    while (true) {
        std::cout << "[1] Download a video" << std::endl;
        std::cout << "[2] Download multiple video" << std::endl;
        std::cout << "[3] Modify json information" << std::endl;
        std::cout << "[4] Exit" << std::endl;
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

                if (destination.find(destination) == std::string::npos) {
                    std::cout << "Invalid file destination" << std::endl;
                    std::cout << "Please modify the json file" << std::endl;
                    std::cout << "Press any key to continue..." << std::endl;
                    getch();
                } else {
                    std::cout << "Valid file destination" << std::endl;
                }

                if (verboseString == "true") {
                    verbose = true;
                } else {
                    verbose = false;
                }

                downloadVideo(path, destination, url, verbose);

                std::string downloadMessage = "Download completed in the folder " + destination;
                std::cout << downloadMessage << std::endl;
                std::cout << "Press any key to continue..." << std::endl;
                getch();
            }

        } else if (choice == "2") {
            std::string urlMaxString = "y";
            std::string urls[100];
            int length = 0;

            while (urlMaxString == "y") {

                if (length == 100) {
                    std::cout << "You can't add more than 100 videos" << std::endl;
                    break;
                }

                std::cout << "Enter a url of a  video : ";
                std::getline(std::cin, url);
                if (url.find(url) == std::string::npos) {
                    std::cout << "Invalid URL" << std::endl;
                    return 0;
                }

                urls[length] = url;
                length++;

                std::cout << "Do you want to add another video ? (y/n) : ";
                std::getline(std::cin, urlMaxString);
            }

            downloadMultipleVideo(path, destination, urls, length, verbose);

        } else if (choice == "3") {
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

            std::cout << "Json file modified" << std::endl;
            std::cout << "Please restart the program" << std::endl;
            std::cout << "Press any key to continue..." << std::endl;
            getch();

            return 0;
        } else if (choice == "4") {
            return 0;
        } else {
            std::cout << "Invalid choice" << std::endl;
        }
    }
}

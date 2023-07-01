//
// Created by matis on 01/07/2023.
//

#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
#include "nlohmann/json.hpp"

void createJson() {
    std::ofstream json("info.json");
}

bool initiated() {
    std::string file = "info.json";

    if (std::filesystem::exists(file)) {
        return true;
    } else {
        return false;
    }
}

bool fileContainsCharacter(const std::string& fileName) {
    std::ifstream file(fileName);

    // Vérifier si le file est ouvert avec succès
    if (!file.is_open()) {
        std::cerr << "Impossible d'ouvrir le file." << std::endl;
        return false;
    }

    char caractere;
    while (file.get(caractere)) {
        // Vérifier si le caractère est un caractère imprimable
        if (isprint(caractere)) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

void initJson() {
    std::string destination;
    std::string path;
    std::string verbose;

    std::string file = "info.json";

    std::cout << "Enter destination path for your videos : ";
    std::getline(std::cin, destination);

    std::cout << "Enter path of YConverter (The folder which contains YConverter.exe) : ";
    std::getline(std::cin, path);

    std::cout << "Do you want to see the logs ? (y/n) : ";
    std::getline(std::cin, verbose);

    if (verbose == "y") {
        verbose = "true";
    } else if (verbose == "n") {
        verbose = "false";
    } else {
        std::cout << "Invalid answer" << std::endl;
        return;
    }

    nlohmann::json jsonObject {
            {"destination", destination},
            {"path", path},
            {"verbose", verbose}
    };

    std::ofstream jsonFile(file);

    if (!jsonFile.is_open()) {
        std::cerr << "Impossible d'ouvrir le file." << std::endl;
        return;
    }

    jsonFile << jsonObject.dump(4);

    jsonFile.close();

    std::cout << "Json file has been writed." << std::endl;
}

bool jsonIsNull() {
std::ifstream file("info.json");
    nlohmann::json jsonObject;

    file >> jsonObject;

    if (jsonObject["destination"].is_null() || jsonObject["path"].is_null() || jsonObject["verbose"].is_null()) {
        return true;
    } else {
        return false;
    }
}

void modify(const std::string& path, const std::string& destination, const std::string& verbose) {
    std::string file = "info.json";

    std::ifstream jsonFile(file);

    if (!jsonFile.is_open()) {
        std::cerr << "The file can't be open." << std::endl;
        return;
    }

    std::string jsonContent((std::istreambuf_iterator<char>(jsonFile)), std::istreambuf_iterator<char>());

    jsonFile.close();

    nlohmann::json jsonObj = nlohmann::json::parse(jsonContent);

    jsonObj["destination"] = destination;
    jsonObj["path"] = path;
    jsonObj["verbose"] = verbose;

    std::ofstream jsonFile2(file);

    if (!jsonFile2.is_open()) {
        std::cerr << "The file can't be open." << std::endl;
        return;
    }

    jsonFile2 << jsonObj.dump(4);

    jsonFile2.close();

    std::cout << "Json file has been writed." << std::endl;
}
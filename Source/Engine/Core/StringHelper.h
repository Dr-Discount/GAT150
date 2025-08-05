#pragma once  
#include <string>  
#include <cctype> // Include this for std::tolower and std::toupper  

namespace viper {  
    std::string toLower(const std::string& str) {  
        std::string result = str;  

        for (char& c : result) {  
            c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));  
        }  

        return result;  
    }  

    std::string toupper(const std::string& str) {  
        std::string result = str;  

        for (char& c : result) {  
            c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));  
        }  

        return result;  
    }  
}
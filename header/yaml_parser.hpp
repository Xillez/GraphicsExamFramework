#pragma once

#include <string>
#include <utility>
#include <iostream>

/**
 * @brief class that parse yaml file
 * 
 */
class YamlParser {

private:
    
    std::string data;
    int position = 0;

public:
    
    /**
     * @brief Construct a new yaml Parser object
     * 
     * @param path 
     */
    YamlParser(const std::string path);
	
    /**
	 * @brief 
	 * 
	 * @return std::string 
	 */
    auto nextLine() -> std::string;
    
    /**
     * @brief 
     * 
     * @return std::pair<std::string, std::string> 
     */
    auto nextStringString() -> std::pair<std::string, std::string>;
   
    /**
     * @brief 
     * 
     * @return std::pair<std::string, int> 
     */
    auto nextStringInt() -> std::pair<std::string, int>;
};
#pragma once

#include <string>
#include <utility>

/**
 * @brief Container for functions used across application.
 */
namespace helpers{
    /**
     * @brief class that parse yaml file.
     */
    class YamlParser {
    
    public:
        
        /**
         * @brief Construct a new yaml Parser object.
         * 
         * @param path - File path to the yaml file.
         */
        YamlParser(const std::string path);
    	
        /**
    	 * @brief Gets the next line in the yaml file.
    	 * 
    	 * @return the next line as string.
    	 */
        auto nextLine() -> std::string;
        
        /**
         * @brief Next string with key and string value.
         * 
         * @return pair with key and string value.
         */
        auto nextStringString() -> std::pair<std::string, std::string>;
       
        /**
         * @brief Next key with integer value.
         * 
         * @return pair with key and integer value.
         */
        auto nextStringInt() -> std::pair<std::string, int>;
    
    private:
        
        std::string data;           //!< Input from yaml file.
        int position = 0;           //!< Current reading position in yaml file.
    
    };
}
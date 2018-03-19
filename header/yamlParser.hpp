#include <string>
#include <fstream>

/**
 * @brief Class that parse yaml file
 * 
 */
class yamlParser {
private:
    std::string data;
    int position = 0;
public:
    yamlParser(const std::string path) {
        std::ifstream file(path);
        std::string buffer;
        while(!file.eof()){
            std::getline(file, buffer);       
            data.append(buffer);

        }
    }
    auto nextLine() -> std::string{
        std::string temp;
        int count = position;
        while(data.at(count) != '/n'){
            temp.append(data.at(count));
            count++;

        }
    };
    auto nextString() -> std::string;
    auto nextInt() -> int; 
}
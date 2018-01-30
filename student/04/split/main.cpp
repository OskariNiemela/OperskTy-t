#include <iostream>
#include <string>
#include <vector>


// TODO: Toteuta split-funktio tänne
// Älä tee mitään muutoksia main-funktioon
std::vector<std::string> split(std::string user_string, char separator,bool ignore_empty = false)
{
    std::size_t separator_index = user_string.find(separator);
    std::vector<std::string> separated;
    if(separator_index == std::string::npos)
    {
        separated.push_back(user_string);
        return separated;
    }

    while(separator_index!=std::string::npos)
    {
        int substr_length = static_cast<int>(separator_index);
        if(substr_length == 0){
            if(not ignore_empty)
            {
                separated.push_back(user_string.substr(0,substr_length));
            }
        }else
        {
            separated.push_back(user_string.substr(0,substr_length));
        }
        substr_length++;
        user_string.erase(0,substr_length);
        separator_index = user_string.find(separator);

    }
    separated.push_back(user_string);
    return separated ;
}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto o : parts ) {
        std::cout << o << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto o : parts_no_empty ) {
        std::cout << o << std::endl;
    }
}

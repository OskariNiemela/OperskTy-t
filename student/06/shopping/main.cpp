#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>

const std::string nostock = "out-of-stock";



bool is_double(const std::string& s)
{
    try
    {
        std::stod(s);
    }
    catch(...)
    {
        return false;
    }
    return true;
}

struct Fileline
{
    std::string chain;
    std::string location;
    std::string product;
    double price;
    bool in_stock;
};


struct Product
{
    std::string product_name;
    double price;
};

//Compare product names in order to make the set the correct order
bool operator<(Product const & a, Product const & b)
{
    return a.product_name < b.product_name;

}

Fileline split(std::string user_string, char separator=';')
{
    std::size_t separator_index = user_string.find(separator);
    std::string str;
    Fileline separated{" "," "," ",-1.0,false};
    if(separator_index == std::string::npos)
    {
        return separated;
    }

    int loops = 0;
    while(separator_index!=std::string::npos)
    {
        int substr_length = static_cast<int>(separator_index);


        if(substr_length == 0){
            return separated;
        }else
        {

            switch(loops)
            {
                case 0:
                    str = user_string.substr(0,substr_length);
                    separated.chain = str;
                break;

                case 1:
                    str = user_string.substr(0,substr_length);
                    separated.location = str;
                break;

                case 2:
                    str = user_string.substr(0,substr_length);
                    separated.product = str;
                break;

                default:
                    separated.chain=" ";
                    return separated;
            }

        }
        substr_length++;
        user_string.erase(0,substr_length);
        separator_index = user_string.find(separator);
        loops++;
    }

        if(is_double(user_string)){
            separated.price=std::stod(user_string);
        }
        else
        {
            if(str==nostock)
            {
                separated.in_stock = false;
            }
            else{
                separated.chain = " ";
                return separated;
            }
        }

    return separated ;
}


int main()
{
    std::string file_path;
    std::cout<<"Input file: ";
    std::cin>>file_path;

    std::ifstream file(file_path);

    if (not file)
    {
        std::cout<<"Error: the input file cannot be opened"<<std::endl;
        return EXIT_FAILURE;
    }

    Fileline store_info;
    std::map<std::string,std::map<std::string,std::set<Product>>> storechains_map;
    std::string line;
    while(std::getline(file,line))
    {
        store_info = split(line);
        std::cout<<store_info.chain<<store_info.location;

    }
    return EXIT_SUCCESS;
}



#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>

const std::string nostock = "out-of-stock";

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
    bool no_stock;
};


struct Product
{
    std::string product_name;
    double price;
    std::string stock;
};

bool nonspace(std::string string)
{
    if(string.find_first_not_of(' ')!=std::string::npos)
    {
        return true;
    }
    return false;
}


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
            separated.no_stock = false;
        }
        else
        {
            if(user_string==nostock)
            {
                separated.no_stock = true;
            }
            else{
                separated.chain = " ";
                return separated;
            }
        }

    return separated ;
}

void check_replace(std::set<Product> & set, Product item)
{
    std::set<Product>::iterator index;
    index = set.begin();

    while(index!=set.end())
    {
        Product metest = *index;
        if(metest.product_name == item.product_name)
        {
            set.erase(metest);
            break;
        }
        index++;

    }

    set.insert(item);

}

void print_products(std::set<std::string> const & products)
{
    std::set<std::string>::iterator product_name;
    product_name = products.begin();

    while(product_name!=products.end())
    {
        std::cout<<*product_name<<std::endl;
        product_name++;
    }

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
    Product produce;
    std::set<std::string> all_products;
    std::map<std::string,std::set<Product>>* chains_map;


    while(std::getline(file,line))
    {
        store_info = split(line);

        if(nonspace(store_info.chain)&&nonspace(store_info.location)&&nonspace(store_info.product)&&(store_info.no_stock||store_info.price>0))
        {
            all_products.insert(store_info.product);

            if(storechains_map.find(store_info.chain)!=storechains_map.end())
            {
                if(storechains_map[store_info.chain].find(store_info.location)==storechains_map[store_info.chain].end())
                {
                    chains_map = & storechains_map[store_info.chain];

                    produce.price = store_info.price;
                    produce.product_name= store_info.product;
                    produce.stock = not store_info.no_stock;

                    std::set<Product> new_set;
                    new_set.insert(produce);

                    chains_map->insert({store_info.location,new_set});
                }
                else
                {
                    produce.price = store_info.price;
                    produce.product_name= store_info.product;
                    produce.stock = not store_info.no_stock;

                    check_replace(storechains_map[store_info.chain][store_info.location],produce);
                }


            }
            else
            {

                produce.price = store_info.price;
                produce.product_name= store_info.product;
                produce.stock = not store_info.no_stock;

                std::map<std::string,std::set<Product>> new_map;
                std::set<Product> new_set;
                new_set.insert(produce);
                new_map[store_info.location].insert(produce);


                storechains_map.insert({store_info.chain,new_map});
            }
        }
        else
        {
            std::cout<<"Error: the file has an erroneous line"<<std::endl;
            return EXIT_FAILURE;
        }

    }

    while(true){
        std::string line;
        std::cout << "> ";
        std::cin>>line;
        std::vector<std::string> split_cmd = split(line, ' ', true);

        std::string command = split_cmd.at(0);

        if(command == "Selection" || command == "selection")
        {
            if(split_cmd.size() != 2){
                std::cout << "Error: error in command selection";
                continue;
            }


        }
        else if(command == "Cheapest" || command == "cheapest")
        {
            if(split_cmd.size() != 2){
                std::cout << "Error: error in comand cheapest"<<std::endl;
                continue;
            }
            std::string cheap_product = split_cmd.at(1);

            if(all_products.find(cheap_product)==all_products.end())
            {
                std::cout<<"Product is not part of product selection."<<std::endl;
                continue;
            }



        }
        else if(command == "Products" || command == "products")
        {
            if(split_cmd.size() != 1){
                std::cout << "Error: error in command products";
                continue;
            }

            print_products(all_products);

        }
        else if(command == "Chains" || command == "ćhains")
        {
            if(split_cmd.size() != 1){
                std::cout << "Error: error in command chains";
                continue;
            }

        }
        else if(command == "Stores" || command == "stores")
        {
            if(split_cmd.size() != 2){
                std::cout << "Error: error in command stores";
                continue;
            }

        }
        else if(command == "Quit" || command == "quit")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Error: unknown command"<<std::endl;
        }
    }

    return EXIT_SUCCESS;
}



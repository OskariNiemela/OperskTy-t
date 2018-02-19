#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <iomanip>

const std::string nostock = "out-of-stock";

//Split a string at the separator characters and store it in a vector
std::vector<std::string> split_vec(std::string user_string, char separator,bool ignore_empty = false)
{
    std::size_t separator_index = user_string.find(separator);
    std::vector<std::string> separated;

    //If the string has no seperator characters then we just return the original string in a vector
    if(separator_index == std::string::npos)
    {
        separated.push_back(user_string);
        return separated;
    }

    // Iterate through the string, find all the separator characters and add the substr from 0 to
    // the index of the separator char index, then delete the substr from the string.
    while(separator_index!=std::string::npos)
    {
        //the separator index returns a string::size_type, which is an unsigned integer
        //so to not get a warning we static cast it into an int.
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
        //since the erase function excludes the last index that it is given we need to add one to
        //the substr length to delete the separator character
        substr_length++;
        user_string.erase(0,substr_length);
        separator_index = user_string.find(separator);
    }
    separated.push_back(user_string);
    return separated ;
}

//Check if the given string is a double
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

//When we parse through the text file we save all the relevant info into this type of structure.
//The idea was that it would make the code a bit easier to read/parse, but it just made the whole
//thing a bit of a mess, but its done so im keeping it.
struct Fileline
{
    std::string chain;
    std::string location;
    std::string product;
    double price;
    bool no_stock;
};

//We save all the relevant information about a given product in a store into a struct of this type.
struct Product
{
    std::string product_name;
    double price;
};

//Check if the string has nonspace characters in it
bool nonspace(std::string string)
{
    if(string.find_first_not_of(' ')!=std::string::npos)
    {
        return true;
    }
    return false;
}

//Compare product names in order to make the set the correct order
//needed to save Product types into sets.
bool operator<(Product const & a, Product const & b)
{
    return a.product_name < b.product_name;
}

//Split the information on a text line and store it into
//a Fileline structure.
Fileline split(std::string user_string, char separator=';')
{
    std::size_t separator_index = user_string.find(separator);
    std::string str;

    //Initialize the fileline structure.
    Fileline separated{" "," "," ",-1.0,false};
    if(separator_index == std::string::npos)
    {
        return separated;
    }

    int loops = 0;

    while(separator_index!=std::string::npos)
    {
        int substr_length = static_cast<int>(separator_index);

        //If the substring has a length of 0 then we have
        //a faulty line in the textfile so we return
        //it with an empty space so the main loop recognizes
        //that something went wrong.
        if(substr_length == 0){
            separated.chain = " ";
            return separated;
        }else
        {

            switch(loops)
            {
            //Every line should have chain,location and product so if
            //there is more separator characters after the product name
            //then the line is faulty.
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

    //Lastly we check the price of the item
        if(is_double(user_string)){
            separated.price=std::stod(user_string);
            separated.no_stock = false;
        }
        else
        {
            //If the last value is not a double, we check it its out-of-stock
            //it its not that either the text line if faulty.
            if(user_string==nostock)
            {
                separated.no_stock = true;
                separated.price = -1;
            }
            else{
                separated.chain = " ";
                return separated;
            }
        }

    return separated ;
}

//check if the given Product is in the given set if it
//is, then we replace it if its not then we just add the item
//to the set.
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


//print the products that are sold in the stores
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

//Print all the available store chains.
void print_chains(std::map<std::string,std::map<std::string,std::set<Product>>> & map)
{
    std::map<std::string,std::map<std::string,std::set<Product>>>::iterator map_index;
    map_index = map.begin();

    while(map_index!=map.end())
    {
        std::cout<<map_index->first<<std::endl;
        map_index++;
    }

}

//Print all the stores
void print_stores(std::map<std::string,std::set<Product>> & locations)
{
    std::map<std::string,std::set<Product>>::iterator map_index;
    map_index = locations.begin();

    while(map_index!=locations.end())
    {
        std::cout<<map_index->first<<std::endl;
        map_index++;
    }

}

//Print the selection of a given store
void print_selection(std::set<Product> & produce)
{
    std::set<Product>::iterator set_index;
    set_index = produce.begin();

    while(set_index!=produce.end())
    {
        Product metest = *set_index;

        std::cout<<metest.product_name<<' ';

        if(metest.price>0)
        {
            std::cout<<std::setprecision(2)<<std::fixed<<metest.price<<std::endl;
        }
        else
        {
            std::cout<<"out of stock"<<std::endl;
        }

        set_index++;
    }
}

//Print the cheapest product by going through the main data structure
void print_cheapest(std::map<std::string,std::map<std::string,std::set<Product>>> & chains, std::string item)
{
    std::map<std::string,std::map<std::string,std::set<Product>>>::iterator chain;
    std::map<std::string,std::set<Product>> ::iterator location;
    std::set<Product>::iterator produce;
    double cheapest_price = -1;
    std::set<std::string> stores;
    bool in_stock = false;

    chain = chains.begin();
    /* The search loops through the whole structure containing
     * all the chains, locations and products available
     */
    while(chain!=chains.end())
    {
        location = chain->second.begin();
        while(location!=chain->second.end())
        {
            produce = location->second.begin();
            while(produce!=location->second.end())
            {
               //For some reason that I dont get I need to
               //first store the *produce into a new Product
               //variable to be able to access the information within the struct.
               Product item_struct = *produce;
               if(item_struct.price>0 && item_struct.product_name==item)
               {
                   in_stock = true;
                   //If there is no cheapest_price yet set (the default price is -1)
                   //or if our price is the cheapest we've find so far.
                   if(item_struct.price<cheapest_price || cheapest_price< 0)
                   {
                       //Clear the stores set to delete the previous cheapest stores
                       stores.clear();
                       cheapest_price = item_struct.price;
                       //We store the store name by chain and location
                       stores.insert(chain->first+' '+location->first);
                   }
                   else if(item_struct.price==cheapest_price)
                   {
                       stores.insert(chain->first+' '+location->first);
                   }

               }

                produce++;
            }

           location++;
        }

        chain++;
    }

    if(not in_stock)
    {
        std::cout<<"The product is temporarily out of stock everywhere."<<std::endl;
        return;
    }

    //setprecision is part of the iomanip library which allows to set the amount
    //of decimals to be printed.
    std::cout<<std::setprecision(2)<<std::fixed<<cheapest_price;
    std::cout<<" euros"<<std::endl;

    for(std::set<std::string>::iterator store = stores.begin(); store!=stores.end();store++)
    {
        std::cout<<*store<<std::endl;
    }


}



int main()
{
    std::string file_path;
    std::cout<<"Input file: ";
    std::getline(std::cin,file_path);
    std::ifstream file(file_path);

    if (not file)
    {
        std::cout<<"Error: the input file cannot be opened"<<std::endl;
        return EXIT_FAILURE;
    }

    //We'll store information about a particular store in this
    //before adding it to the main structure
    Fileline store_info;

    //The main data structure we're using
    std::map<std::string,std::map<std::string,std::set<Product>>> storechains_map;
    std::string line;
    Product produce;
    //Store all the product names in this set
    std::set<std::string> all_products;
    std::map<std::string,std::set<Product>>* chain_map;

    //Store the product information in the appropriate data structure.
    while(std::getline(file,line))
    {
        store_info = split(line);

        //Checks that all went correctly when storing the info from the textfile
        if(nonspace(store_info.chain)&&nonspace(store_info.location)&&nonspace(store_info.product)&&(store_info.no_stock||store_info.price>0))
        {

            all_products.insert(store_info.product);

            //Check where on the structure we should add the new
            //information.
            if(storechains_map.find(store_info.chain)!=storechains_map.end())
            {
                //New location, but we already know the chain
                if(storechains_map[store_info.chain].find(store_info.location)==storechains_map[store_info.chain].end())
                {
                    chain_map = & storechains_map[store_info.chain];

                    produce.price = store_info.price;
                    produce.product_name= store_info.product;

                    std::set<Product> new_set;
                    new_set.insert(produce);

                    chain_map->insert({store_info.location,new_set});
                }
                //New product in a known store
                else
                {
                    produce.price = store_info.price;
                    produce.product_name= store_info.product;

                    check_replace(storechains_map[store_info.chain][store_info.location],produce);
                }
            }
            //The chain hasnt been stored in our data yet
            else
            {

                produce.price = store_info.price;
                produce.product_name= store_info.product;

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

    while(true)
    {
        std::string line;
        std::cout << "> ";
        std::getline(std::cin,line);
        std::vector<std::string> split_cmd = split_vec(line, ' ', true);

        std::string command = split_cmd.at(0);

        if(command == "Selection" || command == "selection")
        {
            if(split_cmd.size() != 3){
                std::cout << "Error: error in command selection"<<std::endl;
                continue;
            }
            std::string chain = split_cmd.at(1);
            std::string locale = split_cmd.at(2);

            if(storechains_map.find(chain)==storechains_map.end())
            {
                std::cout<<"Error: unknown chain"<<std::endl;
                continue;
            }

            if(storechains_map[chain].find(locale)==storechains_map[chain].end())
            {
                std::cout<<"Error: unknown store"<<std::endl;
                continue;
            }

            print_selection(storechains_map[chain][locale]);
        }
        else if(command == "Cheapest" || command == "cheapest")
        {
            if(split_cmd.size() != 2){
                std::cout << "Error: error in command cheapest"<<std::endl;
                continue;
            }
            std::string cheap_product = split_cmd.at(1);

            if(all_products.find(cheap_product)==all_products.end())
            {
                std::cout<<"Product is not part of product selection."<<std::endl;
                continue;
            }
            print_cheapest(storechains_map, cheap_product);

        }
        else if(command == "Products" || command == "products")
        {
            if(split_cmd.size() != 1){
                std::cout << "Error: error in command products"<<std::endl;
                continue;
            }
            print_products(all_products);
        }
        else if(command == "Chains" || command == "chains")
        {
            if(split_cmd.size() != 1){
                std::cout << "Error: error in command chains"<<std::endl;
                continue;
            }
            print_chains(storechains_map);

        }
        else if(command == "Stores" || command == "stores")
        {
            if(split_cmd.size() != 2){
                std::cout << "Error: error in command stores"<<std::endl;
                continue;
            }
            std::string chain = split_cmd.at(1);

            if(storechains_map.find(chain)==storechains_map.end())
            {
                std::cout<<"Error: an unknown chain"<<std::endl;
                continue;
            }
            print_stores(storechains_map[chain]);
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



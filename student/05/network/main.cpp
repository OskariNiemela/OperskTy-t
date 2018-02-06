#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

const std::string HELP_TEXT = "S = store id1 i2\n P = print id\n"
                              "C = count id\n D = depth id";

void store(std::string key, std::string value, std::map<std::string,std::vector<std::string>>& network)
{
    if(network.find(key)!=network.end())
    {
        network[key].push_back(value);
    }else
    {
        std::vector<std::string> a;
        a.push_back(value);
        network.insert({key,a});
    }
}

void print(std::string key, std::map<std::string,std::vector<std::string>> & network, std::string dots = "")
{
    std::cout<<dots<<key<<std::endl;
    if(network.find(key)!=network.end())
    {
        std::vector<std::string>::iterator person;
        person = network[key].begin();
        dots.append("..");
        while(person!=network[key].end())
        {
            print(*person,network,dots);
            person++;
        }
    }
}

int count(std::string key, std::map<std::string,std::vector<std::string>> & network)
{
    int network_size = 0;
    if(network.find(key)!=network.end())
    {
        std::vector<std::string>::iterator person;
        person = network[key].begin();
        while(person!=network[key].end())
        {
            network_size++;
            network_size +=count(*person,network);
            person++;
        }
    }
    return network_size;
}

int depth(std::string key, std::map<std::string,std::vector<std::string>> & network)
{
    int network_max_depth = 1;

    if(network.find(key)!=network.end())
    {
        int current_depth = 1;
        int network_depth = 0;
        network_max_depth = 2;
        std::vector<std::string>::iterator person;
        person = network[key].begin();
        while(person!=network[key].end())
        {
            network_depth = depth(*person,network);
            if(network_max_depth<current_depth+network_depth)
            {
                network_max_depth = current_depth+network_depth;
            }

            person++;
        }
    }
    return network_max_depth;
}


std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}



int main()
{
    // TODO: Implement the datastructure here
    std::map<std::string,std::vector<std::string>> network;
    while(true){
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        std::string command = parts.at(0);

        if(command == "S" or command == "s"){
            if(parts.size() != 3){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            store(id1,id2,network);
            // TODO: Implement the command here!

        } else if(command == "P" or command == "p"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            print(id,network);

        } else if(command == "C" or command == "c"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id = parts.at(1);


            std::cout<<count(id,network)<<std::endl;
            // TODO: Implement the command here!

        } else if(command == "D" or command == "d"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            std::cout<<depth(id,network)<<std::endl;

        } else if(command == "Q" or command == "q"){
           return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}

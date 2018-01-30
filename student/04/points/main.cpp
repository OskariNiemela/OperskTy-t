#include <iostream>
#include <fstream>
#include <string>
#include <map>

std::map<std::string,int> split(std::ifstream user_string, char separator)
{
    int separator_index = 0;
    std::map<std::string,int> scores;
    std::string name;
    int score;
    std::string line;
    while(std::getline(user_string,line))
    {

        separator_index = line.find(separator);
        int substr_length = static_cast<int>(separator_index);
        name = line.substr(0,substr_length);
        substr_length++;
        line.erase(0,substr_length);
        score = stoi(line);

        if(scores.find(name)!=scores.end())
        {
            scores.at(name) += score;
        }else
        {
            scores.insert({name,score});
        }


    }

    return scores;
}

int main()
{

    std::string file_name;
    std::cout<<"Input file: ";
    std::cin>> file_name;
    std::ifstream scores_file(file_name);

    if(not scores_file)
    {
        std::cout<<"Error! The file "<<file_name<<" cannot be opened.";
        return EXIT_FAILURE;
    }
    char separator = ':';

    int separator_index = 0;
    std::map<std::string,int> scores;
    std::string name;
    int score;
    std::string line;
    while(std::getline(scores_file,line))
    {

        separator_index = line.find(separator);
        int substr_length = static_cast<int>(separator_index);
        name = line.substr(0,substr_length);
        substr_length++;
        line.erase(0,substr_length);
        score = stoi(line);

        if(scores.find(name)!=scores.end())
        {
            scores.at(name) += score;
        }else
        {
            scores.insert({name,score});
        }


    }
    std::map<std::string,int>::iterator key;
    key = scores.begin();


    std::cout<<"Final scores:"<<std::endl;
    while(key != scores.end())
    {
        std::cout<<key->first<<": "<<key->second<<std::endl;
        key++;
    }

}

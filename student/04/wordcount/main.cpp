#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

std::vector<std::string> split(std::string user_string, char separator=' ',bool ignore_empty = true)
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
    return separated;
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

    std::vector<std::string> words_vec;
    std::map<std::string,int> scores;
    std::string line;
    std::vector<std::string>::iterator name;
    std::map<std::string,std::vector<int>> lines;
    int current_line = 0;

    while(std::getline(scores_file,line))
    {
        current_line++;
        words_vec = split(line);
        name = words_vec.begin();
        std::vector<std::string> words_added;

        while(name!=words_vec.end())
        {

            if(scores.find(*name)!=scores.end())
            {
                if(std::find(words_added.begin(), words_added.end(), *name) == words_added.end())
                {
                    words_added.push_back(*name);
                    scores.at(*name) ++;
                }
            }else
            {
                words_added.push_back(*name);
                scores.insert({*name,1});
            }

            if(lines.find(*name)!=lines.end())
            {
                if(std::find(lines[*name].begin(), lines[*name].end(), current_line) == lines[*name].end())
                {
                    lines[*name].push_back(current_line);

                }

            }else
            {
                std::vector<int> v;
                v.push_back(current_line);
                lines.insert({*name,v});
            }


            name++;
        }



    }

    std::map<std::string,int>::iterator key;
    key = scores.begin();
    std::vector<int>::iterator c;

    while(key != scores.end())
    {


        std::cout<<key->first<<" "<<key->second<<": ";
        c = lines[key->first].begin();
        while(c!=lines[key->first].end())
        {
            std::cout<<*c;
            c++;
            if(c!=lines[key->first].end())
            {
                std::cout<<", ";
            }

        }


        std::cout<<std::endl;
        key++;
    }

}

#include <iostream>
#include <fstream>
#include <string>

void print_line_numbers(std::string line)
{

}


int main()
{
    std::string write_file = "";
    std::string file_name = "";
    std::cout<<"Input file: ";
    std::cin >> file_name;
    std::cout<<"Output file: ";
    std::cin >> write_file;

    std::ifstream file_text(file_name);
    if(not file_text)
    {
        std::cout<<"Error! The file "<< file_name << " cannot be opened.";
        return EXIT_FAILURE;
    }
    std::ofstream write_text(write_file);
    std::string line;
    int line_number = 1;
    while(std::getline(file_text,line))
    {
        write_text<<line_number<<" "<<line<<std::endl;
        line_number++;
    }

}

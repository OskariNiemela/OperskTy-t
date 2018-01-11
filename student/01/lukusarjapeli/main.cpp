#include <iostream>
#include <string>

int main()
{
    int numbers=0;
    std::cout << "How many numbers would you like to have? ";
    std::cin >> numbers;

    for(int i = 1; i<=numbers; i+=1){
        std::string s = std::to_string(i);
        if(i%3==0){
            s = "zip";
        }


        std::cout << s << std::endl;
    }
}

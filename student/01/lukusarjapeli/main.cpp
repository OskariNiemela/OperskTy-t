#include <iostream>


int main()
{
    int numbers=0;
    std::cout << "How many numbers would you like to have? ";
    std::cin >> numbers;

    for(int i = 1; i<=numbers; i+=1){
        std::cout << i << std::endl;
    }
}

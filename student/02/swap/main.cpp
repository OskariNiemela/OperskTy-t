#include <cstdlib>
#include <iostream>

// TODO: Kirjoita funktion swap maarittely tahan
void swap(int& int1, int& int2){
    int we = int1;
    int1 = int2;
    int2 = we;
}

int main()
{
    std::cout << "Enter an integer: ";
    int i = 0;
    std::cin >> i;

    std::cout << "Enter another integer: ";
    int j = 0;
    std::cin >> j;

    swap(i, j);
    std::cout << "The integers are " << i << " and " << j << std::endl;

    return EXIT_SUCCESS;
}

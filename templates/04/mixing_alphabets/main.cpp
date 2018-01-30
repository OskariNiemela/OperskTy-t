#include <iostream>
#include <string>
#include <algorithm>
#include <random>

int main()
{
    // Tämä on random-numerogeneraattori, joka pitää antaa parametrina sille
    // algorithm-kirjaston funktiolle, joka sekoittaa kirjaimet
    std::minstd_rand generator;

    std::cout << "Enter some text. Quit by entering the word \"END\"." << std::endl;
    std::string word;

    while (std::cin >> word)
    {
        if (word == "END")
        {
            return EXIT_SUCCESS;
        }

        // TODO: toteuta ratkaisusi tähän
	
        std::cout << word << std::endl;
    }
}

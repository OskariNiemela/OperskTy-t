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
        std::vector<char> word_chars(word.begin(),word.end());
        int size = static_cast<int>(word_chars.size());
        if( size > 1)
        {
            shuffle(word_chars.begin()+1,word_chars.end()-1,generator);
        }
        std::string s(word_chars.begin(),word_chars.end());
        word = s;

        std::cout << word << std::endl;
    }
}

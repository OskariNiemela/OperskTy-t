#include <iostream>
#include <string>
bool palindrome_recursive(std::string word_pal)
{
    char a = word_pal.at(0);
    std::string::iterator b = word_pal.end();
    b--;

    if(a == *b)
    {
        word_pal.erase(b);
        word_pal.erase(0,1);
        if((word_pal.length()==0)or(word_pal.length()==1))
        {
            return true;
        }else if(palindrome_recursive(word_pal))
        {
            return true;
        }
    }else
    {
        return false;
    }
    return true;
}


int main()
{
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    if(palindrome_recursive(word)){
        std::cout << word << " is a palindrome" << std::endl;
    } else {
        std::cout << word << " is not a palindrome" << std::endl;
    }
}

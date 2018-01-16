#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

bool all_lower_case(string key){
    size_t le = key.length();
    int length_int = static_cast<int>(le);

    for(int a=0;a<length_int;a+=1){
        if (isupper(key[a])){
            return false;
        }
    }
    return true;
}

bool correct_size(string key){
    size_t le = key.length();
    int length = static_cast<int>(le);

    if(length == 26){
        return true;
    }else
    {
        return false;
    }
}

bool all_letters_present(string key){
    int length = static_cast<int>(key.length());
    for(int a=0;a<length;a+=1){
        bool stop = true;
        for(char letter = 'a';letter<='z';++letter){
            if(key[a]==letter){
                stop = false;
                break;
            }

        }
        if(stop){
            return false;
        }
    }
    return true;
}

void caesar_cipher(string& text, string key){
    int text_len = static_cast<int>(text.length());
    int key_ind = 0;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    char replace = 'a';
    for(int text_letter=0;text_letter<text_len;text_letter+=1){
        key_ind = static_cast<int>(alphabet.find(text[text_letter]));
        replace = key[key_ind];
        text[text_letter]=replace;
    }

}

int main(int argc, char *argv[])
{
    string enc_key;
    cout<<"Enter the encryption key: ";
    cin>> enc_key;
    if(!correct_size(enc_key)){
        cout<<"Error! The encryption key must contain 26 characters."<<endl;
        return EXIT_FAILURE;
    }
    if(!all_letters_present(enc_key)){
        cout<<"Error! The encryption key must contain all alphabets a-z."<<endl;
        return EXIT_FAILURE;
    }
    if(!all_lower_case(enc_key)){
        cout<<"Error! The encryption key must contain only lower case characters."<<endl;
        return EXIT_FAILURE;
    }

    string text;
    cout<<"Enter the text to be encrypted: ";
    cin>> text;

    if(!all_lower_case(text)){
        cout<<"Error! The encryption key must contain only lower case characters."<<endl;
        return EXIT_FAILURE;
    }
    caesar_cipher(text,enc_key);
    cout<<"Encrypted text: "<<text<<endl;
    return 0;
}

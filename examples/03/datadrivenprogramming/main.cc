#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum PostalAbbreviation {AL, AK, AZ, AR, CA, CO, ERROR_CODE};  // Lyhennetty pois 44 alkiota

// Versio 1: Ensimmäinen toteutusidea
PostalAbbreviation name_to_abbreviation1(string name)
{
    if(name == "Alabama"){
        return AL;
    } else if (name == "Alaska"){
        return AK;
    } else if (name == "Arizona"){
        return AZ;
    } else if (name == "Arkansas"){
        return AR;
    } else if (name == "California"){
        return CA;
    } else if (name == "Colorado"){
        return CO;
    } else {   // Lyhennetty 44 else if -lohkoa
        return ERROR_CODE;
    }
}

struct StateInfo {
    string name;
    PostalAbbreviation abbreviation;
};

const vector<StateInfo> STATES = {
    { "Alabamaa", AL },
    { "Alaska", AK },
    { "Arizona", AZ },
    { "Arkansas", AR },
    { "California", CA },
    { "Colorado", CO }  // Lyhennetty 44 riviä
};

// Versio 2: Parempi toteutus
PostalAbbreviation name_to_abbreviation2(string name)
{
    for(auto s : STATES) {
        if(name == s.name){
            return s.abbreviation;
        }
    }
    return ERROR_CODE;
}

int main(){  // Välttävä testaus
    if(name_to_abbreviation1("California") == CA){
        cout << "Correct" << endl;
    } else {
        cout << "Error!" << endl;
    }

    if(name_to_abbreviation2("California") == CA){
        cout << "Correct" << endl;
    } else {
        cout << "Error!" << endl;
    }

    if(name_to_abbreviation1("Not a State") == ERROR_CODE){
        cout << "Correct" << endl;
    } else {
        cout << "Error!" << endl;
    }

    if(name_to_abbreviation2("Not a State") == ERROR_CODE){
        cout << "Correct" << endl;
    } else {
        cout << "Error!" << endl;
    }
}

// Tehtävä: Miten toteutettaisiin abbreviation_to_name-funktio?
// Vinkki: Jos tunnet C++:n enum-tietotyypin toteutustavan, saat tämän tehtyä todella helposti.

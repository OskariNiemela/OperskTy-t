#include <iostream>

using namespace std;


int main() {
    int luku1;
    int luku2 = 111;
    int *osoitin1 = new int;
    int *osoitin2 = new int(222);

    cout << luku1 << " "
         << luku2 << " "
         << *osoitin1 << " "
         << *osoitin2 << endl;

    delete osoitin1;

    *osoitin1 = 333;
}

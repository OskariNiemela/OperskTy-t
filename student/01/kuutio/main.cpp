#include <iostream>

using namespace std;

int main()
{
    int number = 0;
    cout << "Enter a number: ";
    cin >> number;

    int digits= 0;
    int num = number;
    while(num>1){
        num = num/10;
        digits+=1;
    }
    --digits;

    int pow3 = number*number*number;
    int pow3digits = digits*digits*digits;
    if (pow3digits > 10){
        cout<<"Error! The cube of "<<number<<" is not "<<pow3<<"."<<endl;
    }else{
        if(((number > 0) && (pow3<0)) || ((number<0)&&(pow3>0))){
            cout<<"Error! The cube of "<<number<<" is not "<<pow3<<"."<<endl;

        }
        else{
            cout<<"The cube of "<<number<<" is "<<pow3<<"."<<endl;

        }
    }

}

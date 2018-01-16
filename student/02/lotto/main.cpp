#include <iostream>


int combinations(int all,int drawn){
    int multiplier = all-drawn;

    unsigned long int all_factorial = 0;

    unsigned long int total = 1;

    for(unsigned long int a=2;a<=all;a+=1){
        total = total*a;

    }

    all_factorial = total;

    total = 1;
    for(unsigned long int a=2;a<=drawn;a+=1){
        total = total*a;

    }

    unsigned long int drawn_factorial = total;

    total = 1;
    for(unsigned long int a=2;a<=multiplier;a+=1){
        total = total*a;

    }
    unsigned long int  multiplier_factorial = total;

    int all_combin = all_factorial/(multiplier_factorial*drawn_factorial);

    return all_combin;
}

int main()
{
    int balls_total = 0;
    int balls_drawn = 0;

    std::cout << "Enter the total number of lottery balls: ";
    std::cin >> balls_total;


    std::cout << "Enter the number of the drawn balls: ";
    std::cin >> balls_drawn;


    if ((balls_total>0)&&(balls_drawn>0)){
        if (balls_drawn<=balls_total){
            unsigned long int no_combinations = 0;
            no_combinations = combinations(balls_total,balls_drawn);
            std::cout<<"The probability of guessing all "<<balls_drawn<<" correctly is "<<1<<"/"<<no_combinations<<std::endl;
        }
        else{
            std::cout<<"At most the total number of balls can be drawn."<<std::endl;

        }
    }else{
       std::cout<<"The number of balls must be a positive number."<<std::endl;

    }

}

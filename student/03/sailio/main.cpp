#include <cstdlib>
#include <iostream>
#include <vector>

void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        ints.push_back(new_integer);
    }
}

// TODO: Implement your solution here
bool same_values(const std::vector<int> &ints){
    int vector_size = static_cast<int>(ints.size());
    for(int a=1;a<vector_size;a++){
        if(ints.at(a-1)!=ints.at(a)){
            return false;
        }
    }
    return true;
}

bool is_ordered_ascending(const std::vector<int> &ints){
    int vector_size = static_cast<int>(ints.size());
    for(int a=1;a<vector_size;a++){
        if(ints.at(a-1)>ints.at(a)){
            return false;
        }
    }
    return true;
}

bool is_arithmetic_series(const std::vector<int> &ints){
    int vector_size = static_cast<int>(ints.size());
    int diff = 0;

    for(int a=1;a<vector_size;a++){
        diff = ints.at(a)-ints.at(a-1);
        break;
    }

    for(int b=1;b<vector_size;b++){
        if(ints.at(b)!=(ints.at(b-1)+diff)){
            return false;
        }
    }

    return true;
}

bool is_geometric_series(const std::vector<int> &ints){

    int vector_size = static_cast<int>(ints.size());
    int multiplier = 0;

    for(int a=1;a<vector_size;a++){
        multiplier = ints.at(a)/ints.at(a-1);
        break;
    }

    for(int b=1;b<vector_size;b++){
        if(ints.at(b)!=(ints.at(b-1)*multiplier)){
            return false;
        }
    }

    return true;
}

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_ascending(integers))
        std::cout << "The integers are in an ascending order" << std::endl;
    else
        std::cout << "The integers are not in an ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}

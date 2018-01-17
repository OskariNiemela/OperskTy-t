#ifndef PLAYER_HH
#define PLAYER_HH
#include <string>

class Player
{
    public:
        Player(std::string name);
        bool has_won();
        void add_points(int pts);
        std::string get_name();
        int get_points();
    private:
        std::string name_;
        int score_;
};

#endif // PLAYER_HH

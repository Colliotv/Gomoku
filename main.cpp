#include <iostream>

#include "referee/Referee.hh"

int main()
{
    referee::Referee r;

    std::cout << std::boolalpha << r.place_at({0, 0}) << std::endl;

    return 0;
}
//
// Created by naelior on 15/12/15.
//

#ifndef GOMOKU_IAMINMAX_HH
#define GOMOKU_IAMINMAX_HH

#include "referee/Referee.hh"

class IAminmax : game::Player
{
private:
    referee::Referee _referee;
    const int _depth;

private:
    double  min(referee::Referee ref, int depth);
    double  max(referee::Referee ref, int depth);
    double  eval(referee::Referee ref);
    double  countScore(referee::Piece::identity playerTurn);
    int     countRow(referee::Piece::identity playerTurn, int n);

public:
    IAminmax(const referee::Piece::identity& identity, int depth = 3);
    ~IAminmax() {};

public:
    void IaTurn();
    inline void setReferee(referee::Referee& ref) {this->_referee = ref;}
};


#endif //GOMOKU_IAMINMAX_HH

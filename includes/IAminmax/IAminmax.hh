//
// Created by naelior on 15/12/15.
//

#ifndef GOMOKU_IAMINMAX_HH
#define GOMOKU_IAMINMAX_HH

#include "referee/Referee.hh"

class IAminmax
{
private:
    referee::Referee _referee;
    int _depth;
    referee::Piece::identity _myColor;

private:
    double  min(referee::Referee ref, int depth);
    double  max(referee::Referee ref, int depth);
    double  eval(referee::Referee ref);
    double  countScore(referee::Piece::identity playerTurn);
    int     countRow(referee::Piece::identity playerTurn, int n);

public:
    IAminmax(referee::Referee referee, int depth, referee::Piece::identity myColor);
    ~IAminmax() {};

public:
    void IaTurn();
};


#endif //GOMOKU_IAMINMAX_HH

//
// Created by naelior on 15/12/15.
//

#include <referee/Piece.hh>
#include <referee/Referee.hh>
#include <IAminmax/IAminmax.hh>

IAminmax::IAminmax(const referee::Piece::identity& identity, int depth) : Player(identity), _depth(depth)
{
    this->_referee = nullptr;
}

int IAminmax::countRow(referee::Piece::identity playerTurn, int n)
{
    int serieCt = 0;
    int actCount = 0;
    bool haveSpace;
    referee::Piece::Position pos(0,0);
    //left to right row
    for (; pos.y < 19; pos.y++)
    {
        actCount = 0;
        haveSpace = false;
        pos.x = 0;
        for (; pos.x < 19; pos.x++)
        {
            if (this->_referee->board()[pos].is_same_color(playerTurn))
                actCount += 1;
            else
            {
                if (this->_referee->board()[pos].is_none())
                    haveSpace = true;
                else if (this->_referee->board()[pos].is_other_color(playerTurn))
                    haveSpace = false;
                if (haveSpace && actCount == n)
                    serieCt += 1;
                actCount = 0;
            }
        }
    }
    //up to down row
    pos.x = 0;
    for (; pos.x < 19; pos.x++)
    {
        actCount = 0;
        haveSpace = false;
        pos.y = 0;
        for (; pos.y < 19; pos.y++)
        {
            if (this->_referee->board()[pos].is_same_color(playerTurn))
                actCount += 1;
            else
            {
                if (this->_referee->board()[pos].is_none())
                    haveSpace = true;
                else if (this->_referee->board()[pos].is_other_color(playerTurn))
                    haveSpace = false;
                if (haveSpace && actCount == n)
                    serieCt += 1;
                actCount = 0;
            }
        }
    }
    //TODO diagonal

    return serieCt;
}

double IAminmax::countScore(referee::Piece::identity playerTurn)
{
    int fourRow = countRow(playerTurn, 4);
    int threeRow = countRow(playerTurn, 3);
    int twoRow = countRow(playerTurn, 2);
    double score = fourRow * 100.0 + threeRow * 5.0 + twoRow * 1.0;
    //TODO eatthemall
    return score;
}

double IAminmax::eval(referee::Referee& ref)
{
    if (ref.win() == this->m_identity)
        return (10000);
    else if (ref.win() != this->m_identity && ref.win() != referee::Piece::identity::none)
        return (-10000);
    else
    {
        return (countScore(ref.getMTurn()));
    }
}

double IAminmax::max(referee::Referee& ref, int depth)
{
    double maxScore = -100000;
    double tmpScore = 0;
    referee::Piece::Position pos(0,0);

    if (depth == 0 || ref.win() != referee::Piece::identity::none)
        return eval(ref);
    for (; pos.y < 19; pos.y++)
    {
        pos.x = 0;
        for (; pos.x < 19; pos.x++)
        {
            referee::Referee tmpRef(this->_referee->copy());
            if (tmpRef.place_at(pos)) {
                tmpScore = max(tmpRef, depth - 1);
                if (tmpScore > maxScore)
                    maxScore = tmpScore;
            }
        }
    }
    return maxScore;
}

double IAminmax::min(referee::Referee& ref, int depth) {
    double minScore = 100000;
    double tmpScore = 0;
    referee::Piece::Position pos(0,0);

    if (depth == 0 || ref.win() != referee::Piece::identity::none)
        return eval(ref);
    for (; pos.y < 19; pos.y++)
    {
        pos.x = 0;
        for (; pos.x < 19; pos.x++)
        {
            referee::Referee tmpRef(this->_referee->copy());
            if (tmpRef.place_at(pos)) {
                tmpScore = max(tmpRef, depth - 1);
                if (tmpScore < minScore)
                    minScore = tmpScore;
            }
        }
    }
    return minScore;
}

void IAminmax::IaTurn() {
    double maxScore = -100000;
    double tmpScore = 0;
    referee::Piece::Position bestMove(0,0);
    referee::Piece::Position pos(0,0);

    if (this->_referee->getFirstPlay())
    {
        this->_referee->place_at(referee::Piece::Position(9,9));
        return;
    }

    for (; pos.y < 19; pos.y++)
    {
        pos.x = 0;
        for (; pos.x < 19; pos.x++)
        {
            referee::Referee tmpRef(this->_referee->copy());
            if (tmpRef.place_at(pos)) {
                if (tmpRef.win() != referee::Piece::identity::none)
                {
                    this->_referee->place_at(pos);
                    return;
                }
                tmpScore = min(tmpRef, this->_depth - 1);
            }
            if (tmpScore > maxScore)
            {
                maxScore = tmpScore;
                bestMove.x = pos.x;
                bestMove.y = pos.y;
            }
        }
    }
    this->_referee->place_at(bestMove);
}

bool IAminmax::is_human() {
    return Player::is_human();
}

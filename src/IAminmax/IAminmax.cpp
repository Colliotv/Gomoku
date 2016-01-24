//
// Created by naelior on 15/12/15.
//

#include <referee/Piece.hh>
#include <referee/Referee.hh>
#include <IAminmax/IAminmax.hh>
#include <iostream>

IAminmax::IAminmax(const referee::Piece::identity& identity, int depth) : Player(identity), _depth(depth)
{
    this->_referee = nullptr;
}

int IAminmax::countRow(referee::Referee* ref, referee::Piece::identity playerTurn, int n)
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
            if (ref->board()[pos].is_same_color(playerTurn))
                actCount += 1;
            else
            {
                if (ref->board()[pos].is_none())
                    haveSpace = true;
                else if (ref->board()[pos].is_other_color(playerTurn))
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
            if (ref->board()[pos].is_same_color(playerTurn))
                actCount += 1;
            else
            {
                if (ref->board()[pos].is_none())
                    haveSpace = true;
                else if (ref->board()[pos].is_other_color(playerTurn))
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

double IAminmax::eval(referee::Referee* ref)
{
    double score = 0;
    if (ref->win() == this->m_identity)
        score = 10000;
    else if (ref->win() != this->m_identity && ref->win() != referee::Piece::identity::none)
        score = -10000;
    else
    {

        int fourRow = countRow(ref, referee::Piece::identity::white , 4);
        int threeRow = countRow(ref,referee::Piece::identity::white, 3);
        int twoRow = countRow(ref,referee::Piece::identity::white, 2);
        int fourRowadv = countRow(ref, referee::Piece::identity::black, 4);
        int threeRowadv = countRow(ref,referee::Piece::identity::black, 3);
        int twoRowadv = countRow(ref,referee::Piece::identity::black, 2);
        score = (fourRow * 100.0 + threeRow * 5.0 + twoRow * 1.0) - (fourRowadv * 100.0 + threeRowadv * 5.0 + twoRowadv * 1.0);

        //TODO eatthemall
    }
    return score;
}

double IAminmax::max(referee::Referee* ref, int depth)
{
    double maxScore = -100000;
    double tmpScore;
    referee::Piece::Position pos(0,0);

    if (depth == 0 || ref->win() != referee::Piece::identity::none)
        return eval(ref);
    for (; pos.y < 19; pos.y++)
    {
        pos.x = 0;
        for (; pos.x < 19; pos.x++)
        {
            referee::Referee tmpRef(ref->copy());
            if (tmpRef.board()[pos].can_pose(tmpRef.getMTurn())) {
                tmpRef.place_at(pos);
                tmpScore = min(&tmpRef, depth - 1);
                if (tmpScore > maxScore)
                    maxScore = tmpScore;
            }
        }
    }
    return maxScore;
}

double IAminmax::min(referee::Referee* ref, int depth) {
    double minScore = 100000;
    double tmpScore;
    referee::Piece::Position pos(0,0);

    if (depth == 0 || ref->win() != referee::Piece::identity::none)
        return eval(ref);
    for (; pos.y < 19; pos.y++)
    {
        pos.x = 0;
        for (; pos.x < 19; pos.x++)
        {
            referee::Referee tmpRef(ref->copy());
            if (tmpRef.board()[pos].can_pose(tmpRef.getMTurn())) {
                tmpRef.place_at(pos);
                tmpScore = max(&tmpRef, depth - 1);
                if (tmpScore < minScore)
                    minScore = tmpScore;
            }
        }
    }
    return minScore;
}

void IAminmax::IaTurn() {
    double maxScore = -100000;
    double tmpScore;
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
        for (; pos.x < 19; pos.x++) {
            referee::Referee tmpRef(this->_referee->copy());
            this->_precTaken = this->taken();
            if (tmpRef.board()[pos].can_pose(tmpRef.getMTurn())) {
                if (tmpRef.place_at(pos)) {
                    this->_referee->place_at(pos);
                    return;
                }
                tmpScore = min(&tmpRef, this->_depth - 1);
                std::cout << tmpScore << " posx : " << pos.x << " posy " << pos.y << std::endl;
                if (tmpScore > maxScore) {
                    maxScore = tmpScore;
                    bestMove.x = pos.x;
                    bestMove.y = pos.y;
                }
            }
        }
    }
    this->_referee->place_at(bestMove);
}

//
// Created by collio_v on 11/10/15.
//

#ifndef GOMOKU_STATE_HH
#define GOMOKU_STATE_HH

#include "referee/Board.hh"

namespace referee {

    namespace game{class Ia;};

    class Referee {
    private:
        referee::Piece::identity  m_turn;
        referee::Board  m_board;

    private:
        referee::Piece::identity  m_win;

    private:
        game::Ia*       m_white;
        game::Ia*       m_black;

    private:
        bool                        double_three_rule(const Piece::Position&);

    public:
        bool                        can_pose(const Piece::Position&);
        bool                        place_at(const Piece::Position&);
        referee::Piece::identity    win() { return m_win; }

    public:
        Referee(game::Ia* white = nullptr, game::Ia* black = nullptr);
    };

};

#endif //GOMOKU_STATE_HH

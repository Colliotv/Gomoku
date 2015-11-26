//
// Created by collio_v on 11/10/15.
//

#ifndef GOMOKU_STATE_HH
#define GOMOKU_STATE_HH

#include "referee/Board.hh"
#include "game/Player.hh"

namespace referee {

  /**
   * Referee definition
   */
  class Referee {
  private:
    bool                        m_first_play;
    std::list<Piece::Position>  m_potential_win;

  private:
    referee::Piece::identity  m_turn;
    referee::Board  m_board;

  private:
    referee::Piece::identity  m_win;

  private:
    game::Player*       m_white;
    game::Player*       m_black;
  public:
    game::Player&       white_player() { return *m_white; }
    game::Player&       black_player() { return *m_black; }

  public:
    inline referee::Board&             board() { return  m_board; }

  public:
    void                        take(const Piece::Position&);
    void                        place(const Piece::Position&);
    bool                        place_at(const Piece::Position&);
    bool                        test_potential_win(const Piece::Position&, bool in_test = false);

  public:
    referee::Piece::identity    win() { return m_win; }

  public:
    Referee(game::Player* white = new game::Player(), game::Player* black = new game::Player());
  };

};

#endif //GOMOKU_STATE_HH

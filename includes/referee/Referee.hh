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
    bool                human_turn();

  public:
    inline referee::Board&            board() { return  m_board; }

  private:
    Referee(const Referee& _referee)
      : m_first_play(_referee.m_first_play), m_potential_win(_referee.m_potential_win),
        m_turn(_referee.m_turn), m_board(_referee.m_board), m_win(_referee.m_win),
        m_white(_referee.m_white->copy()), m_black(_referee.m_black->copy()) {}
  public:
    Referee(Referee&&) = default;
    Referee   copy() const {
      return *this;
    }

  public:
    void                        take(const Piece::Position&);
    void                        place(const Piece::Position&);
    bool                        place_at(const Piece::Position&);
    bool                        test_potential_win(const Piece::Position&, bool in_test = false);

  public:
    referee::Piece::identity    win() { return m_win; }
    inline bool                 getFirstPlay() { return m_first_play; }
    inline referee::Piece::identity getMTurn() {return m_turn; }

  public:
    Referee(game::Player* white = new game::Player(Piece::identity::white), game::Player* black = new game::Player(Piece::identity::black));
    void ia_place();
  };

};

#endif //GOMOKU_STATE_HH

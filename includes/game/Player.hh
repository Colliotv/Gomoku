//
// Created by collio_v on 11/16/15.
//

#ifndef GOMOKU_PLAYER_HH
#define GOMOKU_PLAYER_HH

#include <referee/Piece.hh>

namespace game {

  class Player {
  protected:
    int m_taken;
    referee::Piece::identity m_identity;

  public:
    void  add_taken();
    int   taken();

  public:
    virtual bool is_human() { return true; }

  private:
    Player(const Player& _player)
        : m_taken(_player.m_taken), m_identity(_player.m_identity) {}
  public:
    Player* copy() {
      return new Player(*this);
    }
  public:
    Player(const referee::Piece::identity& identity)
        :m_taken(0), m_identity(identity) { }
  };

}

#endif //GOMOKU_PLAYER_HH

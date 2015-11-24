//
// Created by collio_v on 11/10/15.
//

#ifndef GOMOKU_BOARD_HH
#define GOMOKU_BOARD_HH

#include <array>
#include "referee/Piece.hh"

namespace referee {

  class Board {
  private:
    std::array<std::array<referee::Piece, 19>, 19> m_board;

  public:
    Board() = default;

  public:
    referee::Piece& operator [] (const Piece::Position&);

  public:

  };
};

#endif //GOMOKU_BOARD_HH

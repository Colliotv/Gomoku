//
// Created by collio_v on 11/10/15.
//

#include <iostream>
#include "referee/Board.hh"
namespace referee {
  Piece& Board::operator[](const Piece::Position& pair)
  {
    static Piece tampon(Piece::identity::out);
    try {
      return m_board.at(static_cast< unsigned >(pair.y)).at(static_cast< unsigned >(pair.x));
    } catch (std::out_of_range r) {
      std::cout << "throw back a tampon" << std::endl;
      return tampon;
    }
  }
}
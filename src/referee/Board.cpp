//
// Created by collio_v on 11/10/15.
//

#include <iostream>
#include "referee/Board.hh"
namespace referee {

  Piece& Board::operator[](const Piece::Position& pair)
  {
    static Piece tampon(Piece::identity::out);

    if (is_out(pair))
      return tampon;
    return m_board.at(static_cast< unsigned >(pair.y)).at(static_cast< unsigned >(pair.x));
  }

  void Board::notify(const Piece::Position& position)
  {
    auto& b = *this;
    auto& notifier = b[position];

    for (const auto& d : {Piece::Alignment::horizontal, Piece::Alignment::vertical, Piece::Alignment::counter_diagonal, Piece::Alignment::leading_diagonal})
      notifier.notify(b, d, 0, notifier);
    for (int it(1); it <= 4; ++it) {
      auto r = Piece::Alignment::horizontal * it + position;
      if (!is_out(r) && b[r].notify(b, Piece::Alignment::horizontal, it, notifier)) notify(r);
      r = Piece::Alignment::horizontal * -it + position;
      if (!is_out(r) && b[r].notify(b, Piece::Alignment::horizontal, -it, notifier)) notify(r);
      r = Piece::Alignment::vertical * it + position;
      if (!is_out(r) && b[r].notify(b, Piece::Alignment::vertical, it, notifier)) notify(r);
      r = Piece::Alignment::vertical * -it + position;
      if (!is_out(r) && b[r].notify(b, Piece::Alignment::vertical, -it, notifier)) notify(r);
      r = Piece::Alignment::leading_diagonal * it + position;
      if (!is_out(r) && b[r].notify(b, Piece::Alignment::leading_diagonal, it, notifier)) notify(r);
      r = Piece::Alignment::leading_diagonal * -it + position;
      if (!is_out(r) && b[r].notify(b, Piece::Alignment::leading_diagonal, -it, notifier)) notify(r);
      r = Piece::Alignment::counter_diagonal * it + position;
      if (!is_out(r) && b[r].notify(b, Piece::Alignment::counter_diagonal, it, notifier)) notify(r);
      r = Piece::Alignment::counter_diagonal * -it + position;
      if (!is_out(r) && b[r].notify(b, Piece::Alignment::counter_diagonal, -it, notifier)) notify(r);
    }
  }

  bool Board::is_out(const Piece::Position& position)
  {
    return position.x >= 18 || position.x < 0 || position.y >= 18 || position.y < 0;
  }
}
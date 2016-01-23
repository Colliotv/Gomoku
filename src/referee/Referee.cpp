//
// Created by collio_v on 11/10/15.
//

#include <bits/stl_pair.h>
#include <iostream>
#include "referee/Referee.hh"
#include "IAminmax/IAminmax.hh"

static const std::array< referee::Piece::Position, 8> directions({
      referee::Piece::Position{ 0, -1},
      referee::Piece::Position{ 0,  1},

      referee::Piece::Position{ 1, -1},
      referee::Piece::Position{-1,  1},

      referee::Piece::Position{-1,  0},
      referee::Piece::Position{ 1,  0},

      referee::Piece::Position{-1, -1},
      referee::Piece::Position{ 1,  1}
                                                                 });

static const std::array< referee::Piece::Position, 4> halved_directions({
      referee::Piece::Position{ 0, -1},

      referee::Piece::Position{ 1, -1},

      referee::Piece::Position{-1,  0},

      referee::Piece::Position{-1, -1},
                                                                        });


bool referee::Referee::place_at(const Piece::Position& _position)
{
  if (win() != Piece::identity::none)
    return false;

  referee::Piece::Position position(m_first_play ? referee::Piece::Position({9, 9}) : _position);

  if ( not m_first_play and ( not m_board[position].can_pose(m_turn) ) )
    return false;

  m_first_play = false;
  take(position);
  place(position);

  if (test_potential_win(position))
    return true;
  for (const auto& p: m_potential_win)
    if (test_potential_win(p, true)) return true;

  if (m_turn == Piece::identity::black)
    m_turn = Piece::identity::white;
  else
    m_turn = Piece::identity::black;

  return true;
}

referee::Referee::Referee(game::Player* white, game::Player* black)
    : m_first_play(true), m_turn(referee::Piece::identity::black), m_win(referee::Piece::identity::none), m_white(white), m_black(black) {}

void referee::Referee::place(const Piece::Position& position)
{
  std::cout << "place" << std::endl;
  board()[position].set_identity(m_turn);
  std::cout << "notify" << std::endl;
  board().notify(position);
  std::cout << "notified" << std::endl;
}

void referee::Referee::take(const Piece::Position& position) {
  for (const auto& oth: directions) {
    if (
        board()[oth * 3 + position].is_same_color(m_turn)
            and board()[oth * 2 + position].is_other_color(m_turn)
            and board()[oth * 1 + position].is_other_color(m_turn)
        ) {
      board().notify(oth * 2 + position);
      board()[oth * 2 + position].set_identity(Piece::identity::none);
      board().notify(oth * 1 + position);
      board()[oth * 1 + position].set_identity(Piece::identity::none);
      if (m_turn == Piece::identity::white) {
        m_white->add_taken();
        if (m_white->taken() >= 10)
          m_win = Piece::identity::white;
      } else {
        m_black->add_taken();
        if (m_black->taken() >= 10)
          m_win = Piece::identity::black;
      }
    }
  }
}

bool referee::Referee::test_potential_win(const referee::Piece::Position& position, bool in_test)
{
  for (const auto& oth : halved_directions) {
    int line(0);
    int pseudo_line(0);
    {
      int pre(1);
      for (; this->m_board[oth * -pre + position].is_same_color(m_turn) && !this->m_board[oth * -pre + position].is_breakable(); ++pre) ++ line, ++pseudo_line;
      for (; this->m_board[oth * -pre + position].is_same_color(m_turn) ; ++pre) ++ pseudo_line;
    }
    {
      int post(1);
      for (;this->m_board[oth * post + position].is_same_color(m_turn) && !this->m_board[oth * post + position].is_breakable(); ++post) ++ line, ++pseudo_line;
      for (;this->m_board[oth * post + position].is_same_color(m_turn) ; ++post) ++ pseudo_line;
    }
    if (line >= 4) {
      m_win = m_turn;
      return true;
    }
    if (pseudo_line >= 4 && !in_test) {
      m_potential_win.push_back(position);
    }
  }
  if (m_turn == Piece::identity::white && m_white->taken() >= 10) {
    m_win = m_turn;
  } else if ( m_turn == Piece::identity::black && m_black->taken() >= 10) {
    m_win = m_turn;
  }

  return false;
}

bool referee::Referee::human_turn()
{
  return m_turn == referee::Piece::identity::black ? m_black->is_human() : m_white->is_human();
}

void referee::Referee::ia_place()
{
  switch (m_turn){
    case Piece::identity::white:
      dynamic_cast<IAminmax*>(m_white)->IaTurn();
      break;
    case Piece::identity::black:
      dynamic_cast<IAminmax*>(m_black)->IaTurn();
      break;
  case Piece::identity::none:break;
  case Piece::identity::out:break;
  }
}

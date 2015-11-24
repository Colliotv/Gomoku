//
// Created by collio_v on 11/10/15.
//

#include <bits/stl_pair.h>
#include <iostream>
#include "referee/Referee.hh"

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

# define MARK_LOG(p)\
  std::cout << "mark at " << (p).x << "/" << (p).y << std::endl;
# define UNMARK_LOG(p)\
  std::cout << "unmark at " << (p).x << "/" << (p).y << std::endl;

bool referee::Referee::double_three_rule(const Piece::Position& position)
{
  int     direction_identifier(0);

  for (const auto& oth : directions) {
    if (this->m_board[oth+position].is_empty()) {
      if (not this->m_board[oth*2 + position].is_empty()) {
        if (this->m_board[oth*2+ position].is_same_color(m_turn)) {
          if (this->m_board[oth*3 + position].is_empty()) {
            MARK_LOG(oth*3+position)
            this->m_board[oth*3 + position].mark_for(m_turn, direction_identifier / 2);
            MARK_LOG(-oth+position)
            this->m_board[oth + position].mark_for(m_turn, direction_identifier / 2);
            MARK_LOG(oth+position)
            this->m_board[-oth + position].mark_for(m_turn, direction_identifier / 2);
          } else
          if (this->m_board[oth*3 + position].is_same_color(m_turn)) {
            UNMARK_LOG(oth*3+position)
            this->m_board[oth*3 + position].unmark_for(m_turn, direction_identifier / 2);
            UNMARK_LOG(oth+position)
            this->m_board[oth + position].unmark_for(m_turn, direction_identifier / 2);
            UNMARK_LOG(-oth+position)
            this->m_board[-oth + position].unmark_for(m_turn, direction_identifier / 2);

            MARK_LOG(position)
            this->m_board[position].mark_for(m_turn, direction_identifier / 2);
            MARK_LOG(oth*2+position)
            this->m_board[oth*2 + position].mark_for(m_turn, direction_identifier / 2);
            MARK_LOG(oth*3+position)
            this->m_board[oth*3 + position].mark_for(m_turn, direction_identifier / 2);
          }
        }
        continue;
      }
    } else
    if (this->m_board[oth+position].is_same_color(m_turn)) {//NX
      if (this->m_board[oth * 2 + position].is_same_color(m_turn)) {//NXX
        UNMARK_LOG(-oth + position)
        this->m_board[-oth + position].unmark_for(m_turn, direction_identifier / 2);
        UNMARK_LOG(oth*3 + position)
        this->m_board[oth*3 + position].unmark_for(m_turn, direction_identifier / 2);
        UNMARK_LOG(oth*4 + position)
        this->m_board[oth*4 + position].unmark_for(m_turn, direction_identifier / 2);

        MARK_LOG(oth + position)
        this->m_board[oth + position].mark_for(m_turn, direction_identifier / 2);
        MARK_LOG(oth*2 + position)
        this->m_board[oth*2 + position].mark_for(m_turn, direction_identifier / 2);
      } else
      if (this->m_board[oth*2+position].is_empty() and not (
            this->m_board[oth  * -1 + position].is_other_color(m_turn) or
            this->m_board[oth  * -2 + position].is_other_color(m_turn) or
            this->m_board[oth  * +2 + position].is_other_color(m_turn) or
            this->m_board[oth  * +3 + position].is_other_color(m_turn)
      )) {//NX_
        MARK_LOG(-oth + position)
        this->m_board[-oth + position].mark_for(m_turn, direction_identifier / 2);
        MARK_LOG(-oth*2 + position)
        this->m_board[-oth*2 + position].mark_for(m_turn, direction_identifier / 2);
        MARK_LOG(oth*2 + position)
        this->m_board[oth*2 + position].mark_for(m_turn, direction_identifier / 2);
        MARK_LOG(oth*3 + position)
        this->m_board[oth*3 + position].mark_for(m_turn, direction_identifier / 2);
      }
    } else
    if (this->m_board[position + oth].is_other_color(m_turn)) {//NO
      if (this->m_board[oth * 2 + position].is_other_color(m_turn)) {//NOO
        if (this->m_board[oth * 3 + position].is_other_color(m_turn) and this->m_board[oth * 4 + position].is_empty()) {//NOOO_
          this->m_board[position + oth * 1].unmark_adv(m_turn, direction_identifier / 2);
          this->m_board[position + oth * 2].unmark_adv(m_turn, direction_identifier / 2);
          this->m_board[position + oth * 3].unmark_adv(m_turn, direction_identifier / 2);
        }
        else if (this->m_board[oth * 3 + position].is_empty() and this->m_board[oth * 4 + position].is_other_color(m_turn) and this->m_board[oth * 5 + position].is_empty()) {//NOO_O
          this->m_board[position + oth * 1].unmark_adv(m_turn, direction_identifier / 2);
          this->m_board[position + oth * 2].unmark_adv(m_turn, direction_identifier / 2);
          this->m_board[position + oth * 4].unmark_adv(m_turn, direction_identifier / 2);
        }
        else if (this->m_board[oth * 3 + position].is_empty() and this->m_board[oth * 4 + position].is_empty()) {
          this->m_board[position + oth * -1].unmark_adv(m_turn, direction_identifier / 2);
          this->m_board[position + oth * 0].unmark_adv(m_turn, direction_identifier / 2);
          this->m_board[position + oth * 3].unmark_adv(m_turn, direction_identifier / 2);
          this->m_board[position + oth * 4].unmark_adv(m_turn, direction_identifier / 2);
        }
      } else
      if (this->m_board[oth*2 + position].is_empty() and this->m_board[oth * 3 + position].is_other_color(m_turn)) {//NO_O

      }
    }
    ++direction_identifier;
  }
  return false;
}

bool referee::Referee::place_at(const Piece::Position& _position)
{
  if (win() != Piece::identity::none)
    return false;
  referee::Piece::Position position(m_first_play ? referee::Piece::Position({9, 9}) : _position);

  if ( not m_first_play and ( not m_board[position].can_pose() or !can_pose(position) ) )
    return false;
  if ( not m_first_play and double_three_rule(position) )
    return false;

  m_first_play = false;
  take(position);
  place(position);
  if (test_potential_win(position)) {
    return true;
  }

  if (m_turn == Piece::identity::black)
    m_turn = Piece::identity::white;
  else
    m_turn = Piece::identity::black;

  return true;
}

referee::Referee::Referee(game::Player* white, game::Player* black)
    : m_first_play(true), m_turn(referee::Piece::identity::black), m_win(referee::Piece::identity::none), m_white(white), m_black(black) {}

bool referee::Referee::can_pose(const referee::Piece::Position& position)
{
  m_first_play = false;
  referee::Piece& piece(m_board[position]);

  if (m_turn == Piece::identity::white) {
    std::array<int, Piece::alignements_count>::iterator it;
    it = std::find_if(piece.m_white_three_alignement.begin(), piece.m_white_three_alignement.end(), [](int p){
      std::cout << p << std::endl;
      return p > 0;});
    if (it != piece.m_white_three_alignement.end())
      std::cout << "i'm on a marked case" << std::endl;
    if (it != std::end(piece.m_white_three_alignement)
        && std::find_if(it + 1, piece.m_white_three_alignement.end(), [](int p){return p > 0;}) != std::end(piece.m_white_three_alignement)) {
      std::cout << "false" << std::endl;
      return false;
    }

    if (piece.is_three_white_aligned()) {

    }

  } else {
    std::array<int, Piece::alignements_count>::iterator it;
    it = std::find_if(piece.m_black_three_alignement.begin(), piece.m_black_three_alignement.end(), [](int p){return p > 0;});
    if (it != std::end(piece.m_black_three_alignement)
        && std::find_if(it + 1, piece.m_black_three_alignement.end(), [](int p){return p > 0;}) != std::end(piece.m_black_three_alignement))
      return false;

    if (piece.is_three_black_aligned()) {

    }


  }
  return true;
}

void referee::Referee::place(const Piece::Position& position)
{
  for (const auto& oth : directions) {
    board()[position + oth].near_enable();
  }
  board()[position].set_identity(m_turn);
}

void referee::Referee::take(const Piece::Position& position) {
  for (const auto& oth: directions) {
    if (
        board()[oth * 3 + position].is_same_color(m_turn)
            and board()[oth * 2 + position].is_other_color(m_turn)
            and board()[oth * 1 + position].is_other_color(m_turn)
        ) {
      for (const auto& _oth: directions) {
        board()[oth * 2 + position + _oth].near_disable();
        board()[oth * 1 + position + _oth].near_disable();
      }
      if (m_turn == Piece::identity::white) {
	m_white->add_taken();
      } else {
	m_black->add_taken();
      }
      board()[oth * 2 + position].set_identity(Piece::identity::none);
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

bool referee::Referee::test_potential_win(const referee::Piece::Position& position)
{
  for (const auto& oth : halved_directions) {
    int line(0);

    {
      int pre(1);
      for (; this->m_board[oth * -pre + position].is_same_color(m_turn); ++pre) ++ line;
    }
    {
      int post(1);
      for (;this->m_board[oth * post + position].is_same_color(m_turn); ++post) ++ line;
    }
    if (line >= 4) {
      m_win = m_turn;
      return true;
    }
  }
  if (m_turn == Piece::identity::white && m_white->taken() >= 10) {
    m_win = m_turn;
  } else if ( m_turn == Piece::identity::black && m_black->taken() >= 10) {
    m_win = m_turn;
  }

  return false;
}

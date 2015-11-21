//
// Created by collio_v on 11/16/15.
//

#include "Player.hh"

void game::Player::add_taken()
{
  m_taken += 2;
}

int game::Player::taken()
{
  return m_taken;
}

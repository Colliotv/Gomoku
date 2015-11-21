//
// Created by collio_v on 11/16/15.
//

#ifndef GOMOKU_PLAYER_HH
#define GOMOKU_PLAYER_HH

namespace game {

  class Player {
  private:
    int m_taken;

  public:
    void  add_taken();
    int   taken();

  };

}

#endif //GOMOKU_PLAYER_HH

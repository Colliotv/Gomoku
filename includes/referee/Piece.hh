//
// Created by collio_v on 11/10/15.
//

#ifndef GOMOKU_PIECE_HH
#define GOMOKU_PIECE_HH

#include <array>
#include <algorithm>
#include <map>
#include <bits/stl_list.h>

namespace referee {

  class Board;

  class Piece {
  public:
    struct Position {
      int x;
      int y;

      Position(int x, int y)
          :x(x), y(y) {}

      Position(Position&&) = default;
      Position(const Position&) = default;

      const bool     operator == (const Position&) const;

      const Position operator + (const Position&) const;
      const Position operator * (int) const;
      const Position operator - () const;
      const Position operator - (const Position&) const;
    };
    using Direction = Piece::Position;

    class Alignment {
    public:
      static const Position vertical;
      static const Position horizontal;
      static const Position leading_diagonal;
      static const Position counter_diagonal;
    };

    struct Mask {
      unsigned int mask;
      unsigned int size;

      unsigned int self_mask;

      std::list<unsigned int> concerned_distances;

      Mask(unsigned int mask, unsigned int size, const std::list<unsigned int>& concerned_distances, unsigned int self_mask)
          :mask(mask), size(size), self_mask(self_mask), concerned_distances(concerned_distances) { }
    };

  public:
    enum class identity {
      none,
      white,
      black,
      out
    };

  private: //identity
    identity            m_identity;

  public:
    identity            operator*() { return m_identity; }
    bool                is_empty();
    bool                is_white();
    bool                is_black();

    bool                is_same_color(Piece::identity);
    bool                is_other_color(Piece::identity);

    void                set_identity(identity);


  private://observer pattern
    struct DirectedObserver {
      unsigned int m_observed_states;
      unsigned int m_observed_three_belonging;

      bool         m_is_in_unbreakable_three;

      DirectedObserver() : m_observed_states(0), m_observed_three_belonging(0), m_is_in_unbreakable_three(false) {}
    };
    std::map< const Direction, DirectedObserver >   directedObservers;

    bool                calculate_playable_by_white();
    bool                calculate_playable_by_black();

  public:
    bool                notify(const referee::Board&, const Direction& direction, int distance, const Piece& oth);

  private://observable pattern
    bool          has_status_changed;

  private:
    bool                                            m_cannot_be_played_as_white;
    bool                                            m_cannot_be_played_as_black;
    unsigned short                                  m_near;


  public://go rule
    void                force_near();
    bool                can_pose(identity);


  public:
    Piece(identity i = referee::Piece::identity::none) : m_identity(i), m_cannot_be_played_as_white(false), m_cannot_be_played_as_black(false), m_near(0) { }
    Piece(const Piece&) = default;
  };
};

#endif //GOMOKU_PIECE_HH

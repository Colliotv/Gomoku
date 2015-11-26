//
// Created by collio_v on 11/10/15.
//

#ifndef GOMOKU_PIECE_HH
#define GOMOKU_PIECE_HH

#include <array>
#include <algorithm>
#include <map>
#include <list>

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

      bool     operator == (const Position&) const;
      bool     operator <  (const Position&) const;

      Position& operator = (const Position&) = default;

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

      Mask(unsigned int mask, unsigned int size, const std::list<unsigned int>& concerned_distances = {}, unsigned int self_mask = 0)
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
    inline identity&           operator*() { return m_identity; }
    inline identity            operator*() const { return m_identity; }

    bool                is_white();
    bool                is_black();

    bool                is_same_color(Piece::identity);
    bool                is_other_color(Piece::identity);

    bool                is_breakable();

    void                set_identity(identity);


  private://observer pattern
    struct DirectedObserver {
      unsigned int m_observed_states;
      unsigned int m_observed_three_belonging;

      bool         m_is_in_unbreakable_three;

      DirectedObserver() : m_observed_states(0), m_observed_three_belonging(0), m_is_in_unbreakable_three(false) {}
    };
    std::map< const Direction, DirectedObserver >   directedObservers;
    bool                m_is_breakable;

    bool                calculate_playable_by_white();
    bool                calculate_playable_by_black();
    bool                calculate_in_unbreakable_three();
    bool                calculate_breakable();

  public:
    bool                notify(const referee::Board&, const Direction& direction, int distance, const Piece& oth);

  private:
    bool                                            m_cannot_be_played_as_white;
    bool                                            m_cannot_be_played_as_black;
    unsigned short                                  m_near;


  public://go rule
    bool                can_pose(identity);


  public:
    Piece(identity i = referee::Piece::identity::none);
    Piece(const Piece&) = default;
  };
};

#endif //GOMOKU_PIECE_HH

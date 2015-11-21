//
// Created by collio_v on 11/10/15.
//

#ifndef GOMOKU_PIECE_HH
#define GOMOKU_PIECE_HH

#include <array>
#include <algorithm>

namespace referee {

  class Piece {
  public:
    struct Position {
      int x;
      int y;

      Position(int x, int y)
          :x(x), y(y) {}

      Position(Position&&) = default;
      Position(const Position&) = default;

      const Position operator + (const Position&) const;
      const Position operator * (int) const;
      const Position operator - () const;
    };
  public:
    enum class identity {
      none,
      white,
      black,
      out
    };
    enum class alignement : short{
      vertical,
      oblique_bh,
      horizontal,
      oblique_hb
    };
    constexpr static const short alignements_count = 4;

  private:
    identity    m_piece;

  public:
    std::array<int, alignements_count>  m_white_three_alignement;
    std::array<int, alignements_count>  m_black_three_alignement;
    bool  is_three_aligned() const;
    bool  is_three_black_aligned() const;
    bool  is_three_white_aligned() const;
    void  mark_for(Piece::identity, int alignement);
    void  unmark_for(Piece::identity, int alignement);
    void  unmark_adv(Piece::identity, int alignement);

  private:
    int m_near;
  public:
    inline void          near_enable() { m_near += 1; }
    inline void          near_disable() { m_near -= 1; }

  public:
    identity     operator*() { return m_piece; }

  public:
    bool                can_pose();
    bool                is_same_color(Piece::identity);
    bool                is_other_color(Piece::identity);

  public:
    bool                is_empty();
    bool                is_white();
    bool                is_black();
    void                set_identity(identity);

  public:
    Piece(identity i = referee::Piece::identity::none) : m_piece(i), m_white_three_alignement(), m_black_three_alignement(), m_near(false) { }
    Piece(const Piece&) = default;
  };
};

#endif //GOMOKU_PIECE_HH

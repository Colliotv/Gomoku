//
// Created by collio_v on 11/10/15.
//

#include <iostream>
#include "referee/Piece.hh"
#include "referee/Board.hh"

namespace referee {

  /*
   * Position
   */
  const bool            Piece::Position::operator == (const Position& oth) const {
    return oth.x == x && oth.y == y;
  }

  const bool            Piece::Position::operator<(const Position& oth) const {
    return x < oth.x || (x == oth.x && y < oth.y);
  }

  const Piece::Position Piece::Position::operator+(const Piece::Position& oth) const
  {
    return Piece::Position(oth.x + x, oth.y + y);
  }

  const Piece::Position Piece::Position::operator*(int i) const
  {
    return Piece::Position(x * i, y * i);
  }

  const Piece::Position Piece::Position::operator-() const
  {
    return Piece::Position(-x, -y);
  }

  const Piece::Position  Piece::Position::operator - (const Position& oth) const {
    return Piece::Position({ this->x - oth.x, y - oth.y});
  }


  /*
   * Alignment
   */
  const Piece::Position Piece::Alignment::vertical({0, 1});
  const Piece::Position Piece::Alignment::horizontal({1, 0});
  const Piece::Position Piece::Alignment::leading_diagonal({1, 1});
  const Piece::Position Piece::Alignment::counter_diagonal({1, -1});


  /*
   * Piece
   */

#define PieceIdentity
  bool Piece::can_pose(identity _identity)
  {
    return m_identity == identity::none && m_near > 0 &&
        ( (_identity == identity::white && !m_cannot_be_played_as_white) || (_identity == identity::black && !m_cannot_be_played_as_black) );
  }

  bool Piece::is_black()
  {
    return m_identity == Piece::identity::black;
  }

  bool Piece::is_white()
  {
    return m_identity == Piece::identity::white;
  }


  bool Piece::is_same_color(Piece::identity identity)
  {
    return identity == m_identity;
  }

  bool Piece::is_other_color(Piece::identity _identity)
  {
    return _identity == identity::white ? m_identity == identity::black : m_identity == identity::white;
  }


  bool Piece::is_breakable() {
    return m_is_breakable;
  }

  void Piece::set_identity(Piece::identity _identity){
    m_identity = _identity;
  }

#undef PieceIdentity

#define PieceObservator
# define ObservableCenter 4

  static const std::array<Piece::Mask, 2> _3off_potential_white_three_mask({
                                                                               //            _ W W _ S _
                                                                               Piece::Mask(0b001010000000, 6, {6, 7},
                                                                                           0b001010001000),
                                                                               //            _ W _ W S _
                                                                               Piece::Mask(0b001000100000, 6, {5, 7},
                                                                                           0b001000101000),
                                                                           });

  static const std::array<Piece::Mask, 2> _2off_potential_white_three_mask({
                                                                               //            _ _ W W S _ _
                                                                               Piece::Mask(0b00001010000000, 7, {5, 6},
                                                                                           0b00001010100000),
                                                                               //            _ W _ S W _
                                                                               Piece::Mask(0b001000001000, 6, {3, 6},
                                                                                           0b000100101000),
                                                                           });

  static const std::array<Piece::Mask, 2> _1off_potential_white_three_mask({
                                                                               //            _ _ W S W _ _
                                                                               Piece::Mask(0b00001000100000, 7, {3, 5},
                                                                                           0b00001010100000),
                                                                               //            _ W S _ W _
                                                                               Piece::Mask(0b001000001000, 6, {2, 5},
                                                                                           0b001010001000)
                                                                           });

  static const std::array<Piece::Mask, 3> _0off_potential_white_three_mask({
                                                                               //            _ _ S W W _ _
                                                                               Piece::Mask(0b00000010100000, 7, {2, 3},
                                                                                           0b00001010100000),
                                                                               //            _ S W _ W _
                                                                               Piece::Mask(0b000010001000, 6, {1, 3},
                                                                                           0b001010001000),
                                                                               //            _ S _ W W _
                                                                               Piece::Mask(0b000000101000, 6, {1, 2},
                                                                                           0b001000101000),
                                                                           });

  static const std::array<Piece::Mask, 2> _3off_breakable_white({
                                                                    //            B W S _
                                                                    Piece::Mask(0b01101000, 4),
                                                                    //            _ W S B
                                                                    Piece::Mask(0b00101001, 4),
                                                                });

  static const std::array<Piece::Mask, 2> _2off_breakable_white({
                                                                    //            B S W _
                                                                    Piece::Mask(0b01101000, 4),
                                                                    //            _ S W B
                                                                    Piece::Mask(0b00101001, 4),
                                                                });



  static const std::array<Piece::Mask, 2> _3off_potential_black_three_mask({
                                                                               //             _ B B _ S _
                                                                               Piece::Mask(0b000101000000, 6, {6, 7},
                                                                                           0b000101000100),
                                                                               //             _ B _ B S _
                                                                               Piece::Mask(0b000100010000, 6, {5, 7},
                                                                                           0b000100010100),
                                                                           });

  static const std::array<Piece::Mask, 2> _2off_potential_black_three_mask({
                                                                               //             _ _ B B S _ _
                                                                               Piece::Mask(0b00000101000000, 7, {5, 6},
                                                                                           0b00000101010000),
                                                                               //             _ B _ S B _
                                                                               Piece::Mask(0b000100000100, 6, {3, 6},
                                                                                           0b000100010100),
                                                                           });

  static const std::array<Piece::Mask, 2> _1off_potential_black_three_mask({
                                                                               //             _ _ B S B _ _
                                                                               Piece::Mask(0b00000100010000, 7, {3, 5},
                                                                                           0b00000101010000),
                                                                               //             _ B S _ B _
                                                                               Piece::Mask(0b000100000100, 6, {2, 5},
                                                                                           0b000101000100)
                                                                           });

  static const std::array<Piece::Mask, 3> _0off_potential_black_three_mask({
                                                                               //             _ _ S B B _ _
                                                                               Piece::Mask(0b00000001010000, 7, {2, 3},
                                                                                           0b00000101010000),
                                                                               //             _ S B _ B _
                                                                               Piece::Mask(0b000001000100, 6, {1, 3},
                                                                                           0b000101000100),
                                                                               //             _ S _ B B _
                                                                               Piece::Mask(0b000000010100, 6, {1, 2},
                                                                                           0b000100010100),
                                                                           });

  static const std::array<Piece::Mask, 2> _3off_breakable_black({
                                                                    //            W B S _
                                                                    Piece::Mask(0b10010100, 4),
                                                                    //            _ B S W
                                                                    Piece::Mask(0b00010110, 4),
                                                                });

  static const std::array<Piece::Mask, 2> _2off_breakable_black({
                                                                    //            W B S _
                                                                    Piece::Mask(0b10010100, 4),
                                                                    //            _ S B W
                                                                    Piece::Mask(0b00010110, 4),
                                                                });


  bool Piece::notify(const Board& board, const Direction& direction, int distance, const Piece& oth)
  {

    if (oth.m_identity != identity::none && (distance == 1 || distance == -1)) {
      std::cout << "near placed" << std::endl;
      m_near += 1;
    } else if (distance == 1 || distance == -1) {
      m_near -= 1;
    }


    DirectedObserver& d = directedObservers.at(direction);

    unsigned int  mask(3);
    unsigned int  value( (0b10u * (*oth == identity::white)) | (0b01u * (*oth == identity::black)) | (0b11u * (*oth == identity::out)) );

    mask <<= (distance + ObservableCenter) * 2;
    value <<= (distance + ObservableCenter) * 2;

    d.m_observed_states &= ~mask;
    d.m_observed_states |= value;

    {
      unsigned int  _mask(0b1u);
      unsigned int  is_in_unbreakable_three(0b0u);
      for (const auto& oth_d : oth.directedObservers) {
        if (oth_d.first == direction) continue;
        if (oth_d.second.m_is_in_unbreakable_three)
          is_in_unbreakable_three = 0b1u;
      }

      _mask <<= (distance + ObservableCenter);
      is_in_unbreakable_three <<= (distance + ObservableCenter);

      d.m_observed_three_belonging &= ~_mask;
      d.m_observed_three_belonging |= is_in_unbreakable_three;
    }

    m_cannot_be_played_as_black = calculate_playable_by_black();
    m_cannot_be_played_as_white = calculate_playable_by_white();
    m_is_breakable = calculate_breakable();

    return calculate_in_unbreakable_three();
  }

  bool Piece::calculate_in_unbreakable_three()
  {
    bool has_changed(false);

    for (auto& d: directedObservers) {
      bool in_unbreakable_three(false);

      for (const Piece::Mask& m: _3off_potential_white_three_mask) {
        unsigned int v = (d.second.m_observed_states >> 6) & ((1 << (m.size * 2)) -1);
        if (v == m.self_mask) {
          in_unbreakable_three = true;
        }
      }
      for (const Piece::Mask& m: _2off_potential_white_three_mask) {
        unsigned int v = (d.second.m_observed_states >> 4) & ((1 << (m.size * 2)) -1);
        if (v == m.self_mask) {
          in_unbreakable_three = true;
        }
      }
      for (const Piece::Mask& m: _1off_potential_white_three_mask) {
        unsigned int v = (d.second.m_observed_states >> 2) & ((1 << (m.size * 2)) -1);
        if (v == m.self_mask) {
          in_unbreakable_three = true;
        }
      }
      for (const Piece::Mask& m: _0off_potential_white_three_mask) {
        unsigned int v = (d.second.m_observed_states >> 0) & ((1 << (m.size * 2)) -1);
        if (v == m.self_mask) {
          in_unbreakable_three = true;
        }
      }

      for (const Piece::Mask& m: _3off_potential_black_three_mask) {
        unsigned int v = (d.second.m_observed_states >> 6) & ((1 << (m.size * 2)) -1);
        if (v == m.self_mask) {
          in_unbreakable_three = true;
        }
      }
      for (const Piece::Mask& m: _2off_potential_black_three_mask) {
        unsigned int v = (d.second.m_observed_states >> 4) & ((1 << (m.size * 2)) -1);
        if (v == m.self_mask) {
          in_unbreakable_three = true;
        }
      }
      for (const Piece::Mask& m: _1off_potential_black_three_mask) {
        unsigned int v = (d.second.m_observed_states >> 2) & ((1 << (m.size * 2)) -1);
        if (v == m.self_mask) {
          in_unbreakable_three = true;
        }
      }
      for (const Piece::Mask& m: _0off_potential_black_three_mask) {
        unsigned int v = (d.second.m_observed_states >> 0) & ((1 << (m.size * 2)) -1);
        if (v == m.self_mask) {
          in_unbreakable_three = true;
        }
      }

      if (in_unbreakable_three && !d.second.m_is_in_unbreakable_three) {
        d.second.m_is_in_unbreakable_three = !d.second.m_is_in_unbreakable_three;
        has_changed = true;
      } else if (!in_unbreakable_three && d.second.m_is_in_unbreakable_three) {
        d.second.m_is_in_unbreakable_three = !d.second.m_is_in_unbreakable_three;
        has_changed = true;
      }

    }
    return has_changed;
  }

  bool  Piece::calculate_playable_by_white()
  {
    int potential_three_overlapping(0);

    for (auto& d: directedObservers) {
      bool _potential_three_overlapping(false);

      for (const Piece::Mask& m: _3off_potential_white_three_mask) {
        unsigned int v = (d.second.m_observed_states >> 6) & ((1 << (m.size * 2)) -1);
        if ( v == m.mask && !_potential_three_overlapping) {
          for (unsigned int t: m.concerned_distances)
            if ( (d.second.m_observed_three_belonging >> t) & 0b1u)
              return true;
          _potential_three_overlapping = true;
        }
      }

      for (const Piece::Mask& m: _2off_potential_white_three_mask) {
        unsigned int v = (d.second.m_observed_states >> 4) & ((1 << (m.size * 2)) -1);
        if ( v == m.mask && !_potential_three_overlapping) {
          for (unsigned int t: m.concerned_distances)
            if ( (d.second.m_observed_three_belonging >> t) & 0b1u)
              return true;
          _potential_three_overlapping = true;
        }
      }

      for (const Piece::Mask& m: _1off_potential_white_three_mask) {
        unsigned int v = (d.second.m_observed_states >> 2) & ((1 << (m.size * 2)) -1);
        if ( v == m.mask && !_potential_three_overlapping) {
          for (unsigned int t: m.concerned_distances)
            if ( (d.second.m_observed_three_belonging >> t) & 0b1u)
              return true;
          _potential_three_overlapping = true;
        }
      }

      for (const Piece::Mask& m: _0off_potential_white_three_mask) {
        unsigned int v = (d.second.m_observed_states >> 0) & ((1 << (m.size * 2)) -1);
        if ( v == m.mask && !_potential_three_overlapping) {
          for (unsigned int t: m.concerned_distances)
            if ( (d.second.m_observed_three_belonging >> t) & 0b1u)
              return true;
          _potential_three_overlapping = true;
        }
      }

      if (_potential_three_overlapping) {
        potential_three_overlapping += 1;
      }
    }

    return potential_three_overlapping > 1;
  }

  bool  Piece::calculate_playable_by_black()
  {
    int potential_three_overlapping(0);

    for (auto& d: directedObservers) {

      for (const Piece::Mask& m: _3off_potential_black_three_mask) {
        unsigned int v = (d.second.m_observed_states >> 6) & ((1 << (m.size * 2)) -1);
        if ( v == m.mask ) {
          for (unsigned int t: m.concerned_distances)
            if ( (d.second.m_observed_three_belonging >> t) & 0b1u)
              return true;
          potential_three_overlapping += 1;
          goto next_direction;
        }
      }

      for (const Piece::Mask& m: _2off_potential_black_three_mask) {
        unsigned int v = (d.second.m_observed_states >> 4) & ((1 << (m.size * 2)) -1);
        if ( v == m.mask ) {
          for (unsigned int t: m.concerned_distances)
            if ( (d.second.m_observed_three_belonging >> t) & 0b1u)
              return true;
          potential_three_overlapping += 1;
          goto next_direction;
        }
      }

      for (const Piece::Mask& m: _1off_potential_black_three_mask) {
        unsigned int v = (d.second.m_observed_states >> 2) & ((1 << (m.size * 2)) -1);
        if ( v == m.mask ) {
          for (unsigned int t: m.concerned_distances)
            if ( (d.second.m_observed_three_belonging >> t) & 0b1u)
              return true;
          potential_three_overlapping += 1;
          goto next_direction;
        }
      }

      for (const Piece::Mask& m: _0off_potential_black_three_mask) {
        unsigned int v = (d.second.m_observed_states >> 0) & ((1 << (m.size * 2)) -1);
        if ( v == m.mask ) {
          for (unsigned int t: m.concerned_distances)
            if ( (d.second.m_observed_three_belonging >> t) & 0b1u)
              return true;
          potential_three_overlapping += 1;
          goto next_direction;
        }
      }

      next_direction:0;
    }
    return potential_three_overlapping > 1;
  }

  bool Piece::calculate_breakable()
  {
    for (const auto& d: directedObservers) {
      for (const Piece::Mask& m: _3off_breakable_black) {
        unsigned v( (d.second.m_observed_states >> 6) & ((1 << (m.size * 2)) - 1) );
        if (v == m.mask)
          return true;
      }
      for (const Piece::Mask& m: _2off_breakable_black) {
        unsigned v( (d.second.m_observed_states >> 4) & ((1 << (m.size * 2)) - 1) );
        if (v == m.mask)
          return true;
      }
      for (const Piece::Mask& m: _3off_breakable_white) {
        unsigned v( (d.second.m_observed_states >> 6) & ((1 << (m.size * 2)) - 1) );
        if (v == m.mask)
          return true;
      }
      for (const Piece::Mask& m: _2off_breakable_white) {
        unsigned v( (d.second.m_observed_states >> 4) & ((1 << (m.size * 2)) - 1) );
        if (v == m.mask)
          return true;
      }
    }
    return false;
  }

#undef PieceObservator

  Piece::Piece(identity i)
      :m_identity(i),
      directedObservers({
                            std::make_pair(Alignment::horizontal, DirectedObserver()),
                            std::make_pair(Alignment::counter_diagonal, DirectedObserver()),
                            std::make_pair(Alignment::leading_diagonal, DirectedObserver()),
                            std::make_pair(Alignment::vertical, DirectedObserver()),
                        }),
      m_cannot_be_played_as_white(false),
      m_cannot_be_played_as_black(false),
      m_near(0)
  { }
}

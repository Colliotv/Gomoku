//
// Created by collio_v on 11/10/15.
//

#include "referee/Piece.hh"

namespace referee {
    bool Piece::can_pose(Piece::identity i)
    {
        return m_piece == identity::none &&
                !(i==identity::white ? m_white_interdiction : m_black_interdiction);
    }

    const Piece::Position Piece::Position::operator+(const Piece::Position& oth) const
    {
        return Piece::Position(oth.x + x, oth.y + y);
    }

    bool  Piece::is_three_aligned() const
    {
        return std::find(m_black_three_alignement.begin(), m_black_three_alignement.end(), true) != std::end(m_black_three_alignement)
                && std::find(m_white_three_alignement.begin(), m_white_three_alignement.end(), true) != std::end(m_white_three_alignement);
    }

    bool  Piece::is_three_black_aligned() const
    {
        return std::find(m_black_three_alignement.begin(), m_black_three_alignement.end(), true) != std::end(m_black_three_alignement);
    }

    bool  Piece::is_three_white_aligned() const
    {
        return std::find(m_white_three_alignement.begin(), m_white_three_alignement.end(), true) != std::end(m_white_three_alignement);
    }

    bool Piece::is_empty()
    {
        return this->m_piece == referee::Piece::identity::none;
    }

    const Piece::Position Piece::Position::operator*(int i) const
    {
        return Piece::Position(x * i, y * i);
    }

    const Piece::Position Piece::Position::operator-() const
    {
        return Piece::Position(-x, -y);
    }

    bool Piece::is_same_color(Piece::identity identity)
    {
        return identity == m_piece;
    }
    void Piece::mark_for(Piece::identity identity, int alignement)
    {
        if (identity == Piece::identity::black) {
            m_black_three_alignement[alignement] += 1;
        }
        if (identity == Piece::identity::white) {
            m_black_three_alignement[alignement] += 1;
        }
    }
    void Piece::unmark_for(Piece::identity identity, int alignement)
    {
        if (identity == Piece::identity::black && m_black_three_alignement[alignement] > 0) {
            m_black_three_alignement[alignement] -= 1;
        }
        if (identity == Piece::identity::white && m_black_three_alignement[alignement] > 0) {
            m_black_three_alignement[alignement] -= 1;
        }
    }
}
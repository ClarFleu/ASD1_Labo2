//
//  pieces.h
//  Puzzle récursif
//
//  Created by Olivier Cuisenaire on 06.11.18.
//  Copyright © 2018 Olivier Cuisenaire. All rights reserved.
//

#ifndef pieces_h
#define pieces_h

#include <array>
#include <vector>
#include <string>

enum AttachementType {
  FILLE_HAUT, FILLE_BAS, DAME_HAUT, DAME_BAS, ARROSOIR_GAUCHE, ARROSOIR_DROIT, GATEAU_GAUCHE, GATEAU_DROIT,  ARROSOIR_INVERSE, NONE };

using Piece  = std::array<AttachementType,4>;
using Pieces = std::vector<Piece>;

extern const Pieces PIECES;

std::ostream& operator<<(std::ostream& lhs, const Piece& rhs);

std::ostream& operator<<(std::ostream& lhs, const AttachementType& rhs);

bool operator==(const Piece& lhs, const Piece& rhs);

void rotation(const Piece& piece, int rotNum, Pieces& rotations);

bool memePiece(const Piece& piece1, const Piece& piece2);

#endif /* pieces_h */

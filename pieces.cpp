//
//  pieces.cpp
//  Puzzle récursif
//
//  Created by Olivier Cuisenaire on 06.11.18.
//  Copyright © 2018 Olivier Cuisenaire. All rights reserved.
//

#include "pieces.h"

#include <iostream>

const Pieces PIECES = {
  { DAME_HAUT, GATEAU_DROIT, ARROSOIR_GAUCHE, FILLE_HAUT }, //1
  { DAME_BAS, ARROSOIR_GAUCHE, FILLE_HAUT, GATEAU_DROIT },  //2
  { FILLE_BAS, GATEAU_GAUCHE, DAME_HAUT, ARROSOIR_DROIT },  //3
  { ARROSOIR_DROIT, GATEAU_GAUCHE, DAME_HAUT, FILLE_HAUT},  //4
  { FILLE_BAS, DAME_HAUT, ARROSOIR_DROIT, GATEAU_DROIT },   //5
  { DAME_BAS, GATEAU_GAUCHE, FILLE_HAUT, ARROSOIR_DROIT},   //6
  { FILLE_BAS, ARROSOIR_GAUCHE, DAME_HAUT, GATEAU_DROIT },  //7
  { DAME_BAS, ARROSOIR_GAUCHE, GATEAU_DROIT, FILLE_HAUT },  //8
  { ARROSOIR_INVERSE, DAME_HAUT, GATEAU_DROIT, FILLE_BAS }, //9
};

void rotation(const Piece& piece, int rotNum, Pieces& rotations) {
    
    if(rotNum == 3) {
        return;
    } else {
        Piece r;
        
        AttachementType temp = piece.at(3);
        
        for (int i = 1; i < 4; ++i) {
            r.at(i) = piece.at(i-1);
        }
        r.at(0) = temp;
        
        rotations.push_back(r);
        
        rotation(r, rotNum+1, rotations);
    }
}

bool operator==(const Piece& lhs, const Piece& rhs) {
    for (int i = 0; i < 4; ++i) {
        if (lhs.at(i) != rhs.at(i)){
            return false;
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& lhs, const AttachementType& rhs) {
    switch (rhs) {
        case FILLE_HAUT:       return lhs << "FILLE_HAUT";
        case FILLE_BAS:        return lhs << "FILLE_BAS";
        case DAME_HAUT:        return lhs << "DAME_HAUT";
        case DAME_BAS:         return lhs << "DAME_BAS";
        case ARROSOIR_GAUCHE:  return lhs << "ARROSOIR_GAUCHE";
        case ARROSOIR_DROIT:   return lhs << "ARROSOIR_DROIT";
        case GATEAU_GAUCHE:    return lhs << "GATEAU_GAUCHE";
        case GATEAU_DROIT:     return lhs << "GATEAU_DROIT";
        case ARROSOIR_INVERSE: return lhs << "ARROSOIR_INVERSE";
        case NONE:             return lhs << "NONE";
            
        default:
            return lhs;
    }
    
}

std::ostream& operator<<(std::ostream& lhs, const Piece& rhs) {
    
    for (int i = 0; i < 9; ++i) {
        Pieces rotations;
        rotations.push_back(PIECES.at(i));
        rotation(PIECES.at(i), 0, rotations);
        char r = 'A';
        for (int j = 0; j < 4; ++j) {
            if (rhs == rotations.at(j)) {
                return lhs << i+1 << r;
            }
            ++r;
        }
    }
    return lhs;
}

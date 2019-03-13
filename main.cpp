//
//  main.cpp
//  Labo2
//
//  Created by Clarisse Fleurimont on 06.03.19.
//  Copyright © 2019 Clarisse Fleurimont. All rights reserved.
//

#include <iostream>

#include "pieces.h"

using namespace std;

// Compteur de solutions
unsigned nbSolutions = 0;
// Vecteur de solution
Pieces solution;
// Toutes les pieces possibles (y compris les rotations)
Pieces pieces;

// void placerPiece(int positionPiece);
void placerPiece(const Piece& premierePiece, const Piece& pieceAPlacer);

bool pieceValable(const Piece& piece);

int pieceSuivante(int positionPiece);

int rotationOuPieceSuivante(int positionPiece);

std::ostream& operator<<(std::ostream& lhs, const Piece& rhs);

std::ostream& operator<<(std::ostream& lhs, const AttachementType& rhs);

bool operator==(const Piece& lhs, const Piece& rhs);

void rotation(const Piece& piece, int rotNum, Pieces& rotations);

bool memePiece(const Piece& piece1, const Piece& piece2);


int main() {
    cout << PIECES.size() << " pieces." << endl;
    
    for (int i = 0; i < PIECES.size(); ++i) {
        pieces.push_back(PIECES.at(i));
        rotation(PIECES.at(i), 0, pieces);
    }
    cout << pieces.size() << " rotations en tout." << endl;
    

    cout << "Nb solution totale : " << nbSolutions << endl;
    
    /* affichage de toutes les pieces et leurs rotations
    for (size_t i = 0; i < pieces.size(); ++i) {
        cout << pieces.at(i) << endl;
    }*/
    
    return 0;
}

void placerPiece(const Piece& premierePiece, const Piece& pieceAPlacer) {
    if (solution.size() == 9) {
        ++nbSolutions;
        // On affiche la solution trouvée
        int cpt = 0;
        for(Piece p : solution) {
            cout << p;
            if (cpt % 3)
                cout << endl;
            else
                cout << ' ';
        }
        //placerPiece(pieceSuivante(premierePiece), pieceSuivante(pieceSuivante(premierePiece)))
    } else if (false){
       
    }
    
}

/*
void placerPiece(int positionPiece) {
    if (solution.size() == 9) {
        ++nbSolutions;
        // On affiche les solutions
        for(Piece p : solution)
            cout << p << ' ';
    } else if (positionPiece >= pieces.size() || rotationOuPieceSuivante(positionPiece) < 0) {
        return;
    } else {
        if (pieceValable(pieces.at(positionPiece))) {
            solution.push_back(pieces.at(positionPiece));
            return placerPiece(pieceSuivante(positionPiece));
        }
    }
    placerPiece(positionPiece);
}
*/
bool pieceValable(const Piece& piece) {
    
    
    return false;
}

int pieceSuivante(int positionPiece){
    size_t tailleMax = pieces.size() - positionPiece;
    if (tailleMax > 4) {
        for (int a = 0; a < tailleMax; ++a) {
            if (!memePiece(pieces.at(positionPiece), pieces.at(positionPiece+a))) {
                return a;
            }
        }
    }
    return -1;
}

int rotationOuPieceSuivante(int positionPiece){
    if (positionPiece < pieces.size()-1) {
        return ++positionPiece;
    }
    return -1;
}

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

bool memePiece(const Piece& piece1, const Piece& piece2) {
   Pieces rotations;
   rotations.push_back(piece1);
   rotation(piece1, 0, rotations);
   for (int i = 0; i < rotations.size(); ++i) {
      if (piece2 == rotations.at(i)) {
         return true;
      }
   }
   return false;
}

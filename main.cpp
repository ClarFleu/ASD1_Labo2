//
//  main.cpp
//  Labo2
//
//  Created by Clarisse Fleurimont on 06.03.19.
//  Copyright © 2019 Clarisse Fleurimont. All rights reserved.
//

#include <iostream>
#include <vector>

#include "pieces.h"

using namespace std;

const Piece PIECE_VIDE = {NONE, NONE, NONE, NONE};
// Toutes les pieces possibles (y compris les rotations)
Pieces pieces;
// Compteur de solutions --> devrait être égal à toutesLesSolutions.size()
unsigned nbSolutions = 0;

unsigned piecesTentees = 0;
// Vecteur de solution
Pieces solution(9), plan(9);
// Vecteur contenant toutes les solutions trouvées
vector<Pieces> toutesLesSolutions;

vector<vector<size_t>> getAdjacents(size_t pos);

void placerPiece(Pieces& plan, size_t piece, unsigned positionPiece);
//void placerPiece(int positionPiece);
//void placerPiece(const Piece& piece);

void afficherSolution(const Pieces& sol);

bool imageComplete(const AttachementType& im1, const AttachementType& im2);

bool pieceValable(size_t posPiece);

int pieceSuivante(int positionPiece);

int rotationOuPieceSuivante(int positionPiece);

std::ostream& operator<<(std::ostream& lhs, const Piece& rhs);

std::ostream& operator<<(std::ostream& lhs, const AttachementType& rhs);

bool operator==(const Piece& lhs, const Piece& rhs);

void rotation(const Piece& piece, int rotNum, Pieces& rotations);

bool memePiece(const Piece& piece1, const Piece& piece2);


// osdjpaéokdjsf
void casseTeteReq(Pieces& aUtiliser, Pieces& plan);
void casseTete();

int main() {
   for (size_t i = 0; i < 9; ++i) {
      plan.at(i) = PIECE_VIDE;
   }
    cout << PIECES.size() << " pieces." << endl;
    
    for (int i = 0; i < PIECES.size(); ++i) {
        pieces.push_back(PIECES.at(i));
        rotation(PIECES.at(i), 0, pieces);
    }
    cout << pieces.size() << " rotations en tout." << endl;
   
   casseTete();
    //placerPiece(solution, 0, 0);
   
    cout << "Nb solution totale : " << nbSolutions << endl;
    
    /* affichage de toutes les pieces et leurs rotations
    for (size_t i = 0; i < pieces.size(); ++i) {
        cout << pieces.at(i) << endl;
    }*/
    
    return 0;
}

void casseTete() {
   Pieces aUtiliser = PIECES;
   casseTeteReq(aUtiliser, plan);
}

void casseTeteReq(Pieces& aUtiliser, Pieces& plan) {
   if (aUtiliser.size() == 0) {
      bool sol = true;
      for (int i = 0; i < plan.size(); ++i) {
         if (plan.at(i)==PIECE_VIDE) {
            sol = false;
            break;
         }
      }
      if (sol) {
         ++nbSolutions;
         afficherSolution(plan);
      }
      return;
   } else {
      
      
      size_t positionPiece;
      for (size_t i = 0; i < plan.size(); ++i) {
         if(plan.at(i)==PIECE_VIDE) {
             positionPiece = i;
            break;
         } else {
            positionPiece = -1;
         }
      }
      
      for (size_t pPos = 0; pPos < aUtiliser.size(); ++pPos) {
         Piece piece = aUtiliser.at(pPos);
         
         vector<vector<size_t>> adj = getAdjacents(positionPiece);
         Pieces rotationsP;
         rotationsP.push_back(piece);
         rotation(piece, 0, rotationsP);
         bool piecesPlaceable = true;
         
         // on parcourt toutes les rotations de la pieces
         for (size_t rot = 0; rot < rotationsP.size(); ++rot) {
            
            for (size_t i = 0; i < adj.size(); ++i) {
               // on test si la piece peut entrer
               size_t POSITION_PIECE_COURANTE = adj.at(i).at(0),
                      PIECE_ADJ = adj.at(i).at(1),
                      POSITION_PIECE_ADJ = adj.at(i).at(2);
               piecesPlaceable = imageComplete(rotationsP.at(rot).at(POSITION_PIECE_COURANTE), plan.at(PIECE_ADJ).at(POSITION_PIECE_ADJ));
            }
            
            if (piecesPlaceable) {
               if (pPos >= aUtiliser.size()) {
                  plan.at(positionPiece) = rotationsP.at(rot);
                  casseTeteReq(aUtiliser, plan);
               } else {
                  plan.at(positionPiece) = rotationsP.at(rot);
                  aUtiliser.erase(aUtiliser.begin() + pPos);
                  casseTeteReq(aUtiliser, plan);
                  plan.at(positionPiece) = PIECE_VIDE;
                  aUtiliser.push_back(piece);
               }
            }
         }
         //aUtiliser.erase(aUtiliser.begin() + pPos);
      }
   }
   return;
}

void afficherSolution(const Pieces& sol) {
   for (int i = 0; i < sol.size();++i) {
      cout << sol.at(i) << " ";
      if (i%3==2) {
         cout << endl;
      }
   }
   cout << endl;
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

vector<vector<size_t>> getAdjacents(size_t pos) {
   vector<vector<size_t>> v;
   switch (pos) {
      case 0:
         v = {};
         break;
      case 1:
         v = {{3, 0, 1}};
         break;
      case 2:
         v = {{3, 1, 1}};
         break;
      case 3:
         v = {{0, 0, 2}};
         break;
      case 4:
         v = {{0, 1, 2}, {3, 3, 1}};
         break;
      case 5:
         v = {{0, 2, 2}, {3, 4, 1}};
         break;
      case 6:
         v = {{0, 3, 2}};
         break;
      case 7:
         v = {{0, 4, 2}, {3, 6, 1}};
         break;
      case 8:
         v = {{0, 5, 2}, {3, 7, 1}};
         break;
         
      default:
         break;
   }
   return v;
}

bool operator==(const Piece& lhs, const Piece& rhs) {
   for (int i = 0; i < 4; ++i) {
      if (lhs.at(i) != rhs.at(i)){
         return false;
      }
   }
   return true;
}

bool imageComplete(const AttachementType& im1, const AttachementType& im2) {
   switch (im1) {
      case FILLE_HAUT:       return im2 == FILLE_BAS;
      case FILLE_BAS:        return im2 == FILLE_HAUT;
      case DAME_HAUT:        return im2 == DAME_BAS;
      case DAME_BAS:         return im2 == DAME_HAUT;
      case ARROSOIR_GAUCHE:  return im2 == ARROSOIR_DROIT;
      case ARROSOIR_DROIT:   return im2 == ARROSOIR_GAUCHE;
      case GATEAU_GAUCHE:    return im2 == GATEAU_DROIT;
      case GATEAU_DROIT:     return im2 == GATEAU_GAUCHE;
      case ARROSOIR_INVERSE: return false;
      case NONE:             return im2 == NONE;
         
      default:
         return false;
   }
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
      char r = 'a';
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

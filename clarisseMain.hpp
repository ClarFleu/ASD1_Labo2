//
//  clarisseMain.hpp
//  Labo2
//
//  Created by Clarisse Fleurimont on 18.03.19.
//  Copyright © 2019 Clarisse Fleurimont. All rights reserved.
//

#ifndef clarisseMain_hpp
#define clarisseMain_hpp

#include <iostream>
#include <vector>

#include "pieces.h"
#include <algorithm>

using namespace std;

// Clarisse
const Piece PIECE_VIDE = {NONE, NONE, NONE, NONE};
// Toutes les pieces possibles (y compris les rotations)
Pieces pieces;
// Compteur de solutions --> devrait être égal à toutesLesSolutions.size()
unsigned nbSolutions = 0;

unsigned piecesTentees = 0;
// Vecteur de solution
Pieces solution(9);
// Vecteur contenant toutes les solutions trouvées
vector<Pieces> toutesLesSolutions;

void placerPiece(Pieces& plan, size_t piece, unsigned positionPiece);

void afficherSolution(const Pieces& sol);

bool imageComplete(const AttachementType& im1, const AttachementType& im2);

bool pieceValable(size_t posPiece);

int pieceSuivante(int positionPiece);

bool estPlacable(const Piece& newPiece, int position, const Pieces& jeu);

std::ostream& operator<<(std::ostream& lhs, const Piece& rhs);

std::ostream& operator<<(std::ostream& lhs, const AttachementType& rhs);

bool operator==(const Piece& lhs, const Piece& rhs);

void rotation(const Piece& piece, int rotNum, Pieces& rotations);

// osdjpaéokdjsf
void casseTete(const Pieces& listePieces, Pieces& plan, int indicePiece);
AttachementType visAVis(size_t positionPiece, size_t positionImage);
Pieces plan(9), plan1(9), plan2(9);


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
   
   casseTete(PIECES, plan, 0);
   //placerPiece(solution, 0, 0);
   
   cout << "Nb solution totale : " << nbSolutions << endl;
   
   /* affichage de toutes les pieces et leurs rotations
    for (size_t i = 0; i < pieces.size(); ++i) {
    cout << pieces.at(i) << endl;
    }*/
   
   return 0;
}

void casseTete(const Pieces& listePieces, Pieces& plan, int indicePiece) {
   if (indicePiece >= listePieces.size()) {
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
      size_t positionVide = -1;
      for (size_t i = 0; i < plan.size(); ++i) {
         if (plan.at(i) == PIECE_VIDE) {
            positionVide = i;
            break;
         }
      }
      
      Piece piece = listePieces.at(indicePiece);
      
      Pieces rotationsP;
      rotationsP.push_back(piece);
      rotation(piece, 0, rotationsP);
      bool piecesPlaceable = true;
      
      // on parcourt toutes les rotations de la pieces
      for (size_t rot = 0; rot < rotationsP.size(); ++rot) {
         // on regarde si la rotation peut être placée
         for (int i = 0; i < 4; ++i) {
            //piecesPlaceable = imageComplete(rotationsP.at(rot).at(i), visAVis(positionPiece, i));
            
            if (!imageComplete(rotationsP.at(rot).at(i), visAVis(positionVide, i)) ) {
               piecesPlaceable = false;
            }
            //piecesPlaceable = true;
         }
         // Si elle peut être placée
         if (piecesPlaceable) {
            // On la met à la bonne position sur le plan
            plan.at(positionVide) = rotationsP.at(rot);
            
            // On appelle la récursive afin de continuer
            casseTete(listePieces, plan, indicePiece+1);
            
            plan.at(indicePiece) = PIECE_VIDE;
         }
      }
   }
}

void afficherSolution(const Pieces& sol) {
   for (int i = 0; i < sol.size();++i) {
      cout << sol.at(i) << " ";
      if (i%3==2) {
         //cout << endl;
      }
   }
   cout << endl;
}

void rotation(const Piece& piece, int rotNum, Pieces& rotations) {
   
   if (rotNum == 3) {
      return;
   } else {
      Piece r;
      
      AttachementType temp = piece.at(3);
      
      for (int i = 1; i < 4; ++i) {
         r.at(i) = piece.at(i - 1);
      }
      r.at(0) = temp;
      
      rotations.push_back(r);
      
      rotation(r, rotNum + 1, rotations);
   }
}

bool operator==(const Piece& lhs, const Piece& rhs) {
   for (int i = 0; i < 4; ++i) {
      if (lhs.at(i) != rhs.at(i)) {
         return false;
      }
   }
   return true;
}

bool imageComplete(const AttachementType& im1, const AttachementType& im2) {
   switch (im1) {
      case FILLE_HAUT:       return (im2 == FILLE_BAS       || im2 == NONE);
      case FILLE_BAS:        return (im2 == FILLE_HAUT      || im2 == NONE);
      case DAME_HAUT:        return (im2 == DAME_BAS        || im2 == NONE);
      case DAME_BAS:         return (im2 == DAME_HAUT       || im2 == NONE);
      case ARROSOIR_GAUCHE:  return (im2 == ARROSOIR_DROIT  || im2 == NONE);
      case ARROSOIR_DROIT:   return (im2 == ARROSOIR_GAUCHE || im2 == NONE);
      case GATEAU_GAUCHE:    return (im2 == GATEAU_DROIT    || im2 == NONE);
      case GATEAU_DROIT:     return (im2 == GATEAU_GAUCHE   || im2 == NONE);
      case ARROSOIR_INVERSE: return (im2 == NONE);
      case NONE:             return true;
         
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
            return lhs << i + 1 << r;
         }
         ++r;
      }
   }
   return lhs;
   
}

AttachementType visAVis(size_t positionPiece, size_t positionImage) {
   switch (positionPiece) {
      case 0: return NONE;
      case 1:
         if (positionImage == 3)
            return plan.at(0).at(1);
         else
            return NONE;
      case 2:
         if (positionImage == 3)
            return plan.at(1).at(1);
         else
            return NONE;
      case 3:
         if (positionImage == 0)
            return plan.at(0).at(2);
         else
            return NONE;
      case 4:
         if (positionImage == 0)
            return plan.at(1).at(2);
         else if (positionImage == 3)
            return plan.at(3).at(1);
         else
            return NONE;
      case 5:
         if (positionImage == 0)
            return plan.at(2).at(2);
         else if (positionImage == 3)
            return plan.at(4).at(1);
         else
            return NONE;
      case 6:
         if (positionImage == 0)
            return plan.at(3).at(2);
         else
            return NONE;
      case 7:
         if (positionImage == 0)
            return plan.at(4).at(2);
         else if (positionImage == 3)
            return plan.at(6).at(1);
         else
            return NONE;
      case 8:
         if (positionImage == 0)
            return plan.at(5).at(2);
         else if (positionImage == 3)
            return plan.at(7).at(1);
         else
            return NONE;
         
      default:
         break;
   }
   return NONE;
}

#endif /* clarisseMain_hpp */

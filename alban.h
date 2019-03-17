//
//  main.cpp
//  Labo2
//
//  Created by Clarisse Fleurimont on 06.03.19.
//  Copyright © 2019 Clarisse Fleurimont. All rights reserved.
//

#include <iostream>

#include "pieces.h"
#include <algorithm>

using namespace std;


const Piece BLANK{ NONE, NONE, NONE, NONE};

using Solutions = vector<string>;


bool estAttachableAttachementType(AttachementType first, AttachementType second);

bool estAttachable(const Pieces& jeu, int position1, int position2);

Pieces fonctionRecursion(const Pieces& oldJeu, Solutions& solutions);

bool estPlacable(const Piece& newPiece, int position, const Pieces& jeu);

bool estAttachableCoteACote(const Piece& up, const Piece& down, bool horizontal);

std::ostream& operator<<(std::ostream& lhs, const Piece& rhs);

std::ostream& operator<<(std::ostream& lhs, const AttachementType& rhs);

bool operator==(const Piece& lhs, const Piece& rhs);

void rotation(const Piece& piece, int rotNum, Pieces& rotations);

bool EXACTEMENTmemePiece(const Piece& piece1, const Piece& piece2);

Piece rotationSimple(const Piece& oldPiece, int nbr);
/*
int main() {

   Solutions mesSolu;

   Pieces jeuTest = {
      BLANK, BLANK, BLANK,
      BLANK, BLANK, BLANK,
      BLANK, BLANK, BLANK
   };


   //fonctionRecursion(jeuTest, mesSolu);

   cout << "-------------------\n---------------------\n---------------------\n---------------------\n---------------------" << endl;

   for (const string& s : mesSolu) {
      cout << s << endl;
   }



   return 0;
}*/

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

//y compris les rotations

bool operator==(const Piece& lhs, const Piece& rhs) {
   
   return (EXACTEMENTmemePiece(lhs, rhs) ||
           EXACTEMENTmemePiece(lhs, rotationSimple(rhs, 1)) ||
           EXACTEMENTmemePiece(lhs, rotationSimple(rhs, 2)) ||
           EXACTEMENTmemePiece(lhs, rotationSimple(rhs, 3)));

}

bool EXACTEMENTmemePiece(const Piece& piece1, const Piece& piece2) {

   for (int i = 0; i < 4; ++i) {
      if (piece1.at(i) != piece2.at(i)) {
         return false;
      }
   }
   return true;
}

std::ostream& operator<<(std::ostream& lhs, const AttachementType& rhs) {
   switch (rhs) {
      case FILLE_HAUT: return lhs << "FILLE_HAUT";
      case FILLE_BAS: return lhs << "FILLE_BAS";
      case DAME_HAUT: return lhs << "DAME_HAUT";
      case DAME_BAS: return lhs << "DAME_BAS";
      case ARROSOIR_GAUCHE: return lhs << "ARROSOIR_GAUCHE";
      case ARROSOIR_DROIT: return lhs << "ARROSOIR_DROIT";
      case GATEAU_GAUCHE: return lhs << "GATEAU_GAUCHE";
      case GATEAU_DROIT: return lhs << "GATEAU_DROIT";
      case ARROSOIR_INVERSE: return lhs << "ARROSOIR_INVERSE";
      case NONE: return lhs << "NONE";

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
            return lhs << i + 1 << r;
         }
         ++r;
      }
   }
   return lhs;
}

Piece rotationSimple(const Piece& oldPiece, int nbr) {

   Piece newPiece = oldPiece;

   for (int i = 0; i < nbr; i++) {
      AttachementType epave = newPiece.at(0);

      for (int i = 0; i < 3; i++) {
         newPiece.at(i) = newPiece.at(i + 1);
      }

      newPiece.at(3) = epave;
   }

   //bizarrement rotate de algorithm marchait pas, car sa aurait été bcp plus simple avec
   return newPiece;
}

int findNextFreePiece(const Pieces& usedPieces, int positionOfLastPiece) {


   for (size_t i = positionOfLastPiece; i < PIECES.size(); i++) {
      //cout << "boucle i" << endl;
      if (i>PIECES.size())
         cout << "error" << endl;
      if (find(usedPieces.begin(), usedPieces.end(), PIECES.at(i)) == usedPieces.end()){
         cout << find(usedPieces.begin(), usedPieces.end(), PIECES.at(i))-usedPieces.begin()<< endl;
         return i;
      }
   }

   return -1;

}

bool estAttachableAttachementType(AttachementType first, AttachementType second) {
   if (first == NONE || second == NONE)
      return true;

   else if (first == second || first == ARROSOIR_INVERSE || second == ARROSOIR_INVERSE)
      return false;

   else if (first / 2 == second / 2)//division entière
      return true;

   else
      return false;
}

bool estAttachable(const Pieces& jeu, int position1, int position2) {
   int pre;
   int post;

   if (position1 > position2) {
      post = position1;
      pre = position2;
   } else {
      post = position2;
      pre = position1;
   }

   int relatifHori = (post % 3)-(pre % 3);
   int relatifVerti = (post / 3)-(pre / 3);

   if (relatifHori == 0 && relatifVerti == 1)
      return estAttachableCoteACote(jeu.at(post), jeu.at(pre), false);


   else if (relatifHori == 1 && relatifVerti == 0)
      return estAttachableCoteACote(jeu.at(post), jeu.at(pre), true);

   else {
      cout << "something went wrong, not placable because no edge in contact" << endl;
      return false;
   }



}

bool estAttachableCoteACote(const Piece& up, const Piece& down, bool horizontal) {
   return estAttachableAttachementType(up.at(0 + horizontal), down.at(2 + horizontal));
}

bool estPlacable(const Piece& newPiece, int position, const Pieces& jeu) {
   switch (position) {
      case 0:
         return (estAttachable(jeu, 0, 1) && estAttachable(jeu, 0, 3));
      case 1:
         return (estAttachable(jeu, 1, 0) && estAttachable(jeu, 1, 4) && estAttachable(jeu, 1, 2));
      case 2:
         return (estAttachable(jeu, 2, 1) && estAttachable(jeu, 2, 5));
      case 3:
         return (estAttachable(jeu, 3, 0) && estAttachable(jeu, 3, 4) && estAttachable(jeu, 3, 6));
      case 4:
         return (estAttachable(jeu, 4, 1) && estAttachable(jeu, 4, 3) && estAttachable(jeu, 4, 7) && estAttachable(jeu, 4, 5));
      case 5:
         return (estAttachable(jeu, 5, 2) && estAttachable(jeu, 5, 4) && estAttachable(jeu, 5, 8));
      case 6:
         return (estAttachable(jeu, 6, 3) && estAttachable(jeu, 6, 7));
      case 7:
         return (estAttachable(jeu, 7, 6) && estAttachable(jeu, 7, 4) && estAttachable(jeu, 7, 8));
      case 8:
         return (estAttachable(jeu, 8, 7) && estAttachable(jeu, 8, 5));
      default:
         cout << "piece hors limite" << endl;
         return false;
   }
}

//recupere le string d'un jeu

string getString(const Pieces& jeu) {
   return "jeej";
}

Pieces fonctionRecursion(const Pieces& oldJeu, Solutions& solutions) {


   Pieces jeu = oldJeu;


   auto iter = find(oldJeu.begin(), oldJeu.end(), BLANK); //on trouve la premiere place libre


   int firstBLANKposition = (iter - oldJeu.begin());

   if (iter == oldJeu.end()) {//si le jeu est remplis, ca veut dire que c'est une solution

      solutions.push_back(getString(oldJeu));
      //ca sert a rien de faire les autres pieces, on teste d'autres jeu

   } else {//le jeu est pas fini

      //recupere la prochaine piece libre 
      int selectedPiecePosition = findNextFreePiece(oldJeu, 0);

      if (selectedPiecePosition == -1) {
         cout << "plus de piece libre, ne devrait pas arriver" << endl; //comme s'il y a des BLANKS il y a des pieces libre
      }

      //debug
      int controlePiece = 0;

      while ((selectedPiecePosition != -1) || (controlePiece = !100)) {

         //debug
         controlePiece++;

         Piece selectedPiece = PIECES.at(selectedPiecePosition);
         //cout << selectedPiecePosition << endl;

         int rotationCounter = 0;
         //debug
         int controleRotation = 0;

         while ((rotationCounter < 4) || (controleRotation = !100)) {

            //debug
            controleRotation++;

            if (estPlacable(selectedPiece, firstBLANKposition, oldJeu)) {
               
               Pieces jeu = oldJeu;
               jeu.at(firstBLANKposition) = selectedPiece;
               fonctionRecursion(jeu, solutions);
               rotationCounter = 7; //break in disguise (basé sur la logique que si cette piece passe dans cette rotation, elle passera jamais dans une autre)
            } else {
               cout << "piece pas posee" << endl;
               rotationCounter++;
               selectedPiece = rotationSimple(selectedPiece, 1);
            }

         }

         //debug
         if (controleRotation == 100) {
            cout << "rotation boucle infinie" << endl;
         }

         int selectedPiecePosition = findNextFreePiece(oldJeu, selectedPiecePosition);

      }

      //debug
      if (controlePiece == 100) {
         cout << "piece boucle infinie" << endl;
      }

   }

   //cout << "test" << endl;
   return oldJeu;



}

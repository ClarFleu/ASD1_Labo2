/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   alban.h
 * Author: faval
 *
 * Created on 16. mars 2019, 19:37
 */

#ifndef ALBAN_H
#define ALBAN_H

#include "pieces.h"


//main{

const Piece BLANK
{
   NONE, NONE, NONE, NONE
};

Pieces test = {
   BLANK, BLANK, BLANK,
   BLANK, BLANK, BLANK,
   BLANK, BLANK, BLANK
};
//}

Piece rotationSimple(const Piece& oldPiece) {

   Piece newPiece = oldPiece;

   AttachementType epave = newPiece.at(0);

   for (int i = 0; i < 3; i++) {
      newPiece.at(i) = newPiece.at(i + 1);
   }

   newPiece.at(3) = epave;

   return newPiece;
}

int findNextFreePiece(const Pieces& usedPieces, int positionOfLastPiece) {

   for (size_t i = positionOfLastPiece; i < PIECES.size(); i++) {
      for (size_t j = 0; j < usedPieces.size(); j++) {
         if (!(usedPieces.at(j) == BLANK)) {
            if (!(memePiece(usedPieces.at(j), PIECES.at(i))))
               return i;
         }
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
#endif /* ALBAN_H */


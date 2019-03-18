/* ---------------------------
 Laboratoire    : 02
 Fichier        : main.cpp
 Auteur(s)      : Alban, Clarisse et Janis
 Date           : 18.03.2019
 
 But            : Creer une fonction recursive permettant de
                  trouver toutes les solutions au puzzle impossible
 --------------------------- */

#include <iostream>

#include "pieces.h"
#include <algorithm>

using namespace std;

// On cree une piece vide
const Piece BLANK{ NONE, NONE, NONE, NONE};

// Le vecteurs de Pieces contenant toutes les solutions trouvees
using Solutions = vector<Pieces>;

/**
 * @brief Verifie si les deux demi-images donnees en forment une entiere
 * @param first (AttachementType) premiere demi-image
 * @param second (AttachementType) seconde demi-image
 * @returns true (bool) si les deux images correspondent, false sinon
 */
bool estAttachableAttachementType(AttachementType first, AttachementType second);

/**
 * @brief Verifie si les deux pieces aux positions donnees sont attachables sur le jeu donne
 * @param  jeu (Pieces) le jeu sur lequel on desire placer les pieces
 * @param position1 (int) position de la premiere piece
 * @param position2 (int) position de la seconde piece
 * @returns true (bool) si les pieces peuvent etre placees, false sinon
 */
bool estAttachable(const Pieces& jeu, int position1, int position2);

/**
 * @brief La fonction recursive permettant de trouver toute les solutions au puzzle impossible
 * @param oldJeu (Pieces) plan de jeu de l'etape precedente
 * @param freePieces (Pieces) pieces qu'il reste a placer sur le jeu
 * @param solutions (Pieces) les solutions deja trouvees
 * @returns oldJeu (Pieces) derniere version du jeu
 */
Pieces fonctionRecursion(const Pieces& oldJeu, const Pieces& freePieces, Solutions& solutions);

/**
 * @brief Permet de tester si la piece donnee peut etre placee a la position donnee sur le jeu donne
 * @param newPiece (Piece) nouvelle piece a placer sur le jeu
 * @param position (int) position a laquelle il faut la placer
 * @param jeu (Pieces) jeu sur lequel il faut placer la piece
 * @returns true (bool) si la newPiece peut etre placee a la position position dans jeu
 */
bool estPlacable(const Piece& newPiece, int position, const Pieces& jeu);

/**
 * @brief Test si une piece est attachable en fonction de sa position et de ses voisins eventuels
 * @param up (Piece) piece au-dessu de la piece a tester
 * @param down (Piece) piece au-dessous de la piece a tester
 * @param horizontal (bool) permet de bouger a l'horizontale sur le jeu si c'est possible (true)
 * @returns true (bool) si la piece peut etre placee, false sinon
 */
bool estAttachableCoteACote(const Piece& up, const Piece& down, bool horizontal);

/**
 * @brief Surcharge de l'operateur de flux afin d'afficher une piece
 * @param lhs (ostream) flux auqel on ajoute la piece a afficher
 * @param rhs (Piece) piece a afficher
 * @returns lhs (ostream) flux apres l'ajout de la piece a afficher
 */
std::ostream& operator<<(std::ostream& lhs, const Piece& rhs);

/**
 * @brief Surcharge de l'operateur de flux pour afficher un AttachmentType
 * @param lhs (ostream) operateur de flux passe en argument et a miôdifier
 * @param rhs (AttachmentType) l'image a afficher
 * @returns lhs (ostream) apres l'ajout de rhs dans le flux
 */
std::ostream& operator<<(std::ostream& lhs, const AttachementType& rhs);

/**
 * @brief Surcharge de l'operateur d'egalite, deux pieces sont egales si elles sont des rotation l'une de l'autre
 * @param lhs (Piece) permiere piece a tester
 * @param rhs (Piece) seconde piece a tester
 * @returns true (bool) si les deux pieces sont des rotations de la meme piece, false sinon
 */
bool operator==(const Piece& lhs, const Piece& rhs);

/**
 * @brief Teste si deux pieces sont exactement les memes (memes images aux memes positions)
 * @param piece1 (Piece) premiere piece a tester
 * @param piece2 (Piece) seconde piece a tester
 * @returns true (bool) si les deux pieces passees en arguments son EXACTEMENT les memes, false sinon
 */
bool EXACTEMENTmemePiece(const Piece& piece1, const Piece& piece2);

/**
 * @brief Fait un nombre de rotations voulues dans le sens inverse dea aiguilles d'une montre sur une piece
 * @param oldPiece (Piece) piece initiale
 * @param nbr (int) nombre de rotations a faire
 * @returns newPiece (Piece) la piece oldpiece apres nbr rotations
 */
Piece rotationSimple(const Piece& oldPiece, int nbr);

int main() {
   
   Solutions mesSolu;
   
   Pieces jeuTest = {
      BLANK, BLANK, BLANK,
      BLANK, BLANK, BLANK,
      BLANK, BLANK, BLANK
   };
   
   Pieces freePieces = PIECES;
   
   fonctionRecursion(jeuTest, freePieces, mesSolu);
   
   cout << "Notre fonction récursive trouve les " << mesSolu.size()
        << " solutions suivantes :" << endl << endl;
   for (const Pieces& P : mesSolu) {
      for (const Piece&p : P) {
         cout << p << " ";
      }
      cout << endl;
   }
   cout << endl;
   
   return 0;
}

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
      case FILLE_HAUT:        return lhs << "FILLE_HAUT";
      case FILLE_BAS:         return lhs << "FILLE_BAS";
      case DAME_HAUT:         return lhs << "DAME_HAUT";
      case DAME_BAS:          return lhs << "DAME_BAS";
      case ARROSOIR_GAUCHE:   return lhs << "ARROSOIR_GAUCHE";
      case ARROSOIR_DROIT:    return lhs << "ARROSOIR_DROIT";
      case GATEAU_GAUCHE:     return lhs << "GATEAU_GAUCHE";
      case GATEAU_DROIT:      return lhs << "GATEAU_DROIT";
      case ARROSOIR_INVERSE:  return lhs << "ARROSOIR_INVERSE";
      case NONE:              return lhs << "NONE";
      default:                return lhs;
   }
   
}

std::ostream& operator<<(std::ostream& lhs, const Piece& rhs) {
   
   for(size_t k = 0; k < PIECES.size(); ++k){
      if(rhs == PIECES.at(k)){
         for(int l = 0; l < 4; ++l){
            char c = 'a';
            if(EXACTEMENTmemePiece(rotationSimple(PIECES.at(k),l),rhs))
               return lhs << k + 1 << char (c + l);
         }
      }
   }
   
   return lhs;
}

Piece rotationSimple(const Piece& oldPiece, int nbr) {
   
   Piece newPiece = oldPiece;
   
   for (int i = 0; i < nbr; i++) {
      AttachementType epave = newPiece.at(0);
      
      for (int i = 0; i < 3; i++)
         newPiece.at(i) = newPiece.at(i + 1);
      
      newPiece.at(3) = epave;
   }
   
   return newPiece;
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
      return estAttachableCoteACote(jeu.at(pre), jeu.at(post), true);
   
   cout << "something went wrong, not placable because no edge in contact" << endl;
   return false;
}

bool estAttachableCoteACote(const Piece& up, const Piece& down, bool horizontal) {
   return estAttachableAttachementType(up.at(0 + horizontal), down.at(2 + horizontal));
}

bool estPlacable(const Piece& newPiece, int position, const Pieces& oldJeu) {
   
   Pieces jeu = oldJeu;
   jeu.at(position) = newPiece;
   
   switch (position) {
      case 0:
         return (estAttachable(jeu, 0, 1) &&
                 estAttachable(jeu, 0, 3));
      case 1:
         return (estAttachable(jeu, 1, 0) &&
                 estAttachable(jeu, 1, 4) &&
                 estAttachable(jeu, 1, 2));
      case 2:
         return (estAttachable(jeu, 2, 1) &&
                 estAttachable(jeu, 2, 5));
      case 3:
         return (estAttachable(jeu, 3, 0) &&
                 estAttachable(jeu, 3, 4) &&
                 estAttachable(jeu, 3, 6));
      case 4:
         return (estAttachable(jeu, 4, 1) &&
                 estAttachable(jeu, 4, 3) &&
                 estAttachable(jeu, 4, 7) &&
                 estAttachable(jeu, 4, 5));
      case 5:
         return (estAttachable(jeu, 5, 2) &&
                 estAttachable(jeu, 5, 4) &&
                 estAttachable(jeu, 5, 8));
      case 6:
         return (estAttachable(jeu, 6, 3) &&
                 estAttachable(jeu, 6, 7));
      case 7:
         return (estAttachable(jeu, 7, 6) &&
                 estAttachable(jeu, 7, 4) &&
                 estAttachable(jeu, 7, 8));
      case 8:
         return (estAttachable(jeu, 8, 7) &&
                 estAttachable(jeu, 8, 5));
      default:
         cout << "piece hors limite" << endl;
         return false;
   }
}

//recupere le string d'un jeu

Pieces fonctionRecursion(const Pieces& oldJeu, const Pieces& freePieces, Solutions& solutions) {

   //on trouve la premiere place libre
   auto iter = find(oldJeu.begin(), oldJeu.end(), BLANK);
 
   int firstBLANKposition = (iter - oldJeu.begin());

   // si le jeu est remplis, ca veut dire que c'est une solution
   // sinon on continue, le jeu n'est pas fini
   if (iter == oldJeu.end())
      solutions.push_back(oldJeu);
   
   else {
      //comme s'il y a des BLANKS il y a des pieces libre
      if (freePieces.size() == 0)
         cout << "plus de piece libre, ne devrait pas arriver" << endl;
    
      int selectedPiecePosition = 0;

      do {
         //recupere la prochaine piece libre
         Piece selectedPiece = freePieces.at(selectedPiecePosition);
         int rotationCounter = 0;

         while (rotationCounter < 4) {
            
            
            if (estPlacable(selectedPiece, firstBLANKposition, oldJeu)) {
               
               Pieces jeu = oldJeu;
               Pieces freePiecesCopy = freePieces;
               freePiecesCopy.erase(freePiecesCopy.begin() + selectedPiecePosition);
               
               jeu.at(firstBLANKposition) = selectedPiece;
               fonctionRecursion(jeu, freePiecesCopy, solutions);
               rotationCounter++;
               selectedPiece = rotationSimple(selectedPiece, 1);
            } else {
               rotationCounter++;
               selectedPiece = rotationSimple(selectedPiece, 1);
            }
         }
         selectedPiecePosition++;
         
      } while (selectedPiecePosition < freePieces.size());
   }
   return oldJeu;
}

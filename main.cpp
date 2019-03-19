/* ---------------------------
 Laboratoire    : 02
 Fichier        : main.cpp
 Auteur(s)      : Alban, Clarisse et Janis
 Date           : 18.03.2019
 
 But            : Creer une fonction recursive permettant de
                  trouver toutes les solutions au puzzle impossible
 --------------------------- */

#include <iostream>
#include <string>
#include "pieces.h"
#include <algorithm>

using namespace std;

// On cree une piece vide
const Piece PIECE_VIDE{ NONE, NONE, NONE, NONE};

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
 * @param up (Piece) piece au-dessu ou a gauche de la piece a tester
 * @param down (Piece) piece au-dessous ou a droite de la piece a tester
 * @param horizontal (bool) indique si les piece sont alignée horizontalement ou non
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
bool MemeRotationPiece(const Piece& piece1, const Piece& piece2);

/**
 * @brief Fait un nombre de rotations voulues dans le sens inverse dea aiguilles d'une montre sur une piece
 * @param oldPiece (Piece) piece initiale
 * @param nbr (int) nombre de rotations a faire
 * @returns newPiece (Piece) la piece oldpiece apres nbr rotations
 */
Piece rotationSimple(const Piece& oldPiece, int nbr);

int main() {

   Solutions mesSolutions;

   Pieces jeuVide = {
      PIECE_VIDE, PIECE_VIDE, PIECE_VIDE,
      PIECE_VIDE, PIECE_VIDE, PIECE_VIDE,
      PIECE_VIDE, PIECE_VIDE, PIECE_VIDE,
   };

   Pieces freePieces = PIECES;

   fonctionRecursion(jeuVide, freePieces, mesSolutions);

   cout << "Notre fonction recursive trouve les " << mesSolutions.size()
           << " solutions suivantes :" << endl << endl;
   for (const Pieces& P : mesSolutions) {
      for (const Piece&p : P) {
         cout << p << " ";
      }
      cout << endl;
   }
   cout << endl;

   return 0;
}

bool operator==(const Piece& lhs, const Piece& rhs) {

   return (MemeRotationPiece(lhs, rhs) ||
           MemeRotationPiece(lhs, rotationSimple(rhs, 1)) ||
           MemeRotationPiece(lhs, rotationSimple(rhs, 2)) ||
           MemeRotationPiece(lhs, rotationSimple(rhs, 3)));

}

bool MemeRotationPiece(const Piece& piece1, const Piece& piece2) {
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
      default: return lhs;
   }

}

std::ostream& operator<<(std::ostream& lhs, const Piece& rhs) {

   for (size_t k = 0; k < PIECES.size(); ++k) {
      if (rhs == PIECES.at(k)) {
         for (int l = 0; l < 4; ++l) {
            char c = 'a';
            if (MemeRotationPiece(rotationSimple(PIECES.at(k), l), rhs))
               return lhs << k + 1 << char (c + l);
         }
      }
   }

   return lhs;
}

//on pourrait enlever le const et le &, pour retirer la ligne "Piece newPiece = oldPiece;"
//le fait que cette fonction rerourne une Piece est la raison de pourquoi on lutilise plutot
//que juste rotate
Piece rotationSimple(const Piece& oldPiece, int nbr) {
   Piece newPiece = oldPiece;
   rotate(newPiece.begin(),newPiece.begin()+nbr,newPiece.end());
   return newPiece;
}

bool estAttachableAttachementType(AttachementType first, AttachementType second) {
   /* si une attache est NONE, ca s'acrocche, 
    * si on organise les AttachementType dans un tableau 2x5, on remarque que les lignes
    * correspondent aux accroches (a l'exception de la ligne 5, qui est "overruled/masquée" 
    * par la condition du NONE de toute façon) et donc on peut savoir si 2 attaches 
    * sont compatibles, si leurs division entière sont les memes et si elles ne sont
    * pas la meme attache.
    */

   return ((first == NONE || second == NONE) || ((first != second)&&(first / 2 == second / 2)));
}

bool estAttachable(const Pieces& jeu, int position1, int position2) {
   int avant;
   int apres;

   //determine quelle piece est placée avant l'autre
   if (position1 > position2) {
      apres = position1;
      avant = position2;
   } else {
      apres = position2;
      avant = position1;
   }

   //determine les distances entre les pieces, modulo et division entiere 3 car c'est une grille de 3x3
   int distancefHorizontale = (apres % 3)-(avant % 3);
   int distanceVerticale = (apres / 3)-(avant / 3);

   if (distancefHorizontale == 0 && distanceVerticale == 1)
      return estAttachableCoteACote(jeu.at(apres), jeu.at(avant), false);
   else if (distancefHorizontale == 1 && distanceVerticale == 0)
      return estAttachableCoteACote(jeu.at(avant), jeu.at(apres), true);

   cout << "erreur, les deux pieces ne sont pas cote a cote, ce message ne devrait jamais apparaitre" << endl;
   return false;
}

bool estAttachableCoteACote(const Piece& up, const Piece& down, bool horizontal) {
   return estAttachableAttachementType(up.at(0 + horizontal), down.at(2 + horizontal));
}

bool estPlacable(const Piece& newPiece, int position, const Pieces& oldJeu) {

   Pieces jeu = oldJeu;
   //on place d'abord la piece dans le jeu puis on verifie si ca colle
   jeu.at(position) = newPiece;

   /*les numéros correspondent a la place dans la grille 
    * 0 1 2
    * 3 4 5
    * 6 7 8*/

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

Pieces fonctionRecursion(const Pieces& oldJeu, const Pieces& freePieces, Solutions& solutions) {

   //on trouve la premiere place libre
   int firstVIDEposition = (find(oldJeu.begin(), oldJeu.end(), PIECE_VIDE) - oldJeu.begin());

   // si le jeu est remplis, ca veut dire que c'est une solution
   // sinon on continue, le jeu n'est pas fini
   if (firstVIDEposition == oldJeu.size())
      solutions.push_back(oldJeu);

   else {
      //comme s'il y a des BLANKS il y a des pieces libre
      //if (freePieces.size() == 0)
      // cout << "plus de piece libre, ne devrait pas arriver" << endl;

      //selectedPiecePosition ne correspond PAS au numéro de piece, ce qui empeche de recuperer efficacement le string de solution
      int selectedPiecePosition = 0;

      while (selectedPiecePosition < freePieces.size()) {
         //recupere la prochaine piece libre
         Piece selectedPiece = freePieces.at(selectedPiecePosition);

         //rotationCounter correspond bien a la rotation de la piece, ce qui permetrait de retrouver efficacement le string de solution 
         int rotationCounter = 0;

         while (rotationCounter < 4) {


            if (estPlacable(selectedPiece, firstVIDEposition, oldJeu)) {

               Pieces nextJeu = oldJeu;
               Pieces freePiecesCopy = freePieces;
               //on retire la piece utilisée des pieces libre
               freePiecesCopy.erase(freePiecesCopy.begin() + selectedPiecePosition);
               //on place la piece dans notre prochain jeu 
               nextJeu.at(firstVIDEposition) = selectedPiece;
               fonctionRecursion(nextJeu, freePiecesCopy, solutions);
            }
            rotationCounter++;
            selectedPiece = rotationSimple(selectedPiece, 1);
         }
         selectedPiecePosition++;

      }
   }
   //on a testé toutes les possibilités à partir de ce jeu
   return oldJeu;
}

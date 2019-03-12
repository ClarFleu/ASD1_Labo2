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
        placerPiece(pieceSuivante(premierePiece), pieceSuivante(pieceSuivante(premierePiece)))
    } else if (<#condition#>)
    
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

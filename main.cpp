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

void rotation(const Piece& piece, int rotNum, Pieces& rotations);

int main() {
    Pieces pieces;
    cout << PIECES.size() << " pieces." << endl;
    
    for (int i = 0; i < PIECES.size(); ++i) {
        pieces.push_back(PIECES.at(i));
        rotation(PIECES.at(i), 0, pieces);
    }
    cout << pieces.size() << " rotations en tout." << endl;
    
    for (size_t i = 0; i < pieces.size(); ++i) {
        cout << pieces.at(i) << endl;
        cout << endl;
    }
    
    return 0;
}

bool placerPiece(const Piece& piece) {
    
    return true;
}

bool pieceValable(const Piece& piece, const Pieces& tab, size_t position) {
    
    
    return false;
}

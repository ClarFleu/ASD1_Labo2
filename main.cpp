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
    
    return 0;
}

bool placerPiece(const Piece& piece) {
    
    return true;
}

void rotation(const Piece& piece, int rotNum, Pieces& rotations) {
    
    if(rotNum == 3) {
        return;
    } else {
        Piece r;
        
        AttachementType temp = piece.at(rotNum);
        
        for (int i = 0; i < 3; ++i) {
            r.at(i) = piece.at(i+1);
        }
        r.at(3) = temp;
        
        rotations.push_back(r);
        
        rotation(r, rotNum+1, rotations);
    }
}

bool pieceValable() {
    
}

#ifndef BOARD_H
#define BOARD_H

#include "raylib.h"

#include <iostream>
#include <vector>
#include <map>

#define screenWidth 1000
#define screenHeight 1000
#define squareWidth 125

using namespace std;

class Piece {
public:
    Texture2D image;
};

class Square {
public:
    Rectangle rec;
    Color color;

    char file;
    int rank;

    int x; // for rendering
    int y;

    Piece piece;

    Square() {
    }
};

class Board {
public:
    map<char, vector<Square>> board;
    string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    Board() {
        int rankInc = 875;

        for(char ch = 'a'; ch <= 'h'; ch++) {
            Square dummy;
            board[ch].push_back(dummy);
        }

        for(int idx = 8; idx >= 1; idx--) {
            int fileInc = 0;
            for(char ch = 'a'; ch <= 'h'; ch++) {
                int x = ch - 97 + 1;
                int y = idx;
                int s = x+y;

                Square sq;

                sq.file = ch;
                sq.rank = idx;

                sq.color = (s%2==1) ? RAYWHITE : DARKPURPLE;
                sq.x = fileInc;
                sq.y = rankInc;
                board[ch].push_back(sq);
                fileInc += squareWidth;
            }
            rankInc -= squareWidth;
        }

        // rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
        Image r = LoadImage("./pieces/white/rook.png");
        Image n = LoadImage("./pieces/white/knight.png");
        Image b = LoadImage("./pieces/white/bishop.png");
        Image q = LoadImage("./pieces/white/queen.png");
        Image k = LoadImage("./pieces/white/king.png");
        Image p = LoadImage("./pieces/white/pawn.png");

        Texture2D tr = LoadTextureFromImage(r);
        Texture2D tn = LoadTextureFromImage(n);
        Texture2D tb = LoadTextureFromImage(b);
        Texture2D tq = LoadTextureFromImage(q);
        Texture2D tk = LoadTextureFromImage(k);
        Texture2D tp = LoadTextureFromImage(p);

        map<char, Texture2D> texture_map;
        texture_map['R'] = tr;
        texture_map['N'] = tn;
        texture_map['B'] = tb;
        texture_map['Q'] = tq;
        texture_map['K'] = tk;
        texture_map['P'] = tp;


        r = LoadImage("./pieces/black/rook.png");
        n = LoadImage("./pieces/black/knight.png");
        b = LoadImage("./pieces/black/bishop.png");
        q = LoadImage("./pieces/black/queen.png");
        k = LoadImage("./pieces/black/king.png");
        p = LoadImage("./pieces/black/pawn.png");

        tr = LoadTextureFromImage(r);
        tn = LoadTextureFromImage(n);
        tb = LoadTextureFromImage(b);
        tq = LoadTextureFromImage(q);
        tk = LoadTextureFromImage(k);
        tp = LoadTextureFromImage(p);

        texture_map['r'] = tr;
        texture_map['n'] = tn;
        texture_map['b'] = tb;
        texture_map['q'] = tq;
        texture_map['k'] = tk;
        texture_map['p'] = tp;
        int rank = 8;
        char file = 'a';
        for(int i = 0; i < fen.length(); i++) {
            if (fen[i] >= 'a' && fen[i] <= 'z' || fen[i] >= 'A' && fen[i] <= 'Z') {
                board[file][rank].piece.image = texture_map[fen[i]];
            }
            file++;
            if (fen[i]=='/') {
                rank--;
                file = 'a';
            }
        }

        //board['f'][5].piece.image = t2d2;
    }
};

#endif 

#pragma once
#include <list>
#include <vector>
#include <SDL2/SDL_render.h>

namespace App {
    struct Vec4;
    Vec4 getUsableSpace(int win_w, int win_h);
    class Board {
    public:
        Board();
        void drawBoardState(SDL_Renderer* renderer, Vec4 use);
        void updateBoardState(int pos, int move = 0);
        void setBoardState(std::vector<int> board);
        std::vector<int> getBoardState();
    private:
        void drawX(SDL_Renderer* renderer, Vec4 pos);
        void drawO(SDL_Renderer* renderer, Vec4 pos);
        std::vector<int> boardState;
    };
    void drawBoardBorders(SDL_Renderer* renderer, Vec4 use);
    void mainapp(int mode);
}
#include "appmain.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_render.h>
#include <stdexcept>
#include <utility>

namespace App {
    struct Vec4 {
        float x1;
        float y1;
        float x2;
        float y2;
        float u_w;
        float u_h;
    };

    Vec4 getUsableSpace(int win_w, int win_h) {
        Vec4 ret;
        if (win_w > win_h) {
            ret.x1 = (win_w-win_h)/2;
            ret.y1 = 0;
            ret.x2 = ((win_w-win_h)/2)+win_h;
            ret.y2 = win_h;
        } else if (win_h> win_w) {
            ret.x1 = 0;
            ret.y1 = (win_h-win_w)/2;
            ret.x2 = win_w;
            ret.y2 = ((win_h-win_w)/2)+win_w;
        } else if (win_w == win_h) {
            ret.x1 = 0;
            ret.y1 = 0;
            ret.x2 = win_w -1;
            ret.y2 = win_h -1;
        } else {
            throw std::invalid_argument("Received invalid win_w and win_hin function getUsableSpace");
        }
        ret.u_w = ret.x2 - ret.x1;
        ret.u_h = ret.y2 - ret.y1;
        return ret;
    }
    Board::Board() {
        boardState.resize(8);
    }

    std::vector<int> Board::getBoardState() {
        return boardState;
    }

    void Board::setBoardState(std::vector<int> board) {
        boardState = std::move(board);
    }

    void Board::updateBoardState(int pos, int move) {
        if (pos > 8 || pos < 0) {
            throw std::invalid_argument("Received invalid pos argument in function updateBoardState");
        } if (move < 0 || move > 2) {
            throw std::invalid_argument("received invalid argument move in function updateBoardState");
        }
        boardState[pos] = move;
    }

    void Board::drawBoardState(SDL_Renderer* renderer, Vec4 use) {
        drawX(renderer, use);
    }

    void Board::drawX(SDL_Renderer* renderer, Vec4 pos) {
        SDL_RenderDrawLineF(renderer, pos.x1, pos.y1, pos.x2, pos.y2);
        SDL_RenderDrawLineF(renderer, pos.x2, pos.y1, pos.x1, pos.y2);
    }

    void Board::drawO(SDL_Renderer* renderer, Vec4 pos) {
        //
    }

    void drawBoardBorders(SDL_Renderer* renderer, Vec4 use, int win_w, int win_h) {
        SDL_RenderDrawLineF(renderer, use.x1, use.y1, use.x1, use.y2);
        SDL_RenderDrawLineF(renderer, use.x2, use.y1, use.x2, use.y2);
        SDL_RenderDrawLineF(renderer, use.x1, use.y1, use.x2, use.y1);
        SDL_RenderDrawLineF(renderer, use.x1, use.y2, use.x2, use.y2);

        SDL_RenderDrawLineF(renderer, use.x1+(use.u_w/3), use.y1, use.x1+(use.u_w/3), use.y2);
        SDL_RenderDrawLineF(renderer, use.x1+(use.u_w/3)+(use.u_w/3), use.y1, use.x1+(use.u_w/3)+(use.u_w/3), use.y2);

        SDL_RenderDrawLineF(renderer, use.x1, use.y1+(use.u_h/3), use.x2, use.y1+(use.u_h/3));
        SDL_RenderDrawLineF(renderer, use.x1, use.y1+(use.u_h/3)+(use.u_h/3), use.x2, use.y1+(use.u_h/3)+(use.u_h/3));
    }

    void mainapp(int mode) {
        if (mode != 0 && mode !=1 && mode !=2) {
            exit(mode);
        }
        SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
        SDL_Window* window = SDL_CreateWindow("TipToe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 900, window_flags);
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_GLContext gl_context = SDL_GL_CreateContext(window);
        SDL_GL_MakeCurrent(window, gl_context);
        SDL_GL_SetSwapInterval(1);

        Board* board = new Board();

        bool done = false;
        while (!done) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        done = true;
                    case SDL_WINDOWEVENT:
                        if (event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window)) {
                            done = true;
                        }
                }
            }
            int win_w, win_h;
            SDL_GetWindowSize(window, &win_h, &win_w);
            Vec4 use = getUsableSpace(win_h, win_w);

            SDL_RenderClear(renderer);

            drawBoardBorders(renderer, use, win_w, win_h);
            board->drawBoardState(renderer, use);

            SDL_RenderPresent(renderer);
            glClearColor(0.3, 0.3, 0.3, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            SDL_GL_SwapWindow(window);
        }
        SDL_DestroyRenderer(renderer);
        SDL_GL_DeleteContext(gl_context);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}
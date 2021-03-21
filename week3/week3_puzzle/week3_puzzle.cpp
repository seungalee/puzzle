#include <bangtal.h>


SceneID scene1, scene2;

ObjectID image00, image01, image02, image10, image11, image12, image20, image21, image22, blank, start;

TimerID timer1;

int boardX[3][3] = {
 {0, 200, 400},
 {0, 200, 400},
 {0, 200, 400}
};

int boardY[3][3] = {
 {400, 400, 400},
 {200,200,200},
 {0,0,0}
};

ObjectID board[3][3] = {
 {image00, image01, image02},
 {image10, image11, image12},
 {image20,image21,blank}
};

ObjectID createObject(const char* name, const char* image, SceneID scene, int x, int y, bool shown) {
    ObjectID object = createObject(name, image);
    locateObject(object, scene, x, y);
    if (shown) {
        showObject(object);
    }
    return object;
}

void Swap(ObjectID a, ObjectID b)
{
    ObjectID t = a;
    a = b;
    b = t;
}

void SwapX(int x1, int x2) {
    int tt = x1;
    x1 = x2;
    x2 = tt;
}

void SwapY(int y1, int y2) {
    int ttt = y1;
    y1 = y2;
    y2 = ttt;
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
    if (object == start) {
        hideObject(start);
        enterScene(scene2);
        startTimer(timer1);
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {

            if (object == board[i][j] && object != blank) {
                if (i < 2 && board[i + 1][j] == blank) {
                    Swap(board[i][j], blank);
                    SwapX(boardX[i][j], boardX[i + 1][j]);
                    SwapY(boardY[i][j], boardY[i + 1][j]);

                    locateObject(board[i][j], scene2, boardX[i + 1][j], boardY[i + 1][j]);
                    locateObject(board[i + 1][j], scene2, boardX[i][j], boardY[i][j]);

                }

                else if (i > 0 && board[i - 1][j] == blank) {
                    Swap(board[i][j], blank);
                    locateObject(board[i][j], scene2, boardX[i - 1][j], boardY[i - 1][j]);
                    locateObject(board[i - 1][j], scene2, boardX[i][j], boardY[i][j]);
                    

                }

                else if (j < 2 && board[i][j + 1] == blank) {
                    Swap(board[i][j], blank);
                    locateObject(board[i][j], scene2, boardX[i][j + 1], boardY[i][j + 1]);
                    locateObject(board[i][j + 1], scene2, boardX[i][j], boardY[i][j]);
                    

                }

                else if (j > 0 && board[i][j - 1] == blank) { 
                    Swap(board[i][j], blank);
                    locateObject(board[i][j], scene2, boardX[i][j - 1], boardY[i][j - 1]);
                    locateObject(board[i][j - 1], scene2, boardX[i][j], boardY[i][j]);
                    

                }

            }

        }

    }

}

void timerCallback(TimerID, timer) {
    if (timer == timer1) {
        showObject(restart);
    }
}

int main() {

    setMouseCallback(mouseCallback);
    scene1 = createScene("puzzle", "harrypotter.png");
    scene2 = createScene("퍼즐", "background.png");
    board[0][0] = createObject("hp01.png", scene2, boardX[0][0], boardY[0][0], true);
    board[0][1] = createObject("hp02.png", scene2, boardX[0][1], boardY[0][1], true);
    board[0][2] = createObject("hp03.png", scene2, boardX[0][2], boardY[0][2], true);
    board[1][0] = createObject("hp04.png", scene2, boardX[1][0], boardY[1][0], true);
    board[1][1] = createObject("hp05.png", scene2, boardX[1][1], boardY[1][1], true);
    board[1][2] = createObject("hp06.png", scene2, boardX[1][2], boardY[1][2], true);
    board[2][0] = createObject("hp07.png", scene2, boardX[2][0], boardY[2][0], true);
    board[2][1] = createObject("hp08.png", scene2, boardX[2][1], boardY[2][1], true);
    createObject("hp09.png", scene2, boardX[2][2], boardY[2][2], false);
    board[2][2] = createObject("black.png", scene2, boardX[2][2], boardY[2][2], true);

    timer1 = createTimer(60, 0f);
    ShowTimer(timer1);
    start = createObject("start.png", scene1, 650, 150, true);
    restart = createObject("restart.png", scene2, 650, 150, false);

    startGame(scene1);
}
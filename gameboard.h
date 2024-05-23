#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include "pacman.h"
#include <QKeyEvent>

#include "point.h"
#include <vector>

using namespace std;


class GameBoard : public QWidget {
    Q_OBJECT

public:
    explicit GameBoard(QWidget *parent = nullptr);
    bool canMove(int newX, int newY); //Para verificar colisiones


protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;


private:
    static const int mazeHeight = 22;
    static const int mazeWidth = 23;
    int maze[mazeHeight][mazeWidth];
    int score;

    void initializeMaze();
    void drawMaze(QPainter &painter);
    Pacman *pacman;

    void checkForPointCollision();
    vector<Point> points; // Vector de puntos
};

#endif // GAMEBOARD_H

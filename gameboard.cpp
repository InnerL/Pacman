#include "gameboard.h"
#include <QPainter>
#include "point.h"


const int TILE_SIZE = 20;

GameBoard::GameBoard(QWidget *parent) : QWidget(parent), score(0), pacman(new Pacman(this, this))  {
    setFixedSize(mazeWidth * TILE_SIZE, mazeHeight * TILE_SIZE);
    setStyleSheet("background-color: black;");
    initializeMaze();
    setFocusPolicy(Qt::StrongFocus);
}

void GameBoard::initializeMaze() {
    int tempMaze[mazeHeight][mazeWidth] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1},
        {1, 3, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 3, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1},
        {1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1},
        {1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 4, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1},
        {2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2},
        {1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1, 2, 1, 2, 2, 2, 2, 0, 2, 2, 2, 2, 1, 2, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1},
        {1, 3, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 3, 1},
        {1, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1},
        {1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1},
        {1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

    for (int y = 0; y < mazeHeight; ++y) {
        for (int x = 0; x < mazeWidth; ++x) {
            maze[y][x] = tempMaze[y][x];
            if (maze[y][x] == 2) {
                points.push_back(Point(x * TILE_SIZE, y * TILE_SIZE, 2)); // Puntos pequeños
            } else if (maze[y][x] == 3) {
                points.push_back(Point(x * TILE_SIZE, y * TILE_SIZE, 3)); // Puntos grandes
            }
        }
    }
}

void GameBoard::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    drawMaze(painter);
    for (Point &point : points) {
        point.draw(painter);
    }
    pacman->draw(painter);

    // Dibuja el puntaje
    painter.setPen(Qt::white);
    painter.drawText(10, 10, QString("Score: %1").arg(score));
}

void GameBoard::drawMaze(QPainter &painter) {
    for (int y = 0; y < mazeHeight; ++y) {
        for (int x = 0; x < mazeWidth; ++x) {
            if (maze[y][x] == 1) {
                painter.setBrush(Qt::blue);
                painter.fillRect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, Qt::blue);
            } else if (maze[y][x] == 0) {
                painter.setBrush(Qt::black);
                painter.fillRect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, Qt::black);
            }else if (maze[y][x] == 2) { //borrar
                painter.setBrush(Qt::black);
                painter.fillRect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, Qt::black);

            }else if (maze[y][x] == 3) { //borrar
                painter.setBrush(Qt::black);
                painter.fillRect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, Qt::black);

            }else if (maze[y][x] == 4) {
                painter.setBrush(Qt::black);
                painter.fillRect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, Qt::black);
                painter.setPen(QPen(Qt::white, 5));
                painter.drawLine((x +0.2) * TILE_SIZE, (y+0.5) * TILE_SIZE, (x + 1) * TILE_SIZE, (y+0.5) * TILE_SIZE); // Línea horizontal

            }
        }
    }
}


void GameBoard::keyPressEvent(QKeyEvent *event) {
    int dx = 0, dy = 0;
    switch (event->key()) {
    case Qt::Key_A:
        dx = -20;
        pacman->setDirection(2); // Dirección izquierda
        //pacman->move(-10, 0);
        //pacman->setDirection(2);
        break;
    case Qt::Key_D:
        dx = 20;
        //pacman->move(10, 0);
        pacman->setDirection(0); // Dirección derecha
        break;
    case Qt::Key_W:
        dy = -20;
        //pacman->move(0, -10);
        pacman->setDirection(3); // Dirección arriba
        break;
    case Qt::Key_S:
        dy = 20;
        //pacman->move(0, 10);
        pacman->setDirection(1); // Dirección abajo
        break;
    default:
        QWidget::keyPressEvent(event);
        return;
    }

    int newX = pacman->position().x() + dx;
    int newY = pacman->position().y() + dy;
    if (canMove(newX, newY)) {
        pacman->move(dx, dy);
        checkForPointCollision();
        update();
    }
    update();

}

bool GameBoard::canMove(int newX, int newY) {
    int gridX = newX / 20;
    int gridY = newY / 20;

    // Verificar que la nueva posicion este dentro de los límites del laberinto
    if (gridX < 0 || gridX >= mazeWidth || gridY < 0 || gridY >= mazeHeight) {
        return false;
    }
    // Verificar que la nueva posicion no sea un bloque azul
    return maze[gridY][gridX] == 2 || maze[gridY][gridX] == 3 || maze[gridY][gridX] == 0;
}


void GameBoard::checkForPointCollision() {
    QRect pacmanRect(pacman->position(), pacman->size());

    for (auto it = points.begin(); it != points.end();){
        QRect pointRect(it->position(), QSize(TILE_SIZE, TILE_SIZE));
        if (pacmanRect.intersects(pointRect)) {
            if (it->type() == 2) {
                score += 100; // Puntos pequeños
            } else if (it->type() == 3) {
                score += 500; // Puntos grandes
            }
            it = points.erase(it); // Eliminar punto
            update();
        } else {
            ++it;
        }
    }
}

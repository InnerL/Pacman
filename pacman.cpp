#include "pacman.h"
#include <QPainter>

Pacman::Pacman(QWidget *gameBoard, QObject *parent)
    : QObject(parent),  m_position(223, 243), direction(0), spriteIndex(0),  ascending(true),gameBoard(gameBoard) {
    loadSprites();
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Pacman::updateSprite);
    timer->start(150); // Actualiza el sprite cada 100 ms
}

void Pacman::move(int dx, int dy) {
    m_position.rx() += dx;
    m_position.ry() += dy;
}

void Pacman::draw(QPainter &painter) {
    int angle = 0;
    switch (direction) {
    case 0: angle = 0; break;    // Derecha
    case 1: angle = 90; break;  // Abajo
    case 2: angle = 180; break;  // Izquierda
    case 3: angle = 270; break;   // Arriba
    }
    QPixmap rotated = rotatedPixmap(sprites[spriteIndex], angle);
    painter.drawPixmap(m_position, rotated);}

void Pacman::setDirection(int dir) {
    direction = dir;
}

//Cambie el sprite
void Pacman::updateSprite() {
    if (ascending) {
        spriteIndex++;
        if (spriteIndex >= sprites.size() - 1) {
            ascending = false;
        }
    } else {
        spriteIndex--;
        if (spriteIndex <= 0) {
            ascending = true;
        }
    }
    gameBoard->update(); // Llama a update() en GameBoard
}

void Pacman::loadSprites() {
    QPixmap spriteSheet(":/pacman.png");
    //int frameWidth = spriteSheet.width() / 3; // 3 sprites en la fila
    //int frameHeight = spriteSheet.height() / 1; // 1 fila en la hoja
    int frameWidth = 15;  // Anchura del frame
    int frameHeight = 15; // Altura del frame

    for (int i = 0; i < 3; ++i) {
        sprites.append(spriteSheet.copy(i * frameWidth, 0, frameWidth, frameHeight));
    }
}
QPixmap Pacman::rotatedPixmap(const QPixmap &pixmap, int angle) {
    QTransform transform;
    transform.rotate(angle);
    return pixmap.transformed(transform);
}

QPoint Pacman::position() const{
    return m_position;
}

QSize Pacman::size() const {
    return QSize(15, 15); // Retorna el tamaño de Pacman
}

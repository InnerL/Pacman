#ifndef PACMAN_H
#define PACMAN_H

#include <QObject>
#include <QPixmap>
#include <QPoint>
#include <QTimer>
#include <QWidget> // Colisiones


class Pacman : public QObject {
    Q_OBJECT

public:
    explicit Pacman(QWidget *gameBoard, QObject *parent = nullptr);
    void move(int dx, int dy);
    void draw(QPainter &painter);
    void setDirection(int direction);
    QPoint position() const; // Añadir método para obtener la posición
    QSize size() const; // Nueva función para obtener el tamaño de Pacman

private slots:
    void updateSprite();

private:
    QVector<QPixmap> sprites;
    QPoint m_position;
    int direction;
    QTimer *timer;
    int spriteIndex;
    bool ascending;
    QWidget *gameBoard; // Agrega una referencia al widget GameBoard

    void loadSprites();
    QPixmap rotatedPixmap(const QPixmap &pixmap, int angle);

};

#endif // PACMAN_H

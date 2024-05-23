#ifndef POINT_H
#define POINT_H

#include <QWidget>
#include <QPixmap>
#include <QPoint>

class Point {
public:
    Point(int x, int y, int type);
    void draw(QPainter &painter);
    QPoint position() const;
    int type() const;

private:
    QPoint m_position;
    QPixmap m_pixmap;
    int m_type; // 2 pequeñas, 3 grandes
};



#endif // POINT_H

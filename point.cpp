#include "point.h"
#include <QPainter>

Point::Point(int x, int y, int type) : m_position(x, y), m_type(type) {
    if (m_type == 2) {
        m_pixmap = QPixmap(":/puntos.png").copy(0, 0, 14, 14); // Puntos pequeños
    } else if (m_type == 3) {
        m_pixmap = QPixmap(":/puntos.png").copy(15, 0, 14, 14); // Puntos grandes
    }
}



void Point::draw(QPainter &painter) {
    QPoint centeredPosition = m_position;
    centeredPosition.setX(centeredPosition.x() + (20 - m_pixmap.width()) / 2); // Centra en X
    centeredPosition.setY(centeredPosition.y() + (20 - m_pixmap.height()) / 2); // Centra en Y
    painter.drawPixmap(centeredPosition, m_pixmap);
}

QPoint Point::position() const {
    return m_position;
}

int Point::type() const {
    return m_type;
}

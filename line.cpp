#include <QColor>

#include "line.h"

Line::Line()
{
}

Line::Line(const Pos &apos, const Pos &bpos, QColor qcol)
{
    col = qcol;
    a   = apos;
    b   = bpos;
}

bool Line::is_near(const Pos &p, float dist)
{
    return a.is_near(p, dist) ||
           b.is_near(p, dist);
}

void Line::draw(QPainter &painter, QSize size)
{
    painter.setPen(col);
    painter.drawLine(a.point(size), b.point(size));
}


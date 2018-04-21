#include "pos.h"
#include <cmath>

Pos::Pos()
{
    x = 0;
    y = 0;
}

Pos::Pos(double xPos, double yPos)
{
    x = xPos;
    y = yPos;
}

Pos::Pos(QPoint point, QSize size)
{
    x = (double)point.x() / (double)size.width();
    y = (double)point.y() / (double)size.height();
}

QPoint Pos::point(QSize size)
{
    return QPoint(x * size.width(), y * size.height());
}

bool Pos::is_near(Pos p, double dist)
{
    double dx, dy, r;
    dx = x - p.x;
    dy = y - p.y;
    r  = sqrt(dx*dx + dy*dy);

    return r < dist;
}


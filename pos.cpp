#include "pos.h"
#include "b64.h"
#include <cmath>
#include <stdint.h>
#include <cstring>
#include <iostream>

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

Pos Pos::operator+(const Pos &other)
{
    return Pos(x + other.x, y + other.y);
}

Pos Pos::operator-(const Pos &other)
{
    return Pos(x - other.x, y - other.y);
}

Pos Pos::operator*(const double &s)
{
    return Pos(x * s, y * s);
}

bool Pos::is_near(Pos p, double dist)
{
    double dx, dy, r;
    dx = x - p.x;
    dy = y - p.y;
    r  = sqrt(dx*dx + dy*dy);

    return r < dist;
}

void Pos::deserialize(vector<char> &data)
{
    uint16_t xint, yint;

    memcpy(&xint, &(*data.end()) - 2, 2);
    data.pop_back();
    data.pop_back();
    memcpy(&yint, &(*data.end()) - 2, 2);
    data.pop_back();
    data.pop_back();

    x = (float)xint / 0xffff;
    y = (float)yint / 0xffff;
}

void Pos::serialize(vector<char> &data)
{
    stringstream stream;
    uint16_t xint,  yint;
    char     xchr[2], ychr[2];
    
    if      (x >= 1) xint = 0xffff;
    else if (x <= 0) xint = 0;
    else             xint = 0xffff * x;

    if      (y >= 1) yint = 0xffff;
    else if (y <= 0) yint = 0;
    else             yint = 0xffff * y;

    memcpy(xchr, &xint, 2);
    memcpy(ychr, &yint, 2);

    data.insert(data.end(), ychr, ychr + 2);
    data.insert(data.end(), xchr, xchr + 2);
}

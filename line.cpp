#include <QColor>

#include <cmath>

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
    bool   perpendicular;
    double m, ylim1, ylim2, r;

    if (a.y == b.y)
    {
        perpendicular = !((p.x > a.x && p.x > b.x) ||
                          (p.x < a.x && p.x < b.x));
    }
    else
    {
        m = (b.x - a.x) / (a.y - b.y);

        ylim1 = m * p.x + b.y - m * b.x;
        ylim2 = m * p.x + a.y - m * a.x;

        perpendicular = !((p.y > ylim1 && p.y > ylim2) ||
                          (p.y < ylim1 && p.y < ylim2));
    }
    
    if (perpendicular)
    {
        r = fabs((b.y - a.y) * p.x - (b.x - a.x) * p.y + b.x * a.y - b.y * a.x) /
               sqrt(pow(b.y - a.y, 2) + pow(b.x - a.x, 2));
        return r < dist;
    }
    else
    {
        return a.is_near(p, dist) ||
               b.is_near(p, dist);
    }

}

void Line::draw(QPainter &painter, QSize size)
{
    QPen pen(col, 3);
    painter.setPen(pen);
    painter.drawLine(a.point(size), b.point(size));
}

bool Line::is_valid(void)
{
    return !((a.x <= 0 && b.x <= 0) ||
             (a.x >  1 && b.x > 1) ||
             (a.y <= 0 && b.y <= 0) ||
             (a.y >  1 && b.y > 1));
}

Pos *Line::top(void)
{
    if (a.y < b.y)
        return &a;
    else
        return &b;
}

Pos *Line::bottom(void)
{
    if (a.y < b.y)
        return &b;
    else
        return &a;
}

Pos *Line::left(void)
{
    if (a.x < b.x)
        return &a;
    else
        return &b;
}

Pos *Line::right(void)
{
    if (a.x < b.x)
        return &b;
    else
        return &a;
}

void Line::trim(void)
{
    Pos *t = top(),  *b = bottom();
    Pos *l = left(), *r = right();

    if (t->y < 0)
        *t = *b + (*t - *b) * ((b->y) / (b->y - t->y));

    if (b->y > 1)
        *b = *t + (*b - *t) * ((1 - t->y) / (b->y - t->y));

    if (r->x > 1)
        *r = *l + (*r - *l) * ((1 - l->x) / (r->x - l->x));

    if (l->x < 0)
        *l = *r + (*l - *r) * ((r->x) / (r->x - l->x));
}

void Line::deserialize(stringstream &stream)
{
    int rval, gval, bval;

    a.deserialize(stream);
    b.deserialize(stream);
    stream >> rval >> gval >> bval;

    col = QColor(rval, gval, bval);
}

string Line::serialize(void)
{
    int rval, gval, bval;    

    rval = col.red();
    gval = col.green();
    bval = col.blue();
    
    std::stringstream col;
    col << rval << ' ' << gval << ' ' << bval;
    return a.serialize() + " " + b.serialize() + " " + col.str();
}
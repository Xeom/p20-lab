#if !defined(LINE_H)
# define LINE_H
# include "pos.h"
# include <QColor>
# include <QPainter>

class Line
{
protected:
    Pos a;
    Pos b;
    QColor col;
public:
    Line();
    Line(const Pos &apos, const Pos &bpos, QColor c);
    bool is_near(const Pos &p, const float dist);
    void draw(QPainter &painter, QSize size);
};

#endif

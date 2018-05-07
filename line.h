#if !defined(LINE_H)
# define LINE_H
# include "pos.h"
# include <QColor>
# include <QPainter>
# include <sstream>

using namespace std;

class Line
{
protected:
    Pos a;
    Pos b;
    QColor col;
    int width;

public:
    Line();
    Line(const Pos &apos, const Pos &bpos, QColor c, int w);

    bool is_near(const Pos &p, const float dist);
    bool is_valid(void);

    Pos *top(void);
    Pos *bottom(void);
    Pos *left(void);
    Pos *right(void);

    void trim(void);
    void draw(QPainter &painter, QSize size);

    void serialize(vector<char> &data);
    void deserialize(vector<char> &data);
};

#endif

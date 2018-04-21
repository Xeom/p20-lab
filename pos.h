#if !defined(POS_H)
# define POS_H
# include <QPoint>
# include <QSize>

class Pos
{
public:
    double x, y;

    Pos();
    Pos(QPoint point, QSize size);
    Pos(double xpos, double ypos);

    QPoint point(QSize size);
    bool is_near(Pos p, double dist);
};

#endif

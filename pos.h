#if !defined(POS_H)
# define POS_H
# include <QPoint>
# include <QSize>
# include <sstream>
# include <vector>

using namespace std;

class Pos
{
public:
    double x, y;

    Pos();
    Pos(QPoint point, QSize size);
    Pos(double xpos, double ypos);

    Pos operator+(const Pos &other);
    Pos operator-(const Pos &other);
    Pos operator*(const double &s);

    QPoint point(QSize size);
    bool is_near(Pos p, double dist);

    void deserialize(vector<char> &data);
    void serialize(vector<char> &data);
};

#endif

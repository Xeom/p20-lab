#if !defined(WINDOW_H)
# define WINDOW_H
# include <QMouseEvent>
# include <QWidget>
# include <QLabel>
# include <QPainter>
# include <QPicture>

# include <map>

# include "line.h"

using namespace std;

class Window : public QWidget
{
    Q_OBJECT

protected:
    map<int, Line> lines;
    Pos            mouse_anchor;
    int            maxid;

    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void mouse_line(Pos fin);
    void mouse_del(Pos p);
    void clear(void);

public:
    Window(QWidget *parent = 0);

    void new_line(Line &line, int id);
    void del_line(int id);
    void draw_all(void);
    void draw_line(int id);
};

#endif

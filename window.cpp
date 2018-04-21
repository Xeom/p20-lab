
#include "window.h"
#include "pos.h"

#include <iostream>

using namespace std;

Window::Window(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Whiteboard");

    maxid = 0;
}

void Window::paintEvent(QPaintEvent * event)
{
    draw_all();
}

void Window::draw_all(void)
{
    QPainter painter(this);
    QPen     pen;
    QSize    sz = size();

    map<int, Line>::iterator it;

    for (it = lines.begin(); it != lines.end(); ++it)
        it->second.draw(painter, sz);
}

void Window::new_line(Line &line, int id)
{
    lines.insert(pair<int, Line>(id, line));
    update();
}

void Window::del_line(int id)
{
    lines.erase(id);
    update();
}

void Window::mouseReleaseEvent(QMouseEvent *event)
{
    Pos p(event->pos(), size());

    switch (event->button())
    {
    case Qt::LeftButton:
        mouse_line(p);
        break;
    default:
        break;
    }
}

void Window::mousePressEvent(QMouseEvent *event)
{
    Pos p(event->pos(), size());

    switch (event->button())
    {
    case Qt::LeftButton:
        mouse_anchor = p;
        break;
    case Qt::RightButton:
        mouse_del(p);
        break;
    default:
        break;
    }
}

void Window::mouseMoveEvent(QMouseEvent *event)
{
    double min_len = 0.01;
    Pos p(event->pos(), size());

    switch (event->buttons())
    {
    case Qt::LeftButton:
        if (!mouse_anchor.is_near(p, min_len))
        {
            mouse_line(p);
            mouse_anchor = p;
        }
        break;
    case Qt::RightButton:
        mouse_del(p);
        break;
    default:
        break;
    }
}

void Window::mouse_line(Pos p)
{
    Line line(p, mouse_anchor, QColor(255, 0, 0));

    new_line(line, maxid++);

    update();
}

void Window::mouse_del(Pos p)
{
    double min_dist = 0.02;
    map<int, Line>::iterator it;

    for (it = lines.begin(); it != lines.end(); ++it)
    {
        Line line = it->second;

        if (line.is_near(p, min_dist))
            del_line(it->first);
    }
}

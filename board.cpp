#include "colourpicker.h"
#include "window.h"
#include "pos.h"
#include <pthread.h>
#include <iostream>

using namespace std;

Board::Board(QWidget *parent) : QWidget(parent)
{
    maxid = 0;

    pthread_mutex_init(&lock, NULL);
}

void Board::paintEvent(QPaintEvent * event)
{
    draw_all();
}

void Board::draw_all(void)
{
    QPainter painter(this);
    QPen     pen;
    QSize    sz = size();

    
    painter.fillRect(rect(), Qt::white);

    pthread_mutex_lock(&lock);

    map<int, Line>::iterator it;
    for (it = lines.begin(); it != lines.end(); ++it)
        it->second.draw(painter, sz);

    pthread_mutex_unlock(&lock);
}

void Board::new_line(Line &line, int id)
{
    if (!line.is_valid()) return;
    
    if (id != maxid - 1 && abs(id - maxid) < 1000)
        maxid += 1000000;

    line.trim();

    lines.insert(pair<int, Line>(id, line));
    
    update();
}

void Board::del_line(int id)
{
    lines.erase(id);
    update();
}

void Board::mouseReleaseEvent(QMouseEvent *event)
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

void Board::mousePressEvent(QMouseEvent *event)
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

void Board::mouseMoveEvent(QMouseEvent *event)
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

void Board::mouse_line(Pos p)
{
    int id;
    Line line(p, mouse_anchor, selected_colour);

    pthread_mutex_lock(&lock);

    id = maxid++;
    new_line(line, id);

    cout << "n " << id << " " << line.serialize() << endl;

    pthread_mutex_unlock(&lock);
    
    update();
}

void Board::mouse_del(Pos p)
{
    double min_dist = 0.02;
    map<int, Line>::iterator it;

    pthread_mutex_lock(&lock);
    
    for (it = lines.begin(); it != lines.end(); ++it)
    {
        Line line = it->second;
        int  id   = it->first;
        
        if (line.is_near(p, min_dist))
        {
            cout << "d " << id << endl;
            del_line(id);
        }
    }

    pthread_mutex_unlock(&lock);

    update();
}

void Board::sync(void)
{
    map<int, Line>::iterator it;

    cout << "c" << endl;

    pthread_mutex_lock(&lock);
    
    for (it = lines.begin(); it != lines.end(); ++it)
    {
        Line line = it->second;
        int  id   = it->first;

        cout << "n " << id << " " << line.serialize() << endl;
    }

    pthread_mutex_unlock(&lock);
}
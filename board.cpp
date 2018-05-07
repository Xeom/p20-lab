#include <pthread.h>
#include <iostream>

#include "output.h"
#include "colourpicker.h"
#include "window.h"
#include "pos.h"

using namespace std;
extern Output *outputter;

ostream *cmdpipe = &cout;

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

    map<int, Line>::iterator it;
}

void Board::del_line(int id)
{
    map<int, Line>::iterator it;
    it = lines.find(id);

    if (it != lines.end())
        lines.erase(id);
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
    Line line(p, mouse_anchor, selected_colour, selected_size);

    pthread_mutex_lock(&lock);

    id = maxid++;
    new_line(line, id);

    outputter->send('n', id, &line);

    pthread_mutex_unlock(&lock);
    
    update();
}

void Board::mouse_del(Pos p)
{
    double min_dist = 0.02;
    map<int, Line>::iterator it;
    vector<int> todel;

    pthread_mutex_lock(&lock);
    
    for (it = lines.begin(); it != lines.end(); ++it)
    {
        Line line = it->second;
        int  id   = it->first;
        
        if (line.is_near(p, min_dist))
            todel.push_back(id);
    }

    vector<int>::iterator it2;

    for (it2 = todel.begin(); it2 != todel.end(); ++it2)
    {
        outputter->send('d', *it2, NULL);
        del_line(*it2);
    }

    pthread_mutex_unlock(&lock);

    update();
}

void Board::sync(void)
{
    map<int, Line>::iterator it;

    *cmdpipe << "c" << endl;

    pthread_mutex_lock(&lock);
    
    for (it = lines.begin(); it != lines.end(); ++it)
    {
        Line line = it->second;
        int  id   = it->first;

        outputter->send('n', id, &line);
    }

    pthread_mutex_unlock(&lock);
}

void Board::clear(void)
{
    lines = map<int, Line>();
}

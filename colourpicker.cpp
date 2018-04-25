#include <QPainter>

#include "colourpicker.h"

#include <iostream>
using namespace std;

static QColor colours[] =
{
    Qt::black,
    Qt::red,
    Qt::yellow,
    Qt::green,
    Qt::blue,
    Qt::magenta
};

QColor selected_colour = Qt::black;

ColourPicker::ColourPicker(QWidget *parent) : QWidget(parent)
{
    size_t num, ind;

    num = sizeof(colours)/sizeof(colours[0]);

    hbox = new QHBoxLayout();

    hbox->setSpacing(2);
    hbox->setContentsMargins(0,0,0,0);

    for (ind = 0; ind < num; ++ind)
        add_colour(colours[ind]);

    setLayout(hbox);
}

void ColourPicker::add_colour(QColor col)
{
    ColourPickerCell *cell = new ColourPickerCell(col, this);
    hbox->addWidget(cell);
}

ColourPickerCell::ColourPickerCell(QColor col, QWidget *parent) : QWidget(parent)
{
    colour = col;
}

void ColourPickerCell::mouseReleaseEvent(QMouseEvent *event)
{
    selected_colour = colour;

    parentWidget()->update();
}

void ColourPickerCell::paintEvent(QPaintEvent *event)
{
    QPainterPath path;
    QPainter painter(this);
    QPen     pen;

    painter.setRenderHint(QPainter::Antialiasing);
    path.addRoundedRect(rect(), 5, 5);   

    if (colour == Qt::black)
        pen = QPen(Qt::gray, 5);
    else
        pen = QPen(colour.darker(), 5);
    
    painter.setPen(pen);

    painter.fillPath(path, colour);

    if (selected_colour == colour)
        painter.drawPath(path);
}

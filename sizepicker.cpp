#include <QPainter>

#include "sizepicker.h"

int selected_size = 3;

static int sizes[] =
{
    2,
    3,
    5,
    8,
    11,
    14
};

SizePicker::SizePicker(QWidget *parent) : QWidget(parent)
{
    size_t num, ind;

    num = sizeof(sizes)/sizeof(sizes[0]);

    hbox = new QHBoxLayout();

    hbox->setSpacing(2);
    hbox->setContentsMargins(0, 0, 0, 0);

    for (ind = 0; ind < num; ++ind)
        add_size(sizes[ind]);

    setLayout(hbox);
}

void SizePicker::add_size(int size)
{
    SizePickerCell *cell = new SizePickerCell(size, this);
    hbox->addWidget(cell);
}

SizePickerCell::SizePickerCell(int sz, QWidget *parent) : QWidget(parent)
{
    size = sz;
}

void SizePickerCell::mouseReleaseEvent(QMouseEvent *event)
{
    selected_size = size;

    parentWidget()->update();
}

void SizePickerCell::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    int x = (QWidget::size().width() - size) / 2;
    int y = (QWidget::size().height() - size)/ 2;



    if (size == selected_size)
    {
        painter.setBrush(Qt::red);
        painter.setPen(Qt::red);
    }
    else
    {
        painter.setBrush(Qt::black);
        painter.setPen(Qt::black);
    }
    painter.drawEllipse(x, y, size, size);
}

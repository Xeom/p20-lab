#include "window.h"
#include "output.h"

extern Output *outputter;

Window::Window(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Whiteboard");

  //  setFixedSize(300, 300);
    setGeometry(0, 0, 300, 300);
    adjustSize();
    board      = new Board(this);
    cpicker    = new ColourPicker(this);
    spicker    = new SizePicker(this);
    clrbutton  = new QPushButton("Clear", this);
    syncbutton = new QPushButton("Sync", this);

    grid  = new QGridLayout();

    grid->addWidget(board,    0, 0, 1, 5);
    grid->addWidget(cpicker,  1, 0, 2, 2);
    grid->addWidget(spicker,  1, 2, 2, 2);
    grid->addWidget(clrbutton,1, 4, 1, 1);
    grid->addWidget(syncbutton, 2, 4, 1, 1);

    grid->setRowStretch(0, 16);
    grid->setRowStretch(1, 1);
    grid->setRowStretch(2, 1);

    grid->setSpacing(5);
    grid->setContentsMargins(5,5,5,5);

    connect(clrbutton,  &QPushButton::clicked, this, &Window::handle_clr);
    connect(syncbutton, &QPushButton::clicked, this, &Window::handle_sync);

    setLayout(grid);
}

void Window::handle_clr(void)
{
    outputter->send('c', 0, NULL);
    get_board()->clear();
    update();
}

void Window::handle_sync(void)
{
    outputter->send('s', 0, NULL);
}

Board *Window::get_board(void)
{
    return board;
}

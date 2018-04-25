#include "window.h"

Window::Window(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Whiteboard");
    board  = new Board(this);
    picker = new ColourPicker(this);

    grid  = new QGridLayout();

    grid->addWidget(board, 0, 0);
    grid->addWidget(picker, 1, 0);

    grid->setRowStretch(0, 8);
    grid->setRowStretch(1, 1);

    grid->setSpacing(5);
    grid->setContentsMargins(5,5,5,5);

    setLayout(grid);
}

Board *Window::get_board(void)
{
    return board;
}
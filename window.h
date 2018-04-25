#if !defined(WINDOW_H)
# define WINDOW_H
# include <QWidget>
# include <QGridLayout>
# include "board.h"
# include "colourpicker.h"

using namespace std;

class Window : public QWidget
{
    Q_OBJECT

protected:
    Board *board;
    ColourPicker *picker;
    QGridLayout *grid;

public:
    Board *get_board(void);
    Window(QWidget *parent = 0);
};

#endif

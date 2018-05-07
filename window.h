#if !defined(WINDOW_H)
# define WINDOW_H
# include <QWidget>
# include <QGridLayout>
# include "board.h"
# include "colourpicker.h"
# include "sizepicker.h"
# include <QPushButton>

using namespace std;

class Window : public QWidget
{
    Q_OBJECT

protected:
    Board *board;
    ColourPicker *cpicker;
    SizePicker   *spicker;
    QGridLayout *grid;
    QPushButton  *clrbutton;
    QPushButton  *syncbutton;

private slots:
    void handle_clr(void);
    void handle_sync(void);

public:
    Board *get_board(void);
    Window(QWidget *parent = 0);
    
};

#endif

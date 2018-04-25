#if !defined(COLOURS_H)
# define COLOURS_H
# include <QWidget>
# include <QHBoxLayout>

extern QColor selected_colour;

class ColourPicker : public QWidget
{
    Q_OBJECT

protected:
    void add_colour(QColor col);

    QHBoxLayout *hbox;
public:
    ColourPicker(QWidget *parent = 0);
};

class ColourPickerCell : public QWidget
{
    Q_OBJECT

protected:
    QColor colour;

    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

public:
    ColourPickerCell(QColor col, QWidget *parent = 0);
};

#endif

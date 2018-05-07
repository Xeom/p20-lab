#if !defined(SIZEPICKER_H)
#define SIZEPICKER_H
# include <QWidget>
# include <QHBoxLayout>

extern int selected_size;

class SizePicker : public QWidget
{
    Q_OBJECT

protected:
    void add_size(int size);

    QHBoxLayout *hbox;
public:
    SizePicker(QWidget *parent = 0);
};

class SizePickerCell : public QWidget
{
    Q_OBJECT

protected:
    int size;

    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

public:
    SizePickerCell(int size, QWidget *parent = 0);
};

#endif

#ifndef GRIDBLOCKS_H
#define GRIDBLOCKS_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>

class gridBlocks : public QWidget
{
    Q_OBJECT
public:
    explicit gridBlocks(QWidget *parent = nullptr);
    void setGridPosition(int row, int col);
    void setProperly();
    int get_x();
    int get_y();

//    void operator+();

signals:
    void gridClicked(int row, int col);

public slots:
    void btnClicked();

protected:
//    void mousePressEvent(QMouseEvent *event);
    void sendClick();

private:
    QLabel* mapGrid;
    QPushButton* btn;
    int row;
    int col;

};

#endif // GRIDBLOCKS_H

#ifndef GRIDBLOCKS_H
#define GRIDBLOCKS_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class gridBlocks : public QWidget
{
    Q_OBJECT
public:
    explicit gridBlocks(QWidget *parent = nullptr);
    void setGridPosition(int row, int col);

signals:
    void gridClicked(int row, int col);

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    QLabel* mapGrid;

    int row;
    int col;

};

#endif // GRIDBLOCKS_H

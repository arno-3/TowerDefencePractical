#include "gridblocks.h"
#include <QLabel>
#include <QDebug>

gridBlocks::gridBlocks(QWidget *parent) : QWidget(parent), row(0), col(0)
{
    setFixedSize(100,100);
    mapGrid = new QLabel(this);
    mapGrid->setGeometry(0,0,width(),height());
    mapGrid->setStyleSheet("rgba(0, 0, 0, 50);");

    setMouseTracking(true);
    setAttribute(Qt::WA_TranslucentBackground);
}

void gridBlocks::setGridPosition(int r, int c)
{
    row = r;
    col = c;
}

void gridBlocks::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit gridClicked(row, col);

    }
}

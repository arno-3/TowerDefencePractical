#include "gridblocks.h"
#include <QLabel>
#include <QDebug>

gridBlocks::gridBlocks(QWidget *parent) : QWidget(parent), row(0), col(0)
{
    setFixedSize(100,100);
    mapGrid = new QLabel(this);
    mapGrid->setGeometry(0,0,width(),height());
    //mapGrid->setStyleSheet("rgba(0, 0, 0, 58);");

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
        QPointF p = event->localPos();

        bool hr =p.x() >(this->x()+25) || p.x()<(x()+width()-25);
        bool vr = p.y()>(this->y()+25) || p.y()<(y()+height()-25);
        qDebug() << "CLICKED: :" << p<<endl;
        if(hr && vr)
            emit gridClicked(row, col);

    }
}

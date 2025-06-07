#include "gridblocks.h"
#include <QLabel>

gridBlocks::gridBlocks(QWidget *parent) : QWidget(parent)
{
    setFixedSize(100,100);
    mapGrid = new QLabel(this);
    mapGrid->setGeometry(0,0,width(),height());
    mapGrid->setStyleSheet(" rgba(0, 0, 0, 0);");

}

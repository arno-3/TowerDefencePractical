#ifndef GRIDBLOCKS_H
#define GRIDBLOCKS_H

#include <QWidget>
#include <QLabel>

class gridBlocks : public QWidget
{
    Q_OBJECT
public:
    explicit gridBlocks(QWidget *parent = nullptr);

signals:

private:
    QLabel* mapGrid;

};

#endif // GRIDBLOCKS_H

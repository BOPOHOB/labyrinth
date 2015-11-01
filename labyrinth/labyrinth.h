#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <QSize>
#include "graph.h"

class QImage;
class QPoint;

class Labyrinth
{
    Graph __data;
    QSize __size;
    QSize __roomSize;

public:
    Labyrinth();
    Labyrinth(QSize size);
    ~Labyrinth();

    int doors(const QPoint& room) const;

    void openDoor(const QPoint& out, const QPoint& in);
    void closeDoor(const QPoint& out, const QPoint& in);

    const QSize& size() const { return __size; }
    const QSize& roomSize() const { return __roomSize; }

    static Labyrinth fromImage(const QImage&, QSize roomSize = QSize(10,10));

    int toId(const QPoint&) const;
};

#endif // LABYRINTH_H

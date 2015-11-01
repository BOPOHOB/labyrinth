#include "labyrinth.h"

#include <QImage>
#include <QSize>
#include <QDebug>

#include "graph.h"
#include "pixmapwidget.h"

Labyrinth::Labyrinth()
{

}

Labyrinth::Labyrinth(QSize size)
    : __data(size.width() * size.height() + 1)
    , __size(size)
{

}

Labyrinth::~Labyrinth()
{

}

int Labyrinth::toId(const QPoint& p) const {
    const int id(p.x() + p.y() * __size.width());
    return id < 0 || id >= __data.size() ? __data.size() - 1 : id;
}

int Labyrinth::doors(const QPoint& room) const {
    int result = 0;
    const int id(toId(room));
    if (room.x() + 1 != __size.width()) {
        if (__data.isConnected(id, id + 1)) {
            result |= Qt::RightEdge;
        }
    } else {
        if (__data.isConnected(id, __data.size() - 1)) {
            result |= Qt::RightEdge;
        }
    }
    if (room.x() > 0) {
        if (__data.isConnected(id, id - 1)) {
            result |= Qt::LeftEdge;
        }
    } else {
        if (__data.isConnected(id, __data.size() - 1)) {
            result |= Qt::LeftEdge;
        }
    }
    if (room.y() > 0) {
        if (__data.isConnected(id, id - __size.width())) {
            result |= Qt::TopEdge;
        }
    } else {
        if (__data.isConnected(id, __data.size() - 1)) {
            result |= Qt::TopEdge;
        }
    }
    if (room.y() + 1 != __size.height()) {
        if (__data.isConnected(id, id + __size.width())) {
            result |= Qt::BottomEdge;
        }
    } else {
        if (__data.isConnected(id, __data.size() - 1)) {
            result |= Qt::BottomEdge;
        }
    }
    return result;
}

void Labyrinth::openDoor(const QPoint& out, const QPoint& in) {
    auto isOutside([this](const QPoint& p)->bool{ return p.x() >= __size.width() || p.x() < 0 || p.y() >= __size.height() || p.y() < 0; });
    if (isOutside(in)) {
        __data.addEdge(toId(out), __data.size() - 1);
    } else if(isOutside(out)) {
        __data.addEdge(__data.size() - 1, toId(in));
    }else {
        __data.addEdge(toId(out), toId(in));
    }
}

void Labyrinth::closeDoor(const QPoint& out, const QPoint& in) {
    __data.rendEdge(toId(out), toId(in));
}

Labyrinth Labyrinth::fromImage(const QImage& img, QSize roomSize) {
    if (img.width() % roomSize.width() != 1 || img.height() % roomSize.height() != 1) {
        return Labyrinth();
    }
    Labyrinth r(QSize(img.width() / roomSize.width(), img.height() / roomSize.height()));
    r.__roomSize = roomSize;
    for (int i(-1); i != r.__size.height(); ++i) {
        for (int j(-1); j != r.__size.width(); ++j) {
            const QImage room(img.copy(1 + j * roomSize.width(), 1 + i * roomSize.height(), roomSize.width(), roomSize.height()));
            if (room.pixel(roomSize.width() - 1, 1) == qRgb(0xFF, 0xFF, 0xFF)) {
                r.openDoor(QPoint(j,i), QPoint(j + 1, i));
            }
            if (room.pixel(1, roomSize.height() - 1) == qRgb(0xFF, 0xFF, 0xFF)) {
                r.openDoor(QPoint(j,i), QPoint(j, i + 1));
            }
        }
    }
    return r;
}

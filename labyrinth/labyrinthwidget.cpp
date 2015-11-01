#include "labyrinthwidget.h"

#include <QPainter>
#include <QDebug>

#include "labyrinth.h"

LabyrinthWidget::LabyrinthWidget(QWidget *parent) : QWidget(parent)
{

}

LabyrinthWidget::~LabyrinthWidget()
{

}

void LabyrinthWidget::setLabyrinth(const Labyrinth& l) {
    __val = l;
    this->setFixedSize(l.roomSize().width() * l.size().width() + 1, l.roomSize().height() * l.size().height() + 1);
}

void LabyrinthWidget::paintEvent(QPaintEvent *) {
    if (__val.size() == QSize()) {
        return;
    }
    QPainter p(this);
    for (int i(0); i != __val.size().width(); ++i) {
        for (int j(0); j != __val.size().height(); ++j) {
            const int sheety(~__val.doors(QPoint(i, j)));
            if (sheety & Qt::RightEdge) {
                p.drawLine((i + 1) * __val.roomSize().width(), (j    ) * __val.roomSize().height(),
                           (i + 1) * __val.roomSize().width(), (j + 1) * __val.roomSize().height());
            }
            if (sheety & Qt::BottomEdge) {
                p.drawLine((i    ) * __val.roomSize().width(), (j + 1) * __val.roomSize().height(),
                           (i + 1) * __val.roomSize().width(), (j + 1) * __val.roomSize().height());
            }
            if (!i && sheety & Qt::LeftEdge) {
                p.drawLine((i    ) * __val.roomSize().width(), (j    ) * __val.roomSize().height(),
                           (i    ) * __val.roomSize().width(), (j + 1) * __val.roomSize().height());
            }
            if (!j && sheety & Qt::TopEdge) {
                p.drawLine((i    ) * __val.roomSize().width(), (j    ) * __val.roomSize().height(),
                           (i + 1) * __val.roomSize().width(), (j    ) * __val.roomSize().height());
            }
        }
    }
}

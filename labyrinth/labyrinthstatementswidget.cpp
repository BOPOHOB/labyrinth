#include "labyrinthstatementswidget.h"
#include "labyrinth.h"

LabyrinthStatementsWidget::LabyrinthStatementsWidget(QWidget *p)
    : QTextBrowser(p)
{

}

LabyrinthStatementsWidget::~LabyrinthStatementsWidget()
{

}


void LabyrinthStatementsWidget::setLabyrinth(const Labyrinth& l) {
    QString text;
    auto pushDoor = [&text, &l](const QPoint& from, const QPoint& to) {
        text.append(QString("passage(%1,%2).\n").arg(QString::number(l.toId(from)), QString::number(l.toId(to))));
    };

    for (int j(0); j != l.size().height(); ++j) {
        for (int i(0); i != l.size().width(); ++i) {
            int doors(l.doors(QPoint(i, j)));
            if (doors & Qt::RightEdge) {
                pushDoor(QPoint(i, j), QPoint(i + 1, j));
            }
            if (doors & Qt::BottomEdge) {
                pushDoor(QPoint(i, j), QPoint(i, j + 1));
            }
            if (!i && doors & Qt::LeftEdge) {
                pushDoor(QPoint(i, j), QPoint(i - 1, j));
            }
            if (!j && doors & Qt::TopEdge) {
                pushDoor(QPoint(i, j), QPoint(i, j - 1));
            }
        }
    }
    this->setText(text);
}

#ifndef LABYRINTHWIDGET_H
#define LABYRINTHWIDGET_H

#include <QWidget>
#include "labyrinth.h"

class LabyrinthWidget : public QWidget
{
    Q_OBJECT

    void paintEvent(QPaintEvent *);
public:
    explicit LabyrinthWidget(QWidget *parent = 0);
    ~LabyrinthWidget();

signals:

public slots:
    void setLabyrinth(const Labyrinth&);

private:
    Labyrinth __val;
};

#endif // LABYRINTHWIDGET_H

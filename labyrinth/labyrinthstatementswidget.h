#ifndef LABYRINTHSTATEMENTSWIDGET_H
#define LABYRINTHSTATEMENTSWIDGET_H

#include <QTextBrowser>

class Labyrinth;

class LabyrinthStatementsWidget : public QTextBrowser
{
    Q_OBJECT
public:
    explicit LabyrinthStatementsWidget(QWidget* p = 0);
    ~LabyrinthStatementsWidget();

public slots:
    void setLabyrinth(const Labyrinth&);
};

#endif // LABYRINTHSTATEMENTSWIDGET_H

#ifndef LABYRINTHPARSER_H
#define LABYRINTHPARSER_H

#include <QWidget>

class Labyrinth;

class LabyrinthParser : public QWidget
{
    Q_OBJECT

    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent*);

    Qt::WindowFrameSection section(const QPoint& p);
public:
    explicit LabyrinthParser(QWidget *parent = 0);
    ~LabyrinthParser();

    void setStep(const QSize& s) { __step = s; }
    const QSize& step() const { return __step; }
    QRect roundedRect() const;

signals:
    void newLabyrinthAppeared(const Labyrinth&);

public slots:
    void loadLabyrint(QString fName);

private:
    QImage __labyrint;
    QRect __rect;
    QSize __step;
    Qt::WindowFrameSection __carring;
    QPoint __mouse;
    QSize __sectorSize;
};

#endif // LABYRINTHPARSER_H

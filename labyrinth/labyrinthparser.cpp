#include "labyrinthparser.h"

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

#include "labyrinth.h"

LabyrinthParser::LabyrinthParser(QWidget *parent) : QWidget(parent), __step(1,1)
{
    this->setMouseTracking(true);
}

LabyrinthParser::~LabyrinthParser()
{

}

QRect LabyrinthParser::roundedRect() const {
    return QRect(__rect.topLeft(),
                 QSize((__rect.width() / __step.width()) * __step.width() + 1,
                       (__rect.height() / __step.height()) * __step.height() + 1));
}

Qt::WindowFrameSection LabyrinthParser::section(const QPoint& p) {
    static const float SENSIBILITY_RADIUS(7.0f);
    typedef QMap<Qt::WindowFrameSection,QPoint> Corners;
    Corners corners;
    corners.insert(Qt::TopLeftSection, __rect.topLeft());
    corners.insert(Qt::TopRightSection, __rect.topRight());
    corners.insert(Qt::BottomLeftSection, __rect.bottomLeft());
    corners.insert(Qt::BottomRightSection, __rect.bottomRight());
    const Corners::const_iterator nearest(std::min_element(corners.begin(), corners.end(),
        [p](const QPoint& a, const QPoint& b)->bool{ return QVector2D(a - p).length() < QVector2D(b - p).length(); }));
    if (QVector2D(*nearest - p).length() <= SENSIBILITY_RADIUS) {
        return nearest.key();
    }
    if (abs(p.x() - __rect.left()) <= SENSIBILITY_RADIUS && p.y() < __rect.bottom() && p.y() > __rect.top()) {
        return Qt::LeftSection;
    }
    if (abs(p.y() - __rect.top()) <= SENSIBILITY_RADIUS && p.x() > __rect.left() && p.x() < __rect.right()) {
        return Qt::TopSection;
    }
    if (abs(p.x() - __rect.right()) <= SENSIBILITY_RADIUS && p.y() < __rect.bottom() && p.y() > __rect.top()) {
        return Qt::RightSection;
    }
    if (abs(p.y() - __rect.bottom()) <= SENSIBILITY_RADIUS && p.x() > __rect.left() && p.x() < __rect.right()) {
        return Qt::BottomSection;
    }
    if (__rect.contains(p)) {
        return Qt::TitleBarArea;
    }
    return Qt::NoSection;
}

void LabyrinthParser::paintEvent(QPaintEvent *) {
    QPainter p(this);
    const QRect rounded(roundedRect());
    p.drawImage(0, 0, __labyrint);
    const QPainterPath veil(([&rounded, this]()->QPainterPath{
                           QPainterPath viel;
                           viel.addRect(QRectF(QPointF(0.0f, 0.0f), size()));
                           QPainterPath rect;
                           rect.addRect(rounded);
                           viel -= rect;
                           return viel;
                      })());
    static const QBrush vielTexture(QColor(0x40,0x80,0x99, 0x70));
    p.fillPath(veil, vielTexture);
    QPen linesPen(QColor(0x00, 0x00, 0x60, 0x20));
    p.setPen(linesPen);
    if (__sectorSize.height() > 0) {
        for (int i(0); i < rounded.height(); i += __sectorSize.height()) {
            p.drawLine(rounded.left(), i + rounded.top(), rounded.right(), i + rounded.top());
        }
    }
    if (__sectorSize.width() > 0) {
        for (int i(0); i < rounded.width(); i += __sectorSize.width()) {
            p.drawLine(i + rounded.left(), rounded.bottom(), i + rounded.left(), rounded.top());
        }
    }
}

void LabyrinthParser::mouseMoveEvent(QMouseEvent * e) {
    __carring = section(__mouse);
    switch (__carring) {
    case Qt::BottomSection: case Qt::TopSection:
        this->setCursor(QCursor(Qt::SizeVerCursor));
        break;
    case Qt::LeftSection: case Qt::RightSection:
        this->setCursor(QCursor(Qt::SizeHorCursor));
        break;
    case Qt::BottomLeftSection: case Qt::TopRightSection:
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
        break;
    case Qt::TopLeftSection: case Qt::BottomRightSection:
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
        break;
    case Qt::TitleBarArea:
        this->setCursor(QCursor(Qt::SizeAllCursor));
        break;
    case Qt::NoSection: default:
        this->setCursor(QCursor(Qt::ArrowCursor));
        break;
    }

    const QPoint delta(e->pos() - __mouse);
    __mouse = e->pos();
    if (e->buttons() & Qt::LeftButton) {
        switch (__carring) {
        case Qt::LeftSection:
            __rect.setLeft(__rect.left() + delta.x());
            break;
        case Qt::RightSection:
            __rect.setRight(__rect.right() + delta.x());
            break;
        case Qt::TopSection:
            __rect.setTop(__rect.top() + delta.y());
            break;
        case Qt::BottomSection:
            __rect.setBottom(__rect.bottom() + delta.y());
            break;
        case Qt::TopLeftSection:
            __rect.setTopLeft(__rect.topLeft() + delta);
            break;
        case Qt::TopRightSection:
            __rect.setTopRight(__rect.topRight() + delta);
            break;
        case Qt::BottomLeftSection:
            __rect.setBottomLeft(__rect.bottomLeft() + delta);
            break;
        case Qt::BottomRightSection:
            __rect.setBottomRight(__rect.bottomRight() + delta);
            break;
        case Qt::TitleBarArea:
            __rect.moveTo(__rect.topLeft() + delta);
            break;
        default:
            break;
        }
        __rect = __rect.normalized();
        this->repaint();

        const Labyrinth currentLabyrint(Labyrinth::fromImage(__labyrint.copy(roundedRect())));
        if (currentLabyrint.size() != QSize()) {
            emit newLabyrinthAppeared(currentLabyrint);
        }
    }
}

void LabyrinthParser::mousePressEvent(QMouseEvent * e) {
    __mouse = e->pos();
    Qt::WindowFrameSection side(section(e->pos()));
    if (__rect.isNull()) {
        __rect.moveTo(e->pos());
        __carring = Qt::BottomRightSection;
    } else {
        __carring = side;
    }
    this->repaint();
}

void LabyrinthParser::mouseDoubleClickEvent(QMouseEvent*) {
    __rect = QRect();
    this->repaint();
}

void LabyrinthParser::mouseReleaseEvent(QMouseEvent*) {
    __carring = Qt::NoSection;
}

void LabyrinthParser::loadLabyrint(QString fName) {
    if (__labyrint.load(fName)) {
        __rect = QRect(QPoint(5, 26), QSize(401, 281));
        __sectorSize = QSize(10,10);
        this->setFixedSize(__labyrint.size());
        const Labyrinth currentLabyrint(Labyrinth::fromImage(__labyrint.copy(__rect)));
        if (currentLabyrint.size() != QSize()) {
            emit newLabyrinthAppeared(currentLabyrint);
        }
    }
}

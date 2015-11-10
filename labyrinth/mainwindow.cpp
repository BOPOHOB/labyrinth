#include "mainwindow.h"

#include <QtWinExtras>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>

#include "filenameedit.h"
#include "labyrinthparser.h"
#include "labyrinthwidget.h"
#include "labyrinthstatementswidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    if (QtWin::isCompositionEnabled()) {
        QtWin::extendFrameIntoClientArea(this, -1, -1, -1, -1);
        setAttribute(Qt::WA_TranslucentBackground, true);
        setAttribute(Qt::WA_NoSystemBackground, false);
        setStyleSheet("MainWindow { background: transparent; }");
    }

    this->setCentralWidget(new QWidget(this));
    this->centralWidget()->setLayout(new QVBoxLayout);

    FileNameEdit* const input(new FileNameEdit(this));
    this->centralWidget()->layout()->addWidget(input);
    input->setOpenFileFunction([](QWidget* parent)->QString {
        return QFileDialog::getOpenFileName(parent, "Укажите файл с лабиринтом Федорука!", QString(), "Image(*.gif)");
    });

    QHBoxLayout* l(new QHBoxLayout);
    static_cast<QVBoxLayout*>(this->centralWidget()->layout())->addLayout(l);
    QVBoxLayout* lP(new QVBoxLayout);
    l->addLayout(lP);

    LabyrinthParser* const parser(new LabyrinthParser(this));
    parser->setStep(QSize(10,10));
    lP->layout()->addWidget(parser);
    connect(input, SIGNAL(fileNameChanged(QString)), parser, SLOT(loadLabyrint(QString)));

    LabyrinthWidget* const display(new LabyrinthWidget(this));
    connect(parser, SIGNAL(newLabyrinthAppeared(Labyrinth)), display, SLOT(setLabyrinth(Labyrinth)));
    lP->addWidget(display);

    lP->addStretch();

    LabyrinthStatementsWidget* result(new LabyrinthStatementsWidget(this->centralWidget()));
    connect(parser, SIGNAL(newLabyrinthAppeared(Labyrinth)), result, SLOT(setLabyrinth(Labyrinth)));
    l->addWidget(result);
}

MainWindow::~MainWindow()
{

}

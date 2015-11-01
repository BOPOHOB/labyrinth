#ifndef FILENAMEEDIT_H
#define FILENAMEEDIT_H

#include <QLineEdit>

class QPushButton;

class FileNameEdit : public QLineEdit {
    Q_OBJECT

private:
    void keyPressEvent(QKeyEvent *);
    void resizeEvent(QResizeEvent *);
    bool eventFilter(QObject *, QEvent *);
    void valueTest();

public:
    FileNameEdit(QWidget* parent = 0);

signals:
    void fileNameChanged(QString);
private slots:
    void callDialod();

private:
    QPushButton* const __pb;
    QWidget* const __warning;
};


#endif // FILENAMEEDIT_H

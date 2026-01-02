#ifndef CONINFWIN_H
#define CONINFWIN_H

#include <QDialog>

namespace Ui {
class ConInfWin;
}

class ConInfWin : public QDialog
{
    Q_OBJECT

public:
    explicit ConInfWin(QWidget *parent = nullptr);
    ~ConInfWin();

private:
    Ui::ConInfWin *ui;
};

#endif // CONINFWIN_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stopwatch.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void slot_startStopClicked();
    void slot_resetClicked();
    void slot_lapClicked();
    void slot_updateTime(qint64 milliseconds);

private:
    QString formatTime(qint64 milliseconds) const;

    Ui::MainWindow* ui;
    Stopwatch stopwatch_;
    int lapCount_ = 0;
};

#endif // MAINWINDOW_H

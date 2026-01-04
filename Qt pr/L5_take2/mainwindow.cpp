#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->btnLap->setEnabled(false);
    ui->timeLabel->setText("00:00:00:0");

    connect(ui->btnStartStop, &QPushButton::clicked,
            this, &MainWindow::slot_startStopClicked);

    connect(ui->btnReset, &QPushButton::clicked,
            this, &MainWindow::slot_resetClicked);

    connect(ui->btnLap, &QPushButton::clicked,
            this, &MainWindow::slot_lapClicked);

    connect(&stopwatch_, &Stopwatch::sig_timeUpdated,
            this, &MainWindow::slot_updateTime);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_startStopClicked()
{
    if (stopwatch_.isRunning()) {
        stopwatch_.stop();
        ui->btnStartStop->setText("Старт");
        ui->btnLap->setEnabled(false);
    } else {
        stopwatch_.start();
        ui->btnStartStop->setText("Стоп");
        ui->btnLap->setEnabled(true);
    }
}

void MainWindow::slot_resetClicked()
{
    stopwatch_.reset();
    ui->timeLabel->setText("00:00:00:0");
    ui->textBrowser->clear();
    lapCount_ = 0;
}

void MainWindow::slot_lapClicked()
{
    lapCount_++;
    qint64 lapMs = stopwatch_.lapMs();

    ui->textBrowser->append(
        QString("Круг %1, время: %2")
            .arg(lapCount_)
            .arg(formatTime(lapMs))
        );
}

void MainWindow::slot_updateTime(qint64 milliseconds)
{
    ui->timeLabel->setText(formatTime(milliseconds));
}

QString MainWindow::formatTime(qint64 ms) const
{
    qint64 totalSeconds = ms / 1000;
    qint64 hours = totalSeconds / 3600;
    qint64 minutes = (totalSeconds % 3600) / 60;
    qint64 seconds = totalSeconds % 60;
    qint64 tenths = (ms % 1000) / 100;

    return QString("%1:%2:%3:%4")
        .arg(hours, 2, 10, QChar('0'))
        .arg(minutes, 2, 10, QChar('0'))
        .arg(seconds, 2, 10, QChar('0'))
        .arg(tenths);
}

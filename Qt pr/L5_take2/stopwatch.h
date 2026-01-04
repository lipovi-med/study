#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTimer>

class Stopwatch : public QObject
{
    Q_OBJECT

public:
    explicit Stopwatch(QObject* parent = nullptr);

    void start();
    void stop();
    void reset();

    qint64 elapsedMs() const;
    qint64 lapMs() ;

    bool isRunning() const;

signals:
    void sig_timeUpdated(qint64 milliseconds);

private slots:
    void slot_onTimeout();

private:
    QTimer timer_;
    qint64 elapsedMs_ = 0;
    qint64 lastLapMs_ = 0;
    bool running_ = false;
};

#endif // STOPWATCH_H

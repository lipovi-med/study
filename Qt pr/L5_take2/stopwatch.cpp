#include "stopwatch.h"

Stopwatch::Stopwatch(QObject* parent)
    : QObject(parent)
{
    timer_.setInterval(100); // 0.1 сек = 100 мс
    connect(&timer_, &QTimer::timeout,
            this, &Stopwatch::slot_onTimeout);
}

void Stopwatch::start()
{
    if (!running_) {
        timer_.start();
        running_ = true;
    }
}

void Stopwatch::stop()
{
    if (running_) {
        timer_.stop();
        running_ = false;
    }
}

void Stopwatch::reset()
{
    stop();
    elapsedMs_ = 0;
    lastLapMs_ = 0;
    emit sig_timeUpdated(elapsedMs_);
}

void Stopwatch::slot_onTimeout()
{
    elapsedMs_ += 100;
    emit sig_timeUpdated(elapsedMs_);
}

qint64 Stopwatch::elapsedMs() const
{
    return elapsedMs_;
}

qint64 Stopwatch::lapMs()
{
    qint64 lap = elapsedMs_ - lastLapMs_;
    lastLapMs_ = elapsedMs_;
    return lap;
}

bool Stopwatch::isRunning() const
{
    return running_;
}

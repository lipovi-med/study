#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}
};

class Observable {
public:
    void addObserver(Observer* obs) {
        observers_.push_back(obs);
    }

    void removeObserver(Observer* obs) {
        observers_.erase(std::remove(observers_.begin(), observers_.end(), obs), observers_.end());
    }

    void warning(const std::string& message) const {
        for (auto obs : observers_) {
            if (obs) obs->onWarning(message);
        }
    }

    void error(const std::string& message) const {
        for (auto obs : observers_) {
            if (obs) obs->onError(message);
        }
    }

    void fatalError(const std::string& message) const {
        for (auto obs : observers_) {
            if (obs) obs->onFatalError(message);
        }
    }

private:
    std::vector<Observer*> observers_;
};


class WarningObserver : public Observer {
public:
    void onWarning(const std::string& message) override {
        std::cout << "[WARNING] " << message << std::endl;
    }
};

class ErrorObserver : public Observer {
public:
    explicit ErrorObserver(const std::string& file_path) : file_path_(file_path) {}

    void onError(const std::string& message) override {
        std::ofstream out(file_path_, std::ios::app);
        if (out.is_open()) {
            out << "[ERROR] " << message << std::endl;
        }
        else {
            std::cerr << "Cannot open file for errors: " << file_path_ << std::endl;
        }
    }

private:
    std::string file_path_;
};

class FatalErrorObserver : public Observer {
public:
    explicit FatalErrorObserver(const std::string& file_path) : file_path_(file_path) {}

    void onFatalError(const std::string& message) override {
        std::cerr << "[FATAL] " << message << std::endl;

        std::ofstream out(file_path_, std::ios::app);
        if (out.is_open()) {
            out << "[FATAL] " << message << std::endl;
        }
        else {
            std::cerr << "Cannot open file for fatal errors: " << file_path_ << std::endl;
        }
    }

private:
    std::string file_path_;
};

int main() {
    Observable logger;

    WarningObserver warnObs;
    ErrorObserver errObs("errors.log");
    FatalErrorObserver fatalObs("fatal.log");

    logger.addObserver(&warnObs);
    logger.addObserver(&errObs);
    logger.addObserver(&fatalObs);

    logger.warning("Low disk space");
    logger.error("Cannot open configuration file");
    logger.fatalError("System crash detected!");

    logger.removeObserver(&warnObs);
    std::cout << "\n[Warning observer removed]\n" << std::endl;
    logger.warning("This will not be shown");

    return 0;
}

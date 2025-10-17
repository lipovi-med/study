#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <stdexcept>

enum class LogType {
    Warning,
    Error,
    Fatal,
    Unknown
};

class LogMessage {
public:
    LogMessage(LogType type, std::string message)
        : type_(type), message_(std::move(message)) {
    }

    LogType type() const { return type_; }
    const std::string& message() const { return message_; }

private:
    LogType type_;
    std::string message_;
};

class LogHandler {
public:
    virtual ~LogHandler() = default;

    void setNext(LogHandler* next) noexcept {
        next_ = next;
    }

    void handle(const LogMessage& msg) {
        if (!process(msg)) {
            if (next_) {
                next_->handle(msg);
            }
            else {
                throw std::runtime_error("No handler for message type!");
            }
        }
    }

protected:
    virtual bool process(const LogMessage& msg) = 0;

private:
    LogHandler* next_ = nullptr;
};

class WarningHandler : public LogHandler {
protected:
    bool process(const LogMessage& msg) override {
        if (msg.type() == LogType::Warning) {
            std::cout << "[WARNING] " << msg.message() << std::endl;
            return true;
        }
        return false;
    }
};

class ErrorHandler : public LogHandler {
public:
    explicit ErrorHandler(const std::string& file_path)
        : file_path_(file_path) {
    }

protected:
    bool process(const LogMessage& msg) override {
        if (msg.type() == LogType::Error) {
            std::ofstream out(file_path_, std::ios::app);
            if (!out.is_open()) {
                throw std::runtime_error("Cannot open error log file!");
            }
            out << "[ERROR] " << msg.message() << std::endl;
            return true;
        }
        return false;
    }

private:
    std::string file_path_;
};

class FatalHandler : public LogHandler {
protected:
    bool process(const LogMessage& msg) override {
        if (msg.type() == LogType::Fatal) {
            throw std::runtime_error("[FATAL] " + msg.message());
        }
        return false;
    }
};

class UnknownHandler : public LogHandler {
protected:
    bool process(const LogMessage& msg) override {
        if (msg.type() == LogType::Unknown) {
            throw std::runtime_error("[UNKNOWN MESSAGE] " + msg.message());
        }
        return false;
    }
};

int main() {
    try {
        FatalHandler fatal;
        ErrorHandler error("errors.log");
        WarningHandler warning;
        UnknownHandler unknown;

        fatal.setNext(&error);
        error.setNext(&warning);
        warning.setNext(&unknown);

        LogMessage msg1(LogType::Warning, "Low disk space");
        LogMessage msg2(LogType::Error, "File not found");
        LogMessage msg3(LogType::Fatal, "Critical system crash");
        LogMessage msg4(LogType::Unknown, "Strange event detected");

        fatal.handle(msg1);
        fatal.handle(msg2);
        fatal.handle(msg4);

        fatal.handle(msg3);

    }
    catch (const std::exception& ex) {
        std::cerr << "Exception caught: " << ex.what() << std::endl;
    }

    return 0;
}

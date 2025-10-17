#include <iostream>
#include <fstream>
#include <string>
#include <memory>

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

class ConsoleLogCommand : public LogCommand {
public:
    void print(const std::string& message) override {
        std::cout << "[Console] " << message << std::endl;
    }
};

class FileLogCommand : public LogCommand {
public:
    explicit FileLogCommand(const std::string& file_path)
        : file_path_(file_path) {
    }

    void print(const std::string& message) override {
        std::ofstream out(file_path_, std::ios::app);
        if (out.is_open()) {
            out << "[File] " << message << std::endl;
        }
        else {
            std::cerr << "Error: cannot open file " << file_path_ << std::endl;
        }
    }

private:
    std::string file_path_;
};

void print(LogCommand& command, const std::string& message) {
    command.print(message);
}

int main() {
    ConsoleLogCommand console_logger;
    FileLogCommand file_logger("log.txt");

    print(console_logger, "Hello from console!");
    print(file_logger, "Hello from file!");

    return 0;
}

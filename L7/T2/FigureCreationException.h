#pragma once

#include <exception>
#include <string>

class FigureCreationException : public std::exception {
private:
    std::string message;

public:
    explicit FigureCreationException(const std::string& msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};
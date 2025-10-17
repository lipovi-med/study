#include <string>
#include <iostream>
#include <fstream>
#include <memory>

class PrintableText {
public:
    virtual ~PrintableText() = default;
    virtual std::string printText() const = 0;
};

class PrintableHTML {
public:
    virtual ~PrintableHTML() = default;
    virtual std::string printHTML() const = 0;
};

class PrintableJSON {
public:
    virtual ~PrintableJSON() = default;
    virtual std::string printJSON() const = 0;
};

class TextData : public PrintableText {
public:
    explicit TextData(std::string data) : data_(std::move(data)) {}
    std::string printText() const override {
        return data_;
    }
private:
    std::string data_;
};

class HTMLData : public PrintableHTML {
public:
    explicit HTMLData(std::string data) : data_(std::move(data)) {}
    std::string printHTML() const override {
        return "<html>" + data_ + "</html>";
    }
private:
    std::string data_;
};

class JSONData : public PrintableJSON {
public:
    explicit JSONData(std::string data) : data_(std::move(data)) {}
    std::string printJSON() const override {
        return "{ \"data\": \"" + data_ + "\" }";
    }
private:
    std::string data_;
};

void saveTo(std::ofstream& file, const PrintableText& printable) {
    file << printable.printText();
}

void saveTo(std::ofstream& file, const PrintableHTML& printable) {
    file << printable.printHTML();
}

void saveTo(std::ofstream& file, const PrintableJSON& printable) {
    file << printable.printJSON();
}

int main() {
    std::ofstream file("output.txt");

    TextData text("Hello Text");
    HTMLData html("Hello HTML");
    JSONData json("Hello JSON");

    saveTo(file, text);
    saveTo(file, html);
    saveTo(file, json);

    file.close();

    std::cout << text.printText() << std::endl;
    std::cout << html.printHTML() << std::endl;
    std::cout << json.printJSON() << std::endl;

    return 0;
}

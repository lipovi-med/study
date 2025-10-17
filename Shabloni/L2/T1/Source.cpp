#include <string>
#include <iostream>
#include <algorithm>

class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }

    virtual ~Text() = default;
};

class DecoratedText : public Text {
public:
    explicit DecoratedText(Text* text) : text_(text) {}
protected:
    Text* text_;
};

class ItalicText : public DecoratedText {
public:
    explicit ItalicText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const override {
        std::cout << "<i>";
        text_->render(data);
        std::cout << "</i>";
    }
};

class BoldText : public DecoratedText {
public:
    explicit BoldText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const override {
        std::cout << "<b>";
        text_->render(data);
        std::cout << "</b>";
    }
};

class Paragraph : public DecoratedText {
public:
    explicit Paragraph(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const override {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};

class Reversed : public DecoratedText {
public:
    explicit Reversed(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const override {
        std::string reversed = data;
        std::reverse(reversed.begin(), reversed.end());
        text_->render(reversed);
    }
};

class Link : public DecoratedText {
public:
    explicit Link(Text* text) : DecoratedText(text) {}

    void render(const std::string& url, const std::string& data) const {
        std::cout << "<a href=" << url << ">";
        text_->render(data);
        std::cout << "</a>";
    }
};

int main() {
    std::cout << "<!DOCTYPE html>\n<html>\n<body>\n\n";

    // Заголовок
    {
        Text* title = new BoldText(new Text());
        std::cout << "<h1>";
        title->render("Welcome to My Page");
        std::cout << "</h1>\n\n";
        delete title;
    }

    // Абзац с курсивом
    {
        Text* paragraph = new Paragraph(new ItalicText(new Text()));
        paragraph->render("This is an italic paragraph.");
        delete paragraph;
    }

    // Реверсированный текст
    {
        Text* reversed = new Paragraph(new Reversed(new Text()));
        reversed->render("Reversed text example!");
        delete reversed;
    }

    // Ссылка
    {
        Link* link = new Link(new Text());
        std::cout << "<p>Visit our site: ";
        link->render("https://netology.ru", "Netology");
        std::cout << "</p>\n";
        delete link;
    }

    // Комбинированный стиль
    {
        Text* combo = new Paragraph(new BoldText(new ItalicText(new Text())));
        combo->render("Stylish and combined text!");
        delete combo;
    }

    std::cout << "\n</body>\n</html>\n";
}

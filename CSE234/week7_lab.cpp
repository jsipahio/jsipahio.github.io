#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct HtmlElement {
    std::string tag;
    std::string content;
};

std::ostream& operator<<(std::ostream& out, const HtmlElement& element) {
    out << '<' << element.tag << '>';
    out << element.content;
    out << "</" << element.tag << '>';

    return out;
}

class MarkdownProcessor {
public:
    MarkdownProcessor();
    void parse(std::ifstream& fin);
    void write(std::ofstream& fout) const;
private:
    std::unordered_map<std::string, std::function<void(const std::string&, std::ifstream&)>> parseHandlers;
    std::vector<HtmlElement> elements;
};

int main(int argc, char** argv) {
    const char* errmsg = "Invalid usage. Expected 2 arguments\n";
    const char* help = "Usage: ./md_convert input_file output_file\n";
    
    if (argc < 3) {
        std::cerr << errmsg;
        std::cerr << help;
    }

    std::ifstream fin(argv[1]);
    if (fin.fail()) {
        std::cerr << "Failed to open file " << argv[1] << "\n";
        return 2;
    }
    std::ofstream fout(argv[2]);
    if (fin.fail()) {
        std::cerr << "Failed to open file " << argv[2] << "\n";
        return 3;
    }

    MarkdownProcessor converter;
    converter.parse(fin);
    fin.close();
    converter.write(fout);
    fout.close();

    return 0;
}

MarkdownProcessor::MarkdownProcessor() {
    // create and assign parseHandlers here
    parseHandlers["# "] = [this](const std::string& line, std::ifstream& fin) {
        HtmlElement element;
        element.tag = "h1";
        element.content = line;
        element.content.erase(0, 2);
        elements.push_back(element);
    };
    parseHandlers["## "] = [this](const std::string& line, std::ifstream& fin) {
        HtmlElement element;
        element.tag = "h2";
        element.content = line;
        element.content.erase(0, 3);
        elements.push_back(element);
    };
    parseHandlers["### "] = [this](const std::string& line, std::ifstream& fin) {
        HtmlElement element;
        element.tag = "h3";
        element.content = line;
        element.content.erase(0, 4);
        elements.push_back(element);
    };
    parseHandlers["#### "] = [this](const std::string& line, std::ifstream& fin) {
        HtmlElement element;
        element.tag = "h4";
        element.content = line;
        element.content.erase(0, 5);
        elements.push_back(element);
    };
    parseHandlers["##### "] = [this](const std::string& line, std::ifstream& fin) {
        HtmlElement element;
        element.tag = "h5";
        element.content = line;
        element.content.erase(0, 6);
        elements.push_back(element);
    };
    parseHandlers["- "] = [this](const std::string& line, std::ifstream& fin) {
        HtmlElement element;
        element.tag = "li";
        element.content = line;
        element.content.erase(0, 2);
        elements.push_back(element);
    };
    parseHandlers[" "] = [this](const std::string& line, std::ifstream& fin) {
        HtmlElement element;
        element.tag = "p";
        element.content = line;
        elements.push_back(element);
    };
}

void MarkdownProcessor::parse(std::ifstream& fin) {
    std::string line;
    while (std::getline(fin, line)) {
        std::size_t i = 0;
        std::size_t length = line.length();
        std::string lineStart = "";
        while (i < length && (line[i] == '#' || line[i] == '-')) {
            lineStart += line[i];
            ++i;
        }
        lineStart += ' ';
        parseHandlers[lineStart](line, fin);
    }
}

void MarkdownProcessor::write(std::ofstream& fout) const {
    bool inList = false;
    for (const auto& element: elements) {
        if (!inList && element.tag == "li") {
            fout << "<ul>\n";
            inList = true;
        }
        if (inList && element.tag != "li") {
            fout << "</ul>\n";
            inList = false;
        }
        fout << element << '\n';
    }
}

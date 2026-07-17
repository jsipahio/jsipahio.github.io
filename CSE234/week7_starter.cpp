#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// stores the tag and content of an HTML element
struct HtmlElement {
    std::string tag;
    std::string content;
};

// prints the start and end tag and content for an HTML element
std::ostream& operator<<(std::ostream& out, const HtmlElement& element) {
    out << '<' << element.tag << '>';
    out << element.content;
    out << "</" << element.tag << '>';

    return out;
}

// parses a Markdown file and converts it to HTML
class MarkdownProcessor {
public:
    // constructor
    MarkdownProcessor();
    // parses Markdown file opened by fin
    void parse(std::ifstream& fin);
    // writes HTML to file opened by fout
    void write(std::ofstream& fout) const;
private:
    // map of function callbacks for handling parsing events 
    std::unordered_map<std::string, std::function<void(const std::string&)>> parseHandlers;
    // HTML elements to be output
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
        fin.close();
        std::cerr << "Failed to open file " << argv[2] << "\n";
        return 3;
    }

    MarkdownProcessor converter;
    // parse the Markdown file
    converter.parse(fin);
    // done with the input file, close it
    fin.close();
    // write the HTML
    converter.write(fout);
    // close the output file
    fout.close();

    return 0;
}

MarkdownProcessor::MarkdownProcessor() {
    // create and assign parseHandlers here
}

void MarkdownProcessor::parse(std::ifstream& fin) {
    // read the lines of the Markdown file and use
    // the parseHandlers map to call the right callback
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

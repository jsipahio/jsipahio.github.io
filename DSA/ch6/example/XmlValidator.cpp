/*
This program validates an XML document.
All it does is validate that all elements are closed.
*/

#include <fstream>
#include <iostream>
#include "stack.hpp"
#include <string>

class XmlValidationException {
public:
    XmlValidationException(const std::string& reason) {
        errorMessage = "XML Validation Failed. Reason: " + reason;
    }
    std::string what() const {
        return errorMessage;
    }
private:
    std::string errorMessage;
};

struct XmlElement {
    std::string name;
    bool closing;
    bool selfClosing;
};

/**
 * readProlog
 * XML documents may start with a prolog 
 * that we want to skip 
 * 
 * Ex:
 * <?xml version="1.0" encoding="utf-8"?>
 * 
 * @param in - input stream to read from
 * @throws XmlValidationException
 */
void readProlog(std::ifstream& in) {
    char prev = '<';
    char curr = '?';
    std::string tagName;
    tagName.reserve(3);
    for (int i = 0; i < 3 && in.get(curr); ++i) {
        tagName[i] = curr;
        prev = curr;
    }
    if (tagName != "xml") {
        throw XmlValidationException(
            "Invalid prologue"
        );
    }
    // read until closing bracket
    while (in.get(curr) && curr != '>') 
        prev = curr;
    // if the close of the tag is not ?>, it's a violation
    // need to check curr because it's possible we reach 
    // eof before finding >
    if (curr != '>' && prev != '?') {
        throw XmlValidationException(
            "Invalid prologue"
        );
    }
}

/**
 * readNextElemement
 * Reads document until reaching next XML element. Ignores comments
 * 
 * @param in - input stream to read from
 * @return first encountered XML element in the stream
 */
XmlElement readNextElement(std::istream &in) {
    // it would be more efficient to use a character buffer,
    // but the point of this example is to show off Stack
    // not be as efficient as possible
    std::string elementName;
    // store the previous character to check if the element is
    // closing or self-closing
    char prev = 0;
    // current character that has been read
    char curr;
    // boolean to let us know we are in a element
    bool inElement;
    // boolean to let us know if the tag is a closing tag
    bool closing;
    // boolean to let us know the current tag is self-closing
    bool selfClosing;
    // boolean that tells us we are in a comment
    bool comment;
    // read a character at a time until reaching a potential element
    while (in.get(curr)) {
        // < cannot be nested within another element tag, validation fails
        if (curr == '<' && inElement) {
            throw XmlValidationException(
                "Nested element start"
            );
        }
        // reset booleans and string when encountering new element
        else if (curr == '<') {
            selfClosing = false;
            closing = false;
            elementName = "";
            inElement = true;
        }
        // if in an element and the current character
        //  is not the close character,
        //  append the character to the tag name
        else if (inElement && !(curr == '>' || curr == '/')) {
            elementName += curr;
        }
        // found the start of a closing tag
        if (prev == '<' && curr == '/') {
            closing = true;
        }
        // found the end of a self closing tag
        if (curr == '>' && prev == '/') {
            selfClosing == true;
            inElement = false;
        }
        // we may have found the end of an element
        if (curr == '>') {
            // we need to check if it is a comment
            // an XML comment looks like: <!-- TEXT -->
            // since we skipped < as part of the name,
            // check that the first three characters are "!--"
            // and the last two characters are "--"
            if (
                !(elementName.length() > 3 &&
                elementName[0] == '!' &&
                elementName[1] == '-' &&
                elementName[2] == '-' &&
                elementName[elementName.length() - 2] == '-' &&
                elementName[elementName.length() - 1] == '-')
            ) {

            }
            break;
        }
        prev = curr;
    }
    return {elementName, closing, selfClosing};
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Expected 1 argument. Got none\n";
        std::cerr << "Usage:\n";
        std::cerr << "./xml_validator filename.xml\n";
        return 1;
    }
    std::ifstream in(argv[1]);
    if (in.fail()) {
        std::cerr << "Could not open file " << argv[1] << "\n";
        return 1;
    }
    Stack<XmlElement> elementStack;
    try {
        XmlElement element = readNextElement(in);
        if (element.closing) {
            throw XmlValidationException(
                "Document starts with closing element"
            );
        }
        if (element.name == "") {
            throw XmlValidationException(
                "No XML elements found"
            );
        }
        elementStack.push(element);
        element = readNextElement(in);
        while (element.name != "") {
            // if we have emptied the stack and found another element,
            // the XML is invalid since all elements have to be nested
            if (elementStack.empty()) {
                throw XmlValidationException(
                    "Unnested element found."
                );
            }

            // skip self closing elements
            if (element.selfClosing) continue;

            // check if the element is closing
            if (element.closing) {
                // we already checked the stack is not empty
                XmlElement openingElement = elementStack.top();
                // we check if the most recent element added to the stack
                // is the same as the closing tag we just found
                // if they are different, the XML is malformed and
                // we throw a validation exception
                if (element.name != openingElement.name) {
                    throw XmlValidationException(
                        "Closing element found with no valid opening."
                    );
                }
                // otherwise we closed an element and can pop it off the stack
                else {
                    elementStack.pop();
                }
            }
            // otherwise, we add the element to the stack
            else {
                // if the stack is full, resize it
                if (elementStack.full()) {
                    elementStack.resize(elementStack.capacity() * 2);
                }
                elementStack.push(element);
            }
        }
    }
    // not a true error, just failed validation
    catch (XmlValidationException ex) {
        std::cerr << ex.what() << "\n";
        return 0;
    }
    // unknown exception occurred
    catch (std::exception ex) {
        std::cerr << "An unhandled exception occurred\n";
        std::cerr << ex.what() << "\n";
        return 1;
    }
    // very unknown exception
    catch (...) {
        std::cerr << "An unknown exception occurred\n";
        return 1;
    }
    std::cout << "XML Validation passed\n";
    return 0;
}

# Stack ADT

The stack ADT describes a container that provides access to its elements last-in, first-out (LIFO) order. A stack can be implemented using an array or linked list. Linked lists will be discussed in the next chapter, so in this chapter the stack will be implemented using an array. 

## Data 
A stack needs to store an ordered collection of data. The data needs to be ordered since the access order of the stack is controlled. In an array based implementation, the number of elements currently stored in the array also needs to be tracked (i.e., the top of the stack). Additionally, the maximum capacity of the array must be stored. A list-based implementation will be discussed in the next chapter.

## Operations
Stacks provide two primary operations: `push()` and `pop()`. `push()` adds an element element to the top of the stack. The `pop()` operation removes an item from the top of the stack. In some implementations, `pop()` returns the element on top of the stack as well, while other implementations have a separate `top()` operation that handles accessing the top of the stack. An `empty()` operation should also be provided to allow programmers using the stack to guard against accessing the top of an empty stack.  
In addition to these operations, our array based stack should also provide operations to access the maximum size of the underlying array, as well as a way to resize the array, if we choose to use a dynamically allocated array for the stack. 

## Rules
In an array-based implementation, pushing an element element to a full stack must throw an exception, as it would overflow the stack. In any implementation accessing the top and/or popping from an empty stack must throw an exception, since this would be an illegal access attempt.

## Operation Efficiency
The point of a stack is to allow fast insertion and removal of elements by limited where elements can be added. We will evaluate the time complexity of `push()` and `pop()`. First, the pseudocode:
```
ADT Stack:
    Array data
    num top
    num max

    operation push(e):
        if top + 1 >= max:
            throw FullStackError
        else:
            top = top + 1
            data[top] = e

    operation pop():
        if top < 0:
            throw EmptyStackError
        else:
            e = data[top]
            top = top - 1
            return e 

    operation empty():
        if top < 0:
            return true
        else:
            return false

    operation full():
        if top + 1 >= maxSize:
            return true
        else:
            return false
```
All of these operations contain only simple statements with no loops or calls, so the complexity of each operation is O(1), i.e., constant time. The space complexity of the stack is O(N), where N is the maximum size of the stack. This is the primary limitations of the array-based stack. Any unused indices of the array are wasted space.

## Example Stack Implementation
Below is an example stack implementation using an array as the data storage mechanism. A dynamically allocated array is used to allow for varying sized stacks to be used. In this implementation, the default maximum stack size is 256, and the user can set the maximum size using the constructor and `resize()` member function. Automatic resizing (like `std::vector` provides) is not implemented for this example. Since dynamic memory is being used, the "big 3" must be implemented for this class. First, the class definition:  
```C++
#ifndef STACK_HPP
#define STACK_HPP

#include <exception>

constexpr size_t DEFAULT_MAX_STACK = 256;

template <typename T>
class Stack {
public:
    Stack();
    Stack(size_t max);
    Stack(const Stack& other);
    ~Stack();
    Stack& operator=(Stack rhs);

    void push(const T& element);
    T& top() const;
    void pop();

    bool full() const;
    bool empty() const;
    bool operator==(const Stack &other) const;
    size_t size() const;
    size_t capacity() const;

    void swap(Stack& other);
    void resize(size_t newSize);
private:
    size_t maxSize;
    size_t top;
    T *data;
};

#include <stack.tcc>
#endif 
```
And, the implementation:
```C++
template <typename T>
Stack<T>::Stack() : 
    maxSize(DEFAULT_MAX_STACK), 
    top(-1), 
    data(new T[DEFAULT_MAX_STACK]) {}

template <typename T>
Stack<T>::Stack(size_t max) :
    maxSize(max),
    top(-1),
    data(new T[max]) {}

template <typename T>
Stack<T>::Stack(const Stack<T> &other) :
    maxSize(other.maxSize),
    top(other.top),
    data(new T[other.maxSize]) 
{
    for (size_t i = 0; i < other.top; ++i) {
        data = other.data[i];
    }
}

template <typename T>
Stack<T>::~Stack() {
    delete[] data;
    maxSize = 0;
    top = -1;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T> rhs) {
    swap(rhs);
}

template <typename T>
void Stack<T>::swap(const Stack<T> &other) {
    size_t tempMax = maxSize;
    size_t tempTop = top;
    T *tempData = data;

    maxSize = other.maxSize;
    other.maxSize = tempMax;

    top = other.top;
    other.top = tempTop;

    data = other.data;
    other.data = tempData;
}

template <typename T>
void Stack<T>::push(const T& element) {
    if (top + 1 >= maxSize) {
        throw std::exception("Stack is full. Cannot push");
    }

    ++top;
    data[top] = element;
}

template <typename T>
T& Stack<T>::top() const {
    if (top < 0) {
        throw std::exception("Cannot check top of empty stack");
    }
    return data[top];
}

template <typename T>
void Stack<T>::pop() const {
    if (top < 0) {
        throw std::exception("Cannot check top of empty stack");
    }
    --top;
}

template <typename T>
void Stack<T>::resize(size_t newSize) {
    // don't resize if new size is same as old max
    if (newSize == maxSize) return;
    // if the new size is smaller than top,
    // adjust the top of the stack
    if (newSize <= top) top = newSize - 1;
    // create a temp array to store copy of elements
    T *tempData = new T[newSize];
    // copy over elements
    for (size_t i = 0; i < top; ++i) {
        tempData[i] = data[i];
    }
    // delete old data
    delete[] data;
    // assign data to new array
    data = tempData;
}

template <typename T>
bool Stack<T>::full() const {
    return top + 1 == maxSize;
}

template <typename T>
bool Stack<T>::empty() const {
    return top < 0;
}

template <typename T>
bool Stack<T>::operator==(const Stack& rhs) const {
    // if the tops are different, the two stacks are different
    if (top != rhs.top) return false;

    // compare elements pairwise
    // if they are different, immediately return false
    for (size_t i = 0; i < top; ++i) {
        if (data[i] != rhs.data[i]) return false;
    }
    // at this point every element of the two stacks is the same
    // so the two stacks must be equal
    return true;
}
```

## Stack Applications
Stacks are used to solve a variety of problems in computer science. We already saw in an earlier chapter how stacks are used manage memory used by function calls in a program. Additionally, stacks are very useful for parsing mathematical expressions. Since parentheses and other brackets need to be matched, we can push each left parenthesis onto a stack, and pop from the stack whenever we find a right parenthesis. If we find a right parenthesis while the stack is empty or still have left parentheses on the stack when we reach the end of an expression, we know that the expression is malformed. We can use this to both check that the expression is valid and to know which parts of the expression to evaluate first, as they are nested in parentheses.  
Stacks are also used for storing histories. For example, a browser history maintains two stacks, one for pages that you have visited previously in that tab, and another to store pages you have left by hitting the "back arrow". These stacks allow you to use the left and right arrows to move backwards, and sometimes forwards, through you history. Whenever you visit a new page after hitting the back button, the forward stack is cleared. Below is a summary of the operations:
```
Stack backward_history
Stack forward_histroy

event back_arrow:
    forward_history.push(backward_history.pop())

event forward_arrow:
    backward_history.push(forward_history.pop())

event click_link_or_enter_url:
    forward_history.clear()
    backward_history.push(current_page)
```
Another application for stacks is parsing structured documents (HTML, XML, JSON, etc.). All of these documents use a nested structure, so a stack can be used to associate data with the correct "label" (what a label is, exactly, depends on the document type). As an example, consider the following HTML snippet:
```HTML
<body>
    <h1>Title</h1>
    <p>This is an example <em>HTML</em> document.</p>
</body>
```
HTML documents form a tree structure. In this snippet, the root of the tree is the `body` element. The `body` has two children, the `h1` element and the `p` element. The `h1` element has no children, and the `p` has one child, the `em` element. A stack can be used to keep track of the currently open element. First, `body` would be added to the stack since it is first tag encountered. Immediately afterwards, the `h1` tag is found, so that gets added to the stack. `h1` gets added as child to `body`'s tree. Then, the text "Title" is added to the `h1` element, since it is at the top of the stack. The next tag encountered is `h1`'s closing tag. Since this matches the tag at the top of the stack, `h1` is popped from the stack. Next, the `p` tag is encountered, so `p` is added to the stack. The text "This is an example " is added to the `p` element's text. Next, `em` in found. Since `p` is the top of the stack, `em` is a child of `p`. The text "HTML" is associated with `em`. Next, the closing `em` tag is found, so `em` is popped from the stack. The text " document" is found next, and `p` is still the top of the stack, so this text is also added to `p`. The closing tag for `p` comes next, so `p` is popped from the stack. Next, the closing `body` tag is found, so `body` is popped from the stack. At this point, we've processed the entire document, and constructed a tree like the following:

## Full Example: XML Validator
For a full example, we'll use the stack we implemented previously in this chapter to implement an XML validator. Since we have not covered trees and recursion yet, we will not be implementing a full parser at this time. However, we do not need a full parser to validate XML. But, before building our validator, we should define what XML is exactly, and what rules it needs to follow to be valid.

### XML

eXtensible Markup Language (XML) is a structured data format that relies on tags (or elements) like HTML does, but with a much stricter format. HTML is primarily used to specify the format of documents, whereas XML is primarily used for data transfer. (There was a point in the mid 2000s where XHTML was created to impose XML strictness to HTML, but it was dropped when HTML5 came out.)  
One major difference between XML and HTML is that all XML elements must be closed (self-closing tags must explicitly contain the trailing slash). Another difference is that the document can only have a single root. While these are both recommendations for HTML, most HTML parsers have safeguards to render malformed HTML. XML parsers do not attempt to parse malformed XML, they report an error and give up. Below are a list of things we should check for in an XML document:  
- A document may optionally start with a prologue, a special element that starts with `<?xml`, is closed by `?>`, and contains metadata as attributes, such as the XML version and character encoding used. If the prologue is included, it must be the first element to appear in the document.
- Comments may appear anywhere in an XML document, except within a tag and before the prologue. A comment starts with `<!--` and ends with `-->`. Comments may span multiple lines.
- All elements must be closed. Elements with no content may be self-closing by ending with a slash before the close bracket. Example: `<self_closing/>`
- An XML document may only have one root element. If there are multiple root elements, the document is invalid XML. The only exception is the prologue, which only contains metadata about the document, and is not considered part of the document itself.
- `<` and `>` cannot appear anywhere within a tag. In other words, `<less<than>` is not a valid element. 
- Tags may contain attributes. Example: `<img src="/resources/images/images.png">` In this tag, `src` is an attribute. A tag can contain zero to many attributes. 
  
Failure to meet any of these rules results in an invalid XML document, and should thus fail our validation check.

### Planning the Validator
To validate the XML, we need to collect every element we encounter in the document. If it is an opening tag, we can add it to a stack of open elements. Any time we encounter a closing tag, we can check if it matches the tag at the top of the stack. If it matches, we can safely pop that tag from the stack. If it doesn't match, we found an element that was not closed correctly, and therefore the document fails validation. We need some other mechanisms, as well. First, we need to read the start of the document and see if it is a prologue. The prologue is only valid if it is the first non-whitespace text encountered in the document. If we find a prologue anywhere else, the document fails validation. We also need to ignore comments, since they start and end with the same character as a normal tag. We do not want to confuse a comment for a normal XML tag. Of course, if the tag itself is malformed in any way, the validation fails.   
Since the focus of this section is on stacks, we will skip implementing the other functionalities and assume that the functions work. The full implementation is included with this chapter's examples, if you are curious how the rest of the validator works.  
First, we need a data structure to represent an XML tag. The tag consists of a name, it may be a closing tag, or it may be a self-closing tag. We are building a full parser, so we don't care about the attributes or the rest of the tag's structure. In this case, a simple struct is sufficient:
```C++
struct XmlElement {
    std::string name;
    bool closing;
    bool selfClosing;
};
```
Next, we need a function to read the next XML tag from the input stream. Again, the implementation is skipped here since it is not needed to illustrate how the stack aids this programming task. Another consideration we do mention, is that this function needs to know what to do with the prologue. We will provide it a boolean parameter that has a default value of false that tells it whether to parse the prologue. The first time we call this function, we can set it to true, so that it will skip the prologue. Otherwise, the function will raise a validation exception if it encounters a prologue. Otherwise, the function reads ahead through the document until it reaches a tag, then returns that tag.
```C++
XmlElement readNextTag(std::ifstream& in, bool allowPrologue = false);
```
Finally, we have the `validate()` function, which uses a stack to ensure that all tags are closed properly. We provide a full, documented implementation of the function here:
```C++
void validate(std::ifstream &in) {
    // first, we create a stack to store the open elements
    Stack<XmlElement> openElements;
    // next, we try reading an XML element
    XmlElement element = readNextTag(in, true);
    // first, we check that we found an element
    // if we didn't raise an exception that the 
    // document doesn't contain XML (and is invalid)
    if (element.name == "") {
        throw XmlValidationException("Document contains no XML");
    }
    // next, check that the tag is not a closing tag
    // if the first tag is a closing tag, that is not valid
    if (element.closing) {
        throw XmlValidationException("Found closing tag with no opening tag");
    }
    // next, check if the tag is not self closing
    // if it is, we don't add it to the stack
    if (!element.selfClosing) {
        openElements.push(element);
    }
    // now we try to parse the rest of the document
    element = readNextElement(in);
    // if readNextElement does not find another element,
    // the name of the element will be an empty string
    while (element.name != "") {
        // first, we check if the stack is empty
        // if the stack is empty, and we found another element
        // then there are multiple root elements
        if (openElements.empty()) {
            throw XmlValidationException("Found multiple root nodes");
        }
        // next, check if the element is self closing
        // if it is, skip to the next element
        if (element.selfClosing) continue;
        // next, check if the element is a closing tag
        if (element.closing) {
            // if the element does not match the top of the stack
            // this is an invalid closing tag and we fail validation
            if (element.name != openElements.top().name) {
                throw XmlValidationException("Found closing tag without matching open.");
            }
            // otherwise, pop the element from the stack. it is closed now
            else {
                openElements.pop();
            }
        }
        // at this point, we have another opening tag to add to the stack
        else {
            openElements.push(element);
        }   
        // read the next element
        element = readNextElement(in);
    }
}
```
Now, for the main function of this program. We will put the call to `validate()` in a `try` block, then catch any `XmlValidationException` that occurs separately from other types of exception. That way, we can report a failure to validate and return with a 0 exit code when validation fails, and exit with a non-zero code when an unhandled exception occurs.
```C++
// we expect to get the filename to validate from the command line args
int main(int argc, char **argv) {
    // ensure a command line arg was provided
    if (argc < 2) {
        std::cerr << "Expected 1 argument. Got none.\n";
        std::cerr << "Usage: \n";
        std::cerr << "./xml_validator filename.xml\n";
        return 1;
    }
    // try to open the file
    std::ifstream fin(argv[1]);
    // report if opening the file failed
    if (fin.fail()) {
        std::cerr << "Failed to open file " << argv[1] << "\n";
        return 1; 
    }
    try {
        // try to validate the XML
        // if an XmlValidationError occurs, it will 
        // end up in the first catch block
        validate(fin);
    }
    // this catches the validation error and exits normally
    // after reporting the validation error
    catch (XmlValidationError ex) {
        fin.close();
        std::cerr << ex.what() << "\n";
        return 0;
    }
    // this handles reporting that an unknown exception occurred
    catch (...) {
        fin.close();
        std::cerr << "An unhandled exception has occurred\n";
        return 1;
    }
    // since C++ does not have a finally block
    // each branch after try has to close the file
    fin.close();
    // if we got here, XML validation must have passed
    std::cout << "XML Validation passed.\n";
    return 0;
}
```

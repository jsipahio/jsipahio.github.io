#ifndef INCLUDED_EXAMPLE_HPP
#define INCLUDED_EXAMPLE_HPP

class Example {
public:
    Example();
    Example(int d);

    void setData(int d);
    int getData() const;
private:
    int data;
};

#endif
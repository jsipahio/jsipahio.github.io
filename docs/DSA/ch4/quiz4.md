# Quiz 4

## Questions

1. True/False: A class that contains a pointer member should usually implement the Big Three.

2. Multiple Choice: Which of the following is the purpose of a destructor?
   - A. To copy an object
   - B. To release dynamically allocated memory
   - C. To compare two objects
   - D. To create a new object

3. Short Answer: What problem occurs when a class uses a default copy constructor and two objects share the same dynamic memory?

4. True/False: The copy constructor should create a deep copy rather than copying the pointer value only.

5. Multiple Choice: In the copy-and-swap idiom, what is passed to the assignment operator by value?
   - A. A raw pointer
   - B. A reference to the left-hand object
   - C. A copy of the right-hand object
   - D. A static array

6. Short Answer: Why is a dynamic array a good choice for implementing a string ADT?

7. True/False: A string ADT should store its length as a member variable in addition to its character data.

8. Multiple Choice: Which character is commonly used as the null terminator for C-style strings?
   - A. `\n`
   - B. `\0`
   - C. `\t`
   - D. `\r`

9. Short Answer: What are two operations commonly included in a string ADT besides construction and destruction?

10. Multiple Choice: Which operator is typically overloaded to concatenate two strings?
   - A. `==`
   - B. `+`
   - C. `[]`
   - D. `=`

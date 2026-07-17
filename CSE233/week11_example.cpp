#include <iostream>
#include <string>

class Student {
public:
    // default constructor does nothing
    Student() {}
    // constructor to set fields
    Student(std::string first, std::string last, double grade, int credits);
    // getters
    std::string getFirstName() const;
    std::string getLastName() const;
    int getCreditHours() const;
    double getGpa() const;
    // setters
    void setFirstName(const std::string& name);
    void setLastName(const std::string& name);
    void setCreditHours(int credits);
    void setGpa(double grade);
    // other functions
    // returns the name in "First Last" format
    std::string getFullName() const;
    // allows users to specify the output format of the name
    // looks for {first} and {last} in the format string
    // for example, format = "{last}, {first}" outputs a name
    // as "Last, First"
    std::string getFullName(const std::string& format) const;
    // updates gpa and credit hours when a student completes a class
    void completeClass(double grade, int credits);
private:
    std::string firstName;
    std::string lastName;
    int creditHours;
    double gpa;
};

int main() {
    // create two student objects
    Student student1("John", "Doe", 3.5, 24);
    Student student2("Jane", "Doe", 3.5, 24);

    std::cout << "Before calling setters\n";

    // use getters to print out the state of the students
    std::cout << "Student 1: \n";
    std::cout << "    " << student1.getFirstName() << " " 
        << student1.getLastName() << "\n";
    std::cout << "    " << student1.getGpa() << " GPA\n";
    std::cout << "    " << student1.getCreditHours() << " Credit Hours\n";
    
    std::cout << "\nStudent 2: \n";
    std::cout << "    " << student2.getFirstName() << " " 
        << student2.getLastName() << "\n";
    std::cout << "    " << student2.getGpa() << " GPA\n";
    std::cout << "    " << student2.getCreditHours() << " Credit Hours\n";

    // use setters to modify the student objects
    student1.setFirstName("Mike");
    student1.setLastName("Smith");
    student1.setGpa(3.6);
    student1.setCreditHours(12);

    student2.setFirstName("Sam");
    student2.setGpa(500);

    std::cout << "\nAfter calling setters\n";
        std::cout << "Student 1: \n";
    std::cout << "    " << student1.getFirstName() << " " 
        << student1.getLastName() << "\n";
    std::cout << "    " << student1.getGpa() << " GPA\n";
    std::cout << "    " << student1.getCreditHours() << " Credit Hours\n";
    
    std::cout << "\nStudent 2: \n";
    std::cout << "    " << student2.getFirstName() << " " 
        << student2.getLastName() << "\n";
    std::cout << "    " << student2.getGpa() << " GPA\n";
    std::cout << "    " << student2.getCreditHours() << " Credit Hours\n";
    std::cout << "\n";

    // create another student
    Student student("John", "Doe", 3.5, 24);
    std::cout << student.getFullName() << "\n";
    std::cout << student.getFullName("Student: {last}, {first}") << "\n";
    std::cout << student.getGpa() << " GPA\n";
    std::cout << student.getCreditHours() << " Credit Hours\n";

    // simulate student completing three classes 
    // and getting 2 As and a B
    student.completeClass(95, 3);
    student.completeClass(87, 3);
    student.completeClass(91, 3);

    // print updated gpa and credit hours
    std::cout << "\nUpdated credit hours and GPA\n";
    std::cout << student.getGpa() << " GPA\n";
    std::cout << student.getCreditHours() << " Credit Hours\n";

    return 0;
}

Student::Student(std::string first, std::string last, double grade, int credits) {
    firstName = first;
    lastName = last;

    if (credits >= 0) {
        creditHours = credits;
    }
    else {
        creditHours = 0;
    }
    if (grade < 4 && grade > 0) {
        gpa = grade;
    }
    else if (grade > 4) {
        gpa = 4;
    }
    else {
        gpa = 0;
    }
}

std::string Student::getFirstName() const {
    return firstName;
}

std::string Student::getLastName() const {
    return lastName;
}

int Student::getCreditHours() const {
    return creditHours;
}

double Student::getGpa() const {
    return gpa;
}

void Student::setFirstName(const std::string& name) {
    firstName = name;
}

void Student::setLastName(const std::string& name) {
    lastName = name;
}

void Student::setCreditHours(int credits) {
    if (credits >= 0) {
        creditHours = credits;
    }
    else {
        creditHours = 0;
    }
}

void Student::setGpa(double grade) {
    if (grade < 4 && grade > 0) {
        gpa = grade;
    }
    else if (grade > 4) {
        gpa = 4;
    }
    else {
        gpa = 0;
    }
}

std::string Student::getFullName() const {
    return firstName + " " + lastName;
}

std::string Student::getFullName(const std::string& format) const {
    std::string output = format;
    // find "{first}" and replace it with firstName
    int firstPos = output.find("{first}");
    if (firstPos != std::string::npos) {
        output.replace(firstPos, 7, firstName);
    }

    // find "{last}" and replace it with lastName
    int lastPos = output.find("{last}");
    if (lastPos != std::string::npos) {
        output.replace(lastPos, 6, lastName);
    }

    return output;
}

void Student::completeClass(double grade, int credits) {
    // convert grade to gradePoint
    double gradePoint;
    // A is 4.0
    if (grade >= 90) {
        gradePoint = 4;
    }
    // B is 3.0
    else if (grade >= 80) {
        gradePoint = 3;
    }
    // C is 2.0
    else if (grade >= 70) {
        gradePoint = 2;
    }
    // D is 1.0
    else if (grade >= 60) {
        gradePoint = 1;
    }
    // F is 0
    else {
        gradePoint = 0;
    }
    // now, use weighted average calculation to determine
    // overall GPA based on the old GPA and new class
    int newCredits = credits + creditHours;
    // (double)newCredits temporarily converts newCredits to a double
    // that way, it performs floating point division instead of integer
    double weightedGpa = (creditHours / (double)newCredits) * gpa;
    double weightedGradePoint = (credits / (double)newCredits) * gradePoint;
    gpa = weightedGpa + weightedGradePoint;
    creditHours = newCredits;
}

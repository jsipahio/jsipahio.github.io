# student_info.py
# this imports the argv list from the sys module
from sys import argv

# like bash, the first command-line argument
# is the command that ran the script
script = argv[0]

# assuming we have the same input as the
# last example, but using command-line args
name = argv[1]
age = int(argv[2])
gpa = float(argv[3])

print("The script you ran is:", script)
print("Your name is", name)
print("Your age is", age)
print("Your GPA is", gpa)

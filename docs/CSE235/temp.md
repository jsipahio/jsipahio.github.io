
## Task Decomposition and Refactoring
Writing a program requires decomposing the task you have been given into more manageable sub-tasks. Then, you can solve the individual sub-tasks until you've created a program that solves the whole task you've been given. However, the resulting code of the program will often be messy, inefficient, and disorganized. Refactoring is the process in which you go through after writing the initial code and clean up the program. Next week, when we discuss testing and test driven development, you'll see a couple of longer examples of this. Here, I'll stick with a shorter example.  
Let's say that we have been given the task of writing a program that, given a range of integers, finds the integer that takes the most steps to reach 1 following the Collatz conjecture. The Collatz conjecture states the following: Given a positive integer, if it is even, divide it by 2. If it is odd, multiply it by 3 and subtract 1. Every integer will eventually reach 1 by doing this. This has never been formally proved, which is why it is called a conjecture and not a theorem, but there has never been an example to disprove it, either.  
Let's break down the requirements of the program into manageable tasks:
1. Read two numbers
2. Apply the Collatz conjecture to each number
3. Count the number of steps to reduce the number to 1
4. Keep track of the number that took the most steps
5. Report the number that took the most steps to reach 1

With these tasks in mind, let's start implementing a solution. The easiest thing to do is to read the two numbers in, so let's do that:
```py
print("This program will find which positive integer"
        " in a given range takes the most steps to reach 1"
        " following the Collatz Conjecture")

start = int(input("Enter start of range: "))
end = int(input("Enter end of range: "))
```
That's task 1 done. However, in writing this, I thought a problem. While I am asking for the minimum and maximum number explicitly, the user could still enter them in the wrong order. They could also enter the same number twice. In that case, we'd only be checking one number. This is technically valid, so we'll allow the user to enter the same number, so the program can be used to check how many steps it takes to reduce a single number to 1. However, we should validate that the min is less than or equal to the max. We could allow the user to continually reenter numbers, but I'd rather just report the invalid usage and end the program. It is short program that only asks the user to enter two numbers, so forcing them to run it again to use it correctly is easier than writing the code to prompt the user to enter the correct value.
```py
print("This program will find which positive integer"
        " in a given range takes the most steps to reach 1"
        " following the Collatz Conjecture")

start = int(input("Enter start of range: "))
end = int(input("Enter end of range: "))

# add logic to check that input is a valid range
if start > end:
    print("Invalid usage. Start must be less than end")
    exit(1)
```
Now, we can test if the program works. Below are some example inputs (the explanation message is excluded):
```
python3 collatz.py
Enter start of range: 1
Enter end of range: 5
python3 collatz.py
Enter start of range: 5
Enter end of range: 1
Invalid usage. Start must be less than end
python3 collatz.py
Enter start of range: 0
Enter end of range: 5
```
In testing it, I discovered another problem. 0 is not a valid input for the program. The input also cannot be 0 or negative. The conjecture does not apply to those values. Therefore, we need to eliminate the possibility that either element of the range is 0 or less.
```py
print("This program will find which positive integer"
        " in a given range takes the most steps to reach 1"
        " following the Collatz Conjecture")

start = int(input("Enter start of range: "))
end = int(input("Enter end of range: "))

if start > end:
    print("Invalid usage. Start must be less than end")
    exit(1)

# add logic to check that 0 is not part of the range
if start <= 0 or end <= 0:
    print("Invalid usage. Range must be positive")
    exit(2)
```
Now, we can test it again:
```
python3 collatz.py
Enter start of range: 0
Enter end of range: 5
Invalid usage. Range must be positive
python3 collatz.py
Enter start of range: -4
Enter end of range: -1
Invalid usage. Range must be positive
```
Now, we've handled getting input from the user. Next, we need to apply the Collatz conjecture to each of them. First, let's loop through the numbers:
```py
print("This program will find which positive integer"
        " in a given range takes the most steps to reach 1"
        " following the Collatz Conjecture")

start = int(input("Enter start of range: "))
end = int(input("Enter end of range: "))

if start > end:
    print("Invalid usage. Start must be less than end")
    exit(1)

if start <= 0 or end <= 0:
    print("Invalid usage. Range must be positive")
    exit(2)

for i in range(start, end + 1):
    print(i)
```
Before implementing anything else, we can check to make sure the loop works as intended:
```
python3 collatz.py
Enter start of range: 1
Enter end of range: 5
1
2
3
4
5
python3 collatz.py
Enter start of range: 500
Enter end of range: 500
500
```
Once we are satisfied, we can eliminate the print statement from the loop. Now, we need to write the algorithm for the Collatz conjecture. Rather testing it on each number in the range, we will comment out the for loop for now, and just run the algorithm on the first element of the range. That way, we can test if it works before running it on each number in the range.
```py
print("This program will find which positive integer"
        " in a given range takes the most steps to reach 1"
        " following the Collatz Conjecture")

start = int(input("Enter start of range: "))
end = int(input("Enter end of range: "))

if start > end:
    print("Invalid usage. Start must be less than end")
    exit(1)

if start <= 0 or end <= 0:
    print("Invalid usage. Range must be positive")
    exit(2)

# for i in range(start, end + 1):
#     print(i)

value = start
while value != 1:
    if value % 2 == 0:
        value //= 2
    else:
        value = value * 3 + 1

print("value now equals", value)
```
We expect that for any number we enter, that start eventually becomes 1. Now, our third requirement states that we need to count the number of steps it takes for the number to reach 1. Again, before looping through each number in the range, let's implement the counting mechanism:
```py
print("This program will find which positive integer"
        " in a given range takes the most steps to reach 1"
        " following the Collatz Conjecture")

start = int(input("Enter start of range: "))
end = int(input("Enter end of range: "))

if start > end:
    print("Invalid usage. Start must be less than end")
    exit(1)

if start <= 0 or end <= 0:
    print("Invalid usage. Range must be positive")
    exit(2)

# for i in range(start, end + 1):
#     print(i)

steps = 0
value = start

while value != 1:
    if value % 2 == 0:
        value //= 2
    else:
        value = value * 3 + 1
    steps += 1

print("value now equals", value)
print("it took", steps, "steps")
```
To verify that it is correct, we can hand calculate a couple of examples:    
**1**  
1 is 1. It takes 0 steps  

**5**

1. 5 is odd. 5 * 3 + 1 = 16
2. 16 is even. 16 / 2 = 8
3. 8 is even. 8 / 2 = 4
4. 4 is even. 4/ 2 = 2
5. 2 is even. 2/2 = 1
6. 1 is 1. It took 5 steps to get here  

**10**  

1. 10 us even. 10 / 2 = 5
2. 5 is odd. But, we know from our previous work that it takes 5 steps to get 5 to 1. Therefore, it takes 1 + 5 = 6 steps for 10 to get to 1.   

**13**  

1. 13 is odd. 13 * 3 + 1 = 40
2. 40 is even. 40 / 2 = 20
3. 20 is even. 20 / 10 = 10
4. 10 is even. But, we know from previous work that it takes 6 steps to get 10 to 1. Therefore, it takes 3 + 6 = 9 steps for 13 to get to 1.  

Once satisfied with the number of test cases, we can run the program with them. Once satisfied that it works, we can move on to the next step, running the Collatz algorithm on all numbers in the range. To do so, we will move the code into the for loop, and replace `start` with `i`.
```py
print("This program will find which positive integer"
        " in a given range takes the most steps to reach 1"
        " following the Collatz Conjecture")

start = int(input("Enter start of range: "))
end = int(input("Enter end of range: "))

if start > end:
    print("Invalid usage. Start must be less than end")
    exit(1)

if start <= 0 or end <= 0:
    print("Invalid usage. Range must be positive")
    exit(2)

for i in range(start, end + 1):
    steps = 0
    value = i
    while value != 1:
        if value % 2 == 0:
            value //= 2
        else:
            value = value * 3 + 1
        steps += 1

    print("value now equals", value)
    print("it took", steps, "steps")
```
Here is some example output for this point in development:
```
python3 collatz.py
Enter start of range: 5
Enter end of range: 6
value now equals 1
it took 5 steps
value now equals 1
it took 8 steps
```
Now, the requirements did not say to print out the steps for each number in the range. We are only supposed to print out the number of steps and the number which took the most steps. Therefore, we'll eliminate the print statements in the for loop that we used for testing, now that we are confident in the logic of the program. To store the number that took the most steps, and the number of steps, we'll need two more variables. Since these need to be used outside the while loop to report the final results at the end of the program, we need to declare them before the while loop.  
The minimum possible number of steps is 0, which happens if the value is 1. Therefore, we assume that the maximum number of steps taken is 0 to start off with. Then, each time we run the Collatz algorithm on a number, we check if the number of steps taken was more than the current maximum. If it is, we update the maximum number of steps and the value that caused the maximum number of steps. This will allow us to save the max steps.
```py
print("This program will find which positive integer"
        " in a given range takes the most steps to reach 1"
        " following the Collatz Conjecture")

start = int(input("Enter start of range: "))
end = int(input("Enter end of range: "))

if start > end:
    print("Invalid usage. Start must be less than end")
    exit(1)

if start <= 0 or end <= 0:
    print("Invalid usage. Range must be positive")
    exit(2)

max_steps = 0
value_with_max_steps = start

for i in range(start, end + 1):
    steps = 0
    value = i
    while value != 1:
        if value % 2 == 0:
            value //= 2
        else:
            value = value * 3 + 1
        steps += 1

    if steps > max_steps:
        max_steps = steps
        value_with_max_steps = i

print("Most steps:", max_steps)
print("For value:", value_with_max_steps)
```
Once again, we will test the program to ensure it works. At this point, all requirements have been met. However, we can clean up the program a bit. First, let's move the greeting message to a separate function. It takes up several lines of the main function, without contributing anything meaningful to anyone reading the code:
```py
def print_greeting():
    print("This program will find which positive integer"
          " in a given range takes the most steps to reach 1"
          " following the Collatz Conjecture")


print_greeting()

start = int(input("Enter start of range: "))
end = int(input("Enter end of range: "))

if start > end:
    print("Invalid usage. Start must be less than end")
    exit(1)

if start <= 0 or end <= 0:
    print("Invalid usage. Range must be positive")
    exit(2)

max_steps = 0
value_with_max_steps = start

for i in range(start, end + 1):
    steps = 0
    value = i
    while value != 1:
        if value % 2 == 0:
            value //= 2
        else:
            value = value * 3 + 1
        steps += 1

    if steps > max_steps:
        max_steps = steps
        value_with_max_steps = i

print("Most steps:", max_steps)
print("For value:", value_with_max_steps)
```
Next, let's move the error handling to a separate function. Recall that we can use the `exit()` function from `cstdlib` to exit the program if an error occurs. This will allow us to terminate the program from a non-main function:
```py
def print_greeting():
    print("This program will find which positive integer"
          " in a given range takes the most steps to reach 1"
          " following the Collatz Conjecture")


def validate_input(start, end):
    if start <= 0 or end <= 0:
        print("Invalid usage. Range must be positive")
        exit(1)

    if start > end:
        print("Invalid usage. Start must be less than end")
        exit(2)


print_greeting()

start = int(input("Enter start of range: "))
end = int(input("Enter end of range: "))

validate_input(start, end)

max_steps = 0
value_with_max_steps = start

for i in range(start, end + 1):
    steps = 0
    value = i
    while value != 1:
        if value % 2 == 0:
            value //= 2
        else:
            value = value * 3 + 1
        steps += 1

    if steps > max_steps:
        max_steps = steps
        value_with_max_steps = i

print("Most steps:", max_steps)
print("For value:", value_with_max_steps)
```
Now, we can move the logic of performing the Collatz algorithm to a separate function. The only thing that we are interested in from the Collatz algorithm is how many steps it takes to complete, so we will have it return the number of steps:
```py
def print_greeting():
    print("This program will find which positive integer"
          " in a given range takes the most steps to reach 1"
          " following the Collatz Conjecture")


def validate_input(start, end):
    if start <= 0 or end <= 0:
        print("Invalid usage. Range must be positive")
        exit(1)

    if start > end:
        print("Invalid usage. Start must be less than end")
        exit(2)


def count_collatz_steps(value):
    steps = 0
    while value != 1:
        if value % 2 == 0:
            value //= 2
        else:
            value = value * 3 + 1
        steps += 1
    return steps


print_greeting()

start = int(input("Enter start of range: "))
end = int(input("Enter end of range: "))

validate_input(start, end)

max_steps = 0
value_with_max_steps = start

for i in range(start, end + 1):
    steps = count_collatz_steps(i)

print("Most steps:", max_steps)
print("For value:", value_with_max_steps)
```
We can also move printing the results to a separate function:
```py
def print_greeting():
    print("This program will find which positive integer"
          " in a given range takes the most steps to reach 1"
          " following the Collatz Conjecture")


def validate_input(start, end):
    if start <= 0 or end <= 0:
        print("Invalid usage. Range must be positive")
        exit(1)

    if start > end:
        print("Invalid usage. Start must be less than end")
        exit(2)


def count_collatz_steps(value):
    steps = 0
    while value != 1:
        if value % 2 == 0:
            value //= 2
        else:
            value = value * 3 + 1
        steps += 1
    return steps


def print_results(steps, value):
    print("Most steps:", steps)
    print("For value:", value)


print_greeting()

start = int(input("Enter start of range: "))
end = int(input("Enter end of range: "))

validate_input(start, end)

max_steps = 0
value_with_max_steps = start

for i in range(start, end + 1):
    steps = count_collatz_steps(i)

print(max_steps, value_with_max_steps)
```
We've now made `main()` function cleaner, with logic that is easier to follow. Next week, when discussing unit testing, we will see that breaking the program up into smaller functions that handle single tasks make it easier to test programs, as well. 

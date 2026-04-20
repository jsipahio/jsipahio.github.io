# Makefile Lab

- Link to the GitHub Classroom: 

This lab asks you to split a C++ program implementing a clock from one file into three, then write the Makefile to compile it.

Labs and projects in this class are managed using GitHub classroom. If you haven't already, create a GitHub account. Information about GitHub and git can be found [here](git.md), however I'll be walking you through the steps for git in this lab as well.  
  
## Getting Started

First, you'll need to join the classroom and accept the assignment. To do so, go to the GitHub classroom link, select your name from the list, and accept the assignment. You should be taken to a repository that looks like the below image:  
  
  
Once you've accepted the assignment, you have two options to work on it: via a GitHub Codespace or locally. Instructions to set up a local environment are here: . Information about Codespaces is available in the [GitHub information page](git.md).  

If you are working locally, you need to clone the repository to a local folder. Go to the "Code" button above the directory listing on your repository homepage, and copy the "HTTPS" link provided. Then, in a local terminal, navigate to the directory you want to save the repository in, and run the command `git clone https://github.com/replace/with/your/repo/url.git`. This will create a new folder with the code in it.
  
No matter which option you choose, you should now be able to open the clock.cpp file in your text editor. The first thing you should do is verify that the code compiles and works. Run `g++ clock.cpp -o clock`, followed by `./clock`. You should see the following output:
```
12:57:34
1:57:34
```

## Requirements
- Using the techniques discussed in the Makefiles lecture, split this code into three files: a main driver, a header file for the class, and an implementation for the class. 
- Write a Makefile that compiles the program into the `clock` executable
- Verify that the output matches the original output

## Submitting Your Work
To submit your work, you must check in your local changes to your remote repository. **!!DO NOT CHECK IN BINARY FILES!!** You should use the `git add` command to add the new files you created to the tracking for the repo. You can use `git status` to make sure you have added all your source code files, and there are not any binary files (.o or executable). If `git status` shows a binary file as being tracked, use `git rm --cached` to remove it from tracking. When you are satisfied, use `git commit -m 'Submission'` to commit the changes locally. Then, use `git push` to push the changes to the remote origin. After pushing your changes, you should be able to refresh the repository on GitHub and see the new files you added.  
  
This concludes the first lab of the class.

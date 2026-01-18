## Terminal Basics
This fact sheet will help familiarize you with the terminal shell. In Linux and Mac, the application to access the shell is typically called "Terminal". In Windows, you can use Command Prompt (cmd.exe) or PowerShell (powershell.exe). You can also open a terminal in VS Code by holding the control (CTRL) key and pressing ~, which is to the left of your "1" key. On Windows, VS Code opens PowerShell by default, which I would recommend using.

### Command Cheat Sheet
Here is a list of commonly used commands in the terminal shell. Note that these are for Mac/Linux, although PowerShell aliases many of its commands to match these. The commands for Command Prompt are totally different, in many cases.

- `man` (manual) - this command will print the help manual for whatever command/program you pass it, assuming that a manual is available for it. The manual can be navigated using `PgUp` and `PgDn`, and exited by pressing `q` on your keyboard. (On most modern Linux systems you can also scroll with the mouse)

- `pwd` (print working directory) - this command prints your current working directory in the file system. It is important to be aware of the directory you are in, and how to navigate the file system, so you are working in the correct location

- `ls` (list) - this command shows you the directory listing, i.e., the list of all the files in and subdirectories in the directory `ls` is querying. Below are some of the command switches
    - `-l` - this switch changes the output to be in a more detailed list that shows you permissions, last access/modify date and time, and the size of file
    - `-a` - this switch shows hidden files and directories. In Linux, directories that start with a period are hidden
    - `-h` - this switch converts the bytes of a file's size into a more human-readable format, like kilobytes, megabytes, or gigabytes, depending on the size of the file
    - The switches can be combined like the following: `ls -lah` (the order of the switches is not important, `-ahl` would do the same thing)
    - By default, `ls` shows the listing for the current directory. But, you can pass it another directory as an argument: `ls -l /var/log`

- `cd` (change directory) - this command is used to change your working directory. It takes one argument, the directory you want to chage to.

- `mkdir` (make directory) - this command is used to create a new directory.
    - `-p` - this switch is used to create intermediate directories if they don't exist

- `cp` (copy) - this command is used to copy files or directories from a source to a destination. Below are some common switches:
    - `-b` - backup destination files
    - `-r` - recursively copy, this is used to copy directories and subdirectories. By default, directories are skipped without this flag
    - `-f` - force. If you try to copy over a file and that file is in use, it will attempt to force delete the destination file to complete the copy action
    - `-i` - interactive. This will prompt you to answer yes or no before overwriting a file. By default, existing files are overwritten without warning
    - `-n` - no-clobber. Blocks existing files from being overwritten

- `mv` (move) - this command will move a file from one location to another. Also, renaming a file is technically a "move" operation, so `mv` can be used to rename a file as well.
    - `-b` - backup destination files
    - `-f` - force. Always overwrite destination
    - `-i` - interactive. Prompt before overwrite
    - `-n` - no clobber. Never overwrite destination
    - `-u` - update. Only update destination if it is older than the source or does not exist

` 'rm` (remove) - this command will delete files and directories. Note that this will delete files permanently (there is not a recycle bin when using `rm`)
    - `-f` - ignore if file is missing (in PowerShell, use `-Force` instead)
    - `-i` - prompt before each removal
    - `-r` - remove directories and their children recursively
    - `-d` - remove empty directories

### Understanding the Command Line Environment
When using the terminal, you are interacting with your computer's filesystem using a text based interface. You are hopefully somewhat familiar with navigating your file system using your file explorer application provided by the operating system (File Explorer on Windows, Finder on Mac, Files on Ubuntu Linux, etc.). When you click your file explorer application, you get a GUI window that shows icons for the various files and folders you have. These files and folders themselves are contained within a folder in your file system. By default, Windows File Explorer opens yp to a Favorites and Recently accessed files screen, which is not an actual folder. Rather, it is a collection of folders. On Mac, Finder opens up your home directory, which contains your Desktop, Documents, iTunes, etc. folders.   
If you open a blank window in VS Code and open a terminal (using CTRL + ~), the terminal opens you your user directory (remember, directories in the terminal correspond to folders in file explorer). On Mac, your user directory is likely `/Users/<your-username>`. On Windows, it is typically `C:\Users\<your-username>`. This folder contains your Desktop, Documents, Downloads, etc. folders. You can check this by running the `ls` command. This command *lists* the files and directories contained in the current directory. To check the name of the directory you are currently in, you can use the `pwd` (print working directory) command. So, what if I am in `/Users/john/`, and want to get to my `Desktop` folder? I can use the `cd` (change directory) command to do so. If I type `cd Desktop`, I will change directory to the Desktop folder within the current directory, /Users/john, that I am in. Now, if I run `pwd`, I will see that I am in `/Users/john/Desktop/`. If I run `ls`, I will see all the files and folders that are contained within my `Desktop` folder. You can verify this by checking your own Desktop folder versus the list of files you get running `ls`.  
Your computer's directory has a tree-like structure. It starts with a root, which is represented by a `/` on Mac and `C:\` on Windows. Below is the typical, default directory structure of a Windows and Mac filesystem:  
*Note: your computer may vary slightly from this, that is okay*  
**Windows**  
```
C:\
    Program Files
    Program Files (x86)
    Users
        Administrator
        Guest
        <your-username>
            Desktop
            Documents
                Photos
            Downloads
    Windows
```
**Mac**
```
/
    bin
    boot
    dev
    etc
    lib
    home
    media
    mnt
    proc
    opt
    proc
    run
    srv
    sys
    usr
    Users
        <your-username>
            Desktop
            Documents
            Downloads
            iTunes
    var
```

For the sake of this class, you only need to worry about the folders and files that are "branches" and "leaves" of directory that is your username, which is why I have only "expanded" those directories in the diagrams above.  
Returning to the example from a couple paragraphs ago, I have changed directory into /Users/john/Desktop/. But, what if I want to go back a directory? Terminal shells reserve two periods, `..`, for this purpose. If I run the command `cd ..`, it will change my directory from /Users/john/Desktop/ to /Users/john/. If I run `cd ..` again, I will change directory from /Users/john/ to /Users/. If I wanted to get back to my Desktop folder, I would first have to `cd john` to get back to /Users/john/, then `cd Desktop` to get to /Users/john/Desktop/. Alternatively, I could provide the whole path to my Desktop folder, with the command `cd john/Desktop`. This would let me change from /Users/ to /Users/john/Desktop/ in a single command.  
As an example, let's say that this is what my (simplified) directory structure looks like:  
```
/
    Users
        john
            Desktop
                CSE122
                    lab1
                        lab1.vbproj
                        obj
                        Program.vb
                    lab2
                NET120
            Documents
            Downloads
```
Assume I am in a terminal, and run the command `pwd`. The output I get is `/Users/john/Downloads/`. There are two things I want to accomplish. First, I want to get to my "lab1" and run the program. Secondly, I want to create the Visual Basic console app project for my "lab2".  
If we look at the directory tree, we can see that both lab1 and lab2 are directories contained within the directory "CSE122". "CSE122" is contained in my "Desktop" directory, which is under my name.  
Currently, I am in /Users/john/Downloads/. "Desktop" is directly below "john", so I first want to get to "/Users/john/". To do so, I can use `cd ..` to move up one directory. Running this command will change my location from `/Users/john/Downloads/` to `/Users/john/`. Now, I want to get to my "Desktop" folder. Since it is directly below "john" in the directory tree, I can use `cd Desktop` to get there. If I run `pwd`, my current directory is now `/Users/john/Desktop/`. However, lab1 and lab2 are in "CSE122", not Desktop. "CSE122" is directly below Desktop, so to get there I can use `cd CSE122`. I am now in `/Users/john/Desktop/CSE122`.  
The first thing I wanted to do was to run my lab1 project. To do so, I should be in the "lab1" directory. Once again, I will use `cd` to get there. `cd lab1` will put me in `/Users/john/Desktop/CSE122/lab1/`. From here, I can run the command `dotnet run` to compile and execute my lab1 project.  
Next, I wanted to create a new project for lab2. The "lab2" directory is directly below "CSE122", and is not contained within "lab1" (use the indention to determine the level of a directory/file). Therefore, to get to "lab2", I must first use `cd ..` to exit the "lab1" directory and return to `/Users/john/Desktop/CSE122`. Now, I can use `cd lab2` to enter the directory `/Users/john/Desktop/CSE122/lab2`. To create a new Visual Basic console app project, type the command `dotnet new console --language VB`. This will create the starter files required for a basic Visual Basic console app. If you run the `ls` command in the "lab2" directory, you will see that it has created a new directory called `obj`, a file called `Program.vb`, and a file called `lab2.vbproj`.  
Below is an example of the terminal I/O for this example. Lines that start with `>` are user input lines. Lines that start with `#` are comments, and are not part of the actual terminal I/O. Lines that do not start with any special characters are the terminal output.  
```
# checking my current directory
> pwd
/Users/john/Downloads
# changing directory to my /User/john home directory
> cd ..
# displaying file listing
> ls 
Desktop
Documents
Downloads
# changing to Desktop and checking contents
> cd Desktop
> ls
CSE122
NET120
# changing to CSE122 and checking contents
> cd CSE122
> ls
lab1
lab2
# changing to lab1 and running project
> cd lab1
> dotnet run
Hello World!
# moving back a directory so I can change to lab2
> cd ..
> cd lab2
# creating a new VB console app in lab2
> dotnet new console --language vb
# there is a lot of text output when this happens that is not included here
> ls
lab2.vbproj
obj
Program.vb
> dotnet run
Hello World!
> 
```

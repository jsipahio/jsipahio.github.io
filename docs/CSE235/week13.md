# CSE235 Week 13: Installing External Packages and NumPy
One of the main reasons Python is and stays popular is the wealth of third-party libraries (often referred to as packages in Python) available for it. Today, we'll discuss how to install packages and create virtual environments for Python. We'll then discuss two of the most popular packages, NumPy and Matplotlib. 

## Pip
Pip is a recursive acronym that means "Pip installs packages". It has been the defacto standard for installing third party software packages in Python since it was released in 2008. Pip interacts with PyPI (Python Package Index), a remote repository of Python packages, as its primary source for installing packages. Pip can be connected to other repositories as well, provided they provide an interface that pip can interact with. We will only be using packages available on PyPI in this course.  

Pip is a command line tool. You can run it in one of the following ways:  
**Windows:**
```powershell
pip install package_name
# or
python -m pip install package_name
```
**Mac/Linux**
```bash
pip3 install package_name
# or
python3 -m pip install package_name
```
The `python -m` syntax tells Python to look for and run a preinstalled Python module. Pip is a preinstalled with all recent versions of Python 3. The `install` command tells it to look for the specified package in the PyPI repo. If it finds that package, it downloads and installs the package. By default, packages are installed into the global Python environment. We will discuss virtual environments in a coming section. Let's install our first package, NumPy. The command to do so is:  
**Windows:**
```powershell
pip install numpy
```
**Mac/Linux:**
```bash
pip3 install numpy
```
This will install NumPy onto your system. We'll discuss using NumPy in a couple of sections. Pip is also used to uninstall packages. If you decide to unistall NumPy, the command would be:  
**Windows:**
```powershell
pip uninstall numpy
```
**Mac/Linux:**
```bash
pip3 uninstall numpy
```
When installing and removing packages from the global environment, these commands can be run anywhere, and they affect the whole system.  
  
Some Python projects may require many external packages, along with specific versions of these packages to work. A `requirements.txt` file is a list of packages that are required for a Python project to work. Pip has the ability to read a `requirements.txt` file and install all of the packages listed within it. To do so, run the following command:  
**Windows:**
```powershell
pip -r requirements.txt
```
**Mac/Linux:**
```bash
pip3 -r requirements.txt
```
However, this may install a large number of packages that you only need for a single project into your global environment. Python is a constantly changing language, and version updates may break existing packages. Therefore, it is often recommended that packages are not installed into the global environment. Virtual environments were created to address this issue. In the next section, we'll discuss how to create and use virtual environments.

## Virtual Environments
A virtual environment is an isolated installation of Python. Typically, a folder called `.venv` is used to store the files for the virtual environment. The environment contains it's own version of the Python interpreter and pip. When using the version of Python and pip in the virtual environment, external packages installed are installed to the `.venv` folder instead of the entire system. This allows you to isolate different projects and keep the global environment clean. The `venv` module is used to create virtual environments. Typically, the `.venv` folder is created within the folder containing the project that the virtual environment is for. Assuming your terminal is in the folder of your project, this command is used to create a virtual environment:  
**Windows:**
```powershell
python -m venv .venv
```
**Mac/Linux:**
```bash
python3 -m venv .venv
```
This creates the virutal environment files, but does not automatically switch your terminal to use that environment. The following commands are used to activate the virtual environment, telling your terminal to use that environment instead of the global one:  
**Windows (Command Prompt):**
```cmd
.venv\Scripts\activate.bat
```
**Windows (PowerShell):**
```powershell
.venv\Scripts\Activate.ps1
```
**Mac/Linux:**
```bash
source .venv/bin/activate
```
You will know your terminal is using a virtual environment due to `(.venv)` appearing before your terminal prompt. To stop using the virtual environment, run `deactivate`.  
  
Most IDEs and even rich text editors like VS Code have the capability to create and activate a virtual environment for you, as well. The process to do so varies by IDE.

## NumPy
NumPy is a mathematics library for Python. One of the biggest problems with Python is that, being an interpreted language, it is very slow. Additionally, lists, while convenient to use, slow down program execution because they can hold different data types. Even if you create a list of all integers, Python does not know that is your intention, and will always have to treat every index in the list as though it could be anything. NumPy is a C library with bindings that make it usable in Python. Compiled C code is much faster than Python, and there are many performance optimizations that can be done in C that are simply impossible in Python. 

### NumPy Arrays
One of the main reasons to use NumPy is it's `Array` data type. Python lists are like arrays, but they can store elements of any data type. NumPy arrays, on the other hand, function more like arrays in other languages, where only a single data type must be stored. This reduces the burden of determining the data type for every element in the array. 

## Matplotlib

## Conclusion

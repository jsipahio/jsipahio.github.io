# Setting up git, gh, and gcc Locally

Working on your code locally requires more setup than using a Codespace, but has the advantage that you do not need to be connected to the internet to work on your code, you do not have the time limits that Codespaces do, and will likely have less lag and slow response times than what code spaces offer.  

## VS Code
The editor that I use and will be able to help you with is Visual Studio Code. It is available for all major operating systems (I've even installed it on a Chromebook). Search VS Code and go to the Download page. It should auto-detect your operating system and provide you with the correct installer. Follow the instructions for the installer on your system. 
  
## Linux
This class targets Linux builds. Due to the underlying similarities between Mac and Linux, Mac users can use their local environment: [instructions](). For Windows users, you have three options: use WSL (Windows Subsystem for Linux), create a Virtual Machine, or set up dual boot. Below are the steps:

### WSL (Easiest)
Setting up WSL is the easiest option. If you've never used WSL on your system before, you will first need to open a PowerShell or Command Prompt terminal as Administrator, and run the command `wsl --install`. This will install all the necessary tooling for WSL and create a WSL environment. As writing this, it will create an Ubuntu 24.04 instance, which is perfectly fine for this class. You will need to restart your computer afterwards. Open a terminal (does not have to be admin) after restarting and enter `wsl` to start the WSL instance. You will be prompted to create a username and password for your WSL environment. WSL does not have a desktop environment, so you will need to install VS Code on your Windows computer, then configure WSL as the default terminal profile, so you can use WSL directly in VS Code any time you create a terminal.
  
### Virtual Machine
If you want to try a Linux desktop environment, a VM is a good option. You may need to go into your computer's BIOS/UEFI to enable virtualization (this will depend on your computer model, so you will have to research how to do it on your machine). You will also need to install a hypervisor. Here are some options:  
- Hyper-V is the Windows hypervisor available on Professional and higher versions of Windows
- VirtualBox is an open-source and free hypervisor that works on all platforms
- VMWare Workstation is technically free for home/education use, but getting them to send you a download for the installer nowadays can be tricky
Whichever option you choose, you will need to select a Linux distribution to install. Ubuntu 24.04 is recommended if you have an Intel or AMD chip, and can be downloaded from [here](https://ubuntu.com/download/desktop). If you are using an ARM processor (e.g., Snapdragon) you will need to use 25.10 which is available at the same link.  
  
Look up a guide for creating a VM for whichever hypervisor you installed (it will vary based on which one and there are plenty available). Once you create the VM, you can boot it and install VS Code in the VM.  

### Dual Boot (Advanced)
Dual booting allows you to boot Linux and Windows on the same computer. This is the riskiest option, and if you don't know what you are doing you could potentially mess up your computer. I don't recommend this option, unless you are confident in your computing skills and/or are interested in switching to Linux full time. 

### Install Linux as Your OS
The other three options assumed you wanted to maintain Windows. If you are okay with entirely replacing Windows, or have an old computer that you want to experiment with, Linux can also be installed as the only OS on the device. The process is the same as dual-boot, except you'll be wiping and reformatting the whole disk for your Linux installation.

## Setting up Linux
I am going to assume you are on Ubuntu. If you have a different distribution, you probably already know how convert these commands to your distro.  
### Update the package lists
The first thing you should do is open a terminal and run these commands to update the package lists and install updates to existing software (sudo will prompt you to enter your password):
```bash
sudo apt update
sudo apt upgrade -y
```
Get in the habit of running these commands every so often, so your software stays up to date.
### Installing build tools
Next, to install `gcc`, `g++`, and `make`, you'll need to run this command:
```bash
sudo apt install build-essential
```
`build-essential` is a collection of tools for C/C++ development that include all the software you'll need for this class.
### Installing git and gh
Run this command to install git and gh:
```bash
sudo apt install git gh
```
`git` is used to run git commands, `gh` is used to allow `git` to access your GitHub repositories.
  
At this point, you should be ready to follow the instructions in the lab.

## Setting up Mac 
Both Mac and Linux are built off of UNIX, and are therefore very similar. The primary difference is that Mac uses `brew` as a package manager and Apple `clang++` as a compiler.  

To install `brew`, run the following command in a terminal:
```zsh
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
To check if `clang` is already installed, run:
```zsh
clang --version
```
If it is not installed, run this command to install it:
```zsh
xcode-select --install
```
To check if `git` is installed, run:
```zsh
git --version
```
If it is not installed, run
```zsh
brew install git
``` 
It is likely that the `gh` command for GitHub is not installed, so run
```zsh
brew install gh
```
Install VS Code for Mac.  
  
You are now ready to use your Mac for this class.

# GitHub and git Cheat Sheet

In this class we will be using GitHub classroom to manage your source code. This page contains useful information about GitHub and git.

GitHub is a frontend for hosting source code repositories using git as a version control system. What are all these, exactly?
- A source code repository (often just called a "repo") is the combination of the source code and metadata used by a version control system to track changes to the code over time.
- A version control system is used to track changes to a source code project (technically version control can be used for any type of file or project, but we are interested in source code in this class). When multiple developers are working on the same code base, it is likely that two or more developers may need to work on the same file at the same time. Early version control systems used a lock system, which prevented other developers from working on a file that another developer was working on until they finished. Newer systems use version merging, where separate versions of the file exist until they are deliberately merged into one final file.
- git is the standard version control system used now (90%+ market share). git is a distributed version control system, meaning that all developers maintain a local copy of the repo. Older version control system used a centralized model where all developers worked on the same copy of code hosted on a centralized server. The distributed model improves branching, merging, and offline work ability.
- GitHub is a frontend for hosting git repos. In addition to providing a server to host the repos, GitHub provides access control, issue tracking, project planning, and more. 
- Branches are separate versions of the same repo. When working on a specific issue or adding a new feature, developers will create a branch of the current version of the source code, modify the branch, then create a pull request to merge their changes back into the main development branch. 
- Commits are groups of changes made to a branch.
- When working on a branch locally, your changes are only applied locally. For your changes to show up on the remote version of the codebase, you must **push** the commit. This updates the remote state of the repo to have the commits you have made. Files that are not committed will not be pushed. If there is a conflict between the remote state and the changes you have made, you must resolve it before the changes can be pushed.
- To update the local state of the repo, you can use **pull** to copy the remote state into your local files. If there are conflicts between your local changes and the remote state being pulled, you will need to resolve them.

## GitHub and gh
To create an account, simply go to [GitHub's Website](https://github.com/) and select the option to create an account. To use GitHub classroom, you will need to enable two-factor authentication when it asks you.  
  
GitHub is the front end you can use to monitor your repositories. Repositories can be public or private. For this class, your repos will all be private.  
  
To access repositories hosted on GitHub locally, the `gh` command is used. This command manages your GitHub authentication on your computer, so you can use `git` locally. To log into GitHub on the command line, run:
```bash
gh auth login
```
This will prompt you to enter some information. For the first question, select "GitHub.com". For the next 

## git Commands
This is not an exhaustive list; git has a ton of functions. This should be enough to use git for this class, unless you really mess something up.
`clone` - The `git clone` command is used to clone a remote repository onto your local machine. By default, it creates a new folder with the same name as the repo in the directory you are currently in  
`pull` - The `git pull` command pulls changes in the remote version of the branch into the local copy of the branch. `pull` operates on the current branch only  
`status` - The `git status` command shows the current branch you are on, the staged changes, changes not staged for commit, and untracked files in the repository. Staged changes are the ones that are added to the commit. Changes not staged for commit are files that are detected as being modified, but have not been added to the commit. Untracked files are files that have never existed in the repository before, and need to be added to be tracked.  
`add` - The `git add` command is used to add files to a commit. Both new files and modified files must be added to the commit. Multiple files can be listed, separated by spaces: `git add class.hpp class.cpp main.cpp`  
`rm` - The `git rm` command is used to remove files. `git rm filename` will remove the file from tracking AND delete the file locally. If you want to keep the local copy of the file, used `git rm --cached filename` to only remove the file from tracking.  
`restore` - The `git restore` command is used to "undo" changes since the last time the file was committed.  
`switch` - The `git switch` command is used to change and create branches. `git switch other-branch` will change to an existing branch called "other-branch". `git switch -c new-branch` will create a new branch called "new-branch", based on the current branch, and switch to that branch.  
`commit` - The `git commit` command is used to commit a set of changes to your local repository. You should always provide a message describing the commit, using the `-m` switch: `git commit -m "Added README"`.
`push` - The `git push` command updates the remote version of the repository to reflect local commits.  
`fetch` - The fetch command is used to access remote branches.

## Codespaces
GitHub Codespaces are a web view of the Visual Studio Code editor running a Linux Virtual Machine. These offer a complete development environment, with all the build tools and git commands already installed and ready to be used. The main drawbacks of Codespaces is that they can be laggy and slow to start up, since they are remote virtual machines, and you need to be connected to the internet to access them. Another consideration is that you have a limited amount of time (currently ~75 hours a month) that you can use Codespaces for free. I don't foresee the usage limit being an issue, but it's worth keeping in mind. If you'd prefer to work locally, instructions to set up a local environment are here: [Set Up A Local Environment](local_env.mmd)  
  
Codespaces are bound to the repository you create it on. To create a Codespace, click the "Code &lt;&gt;" button, click the "Codespaces" tab, and select "Create Codespace on main". This will open a new tab, and after a couple of minutes of set up, the Codespace will be ready to use. Changes you make to your code in the Codespace are local to the Codespace. You will still need to commit and push changes for them to be visible outside the Codespace.  

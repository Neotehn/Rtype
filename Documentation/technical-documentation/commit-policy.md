# Commit Policy

### 1. Structure of commit messages: <a href="#1.-structure-of-commit-messages" id="1.-structure-of-commit-messages"></a>

```
1  One line description of your page
2  
3  Motivation:
4  Explain here the context, and why you're making that change.
5  What is the problem you're trying to solve.
6  
7  Modifications:
8  Describe the modifications you've done.
9  
10 Result:
11 After your change, what will change.
```

#### &#x20;Commit Title <a href="#commit-title" id="commit-title"></a>

The commit title (first line in commit message) is structured as follows:

**\[platform] \[verb] message** **ticket**

**platform** = SERVER or CLIENT or GAME or SETUP

**verb** = ADD, MODIFY, DELETE (inside file), REMOVE (a whole file), WIP (not allowed on main branch), MERGE, TEST, CLEAN, FIX, DISABLE

**message** = describes what the commit does

**ticket** = ticket name (will be automatically attached to your pr)

#### Setup locally <a href="#setup-locally" id="setup-locally"></a>

In order to see the template when commiting, follow those steps:

1. Copy the above template under .git folder as .gitmessage file
   1. as reference, the path is B-CPP-500-BER-5-2-rtype-gylian.karsch/.git/.gitmessage
2. In B-CPP-500-BER-5-2-rtype-gylian.karsch/ execute following command, but replace \<Path>

```
1 git config commit.template <Path>/B-CPP-500-BER-5-2-rtype-gylian.karsch/.git/.gitmessage
```

* as reference for me, the complete command looks like this:

```
1 git config commit.template /home/Josi/delivery/Semester_5/B-CPP-500-BER-5-2-rtype-gylian.karsch/.git/.gitmessage
```

3. Now you can use the template with:
   1. vscode source control tab
   2. jetbrain commit tab
   3. git commit (without already specifying message - no additional flags)

#### Example: <a href="#example" id="example"></a>

```
1  [CLIENT] [ADD] create linting rules
2   
3  Motivation:
4  Currently, the coding style is not applied in all files.
5  Therefore, we are missing consistency in the code.
6   
7  Modifications:
8  Following linting rules were added:
9  - Rule 1
10 - Rule 2
11 - . . .
12 
13 Result:
14 From now on, developers are forced to follow the coding style.
```

### 2. Branch names <a href="#2.-branch-names" id="2.-branch-names"></a>

**ticket-description**

**ticket** = ticket from Jira, for example RTB-17

**description** = name for your branch, doesn't need to be the title of the ticket in Jira, naming convention is all lower case with dashes

Example:\
“RTB-17-adjust-github-actions” for Ticket RTB-17 with name “Add commit check github action”



[Back](../../)

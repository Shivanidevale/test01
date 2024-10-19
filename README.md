Project Title:- To create Shell Program(Command Line Interpreter)

Author Name:- Shivani Devale

Project description:-

This project involves developing a basic shell (command line interpreter) that operates in both interactive and batch modes. The shell executes commands by creating child processes, runs commands simultaneously, and manages its own custom pathname environment. It relies on the `fork()` and `execv()` system calls for command execution. In batch mode, commands are read from a file, while in interactive mode, the user inputs commands directly at the prompt. The shell terminates when the `quit` command is entered or when the input stream ends. While it shares similarities with Unix shells, it is more streamlined in its design and functionality.

Compiling Instruction:-

1) To compile the whole project just run following command-

myshell> make

#This will compile the source files and generate the my_shell executable.

2) To remove compiled files, you can run following command-

myshell> make clean

3) After successful compilation, you can run the shell with following command-

#For Batch mode

myshell> ./myshell <batchFile.txt>

#For Interactive mode

myshell> ./myshell 

Sample Test Run:-

1) Interactive Mode:
Input:
prompt> ls 
prompt> /bin/ls 
prompt> ls -l ; cat file
prompt> ls -l ; cat file ; grep foo file2 
prompt> quit

Output:
1) myshell> ls
Executing: ls
batch1.txt  batchfile.txt  ls  main  main.c  main.o  makefile  myshell  path.c  path.o  README.md  testbatch.txt

2) myshell> /bin/ls
Executing: /bin/ls
batch1.txt  batchfile.txt  ls  main  main.c  main.o  makefile  myshell  path.c  path.o  README.md  testbatch.txt

3) myshell> ls -l ; cat file
Executing: ls -l
total 116
-rw-r--r-- 1 shdevale users    48 Sep 23 22:11 batch1.txt
......

4) myshell> ls -l ; cat file ; grep foo file2
Executing: ls -l
total 116
-rw-r--r-- 1 shdevale users    48 Sep 23 22:11 batch1.txt
......

5) myshell> pwd
/home/student/shdevale/cis545/group11_p1

6) myshell> echo "Hello, World!"
Executing: echo "Hello, World!"
"Hello, World!"

2) Batch Mode:
Batch file<testbatch.txt> contains following commands-
/bin
ls -l
pwd
echo "Hello, World!"

#For this project I have created 3 different batchfile- batchfile.txt, testbatch.txt, batch1.txt

Input:
prompt> ./myshell testbatch.txt

Output:
prompt> ./myshell testbatch.txt
Command directory set to: /bin
Read command from batch file: ls -l
Executing: /bin/ls -l
total 116
-rw-r--r-- 1 shdevale users    48 Sep 23 22:11 batch1.txt
-rw-r--r-- 1 shdevale users    73 Sep 23 22:11 batchfile.txt
-rw-r--r-- 1 shdevale users     0 Sep 20 00:02 ls
-rwxr-xr-x 1 shdevale users 16920 Sep 15 00:46 main
-rw-r--r-- 1 shdevale users  5428 Sep 23 22:26 main.c
-rw-r--r-- 1 shdevale users 13952 Sep 23 22:54 main.o
-rw-r--r-- 1 shdevale users   445 Sep 23 22:11 makefile
-rwxr-xr-x 1 shdevale users 29256 Sep 23 22:54 myshell
-rw-r--r-- 1 shdevale users  4804 Sep 23 22:11 path.c
-rw-r--r-- 1 shdevale users 12048 Sep 23 22:54 path.o
-rw-r--r-- 1 shdevale users  4076 Sep 23 22:26 README.md
-rw-r--r-- 1 shdevale users    36 Sep 23 22:11 testbatch.txt
Read command from batch file: pwd
Executing: /bin/pwd
/home/student/shdevale/cis545/group11_p1
Read command from batch file: echo "Hello, World!"
Executing: /bin/echo "Hello, World!"
"Hello, World!"


Existing Bugs:-
1) File redirection bug- for commands like echo "Hello, World!" > output.txt it does not properly handle redirection.

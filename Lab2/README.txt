AUTHORS: LIAM HOUGHTON, ADELAIDE ZIBROWSKI

This is a program that will find a certain file when you pass in a starting directory. It will 
also print the same thing that the command ls -l will print. These commands are passed in through 
the command line when you run the program. The program also prints out the time it took to run each 
program. There are a few functions to this program. First is the main function, where the two 
arguments are passed in through the command line as args[1] and args[2]. There are flags set so if 
the user does not type in the right command then the program will close gracefully. We also have
a find(const char *path, char file[100], int *flag) function, which will find the file you are looking
for. Then we have a double myList(const char *path) function that will print out what ls -l prints 
out.

Function detail:

int main (int argc, char *argv[])
    This is the initial function that starts the program. When you run the program, you have to enter the proper
    commands. If you do not enter the proper commands, then an error message will pop up saying "Error: Usage: 
    ./a.out myList <directory path> | find <directory path>. Then the program will exit gracefully. If you entered
    myList <directory path> then the myList(const char *path) is called and the ls -l information will print. This
    function returns 1 if it failed and returns the time it took to run the function if it succeeded. If you called
    find <directory path> then you are prompted for the file you want to find and the find function is called. There are
    flags all around the main function to check for proper input. Once the function is done running and the time is
    printed the program exits gracefully.

int find(const char *path, char file[100], int *flag)
    This is the function that will find your file if it exists. It first starts out by opening the directory, then 
    it checks if the directory is valid, if it is not then it closes. If the directory can be opened, then it checks if
    each file in the directory is a directory, in which case it will call the function recursively. "Path" is the 
    directory path, "file" is the name of the file, and "flag" is a flag set that will only be changed if the file is 
    found. The while loop iterates through the elements of the directory, and if the file is the same as the file they
    are looking for, it will print out the file path and a message stating that the file is found. If the file is not
    found then the flag is never set, and a statement will be printed out in the main function stating that the file 
    does not exist. 

double myList(const char *path)
    This function prints out the same things as the ls -l command, but through the macros of the file. It returns the 
    cpu time it takes for the function to be run. It opens the directory, and for each element in the directory it prints
    the permissions, number of hard links to file, the name of the user, the group ID of the owner, the total size
    of the file, the time it was last modified, and the name of the file. It gets the time it took for the program to
    run and returns it.

    
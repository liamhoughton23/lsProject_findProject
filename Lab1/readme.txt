
Liam Houghton


This is mostly a shell program that will do anything a command prompt will do.
If the command is not known then a error message will show up explaining why.
The program will start and you will be asked to enter a string. This string can 
either be a Linux command such as ls -la, or "showProcs" which will show the 
number of new processes being created by the fork_exec() function. If the fork itself
fails then there will be an error message explaining why as well. 

void fork_exec(char str[100])

This function does all the heavy lifting and implements a child process that will run 
the command you said to run. The parent function will wait for the child to be done and then
once the process is complete the main function will prompt you for another input. 

int main()

This is where you will be prompted for an input and then depending on the input either the fork_exec()
function will run or if you typed "showProcs" then the amound of new processes created will show. If you 
type "quit" then the program will end gracefully.
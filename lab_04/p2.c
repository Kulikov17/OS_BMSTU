#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main() 
{
	int child1 = fork();
	if (child1 == -1) 
    {
		perror("Can't fork");
		exit(1);
	} 
    else if (child1 == 0) 
    {
        printf("Child: pid=%d, pidid=%d, groupid=%d\n", getpid(), getppid(), getpgrp());
		return 0;
	}
    printf("Parent: pid=%d, childpid=%d, groupid=%d\n", getpid(), child1, getpgrp());
	
	int child2 = fork();
	if (child2 == -1) 
    {
		perror("Can't fork");
		exit(1);
	} 
    else if (child2 == 0) 
    {
        printf("Child: pid=%d, pidid=%d, groupid=%d\n", getpid(), getppid(), getpgrp());
		return 0;
	}
    printf("Parent: pid=%d, childpid=%d, groupid=%d\n", getpid(), child2, getpgrp());

    if (child1 != 0 && child2 != 0) 
    {
        int status1;
	    pid_t return1 = wait(&status1);
	    if (WIFEXITED(status1))
		    printf("Parent: child %d finished with %d code.\n", return1, WEXITSTATUS(status1) );
	    else if (WIFSIGNALED(status1))
		    printf("Parent: child %d finished from signal with %d code.\n", return1, WTERMSIG(status1));
	    else if (WIFSTOPPED(status1))
		    printf("Parent: child %d finished from signal with %d code.\n", return1, WSTOPSIG(status1));
        
        int status2;
        pid_t return2 = wait(&status2);
        if (WIFEXITED(status2))
        	printf("Parent: child %d finished with %d code.\n", return2, WEXITSTATUS(status2) );
	    else if (WIFSIGNALED(status2))
        	printf("Parent: child %d finished from signal with %d code.\n", return2, WTERMSIG(status2));
        else if (WIFSTOPPED(status2))
	        printf("Parent: child %d finished from signal with %d code.\n", return2, WSTOPSIG(status2));  
    }

    return 0;
}
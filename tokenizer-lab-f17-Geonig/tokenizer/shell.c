#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "shell.h"
#include "mytok.c"




char ** paths;


char *builtin_str[] = {
		"cd",
		"help",
		"exit"
};

int (*builtin_func[]) (char **) = {
		&lsh_cd,
		&lsh_help,
		&lsh_exit
};

int lsh_num_builtins() {
	return sizeof(builtin_str) / sizeof(char *);
}

/*
  Builtin function implementations.
 */

/**
   @brief Bultin command: change directory.
   @param args List of args.  args[0] is "cd".  args[1] is the directory.
   @return Always returns 1, to continue executing.
 */
int compareStr(char *stringa, char *stringb){

	int indexOfa, indexOfb = 0;

	while(stringa[indexOfa] != '\0' || stringb[indexOfb] != '\0'){

		if(stringa[indexOfa] != stringb[indexOfb]){

			return 0;

		}

		indexOfa++;
		indexOfb++;
	}

	return 1;


}


int lsh_cd(char **args)
{
	if (args[1] == NULL) {
		fprintf(stderr, "lsh: expected argument to \"cd\"\n");
	} else {
		if (chdir(args[1]) != 0) {
			perror("lsh");
		}
	}
	return 1;
}

/**
   @brief Builtin command: print help.
   @param args List of args.  Not examined.
   @return Always returns 1, to continue executing.
 */
int lsh_help(char **args)
{
	int i;
	printf("Geoni Griffin's basic shell based on Stephen Brennan's LSH\n");
	printf("Type program names and arguments, and hit enter.\n");
	printf("The following are built in:\n");

	for (i = 0; i < lsh_num_builtins(); i++) {
		printf("  %s\n", builtin_str[i]);
	}

	printf("Use the man command for information on other programs.\n");
	return 1;
}

/**
   @brief Builtin command: exit.
   @param args List of args.  Not examined.
   @return Always returns 0, to terminate execution.
 */
int lsh_exit(char **args)
{
	return 0;
}



char *combine(char *path , char *com ){
	int index;
	int size1 =0;

	for(index = 0 ; path[index] != 0; index++){
		size1++;
	}

	int size2 =0;
	for(index = 0 ; com[index] != 0; index++){
		size2++;
	}

	char * modpath = malloc((sizeof(char) * (size1+size2+1 )));

	modpath[size1] = '/';

	for(index = 0; index < size1; index++){
		modpath[index] = path[index];
	}


	for(index = 0; index + size1+1 <= size1+size2+1; index++){
		modpath[index + size1+1] = com[index];
	}


	return modpath;

}

/**
  @brief Launch a program and wait for it to terminate.
  @param args Null terminated list of arguments (including program).
  @return Always returns 1, to continue execution.
 */


int lsh_launch(char **args, char **paths, char** envp)
{
	pid_t pid;
	int status;
	int success = 0;

	pid = fork();
	if (pid == 0) {
		// Child process
		 success = execve(args[0], args, envp);

		int index;

		for(index = 0; paths[index] != 0; index++ ){

			char * path;

			path = combine(paths[index], args[0]);

			success = execve(path, args, envp);

		}

		if(success == -1) {
			perror("lsh");
		}
		exit(EXIT_FAILURE);



	} else if (pid < 0) {
		// Error forking
		perror("lsh");
	} else {
		// Parent process
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}



	return 1;
}

/**
   @brief Execute shell built-in or launch program.
   @param args Null terminated list of arguments.
   @return 1 if the shell should continue running, 0 if it should terminate
 */
int lsh_execute(char **args, char **paths, char** envp)
{
	int i;

	if (args[0] == NULL) {
		// An empty command was entered.
		return 1;
	}

	for (i = 0; i < lsh_num_builtins(); i++) {
		for(int j = 0 ; args[j] != 0; j++)
		{
			if (compareStr(args[j], builtin_str[i]) == 1) {
				return (*builtin_func[i])(args);}
		}

	}

	return lsh_launch(args, paths, envp);
}

#define LSH_RL_BUFSIZE 1024
/**
   @brief Read a line of input from stdin.
   @return The line from stdin.
 */
char *lsh_read_line(void)
{

	char *line = malloc(sizeof(char) * 512);


	int size = read(0, line, 512 );

	line[size-1] = '\0';


	return line;

}

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
/**
   @brief Split a line into tokens (very naively).
   @param line The line.
   @return Null-terminated array of tokens.
 */




/**
   @brief Loop getting input and executing it.
 */
void lsh_loop(char **paths, char** envp)
{
	char *line;
	char **args;
	int status;



	do {
		write(0 , "$ ", 2);

		line = lsh_read_line();

		args = mytoken(line, ' ');

		int x = 0;

		status = lsh_execute(args , paths, envp);

		free(line);
		free(args);


	} while (status);
}



char **getPaths(char** envp) {
	char** paths;
	char* path = "PATH";
	char delim = '=';
	int index = 0;
	int compare = 0;
	// Load config files, if any.
	while (!compare) {
		char** keys = mytoken(envp[index], delim);
		if (keys[0] != 0) {
			if (compareStr(keys[0], path)) {
				paths = mytoken(keys[1], ':');
				//printf("\n  Printed the word %s \n", keys[1]);
				compare = 1;
			}
		}
		index++;
	}
	return paths;

}



/**
   @brief Main entry point.
   @param argc Argument count.
   @param argv Argument vector.
   @param envp Environment variables.
   @return status code
 */
int main(int argc, char **argv, char **envp)
{

	paths = getPaths(envp);

	// Run command loop.
	lsh_loop(paths, envp);

	// Perform any shutdown/cleanup.

	return EXIT_SUCCESS;
}

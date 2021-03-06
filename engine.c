//This file is redesigning the way the engine works, so that it doesn't rely on separate executables, even if it's modular and possible to get into the nmemory for each and do just fine, it's a hassle.
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> /*for the time n shit */
#include <string.h> //remember strings.h is for openbsd
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#define MAX_INPUT_SZ 256 /*Maximum name size +1*/
#define MAX_DEC_SZ 2  /*Maximum decision size +1*/
#define MAX_STR_SZ 256 /*MAXIMUM string size +1 and yes I know that it's the same as the input size but I want there to be a difference*/
#define MAX_FILEC_SZ 256 /*Maximum string size +1, this is for the file content, character size*/
//the path to the directory is (~)/.config/eco/
//profiles in the blank text file which holds the information
void execo(char *name, char *path, char *input) //name is the name of executable that is going to execute, path is the full path to the name, and input is any arguments
{
	//printf("%s\n", path);
	pid_t pid;
 	 int status;
  	pid_t ret;
  	char *const args[3] = {name, input, NULL}; 
  	char **env;
  	extern char **environ;
 
  	/* ... Sanitize arguments ... */
 
  	pid = fork();
  	if (pid == -1) 
	{
    		/* Handle error */
  	} 
	else if (pid != 0) 
	{
    		while ((ret = waitpid(pid, &status, 0)) == -1) 
		{
      			if (errno != EINTR) 
			{
        			/* Handle error */
        			printf("There is a fucking error with the PID.\n");
				break;
      			}
    	}
    	if ((ret != -1) && (!WIFEXITED(status) || !WEXITSTATUS(status)) ) 
	{
      		/* Report unexpected child status */
      		printf("Unexpected child process or some shit.\n");
    	}
  	} 
	else 
	{
    		/* ... Initialize env as a sanitized copy of environ ... */
    		if (execve(path, args, env) == -1)
		{
      			/* Handle error */
			printf("Holy shit there is an error with a sanitized copy of the environment.\n");
      			_Exit(127);
    		}
  	}

}
void init()
{

}
void business(int money) //this money is special because the bank took much of the original money so it's given to the business
{

}

void bank(int money) //essentially raw money
{
//control how much money is taken, if the business isn't doing their quota or shit to the yada yada yada shit and like fucking do shitisnfjo]phdiodehfvio
}

int main(int argc, char *argv[])
{
//the main is the money, it will go into the bank, and the business will read
//remember & before declared variables or some shit, it's somewhere on stack overflow so remember
//const char *<variable> = "<stuff>" is how to get a string, check to see if const is required
	const char *name = "HOME"; //sets the variable that getenv() will find, it's the environmental variable that it looks for
	char *home;
	char *configp; //this is the config path, but allow the user to change this
	char *configpf; //this is the config pile path
	char *dec = malloc (MAX_DEC_SZ); //can't do case statement or something because it's a string
	char *initp; //init path
	home = getenv(name); 
	if (home == NULL)
	{
		printf("Why the fuck are you using this program without a home directory?\n");
		exit(1);
	}
	asprintf(&configp, "%s/.config/eco/", home);
	asprintf(&configpf, "%s/.config/eco/.profiles", home); //this line needs to exist because chdir doesn't account files
	asprintf(&initp, "%s/Documents/tests/redesign/init.sh", home); //temporary
	//printf("%s\n", initp);
	if (chdir(configp) == -1)
	{
		//printf("%s\n", configp);
		printf("It appears this is either the first time you are using this, or something really bad happened to your home directory.\nDo you want to create the directory %s? y n (Will default to no if not yes, no Exits) ", configp); //this assumes that the user didn't just delete the config
		fgets(dec, MAX_DEC_SZ, stdin);
		if ((strlen(dec) > 0 && (dec[strlen (dec) -1]) == '\n'))
		{
			dec[strlen(dec) - 1] = '\0';
		} 
		if (strcmp(dec, "y") == 0)
		{
			//this file needs to soon implement the functions that shell script is doing for maximum portability
		 	printf("Calling the initilization script...\n"); 
			execo("init.sh", initp, ""); //it may seem redundant, but the execo function needs  like a single name and then the path, like i could just reduce it down to 2 arguments and  pass through the path and then do all the work in the function but like, i don't want to do that right now, by the way, this init shell script is essentially useless. I mean it's useful, but like it's not like it can't be done in c easily 
		}
		else
		{
			//make this so that the user is able to go into a temporary profile in memory, also make that an option at the very start
			printf("Exiting program...\n"); 
			exit(1);
		}
		
	}
	if (argc > 1) //this will change to something more elegant
	{
		printf("Usage: %s\n", argv[0]);
	}
	else
	{
		/* 
		This file is supposed to look like:
		example:
		profilename;directory
		happy;/home/faggot/.config/eco/happy/
		shithead;/home/asshead/Documents/shit/
		wow;/tmp/imafaggotforthisfolderbeinghere
		*/
		//store the numbers in row 0
		//store the profilename in row 1
		//store the directory in row 2
		char *store[2][100]; //0-99;  row 0 is the name, row 1 is the path
		printf("Select a profile. Press n to make a new one. Press d to delete one.\n");
		/*this next part checks to see if anything is in the file*/
		//it currently doesn't do that
		char c = getchar();
		char *name = NULL;
		char *path = NULL;
		char dpath[256]; //max + 1, this will eventually get merged with the one above
		size_t len = 0;
		ssize_t read;
		FILE *f = fopen(configpf, "a+"); //yes a+ kind of makes it unecessary for the the init.sh, but like I need that write append and read and no file length truncate, I think for the latter 
		if (!f)
		{
			printf("For some fucking reason, the file can't be opened.");	
		}
		else 
		{
			//parsing but like, the way that fprintf is working, going to a new line in all, a new method needs to be developed to parse the file https://cboard.cprogramming.com/c-programming/68741-how-can-i-parse-data-file.html
			switch(c) //behavior is weird inside case statements
			{
				case 'n': 
					printf("Enter the name of the new profile: ");
					while ((read = getline(&name, &len, stdin)) != -1) 
					{
						if (read > 1)
						{	
							fprintf(f,"%s", name);
							break;
						}
						//i am aware that the prompt doesn't print again after each iteration, but for some fucking reason, the thing prompts twice when pressing enter on a character, it's retarded, switch statements are retarded
						//propably this is going to be replaced with scanf then from that to fgets(), you know what fuck it, just straight to fgets() https://blog.udemy.com/fgets-in-c/
					}
					free(name);					 
                                        printf("Enter the path which you wish to store your profile: ");
					while ((read = getline(&path, &len, stdin)) != -1)
					{
						if (read > 1)
						{
							fprintf(f,"%s", path);
							break;
						}
					}
					free(path);
					break;
				case 'd':
					printf("Enter the name of the profile you wish to delete: ");
					//fgets(dpath, 256,stdin);
					deletep(dpath);
					printf("Are you sure?");
					break;
			}
			
			fclose(f);
		}	
	}
	return 0;
}


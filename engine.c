//This file is redesigning the way the engine works, so that it doesn't rely on separate executables, even if it's modular and possible to get into the nmemory for each and do just fine, it's a hassle.
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> /*for the time n shit */
#include <string.h> //remember strings.h is for openbsd
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_INPUT_SZ 256 /*Maximum name size +1*/
#define MAX_DEC_SZ 2  /*Maximum decision size +1*/
#define MAX_STR_SZ 256 /*MAXIMUM string size +1 and yes I know that it's the same as the input size but I want there to be a difference*/
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
		number profilename directory
		1 happy	/home/faggot/.config/eco/happy/
		2 shithead /home/asshead/Documents/shit/
		3 wow /tmp/imafaggotforthisfolderbeinghere
		*/
		//store the numbers in row 0
		//store the profilename in row 1
		//store the directory in row 2
		char store[3][100]; //0-99
		printf("Select a profile. Press n to make a new one\n");
		/*this next part checks to see if anything is in the file*/
		//it currently doesn't do that
		int c = 0;
		char *d; //change to regular char if needed
		char str[MAX_STR_SZ];
		FILE *f = fopen(configpf, "a+"); 
		if (!f)
		{
			printf("For some fucking reason, the file can't be opened.");	
		}
		else 
		{
			//these may not seem necessary, but it is if you want to detect numbers
			int l = 0; //char string identifier
			int p = 0; //path string identifier
			int i = 0; //iterator
			//int y = 0; //iterator
			//int z = 0; //iterator
			while ((c = getc(f)) != EOF)
			{
				//make the l the integer boolean
				//HOLY FUCKING SHIT, IF INT DOESN'T GO INTO THE CHAR *STORE THEN JUST CONVERT THE FUCKING NUM TO CHAR* OR SOME SHIT BUT THEN WHEN YOU GET IT BACK OUT IT'S ALL FINE AND DANDY AND INT
				//if (c != ' ' && c != '/')
				//{
					putchar(c);		
				//}
				if (isdigit(c) && l == 0 && p == 0) //where the integer booleans are useful, except yes you could start a counter and if it's not 1 then that's the end of the numbers, but that doesn't account for multiple numbers
				{
					store[0][i] = c; 
				}
				if (c == ' ' && l == 0)
				{
					l = 1; //this now means that any char from now will be inputted into a string
					i = 0; //this can be here because the next iteration it's going into the if statement below
					//no store because who wants a space?
				}
				if (c != ' ' && l == 1)
				{
					str[i] = c;
				}
				if (c == ' ' && l == 1) //could be else, but i don't want to test now
				{
					i = 0; //so that the string can be put into the array, but most likey, there is incompatible types
					l = 0; //this now means that the char string is now ended
					store[1][i] = str;
					memset(str, 0, MAX_STR_SZ); //resets the shits to 0 for future shits
				}
				if (c == '/' && l == 0)
				{
					p = 1; //this now means that any char from now will be inputted into a string
				}
				if (c == '\r' && l == 0 && p == 1)
				{
					p = 0;
				}
				//if (l == 1 || ) //but like one that iteration, there would be characters that are going into into whatever iteration the previous is at
				i++;
			}
			fclose(f);
			printf("%c\n", store);
			//I know how much it sucks to have the following system, but I don't know how to fix, yet 
			/*
			while ((c = getc(f)) != EOF)	
			{
				printf("asdasd");
				if(isdigit(c))
				{
					//putchar(c);
					store[0][i] = c; //just note to properly access these values you need to have a for loop
					printf("%s\n", store[0][i]);
				}
				i++;
			}
			i = 0;
			while ((c = getc(f)) != EOF)
			{
				if (c == ' ' && l == 0)
				{
					//store[
				}
				i++;
			}
			fclose(f);	
			*/
		}
		//printf("%d\n", store[0][0]);
		//fgets(d, MAX_DEC_SZ, stdin);
                //if ((strlen(d) > 0 && (d[strlen (d) -1]) == '\n'))
                //{
                //        d[strlen(d) - 1] = '\0';
                //}
		//if () 
		//scanf("%c", d); 
		//switch(d)
		//{
		//	case
		//	default: printf("Creating new profile: "); 
		//}
		
	}
	return 0;
}

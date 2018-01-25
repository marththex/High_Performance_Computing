#include<iostream>
#include<string.h>
#include<cstdlib>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <unistd.h>
#include <vector>

using namespace std;

int main(int argc, char ** argv)
{
  while ( true )
  {
    // Print the command prompt.
    cout << getcwd(NULL, 0) << ">> " << flush;
    char command[128];
    cin.getline( command, 128 );

	//parse the characters with " " being the delimiter
    vector<char*> args;
    char* prog = strtok( command, " " );
    char* tmp = prog;
    while ( tmp != NULL )
    {
      args.push_back( tmp );
      tmp = strtok( NULL, " " );
    }
	
	//puts the parsed string vector into an argv array 
    char** argv = new char*[args.size()+1];
    for ( int k = 0; k < args.size(); k++ )
	{
      argv[k] = args[k];
	}

	//makes the last index of the argv array NULL
    argv[args.size()] = NULL;

	// if user wants to exit the shell
    if ( strcmp( command, "exit" ) == 0 ) 
    {
      return 0;
    }
	
	//else, start the fork process
    else
    {
      pid_t pid = fork();
      if ( pid < 0 )
      {
        perror( "Internal error: cannot fork." );
        return -1;
      }
	  
      else if ( pid == 0 )
      {
        // Child Process
		
		//if the command is change directory
		if (!strcmp(argv[0], "cd"))
		{
			return 0;
			
		}
		//executes the command
        execvp( prog, argv );
		
        // The following lines should not happen (normally).
        perror( command );
        return -1;
      }
      else
      {
        // Parent Process
		
		//if the command is change directory
		if (!strcmp(argv[0], "cd"))
		{
			chdir(argv[1]);	
		}
		//Waits for the Child Process
        if ( waitpid( pid, 0, 0 ) < 0 )
        {
          perror( "Internal error: cannot wait for child." );
          return -1;
        }
      }
    }
  }

  return 0;
}
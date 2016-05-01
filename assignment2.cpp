#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "assignment2head.h"
using namespace std;


int main()
{
  Base *command_pointer = new CompositeCommand;
  int status = 0;
  int e = 0;
  char connector;
  bool ex_result;
  char **analyzed = new char*[256];
  char **analyzed2 = new char*[256];

  					
  while(true)
  {
    cout << "$ ";   
    command_pointer->get();
    if(command_pointer->check_if_exit() == "exit")
    {
	    cout << "Now exiting shell" << endl;
	    exit(1);
    }
    command_pointer->analyze(analyzed);                    

    for (int i = 0; analyzed[i] != NULL; i++)
    {
      if (*analyzed[i] == ';')
      {
        ex_result = command_pointer->execute(analyzed2);
        delete [] analyzed2;
        analyzed2 = new char*[256];
        e = 0;
      }
      else if (*analyzed[i] == '&')
      {
        ex_result = command_pointer->execute(analyzed2);
        delete [] analyzed2;
        analyzed2 = new char*[256];
        e = 0;
        if (!ex_result)
		{
			break;
		}
      }
      else if (*analyzed[i] == '|' )
      {
        ex_result = command_pointer->execute(analyzed2);
        delete [] analyzed2;
        analyzed2 = new char*[256];
        e = 0;
        if (ex_result)
		{
			break;
		}
      }
      else
      {
        analyzed2[e] = analyzed[i];
        e++;
        analyzed2[e] = NULL;
      }
    }
    if (e > 0)
	{
		command_pointer->execute(analyzed2);
	      	delete [] analyzed2;
		analyzed2 = new char*[256];
	        e = 0;	
	}	
  }

  return 0;
}

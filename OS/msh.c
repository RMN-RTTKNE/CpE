// The MIT License (MIT)
// 
// Copyright (c) 2023 Trevor Bakker 
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

//Roman Rattanakone, 1002097957

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>

#define WHITESPACE " \t\n"      // We want to split our command line up into tokens
                                // so we need to define what delimits our tokens.
                                // In this case  white space
                                // will separate the tokens on our command line

#define MAX_COMMAND_SIZE 128    // The maximum command-line size

#define MAX_NUM_ARGUMENTS 10     // Mav shell currently supports ten arguments

static void handle_signal(int sig)
{
  //Handle CTRL + C and CRTL + Z by doing nothing
}

void execution(char **token, int token_count)   //Where non-built in commands are executed
{
  int piped = 0;
  int oredirect = 0;
  int iredirect = 0;
  for(int i = 1; i < token_count; i++)          //Check the parsed line for redirects or pipes and set flags accordingly
  {
      if (token[i] == NULL) 
      {
        continue;
      }
      if(strcmp(token[i], ">") == 0)
      {
        oredirect = 1;
      }
      if(strcmp(token[i], "<") == 0)
      {
        iredirect = 1;
      }
      if(strcmp(token[i], "|") == 0)
      {
        piped = 1;
      }
  }

  if(oredirect)                                  //If > is found, output the command to a file
  {
    pid_t pid = fork();
    if(pid == 0) 
    {
      for(int i = 1; i < token_count; i++)      //Again, locating the >
      {
        if (token[i] == NULL) 
        {
          continue;
        }
        if(strcmp(token[i], ">") == 0)          //Once found, use the following token to create/open the file as output, replacing STDOUT
        {
          int fd = open(token[i + 1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR );      
          if(fd < 0)
          {
            perror( "Can't open output file." );
            exit(1);                    
          }
          dup2(fd, 1);                                                          
          close(fd);

          token[i] = NULL;                      //Trim the > for execvp
        } 
      }
      int valid = execvp(token[0], token);      //The command is executed, with the output now set to the specified file
      if(valid == -1)
      {
        printf("%s: Command not found\n", token[0]);
        exit(1);
      }
    }
    else if(pid > 0)
    {
      wait(NULL);
    }
    else 
    {
      perror("fork fail");
    }
  }

  else if(iredirect)                              //If < is found, input the file to the command
  {
    pid_t pid = fork();
    if(pid == 0) 
    {
      for(int i = 1; i < token_count; i++)        //Again, searching for <
      {
        if (token[i] == NULL) 
        {
          continue;
        }
        if(strcmp(token[i], "<") == 0)            //Once found, use the following token to open the file as input, replacing STDIN
        {
          int fd = open(token[i + 1], O_RDONLY);  //It can be noted that it is opened in read only, as it is input
          if(fd < 0)
          {
            perror( "Can't open input file." );
            exit(1);                    
          }
          dup2(fd, 0);
          close(fd);

          token[i] = NULL;                        //trim < for execvp
        } 
      }
      int valid = execvp(token[0], token);        //Command is executed with the input file specified by the token following <
      if(valid == -1)
      {
        printf("%s: Command not found\n", token[0]);
        exit(1);
      }
    }
    else if(pid > 0)
    {
      wait(NULL);
    }
    else
    {
      perror("Fork failed");
    }
  }

  else if(piped)                                 //If | is found, set the output of one command to the input of another
  {
    for(int i = 1; i < token_count; i++)
    {
      if (token[i] == NULL) 
      {
        continue;
      }
      if(strcmp(token[i], "|") == 0)             //Locate the pipe, then keep track of the right side of the pipe
      {
        token[i] = NULL;
        char **arg2 = &token[i + 1];             //arg2 is the right side of the pipe

        pid_t pid1 = fork();                     //fork once
        if(pid1 == 0 )
        {
          int pfds[2];
          pipe(pfds);

          int pid = fork();                      //fork off the previous fork
          if(pid == 0)
          {
            close(STDOUT_FILENO);                //The STDOUT of the leftside is closed
            dup(pfds[1]);                        //Redirect the write
            close(pfds[0]);                      //No need to read from the left

            int valid = execvp(token[0], token); //Execute the left side
            if(valid == -1)
            {
              printf("%s: Command not found\n", token[0]);
              exit(1);
            }
          }
          else
          {
            close(STDIN_FILENO);                //In the parent of the previous fork, close STDIN of the right side of pipe
            dup(pfds[0]);                       //Redirect the read
            close(pfds[1]);                     //No need to write from the right

            int valid = execvp(arg2[0], arg2);  //Execute right side
            if(valid == -1)
            {
              printf("%s: Command not found\n", arg2[0]);
              exit(1);
            }
          }
        }
        else
        {
          int status;
          wait(&status);
        }
      } 
    }
  }
  else                                          //If command does not have pipe or redirect, fork/execute normally
  {
    pid_t pid = fork();
    if(pid == 0) 
    {
      int valid = execvp(token[0], token);
      if(valid == -1)
      {
        printf("%s: Command not found\n", token[0]);
        exit(1);
      }
    }
    else 
    {
      int status;
      wait(&status);
    }
  }
}
int main()
{
  char *hist[50];
  int num_hist = 0;
  char * command_string = (char*) malloc( MAX_COMMAND_SIZE );

  struct sigaction act;
  memset(&act, '\0', sizeof(act));               //Zero out the sigaction struct
  act.sa_handler = &handle_signal;               //Set the handler to our custom handler
  if (sigaction(SIGINT , &act, NULL) < 0)        //Check and install the handler
  {
    perror ("sigaction: ");     
    return 1;
  }
  if (sigaction(SIGTSTP , &act, NULL) < 0)      //Check and install the handler
  {
    perror ("sigaction: ");
    return 1;
  }

  while( 1 )
  {
    // Print out the msh prompt
    printf ("msh> ");

    // Read the command from the commandline.  The
    // maximum command that will be read is MAX_COMMAND_SIZE
    // This while command will wait here until the user
    // inputs something since fgets returns NULL when there
    // is no input
    while( !fgets (command_string, MAX_COMMAND_SIZE, stdin) );

    if(command_string[0] == '\n')         //If the input is just a new line, do nothing and start the next iteration.
    {
      continue;
    }
    if(num_hist < 50)                     //Fill our history array. If there are less than 50 commands, simply duplicate the input string into the array. 
    {                                     
      hist[num_hist] = strdup(command_string);
      num_hist++;
    }
    else if(num_hist >= 50)               //If there are more than 50 previously saved commands, then free the first/latest command, 
    {                                     //and shift array by -1 to make room for the newest command. The newest command then gets placed in the newly freed 50th index.
      free(hist[0]);
      for(int i = 1; i < 50; i++) 
      {
        hist[i-1] = hist[i];
      }
    }
    else
    {
      printf("Error with history");
      exit(1);
    }
    /* Parse input */
    char *token[MAX_NUM_ARGUMENTS];

    for( int i = 0; i < MAX_NUM_ARGUMENTS; i++ )
    {
      token[i] = NULL;
    }

    int   token_count = 0;                                 
                                                           
    // Pointer to point to the token
    // parsed by strsep
    char *argument_ptr = NULL;                                         
                                                           
    char *working_string  = strdup( command_string );                

    // we are going to move the working_string pointer so
    // keep track of its original value so we can deallocate
    // the correct amount at the end
    char *head_ptr = working_string;

    // Tokenize the input strings with whitespace used as the delimiter
    while ( ( (argument_ptr = strsep(&working_string, WHITESPACE ) ) != NULL) && 
              (token_count<MAX_NUM_ARGUMENTS))
    {
      token[token_count] = strndup( argument_ptr, MAX_COMMAND_SIZE );
      if( strlen( token[token_count] ) == 0 )
      {
        token[token_count] = NULL;
      }
        token_count++;
    }

    if(strcmp(token[0], "exit") == 0 || strcmp(token[0], "quit") == 0)      //If input is quit or exit, quit the shell
    {
      exit(1);
    }
    else if(strcmp(token[0], "cd") == 0)                      //If input is cd, change the directory to the path specified by the second token
    {
      chdir(token[1]);
    }
    else if(strcmp(token[0], "history") == 0)                 //If input is history, print the history array
    {
      for(int i = 0; i < num_hist; i++)
      {
        printf("[%d] %s", i + 1 , hist[i]);
      }
    } 
    else if(token[0][0] == '!')                              //If !index is entered, retrieve the index of the history command, then retokenize it to run it again
    {
      int index = atoi(&token[0][1]);
      index--;
      char *hist_token[MAX_NUM_ARGUMENTS];
      for( int i = 0; i < MAX_NUM_ARGUMENTS; i++ )
      {
        hist_token[i] = NULL;
      }
      int hist_token_count = 0;
      while ( ( (argument_ptr = strsep(&hist[index], WHITESPACE ) ) != NULL) && 
                (hist_token_count<MAX_NUM_ARGUMENTS))
      {
        hist_token[hist_token_count] = strndup( argument_ptr, MAX_COMMAND_SIZE );
        if( strlen( hist_token[hist_token_count] ) == 0 )
        {
          hist_token[hist_token_count] = NULL;
        }
          hist_token_count++;
      }
      if(strcmp(hist_token[0], "exit") == 0 || strcmp(hist_token[0], "quit") == 0)      //If input is quit or exit, quit the shell
      {
        exit(1);
      }
      else if(strcmp(hist_token[0], "cd") == 0)                      //If input is cd, change the directory to the path specified by the second token
      {
        chdir(hist_token[1]);
      }
      else if(strcmp(hist_token[0], "history") == 0)                 //If input is history, print the history array
      {
        for(int i = 0; i < num_hist; i++)
        {
          printf("[%d] %s", i + 1 , hist[i]);
        }
      } 
      else
      {
      execution(hist_token, hist_token_count);
      }
    }
    else                                                   //If not built in command, check for pipe/redirect and then call execvp
    {
      execution(token, token_count);
    }
    
  
    free( head_ptr );

  } 

  free( command_string );

  return 0;
  // e1234ca2-76f3-90d6-0703ac120004
  
}

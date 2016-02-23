#include <stdio.h>
#include <string.h>
#include "Report.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define IN_FD 3
#define BUF_SIZE 32
#define ARGS 12
#define CHAR_SIZE sizeof(char)

typedef struct {
   int id;
   int pid;
   int steps;
   int inFD;
   int outFD;
   int cellNum;
   Report report;
   double firstCell;
   double lastCell;
   int in[2];
   int out[2];
   int rep[2];
} LinearSim;


//gets initial input and program
void Init(LinearSim *ls, char **argv) {
   char *input;
   int right = 0;
   
   argv++;
   ls->in[0] = ls->in[1] = -1;
   ls->out[0] = ls->out[1] = -1;
   ls->rep[0] = ls->rep[1] = -1;
   ls->steps = ls->cellNum = 0;
   ls->inFD = ls->outFD = -1;
   ls->firstCell = ls->lastCell = 0;

   while ((input = (*argv))) {
      if (ls->firstCell == 0 && *input == 'L')
         sscanf(input + 1, "%lf", &ls->firstCell);
      else if (ls->lastCell == 0 && *input == 'R') {
         sscanf(input + 1, "%lf", &ls->lastCell);
         right = 1;
      }

      else if (ls->steps == 0 && *input == 'S')
         sscanf(input + 1, "%d", &ls->steps);
      else if (ls->cellNum == 0 && *input == 'C')
         sscanf(input + 1, "%d", &ls->cellNum);
       
      argv++;
   }
       
   if (ls->steps == 0 || ls->cellNum == 0) {
      fprintf(stderr, "Usage: LinearSim C S L R (in any order)\n");
      exit(EXIT_FAILURE);
   }
   if (ls->cellNum == 1 && right) {
      fprintf(stderr, "Usage: LinearSim C S L R (in any order)\n");
      exit(EXIT_FAILURE);
   }
}


void GetString(char **input, char *format, int val) {
   *input = calloc(1, BUF_SIZE + 1);
   sprintf(*input, format, val);
}

void GetStringDouble(char **input, char *format, double val) {
   *input = calloc(1, BUF_SIZE + 1);
   sprintf(*input, format, val);
}

//get arguments for the cell
char **GetExecArgs(int st, int out1, int out2, int out3, int in1,
 int in2, double val, int id) {
   char **args, **temp;

   //create array of arg strings
   args = temp = calloc(ARGS, sizeof(char *));
   *temp++ = "./Cell";
   GetString(temp++, "S%d", st);

   if (out1 != 0) {
      GetString(temp++, "O%d", out1);
      if (out2 != 0) {
         GetString(temp++, "O%d", out2);
         if (out3 != 0) {
            GetString(temp++, "O%d", out3);
         }
      }
   }
   
   if (in1 != 0) {
      GetString(temp++, "I%d", in1);
      if (in2 != 0) {
         GetString(temp++, "I%d", in2);
      }
   }

   GetStringDouble(temp++, "V%.3lf", val);
   GetString(temp, "D%d", id);
   
   return args;
}


void FormCell(LinearSim ls) {
   char **args;

   if (ls.id == 0) {
      args = GetExecArgs(ls.steps, ls.out[1], ls.rep[1], 0,
       0, 0, ls.firstCell, ls.id);
      close(ls.out[0]);
      close(ls.in[0]);
      close(ls.in[1]);
   }
   else if (ls.id > 0 && ls.id < ls.cellNum - 1) {
      close(ls.in[1]);
      close(ls.out[0]);

      if (ls.id == 1 && ls.id < ls.cellNum - 2)
         args = GetExecArgs(ls.steps, ls.out[1], ls.rep[1], -1,
          ls.inFD, ls.in[0], 0, ls.id);

      else if (ls.id >= 1 && ls.id == ls.cellNum - 2) {
         args = GetExecArgs(ls.steps, ls.outFD, ls.rep[1], 0,
          ls.inFD, ls.in[0], 0, ls.id);
         close(ls.out[1]);
      }      

      else if (ls.id > 1 && ls.id < ls.cellNum - 2)
         args = GetExecArgs(ls.steps, ls.out[1], ls.outFD, ls.rep[1],
          ls.inFD, ls.in[0], 0, ls.id);
   }
   else {
      close(ls.inFD);
      args = GetExecArgs(ls.steps, ls.outFD, ls.rep[1], 0, 
       0, 0, ls.lastCell, ls.id);
   }
   close(ls.rep[0]);
   execvp("./Cell", args);
}

int FindId(int *arr, int pid) {
   int id = 0;

   while (arr[id] != pid)
      id++;
   
   return id;
}

void MainLoop(LinearSim ls, int *arr) {
   ls.id = 0;
   while (ls.id < ls.cellNum) {
   
      //if id is not equal to end
      if (ls.id != ls.cellNum - 1 && ls.cellNum != 2) {
         pipe(ls.out);
         pipe(ls.in);
      }
  
      if ((ls.pid = fork()) == -1) {
         fprintf(stderr, "Bad fork call\n");
      }
      else if (ls.pid > 0) {
         if (ls.id == 0) {
            close(ls.in[0]);
            close(ls.out[1]);
            close(ls.in[1]);
            ls.inFD = ls.out[0];
         }
         else if (ls.id < ls.cellNum - 1 && ls.id > 0) {
            close(ls.inFD);
            close(ls.outFD);
            ls.inFD = ls.out[0];
            ls.outFD = ls.in[1];
            close(ls.in[0]);
            close(ls.out[1]);
         }
         else {
            close(ls.outFD);
            close(ls.inFD);
         }
         arr[ls.id] = ls.pid;
      }
      else
         FormCell(ls);
      ls.id++;
   }

}


//main method
int main(int argc, char **argv) {
   LinearSim ls;
   int count, status, *arr, *reparr;
   int less = 0;
   int more = 0;
   int run = 0;
   int run2 = 0;
   int ret = EXIT_SUCCESS;

   Init(&ls, argv);
   pipe(ls.rep);
   arr = calloc(sizeof(int), ls.cellNum);
   reparr = calloc(sizeof(int), ls.cellNum);
   
   MainLoop(ls, arr);
   close(ls.rep[1]);
   
   while (read(IN_FD, &(ls.report), sizeof(Report))) {
      printf("Result from %d, step %d: %.3lf\n",
       ls.report.id, ls.report.step, ls.report.value);
      reparr[ls.report.id] += 1;
   }
   
   //checks if too many or too few reports ran
   for (count = ls.cellNum - 1; count >= 0; count--) {
      if (reparr[count] > ls.steps + 1)
         more++;
      if (reparr[count] < ls.steps + 1)
         less++;
   }
   
   if (less) {
      fprintf(stderr, "Error: %d cells reported too few reports\n",
       less);
      ret = EXIT_FAILURE;
   }
   if (more) {
      fprintf(stderr, "Error: %d cells reported too many reports\n",
       more);
      ret = EXIT_FAILURE;
   }
   while (ls.cellNum--) {
      run = FindId(arr, wait(&status));
      run2 = status;
      if (run2) {
         fprintf(stderr, "Error: Child %d exited ", run);
         fprintf(stderr, "with %d\n", run2);
         ret = EXIT_FAILURE;
      }
   }
   
   close(ls.rep[0]);
   free(arr);
   free(reparr);
   
   return ret;
}

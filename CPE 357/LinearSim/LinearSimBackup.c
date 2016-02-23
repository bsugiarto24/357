#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "Report.h"

#define IN_FD 3
#define BUF_SIZE 30
#define EXEC_CELL "./Cell"
#define MAX_ARGS 12
#define CHAR_SIZE sizeof(char)

typedef struct {
   int id;
   int steps;
   int inFD;
   int outFD;
   int numCells;
   double firstCell;
   double lastCell;
   int in[2];
   int out[2];
   int rep[2];
} LinearSim;


//gets initial input and program
void init(LinearSim *ls, char **argv) {
   char *input;
   int rightFlag = 0;
   
   argv++;
   ls->steps = ls->numCells = -1;
   ls->inFD = ls->outFD = -1;
   ls->in[0] = ls->in[1] = -1;
   ls->out[0] = ls->out[1] = -1;
   ls->rep[0] = ls->rep[1] = -1;

   while (input = *argv) {
      if (*input == 'L')
         sscanf(input + 1, "%lf", &ls->firstCell);
      else if (*input == 'R') {
        sscanf(input + 1, "%lf", &ls->firstCell);
         rightFlag = 1;
      }
     
      else if (*input == 'S')
         sscanf(input + 1, "%d", &ls->steps);
      else if (*input == 'C')
         sscanf(input + 1, "%d", &ls->numCells);
       
      argv++;
   }
       
   if (ls->steps == -1 || ls->numCells == -1) {
      printf("Usage: LinearSim C S L R (in any order)");
      exit(0);
   }
   if (ls->numCells == 1 && rightFlag) {
      printf("Usage: LinearSim C S L R (in any order)");
      exit(0);
   }

}


//get arguments for the cell
char **CellArg(int steps, int out1, int out2, int out3, int in1,
 int in2, double value, int id) {
   char buffer[BUF_SIZE], **args, **temp;

   temp = args = calloc(MAX_ARGS, sizeof(char *));
   *temp++ = EXEC_CELL;

   if (steps > 0) {
      sprintf(buffer, "S%d", steps);
      *temp = calloc(strlen(buffer) + 1, sizeof(char));
      strcpy(*temp++, buffer);
   }
   if (out1 > 0) {
      sprintf(buffer, "O%d", out1);
      *temp = calloc(strlen(buffer) + 1, sizeof(char));
      strcpy(*temp++, buffer);
   }
   if (out2 > 0) {
      sprintf(buffer, "O%d", out2);
      *temp = calloc(strlen(buffer) + 1, sizeof(char));
      strcpy(*temp++, buffer);
   }
   if (out3 > 0) {
      sprintf(buffer, "O%d", out3);
      *temp = calloc(strlen(buffer) + 1, sizeof(char));
      strcpy(*temp++, buffer);
   }
   if (in1 > 0) {
      sprintf(buffer, "I%d", in1);
      *temp = calloc(strlen(buffer) + 1, sizeof(char));
      strcpy(*temp++, buffer);
   }
   if (in2 > 0) {
      sprintf(buffer, "I%d", in2);
      *temp = calloc(strlen(buffer) + 1, sizeof(char));
      strcpy(*temp++, buffer);
   }
  
   sprintf(buffer, "V%.3lf", value);
   *temp = calloc(strlen(buffer) + 1, sizeof(char));
   strcpy(*temp++, buffer);
   
   if (id >= 0) {
      sprintf(buffer, "D%d", id);
      *temp = calloc(strlen(buffer) + 1, sizeof(char));
      strcpy(*temp, buffer);
   }

   return args;
}


void CellCreate(LinearSim cf) {
   char **args = NULL;

   if (cf.id == 0) {
      close(cf.out[0]);
      close(cf.in[0]);
      close(cf.in[1]);

      args = CellArg(cf.steps, cf.out[1], -1, cf.rep[1],
       -1, -1, cf.firstCell, cf.id);
   }
   else if (cf.id > 0 && cf.id < cf.numCells - 1) {
      close(cf.in[1]);
      close(cf.out[0]);

      if (cf.id == 1 && cf.id < cf.numCells - 2)
         args = CellArg(cf.steps, cf.out[1], -1, cf.rep[1],
          cf.inFD, cf.in[0], 0, cf.id);

      else if (cf.id > 1 && cf.id < cf.numCells - 2)
         args = CellArg(cf.steps, cf.out[1], cf.outFD, cf.rep[1],
          cf.inFD, cf.in[0], 0, cf.id);

      else if (cf.id >= 1 && cf.id == cf.numCells - 2) {
         close(cf.out[1]);
         args = CellArg(cf.steps, -1, cf.outFD, cf.rep[1],
          cf.inFD, cf.in[0], 0, cf.id);
      }
   }
   else {
      close(cf.inFD);
      args = CellArg(cf.steps, cf.outFD, -1, cf.rep[1],
       -1, -1, cf.lastCell, cf.id);
   }
   close(cf.rep[0]);
   execvp(EXEC_CELL, args);
}


//main method
int main(int argc, char **argv) {
   int pid;
   Report report;
   LinearSim ls;

   init(&ls, argv);
   pipe(ls.rep);
   
   for (ls.id = 0; ls.id < ls.numCells; ls.id++) {
   
      //if id is not equal to end
      if (ls.id != ls.numCells - 1 && ls.numCells != 2) {
         pipe(ls.out);
         pipe(ls.in);
      }
      if ((pid = fork()) == -1) {
         fprintf(stderr, "Bad fork call\n");
      }
      else if (pid > 0) {
          if (ls.id == 0) {
           ls.inFD = ls.out[0];
           close(ls.in[0]);
           close(ls.in[1]);
           close(ls.out[1]);
         }
         else if (ls.id > 0 && ls.id < ls.numCells - 1) {

           ls.inFD = ls.out[0];
           ls.outFD = ls.in[1];
           close(ls.inFD);
           close(ls.outFD);
           close(ls.in[0]);
           close(ls.out[1]);
         }
         else {
           close(ls.outFD);
           close(ls.inFD);
         }
      }
      else
         CellCreate(ls);
   }

   close(ls.rep[1]);
   while (read(IN_FD, &report, sizeof(Report))) {
      printf("Result from %d, step %d: %.3lf\n",
      report.id, report.step, report.value);
   }

   close(ls.rep[0]);
   
   return 0;
}

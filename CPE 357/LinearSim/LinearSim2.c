#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#include "Report.h"

#define REP_IN_FD 3
#define REP_OUT_FD 4
#define BUF_SIZE 30
#define CELL_EXE "./Cell"
#define MAX_ARGS 10
#define NUM_INPUT 4

typedef struct {
   int id;
   int steps;
   int numCells;
   int inPipe[2];
   int outPipe[2];
   int repPipe[2];
   int inFD;
   int outFD;
   double firstCellVal;
   double lastCellVal;
} CellConfig;

int CellID(int *pidArr, int pid) {
   int id;

   for (id = 0; pid != pidArr[id]; id++);
   
   return id;
}

char **CellArg(int steps, int out1, int out2, int out3, int in1,
 int in2, double value, int ident) {
   char buffer[BUF_SIZE], **args, **temp;

   temp = args = calloc(MAX_ARGS, sizeof(char *));
   *temp++ = CELL_EXE;

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
   if (value >= 0) {
      sprintf(buffer, "V%.3lf", value);
      *temp = calloc(strlen(buffer) + 1, sizeof(char));
      strcpy(*temp++, buffer);
   }
   if (ident >= 0) {
      sprintf(buffer, "D%d", ident);
      *temp = calloc(strlen(buffer) + 1, sizeof(char));
      strcpy(*temp, buffer);
   }

   return args;
}

void CellConfInit(CellConfig *cf) {

   cf->inFD = -1;
   cf->outFD = -1;
   cf->inPipe[0] = cf->inPipe[1] = -1;
   cf->outPipe[0] = cf->outPipe[1] = -1;
   cf->repPipe[0] = cf->repPipe[1] = -1;

   if (NUM_INPUT != scanf("%lf %lf %d %d",
    &cf->firstCellVal, &cf->lastCellVal, &cf->steps, &cf->numCells))
      exit(0);
   if (cf->numCells == 1)
      cf->firstCellVal = cf->lastCellVal;

   pipe(cf->repPipe);
}

void CellCreate(CellConfig cf) {
   char **args = NULL;

   if (cf.id == 0) {
      close(cf.outPipe[0]);
      close(cf.inPipe[0]);
      close(cf.inPipe[1]);

      args = CellArg(cf.steps, cf.outPipe[1], -1, cf.repPipe[1],
       -1, -1, cf.firstCellVal, cf.id);
   }
   else if (cf.id > 0 && cf.id < cf.numCells - 1) {
      close(cf.inPipe[1]);
      close(cf.outPipe[0]);

      if (cf.id == 1 && cf.id < cf.numCells - 2)
         args = CellArg(cf.steps, cf.outPipe[1], -1, cf.repPipe[1],
          cf.inFD, cf.inPipe[0], -1, cf.id);

      else if (cf.id > 1 && cf.id < cf.numCells - 2)
         args = CellArg(cf.steps, cf.outPipe[1], cf.outFD, cf.repPipe[1],
          cf.inFD, cf.inPipe[0], -1, cf.id);

      else if (cf.id >= 1 && cf.id == cf.numCells - 2) {
         close(cf.outPipe[1]);
         args = CellArg(cf.steps, -1, cf.outFD, cf.repPipe[1],
          cf.inFD, cf.inPipe[0], -1, cf.id);
      }
   }
   else {
      close(cf.inFD);
      args = CellArg(cf.steps, cf.outFD, -1, cf.repPipe[1],
       -1, -1, cf.lastCellVal, cf.id);
   }
   close(cf.repPipe[0]);
   execvp(CELL_EXE, args);
}

void CellSetup(CellConfig *cf) {

   if (cf->id == 0) {
      cf->inFD = cf->outPipe[0];
      close(cf->inPipe[0]);
      close(cf->inPipe[1]);
      close(cf->outPipe[1]);
   }
   else if (cf->id > 0 && cf->id < cf->numCells - 1) {
      close(cf->inFD);
      close(cf->outFD);
      cf->inFD = cf->outPipe[0];
      cf->outFD = cf->inPipe[1];

      close(cf->inPipe[0]);
      close(cf->outPipe[1]);
   }
   else {
      close(cf->outFD);
      close(cf->inFD);
   }
}

int main(int argc, char **argv) {
   int pid, status, *pidArr;
   Report rep;
   CellConfig cf;

   CellConfInit(&cf);
   pidArr = calloc(cf.numCells, sizeof(int));

   for (cf.id = 0; cf.id < cf.numCells; cf.id++) {

      if (cf.id != cf.numCells - 1 && cf.numCells != 2) {
         pipe(cf.inPipe);
         pipe(cf.outPipe);
      }
      if ((pid = fork()) < 0) {
         fprintf(stderr, "Bad fork call\n");
      }
      else if (pid > 0) {
         pidArr[cf.id] = pid;
         CellSetup(&cf);
      }
      else
         CellCreate(cf);
   }

   close(cf.repPipe[1]);
   while (read(REP_IN_FD, &rep, sizeof(Report))) {
      printf("Result from %d, step %d: %.3lf\n",
       rep.id, rep.step, rep.value);
   }
   while (cf.numCells--) {
      printf("Child %d exits ", CellID(pidArr, wait(&status)));
      printf("with %d\n", WEXITSTATUS(status));
   }

   close(cf.repPipe[0]);
   free(pidArr);

   return 0;
}

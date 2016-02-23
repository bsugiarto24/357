#ifndef REPORT_H
#define REPORT_H

typedef struct {
   int id;       // ID of the Cell reporting
   int step;     // Time for which report is being made
   double value; // Value of the cell at time "step"
} Report;

#endif

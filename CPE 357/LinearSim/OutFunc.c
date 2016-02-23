//get arguments for the cell
char **CellArg(int steps, int firstOut, int secOut, int thirdOut, int in1,
 int in2, double value, int ident) {
   char buffer[BUF_SIZE], **args, **temp;
   int size = strlen(buffer) + 1;

   temp = args = calloc(MAX_ARGS, sizeof(char *));
   *temp++ = EXEC_CELL;

   if (steps > 0) {
      sprintf(buffer, "S%d", steps);
      *temp = calloc(size, CHAR_SIZE);
      strcpy(*temp++, buffer);
   }
   if (firstOut > 0) {
      sprintf(buffer, "O%d", firstOut);
      *temp = calloc(size, CHAR_SIZE);
      strcpy(*temp++, buffer);
   }
   if (secOut > 0) {
      sprintf(buffer, "O%d", secOut);
      *temp = calloc(size, CHAR_SIZE);
      strcpy(*temp++, buffer);
   }
   if (thirdOut > 0) {
      sprintf(buffer, "O%d", thirdOut);
      *temp = calloc(size, CHAR_SIZE);
      strcpy(*temp++, buffer);
   }
   if (in1 > 0) {
      sprintf(buffer, "I%d", in1);
      *temp = calloc(size, CHAR_SIZE);
      strcpy(*temp++, buffer);
   }
   if (in2 > 0) {
      sprintf(buffer, "I%d", in2);
      *temp = calloc(size, CHAR_SIZE);
      strcpy(*temp++, buffer);
   }
   if (value >= 0) {
      sprintf(buffer, "V%.3lf", value);
      *temp = calloc(size, CHAR_SIZE);
      strcpy(*temp++, buffer);
   }
   if (ident >= 0) {
      sprintf(buffer, "D%d", ident);
      *temp = calloc(size, CHAR_SIZE);
      strcpy(*temp, buffer);
   }

   return args;
}
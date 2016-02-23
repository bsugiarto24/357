#include <stdio.h>


/* Accept a count of variadic parameters, followed by that many parameters,
 * which you may assume were passed as char, int, or shorts from main, though
 * they are passed per variadic rules.  Following those is an int * parameter,
 * pointing to a integer onto which you must add the variadic parameters. 
 * (Add the ASCII code in the case of a char.) */
void vaTotal(int num, ...) {
	int *pi, subTot = 0;
	short *ps;
	char *pc;

	pi = &num;
	while(num--)
	{
	subTot += *++pi;
	}
	**(int **)++pi += subTot; 
}

int main() {
   int i, sum = 42;
   short s;
   char c;
  
   scanf("%d %hd %c", &i, &s, &c);
  
   vaTotal(3, i, s, c, &sum);
   vaTotal(4, c, c, s, i, &sum);
  
   printf("%d\n", sum);

   return 0;
}

/******************** SILVER *********************/
#include <stdio.h>
#include <stdarg.h>

/* Accept a format string comprised only of the letters c d i s and f for char,
 * double, int, short, and float, respectively.  Accept as many variadic
 * parameters after that format string as there are letters in the string.
 * Assume the actual parameters in the main were of the indicated types 
 * (though passed variadically).  Total the parameters and return the total
 * (use the ASCII value of any char parameter. */

 double addEm( char* format, ...)
{
   va_list params;
   va_start(params, format);
   int value;
   double dval;
   double total = 0;

   while(*format)
   {
      value = 0;
      dval = 0;
      switch(*format){

      case 'c':
         value = va_arg(params, int);break;
      case 'i':
         value = va_arg(params, int);break;
      case 'd':
         dval = va_arg(params, double);break;
      case 'f':
         dval = va_arg(params, double); break;
      case 's':
         value = va_arg(params, int); break;
         
      }
      total += value;
      total += dval;
      format++;
   }
   va_end(params);
   return total;
}

int main() {
   double dVal;
   float fVal;
   int iVal;
   short sVal;
   char cVal;
  
   scanf("%d %hd %c %f %lf", &iVal, &sVal, &cVal, &fVal, &dVal);
  
   printf("Total is %0.2f or %0.2f if you add 42\n",
    addEm("fdisc", fVal, dVal, iVal, sVal, cVal),
    addEm("siccddf", sVal, iVal, cVal, 42, dVal, 0.0, fVal));

   return 0;
}
#include <stdio.h>
#include "SmartAlloc.h"
#include "CodeSet.h"

int main() {
char command;
void *cs[3]; // Array of three void pointers
int ndx, numCodes, val, set, depth;
unsigned long space, add;
Code code;

while (EOF != scanf(" %c", &command)) {
switch (command) {
case 'C': // create new codeSet C <set> <maxCodes>
scanf("%d%d", &set, &numCodes);
cs[set] = CreateCodeSet(numCodes);
printf("Set %d initialized\n", set);
break;
case 'N': // add new code N <set> <value>
scanf("%d%d", &set, &val);
printf("New code in set %d at index %d\n", set, NewCode(cs[set], val));
break;

case 'E': // extend existing code E <set> <codeIndex>

scanf("%d%d", &set, &ndx); 
printf("Added extended code %d\n", ExtendCode(cs[set], ndx));


break;
case 'S': // set suffix S <set> <codeIndex> <suffix>

scanf("%d%d%d", &set, &ndx, &val); 
SetSuffix(cs[set], ndx, val);

break;
case 'G': // get code G <set> <codeIndex>

scanf("%d%d", &set, &ndx); 
code = GetCode(cs[set], ndx);
printf("Code %d in set %d has value: %d", ndx, set, *(code.data));
while(--code.size)
{
	printf(" %d", *(++code.data));
}	
printf("\n");


break;
case 'F':

scanf("%d%d", &set, &ndx); 
FreeCode(cs[set], ndx);

break;
case 'R': // Report current space
printf("Current space: %d\n", report_space());
break;
case 'B': // Grab current space used
space = report_space();
break;
case '+': // Adds an amount to the current used space.
scanf("%lu", &add);
space += add;
break;
case '-': // Decreases an amount to the current used space.
scanf("%lu", &add);
space -= add;
break;
case 'L': // Call limit space
limit_space(space);
break;
case 'X': // Add many codes in prefix order X <set> <depth>
scanf("%d%d", &set, &depth);
ndx = NewCode(cs[set], 'X');
while (--depth) {
ndx = ExtendCode(cs[set], ndx);
SetSuffix(cs[set], ndx, 'X');
}
break;
case 'D': // Destroy existing code set D <set>
scanf("%d", &set);
DestroyCodeSet(cs[set]);
printf("Set %d destroyed\n", set);
}
}

return 0;
}


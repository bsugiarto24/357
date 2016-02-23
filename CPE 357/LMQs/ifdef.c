
/**************BRONZE **************/
#define F2
#define F1
#define level 5
#undef F3

/************* GOLD *************/
#ifndef COUNT_H 
	#define COUNT_H
	#define PRINT 1
	int count = 0;
	#define counter count
#else
	#if PRINT == 0
		#define PRINT 1
	#else
		#define PRINT 0
	#endif
#endif
count++;
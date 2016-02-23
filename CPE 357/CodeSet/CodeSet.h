/* One entry in a dictionary of codes.
* |data| points to the sequence of bytes the code represents.
* |size| is the sequence length.
*/
typedef struct Code {
char *data;
unsigned short size;
} Code;

/* Allocate, initialize, and return a CodeSet object, via void *
* The CodeSet will have room for |numCodes| codes, though it will
* initially be empty. */
void *CreateCodeSet(int numCodes);

/* Add a new 1-byte code to |codeSet|, returning its index, with
* the first added code having index 0. The new code's byte is
* equal to |val|. Assume (and assert if needed) that there
* is room in the |codeSet| for a new code. */
int NewCode(void *codeSet, char val);

/* Create a new code by copying the existing code at index
* |oldCode| and extending it by one zero-valued byte. Any
* existing code might be extended, not just the most recently
* added one. Return the new code's index. Assume |oldCode|
* is a valid index and that there is enough room for a new code. */
int ExtendCode(void *codeSet, int oldCode);

/* Set the final byte of the code at index |code| to |suffix|.
* This is used to override the zero-byte added by ExtendCode.
* If the code in question has been returned by a GetCode call,
* and not yet freed via FreeCode, then the changed final byte
* will also show in the Code data that was returned from GetCode.*/
void SetSuffix(void *codeSet, int code, char suffix);

/* Return the code at index |code| */
Code GetCode(void *codeSet, int code);

/* Mark the code at index |code| as no longer needed, until a new
* GetCode call is made for that code. */
void FreeCode(void *codeSet, int code);

/* Free all dynamic storage associated with |codeSet| */
void DestroyCodeSet(void *codeSet);


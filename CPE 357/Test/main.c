#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

/*
void InsertSort(int vals[], int size) {
   int ndx, insNdx, toInsert;

   for (ndx = 1; ndx < size; ndx++) {
      toInsert = vals[insNdx = ndx];
      while (insNdx > 0 && toInsert < vals[insNdx-1]) {
         vals[insNdx] = vals[insNdx-1];
         insNdx--;
      }
      vals[insNdx] = toInsert;
   }
}
*/

void FileSort(int fd) {
   size_t ndx, limit;
   int toInsert, temp;
   
  //lseek(fd, -1, SEEK_END);
  //read (fd, &val, sizeof(char));
 // lseek(fd, -1, SEEK_END);
  //write(fd, &in, sizeof(char));

for (ndx = 1; ndx < SEEK_END; ndx++) {
   lseek(fd, 0, ndx);
   read(fd, &toInsert, sizeof(int));
   lseek(fd, -1, ndx);
   read(fd, &temp, sizeof(int));
   while (ndx > 0 && toInsert < temp) { 
     lseek(fd, -1, SEEK_END);
     write(fd, &toInsert, sizeof(int));
     ndx--;
   }

}
   
}  
int main() {
   int fd, data;

   fd = open("temp.txt", O_CREAT|O_RDWR|O_TRUNC, 0600);
   while (EOF != scanf("%d", &data))
      write(fd, &data, sizeof(int));

   FileSort(fd);

   lseek(fd, 0, SEEK_SET);
   while (0 != read(fd, &data, sizeof(int)))
      printf("%d ", data);
   printf("\n");

   close(fd);

   return 0;
}
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]){
     FILE * file;
     char mystr[100];
     int i, n;
     /* printf("%d %s %s", argc, argv[0], argv[1]); */
     int *a;
     n = atoi(argv[1]);
     printf("%d\n", n+1);
     a = malloc(n * sizeof(int));
     if(a == NULL){
     	  printf("Error in allocating memory!!\n");
     	  return 0;
     }
     a[1] = 4;
     a[n-1] = 100;
     printf("%d, %d\n", a[1], a[n-1]);
     free(a);
     
	  


     /* file = fopen("write-test", "r+"); */
     /* if(file == NULL){ */
     /* 	  printf("Error : Unable to open file!\n"); */
     /* 	  return 0; */
     /* } */
     /* printf("\n"); */
     
     /* while(!feof(file)){ */
     /* 	  fgets(mystr, 80, file); */
     /* 	  mystr[strlen(mystr) - 1] = '\0'; */
     /* 	  /\* for(i=0; i<strlen(mystr); i++) *\/ */
     /* 	  /\*      printf("%c ", mystr[i]); *\/ */
     /* 	  /\* puts(mystr); *\/ */
     /* } */
     
     /* /\* printf("HI"); *\/ */
     
     /* fclose(file); */
     return 0;
}

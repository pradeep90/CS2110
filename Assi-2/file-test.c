#include <stdio.h>
#include <string.h>
int main(){
     FILE * file;
     char mystr[100];
     int i;
     

     file = fopen("write-test", "r+");
     if(file == NULL){
	  printf("Error : Unable to open file!\n");
	  return 0;
     }
     printf("\n");
     
     while(!feof(file)){
	  fgets(mystr, 80, file);
	  mystr[strlen(mystr) - 1] = '\0';
	  /* for(i=0; i<strlen(mystr); i++) */
	  /*      printf("%c ", mystr[i]); */
	  /* puts(mystr); */
     }
     
     /* printf("HI"); */
     
     fclose(file);
     return 0;
}

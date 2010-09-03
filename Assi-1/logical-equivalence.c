/********************************************************************** 
 * Program name : Logical Equivalence
 * Program : To get two logical expressions and 
 *           check if truth tables are identical
 * Date : 13 August 2010
 * Successful!!!
 * Works with command line arguments!!

************************************************************************/

#include <stdio.h>
#include <string.h>

char ipstr[100] = "";
int fnvalues1[1000], fnvalues2[1000], numvar;

int get_expression(char ipstr[])
{
     /*
      * Arguments :
      * char ipstr[] - The infix expression from user goes here
      *
      * Return : Nothing in particular
      */


     printf("Operators : \n& AND\n~ Not\n| OR\n> IMPLIES\n= IMPLIES AND IS IMPLIED BY\n");
     printf("Use any alphabets to denote your variables\n");
     printf("Please enter your logical expression : \n");
     gets(ipstr);
}

int test_for_tautology(int arr[], int numvar)
{
     int i, flag = 0;
     for(i=0; i<(1<<numvar); i++){
	  if(!arr[i]){
	       flag = 1;
	  }
     }
     if(!flag)
	  return 1;		/* Tautology */
     
     flag = 0;
     for(i=0; i<(1<<numvar); i++){
	  if(arr[i]){
	       flag = 1;
	  }
     }
     if(!flag)
	  return 2;		/* Contradiction */

     return 0;			/* General function */
}

	       
	  

int main(int argc, char *argv[]){
     int i, j, output;
     int test;
     char combinestr[100] = "(";
     if(argc == 1){
	  printf("Logical Expression 1 :\n");
	  get_expression(ipstr);
	  truth_table(ipstr, fnvalues1, &numvar);
	  
	  strcat(combinestr, ipstr);
	  strcat(combinestr, "=");
	  printf("\nLogical Expression 2 :\n");
	  get_expression(ipstr);
	  truth_table(ipstr, fnvalues2, &numvar);
	  strcat(combinestr, ipstr);
	  strcat(combinestr, ")");

	  truth_table(combinestr, fnvalues1, &numvar);
	  
	  test = test_for_tautology(fnvalues1, numvar);
	  if(test == 1)
	       printf("\nThe given functions are equivalent!\n");
	  else
	       printf("\nThe given functions are NOT equivalent!\n");
     }
     else if(argc != 3){
	  printf("Please enter exactly two logical expressions!");
	  return 0;
     }
     else{
	  printf("Logical Expression 1 :\n");
	  strcpy(ipstr, argv[1]);
	  truth_table(ipstr, fnvalues1, &numvar);
	  
	  strcat(combinestr, ipstr);
	  strcat(combinestr, "=");
	  printf("\nLogical Expression 2 :\n");
	  strcpy(ipstr, argv[2]);
	  truth_table(ipstr, fnvalues2, &numvar);
	  strcat(combinestr, ipstr);
	  strcat(combinestr, ")");

	  truth_table(combinestr, fnvalues1, &numvar);
	  
	  test = test_for_tautology(fnvalues1, numvar);
	  if(test == 1)
	       printf("\nThe given functions are equivalent!\n");
	  else
	       printf("\nThe given functions are NOT equivalent!\n");

     }
     
     return 0;
}



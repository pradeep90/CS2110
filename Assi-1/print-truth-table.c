/********************************************************************** 
 * Program name : print-truth-table
 * Program : To get a logical expression and call truth-table
 * Date : 13 August 2010
 * Successful!!!
 * Things to learn :
 *** Approach the problem from a high-level
 *** Abstract away all the different procedures for easier testing and bug removal
 * Works with command line arguments!!

************************************************************************/



#include <stdio.h>
#include <string.h>


char ipstr[100] = "";
int fnvalues[1000], numvar;

int get_expression(char ipstr[])
{
     printf("Operators : \n& AND\n~ Not\n| OR\n> IMPLIES\n"
	    "= IMPLIES AND IS IMPLIED BY\n");
     printf("Use any alphabets to denote your variables\n");
     printf("Please enter your logical expression : \n");
     gets(ipstr);
}

int main(int argc, char *argv[]){
     int i, j, output;

     if(argc == 1){
	  get_expression(ipstr);
	  truth_table(ipstr, fnvalues, &numvar);
     }
     else if(argc != 2){
	  printf("Please enter exactly one logical expression!");
	  return 0;
     }
     else{
	  strcpy(ipstr, argv[1]);
	  truth_table(ipstr, fnvalues, &numvar);
     }
     
     return 0;
}



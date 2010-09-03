/* 
 * General functions used for converting to and evaluating postfix, etc.
 *
 */

#include <stdio.h>
#include <string.h>

char eval_negation(char ch);
char eval_or(char a, char b);
char eval_and(char a, char b);
int is_token(char ch);
int conv_to_postfix(char ipstr[], char opstr[], int precedence[]);
int compute_val_var_from_perm(int perm, int valvar[], int numvar);
int eval_postfix(char opstr[], int valvar[], int numvar, char listvar[]);


int get_variables(char listvar[], int * numvar, int precedence[]);
int get_expression(char ipstr[]);
int check_for_valid_characters(char ipstr[]);
int remove_spaces(char ipstr[]);
void set_precedence(int precedence[], char ipstr[]);

char token_list[] = "~&|>=";

int is_variable(char ch)
{
     if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
	  return 1;
     else
	  return 0;
}


int is_token(char ch)
{
     int i;
     for(i=0; i<strlen(token_list); i++)
	  if(ch == token_list[i])
	       return 1;
     return 0;
}

int get_variables(char listvar[], int * numvar, int precedence[])
{
     /* Note : numvar has to be a pointer since we change its value here */
     int k, i;
     k=0;
     for(i='A'; i<='z'; i++){
	  if(precedence[i])
	       listvar[k++] = i;
     }
     listvar[k] ='\0';
     *numvar = k;
}

int check_for_valid_characters(char ipstr[])
{
     /*
      * Return 0 if all characters in ipstr are valid
      * Else 1
      * 
      */
     int i, j, flag;
     char ch;
     
     
     /* Check for valid characters */
     for(i=0; i<strlen(ipstr); i++){
	  ch = ipstr[i];
	  switch(ch){
	  case '(':
	  case ')':
	       break;
	  default:
	       flag = 0;
	       for(j=0; j<strlen(token_list); j++)
		    if(ch == token_list[j])
			 flag = 1;
	       if(flag)
		    continue;
	       else if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		    continue;
	       else
		    return 1;
	  }
     }
     return 0;
}

int remove_spaces(char ipstr[])
{
     /* Remove spaces */
     int i, j;
     
     char curr[100];
     strcpy(curr, ipstr);
     for(i=0, j=0; i<strlen(curr); i++)
	  if(curr[i] != ' ')
	       ipstr[j++] = curr[i];
	       
     ipstr[j] = '\0';
     return 0;
}

void set_precedence(int precedence[], char ipstr[])
{
     /* Precedence for tokens */
     precedence['~'] = 5;
     precedence['&'] = 4;
     precedence['|'] = 3;
     precedence['>'] = 2;
     precedence['='] = 1;
     
     /* Precedence */
     char temp[100];
     int k, i;
     strcpy(temp, ipstr);

     for(i='A'; i<='z'; i++){
	  precedence[i] = 0;
     }
     /* Precedence for characters */
     for(i=0; i<strlen(ipstr); i++){
	  if(!precedence[ipstr[i]])
	       precedence[ipstr[i]] = 100;
     }
 

}



char eval_negation(char ch)
{
     return (ch == '0')? '1' : '0';
}

char eval_or(char a, char b)
{
     if(a == '0' && b == '0')
	  return '0';
     else
	  return '1';
}
char eval_and(char a, char b)
{
     if(a == '1' && b == '1')
	  return '1';
     else
	  return '0';
}
char eval_imply(char a, char b)
{
     if(a == '1' && b == '0')
	  return '0';
     else
	  return '1';   
}
char eval_bicond(char a, char b)
{
     if((a == '1' && b == '0') || (a == '0' && b == '1'))
//(eval_imply(a, b) == '1') && (eval_imply(b, a) == '1'))
	  return '0';
     else
	  return '1';
}


int conv_to_postfix(char ipstr[], char opstr[], int precedence[])
{
     /* Convert ipstr to opstr in postfix notation  */
     int i, octr = 0, stctr = 0, len;
     char ch, operstack[100];

     /* Check if given expression doesn't have variables next to each other */
     int flag = 0;
     int tildeflag = 0;

     for(i=0; i<strlen(ipstr); i++){
	  if(is_variable(ipstr[i])){
	       if(flag){
		    printf("\nNot a valid Infix Expression!\n");
		    return 1;
	       }
	       else
		    flag = 1;
	  }
	  else
	       flag = 0;
	  
	  if(tildeflag){
	       if(!is_variable(ipstr[i])){
		    printf("\nNot a valid Infix Expression!\n");
		    return 1;
	       }
	       else
		    tildeflag = 0;
	  }
	  if(ipstr[i] == '~')
	       tildeflag = 1;
     }
     if(tildeflag){
	  printf("\nNot a valid Infix Expression!\n");
	  return 1;
     }

     for(i=0; i<100; i++)
	  operstack[i] = opstr[i] = '\0';

     len = strlen(ipstr);

     for(i=0; i<len; i++){
	  ch = ipstr[i];
	  if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
	       opstr[octr++] = ch;
	  else{
	       switch(ch){
	       case '(':
		    operstack[stctr++] = ch;
		    break;
	       case ')':
		    while(stctr > 0 && operstack[stctr-1] != '(')
			 opstr[octr++] = operstack[--stctr];
		    if(stctr == 0){
			 printf("\nERROR : no (");
			 return 1;
		    }
		    if(operstack[stctr-1] == '(')
			 stctr--;
		    break;
	       default:
		    while(stctr > 0 && is_token(operstack[stctr-1]) && 
			  precedence[operstack[stctr-1]] >= precedence[ch]){
			 
			 /* Pop off operstack onto opstr */
			 opstr[octr++] = operstack[--stctr];			 
		    }
		    operstack[stctr++] = ch;
		    break;
	       }
	  }
     }
     while(stctr > 0){
	  if(operstack[stctr-1] == '(' || operstack[stctr-1] == ')'){
	       printf("\nERROR : Extra parens");
	       return 1;
	  }
	  else
	       opstr[octr++] = operstack[--stctr];
     }
     opstr[octr] = '\0';
     return 0;
     
}

int compute_val_var_from_perm(int perm, int valvar[], int numvar)
{
     /*
      * Get individual bit and put it in the respective valvar 
      */
     int j;
     for(j=numvar-1; j>=0; j--){
	  valvar[numvar-j-1] = (perm & 1<<j)? 1 : 0;
     }
}

     
int eval_postfix(char opstr[], int valvar[], int numvar, char listvar[])
{
     /* Arguments : 
      * char opstr[] - the postfix expression to be evaluated
      * char valvar[] - the values to be substituted for each variable
      * int numvar
      Return the value of the postfix expr. for given inputs
     */
     char stack[100], temp[100], ch;
     int i, j, ctr = 0;
     
     for(i=0; i<100; i++)
	  stack[i] = temp[i] = '\0';
     strcpy(temp, opstr);
     for(i=0; i<numvar; i++){
	  for(j=0; j<strlen(temp); j++){
	       if(temp[j] == listvar[i])
		    temp[j] = (valvar[i]) ? '1' : '0';
	  }
     }

     for(i=0; i<strlen(temp); i++){
	  ch = temp[i];
	  if(ch == '0' || ch == '1')
	       stack[ctr++] = ch;
	  else{
	       switch(ch){
	       case '~':
		    if(ctr <= 0){
			 return 1;
		    }
		    else
			 stack[ctr-1] = eval_negation(stack[ctr-1]);
		    break;
	       case '|':
		    if(ctr <= 1){
			 return 1;
		    }
		    else{
			 stack[ctr-2] = eval_or(stack[ctr-2], stack[ctr-1]);
			 ctr--;
		    }
		    break;
	       case '&':
		    if(ctr <= 1){
			 return 1;
		    }
		    else{
			 stack[ctr-2] = eval_and(stack[ctr-2], stack[ctr-1]);
			 ctr--;
		    }
		    break;
	       case '>':
		    if(ctr <= 1){
			 return 1;
		    }
		    else{
			 stack[ctr-2] = eval_imply(stack[ctr-2], stack[ctr-1]);
			 ctr--;
		    }
		    break;
	       case '=':
		    if(ctr <= 1){
			 return 1;
		    }
		    else{
			 stack[ctr-2] = eval_bicond(stack[ctr-2], stack[ctr-1]);
			 ctr--;
		    }
		    break;
	       }
	  }

     }

     if(ctr == 1){
	  return stack[ctr-1];
     }
     else{
	  return 1;
     }
}

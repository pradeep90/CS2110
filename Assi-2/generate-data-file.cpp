/*
 * Note : Files data-file-x have 10^x student-id|student-names
 */




#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main(){
     
     long int num = 1000000;
     bool id_exists[num+1];
     long int i, curr;
     
     ofstream file;
     ifstream infile;

     //Code for generating the data files
     
     file.open("data-file6");
     for(i=0; i<num; i++)
     	  id_exists[i] = false;

     for(i=0; i<num; i++){
     	  curr = rand()%num;
     	  while(id_exists[curr])
     	       curr = rand()%num;
     	  id_exists[curr] = true;
     	  file<<num + curr<<"|Arbit-Student-"<<i<<'\n';
	  
     }

     file.close();
     
     return 0;
}



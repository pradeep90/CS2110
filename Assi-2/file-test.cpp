// Test for getline, etc.

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
     int a;
     string s;
     ifstream infile;
     infile.open("student-test-cases3");

     while(!infile.eof()){
	  
	  getline(infile, s);
	  //if(s.length()!=0)
	       cout<<s<<endl;
     }
     infile.close();
     return 0;
}

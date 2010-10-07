#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Iterator
{
private:
     int a;
     Iterator * next;
public:
     int & operator*()
	  {
	       return a;
	  }
 
     void set()
	  {
	       a = 100;
	       next = NULL;
	  }
     int * operator->()
	  {
	       
	  }
     
};

     


int main(){
     Iterator iter;
     iter.set();
     cout<<*iter;
     cout<<typeof(iter->);
     
     return 0;
}

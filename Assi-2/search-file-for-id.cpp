/*
 * Search given file for a student's ID
 * Note : Files data-file-x have 10^x student-id|student-names
 */




#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;


class student
{
private://public:
     string ID, name;
public:
     // Selectors
     string get_ID();
     string get_name();
     // Set values
     int set_student_details(string, string);
     // Equality
     bool equal(student);
     bool exists_in_file();
     bool exists_in_array(int, student[]);
     bool get_values_from_file();
     bool get_values_from_test_file();
     void display();
};


ifstream infile, test_infile;

char test_file_name[] = "student-test-cases6";
char data_file_name[] = "data-file6";



const int max_num = 100;
student test_students[max_num];


bool cmp(student a, student b)
{
     return a.get_ID() < b.get_ID();
}





string student::get_ID()
{
     return ID;
}

string student::get_name()
{
     return name;
}

int student::set_student_details(string given_id, string given_name)
{
     ID = given_id;
     name = given_name;
     return 0;
}


// MODIFY THIS TO USE COMP (???)
bool student::equal(student s1)
{
     if(s1.get_ID() == ID && s1.get_name() == name)
	  return true;
     return false;
}

int my_binary_search(student a[], int l, int r, student sval)
{
     // l, r are indices of the first and last element in a[]
     int mid = (l+r)/2;
     if(sval.equal(a[mid]))
	  return mid;
     else if(cmp(sval, a[mid]))
	  if(mid - 1 < l)
	       return -1;
	  else
	       my_binary_search(a, l, mid - 1, sval);
     else
	  if(mid + 1 > r)
	       return -1;
	  else
	       my_binary_search(a, mid + 1, r, sval);
}

bool student::exists_in_array(int n, student inp_students[])
{
     int i = 0;
     if(my_binary_search(inp_students, 0, n-1, *this) != -1)
	  return true;
     
     // for(i=0; i<n; i++)
     // 	  if(equal(inp_students[i]))
     // 	       return true;
     return false;
}


bool student::exists_in_file()
{
     // Assuming read pointer is at the
     // beginning of the file

     string s_id, s_name;
     student temp;
     
     while(temp.get_values_from_file()){
	  if(equal(temp))
	       return true;
     }
     return false;
     
}

bool student::get_values_from_test_file()
{
     string a, b;

     if(test_infile.eof())
	  return false;
     
     getline(test_infile, a, '|');
     getline(test_infile, b);
     set_student_details(a, b);
     return true;
}


bool student::get_values_from_file()
{
     string a, b;

     if(infile.eof())
	  return false;
     
     getline(infile, a, '|');
     getline(infile, b);
     set_student_details(a, b);
     return true;
}



void student::display()
{
     cout<<ID<<"|"<<name<<endl;
}
    
void get_test_inputs()
{
     int i;
     string a, b;
     test_infile.open(test_file_name);
     
     i=0;

     while(test_students[i].get_values_from_test_file()){
     	  i++;
     }
     
     cout<<"i : "<<i<<endl;
     cout<<"Test inputs :\n";
     
     for(i=0; i<max_num; i++)
	  test_students[i].display();

     test_infile.close();
}

void check_in_data_file()
{
     int i;
     
     cout<<"Checking in the file : \n";
     
     infile.open(data_file_name);
     // student foo;
     // infile.seekg(0);
     
     // foo.set_student_details("1173", "Arbit-guy");
     // cout<<"foo : "<<foo.exists_in_file()<<endl;
     
     for(i=0; i<max_num; i++){
     	  infile.seekg(0);
	  
     	  if(test_students[i].exists_in_file())
	       // CHANGE THIS!!!!
	       test_students[i].display();
     }
     
     infile.close();
}

int load_n_students_from_file(int n, student inp_students[])
{
     int i;
     bool flag = false;
     cout<<"Loading "<<n<<" students from file!\n";
     infile.open(data_file_name);

     for(i=0; i<n; i++){
	  if(!inp_students[i].get_values_from_file()){
	       flag = true;
	       break;
	  }
	  //cout<<"Value : "<<inp_students[i].get_values_from_file();

	  //inp_students[i].display();
     }
     infile.close();
     if(flag)
	  return 1;
     return 0;
}

void search_in_array(int n, student inp_students[])
{
     int i;
     cout<<"Searching in Array !\n";
     
     for(i=0; i<max_num; i++){
	  if(test_students[i].exists_in_array(n, inp_students))
	       test_students[i].display();
     }
}





     
     

int main(){
     int i, n = 1000000;
     // cout<<"Please enter n : ";
     // cin>>n;
     // cout<<"n : "<<n;
     
     string a, b;
     get_test_inputs();

     //check_in_data_file();
     // student *sptr = new student;
     // sptr->set_student_details("123", "Arbit-Max");
     // sptr->display();
     //delete sptr;
     student * const inp_students = new student[n];
     load_n_students_from_file(n, inp_students);
     sort(inp_students, inp_students + n, cmp);
     // for(i=0; i<n; i++){
     // 	  inp_students[i].display();
     // }
     search_in_array(n, inp_students);
     // int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
          
     // for(i=0; i<11; i++)
     // 	  cout<<"i : "<<i<<" "<<my_binary_search(arr, 0, 9, i)<<endl;
     

     
     //student * const stud_arr = new student[n];

     return 0;
}

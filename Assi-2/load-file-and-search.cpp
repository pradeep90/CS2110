/*
  Title : Search file for given field

  Purpose : To search a file of '|' separated values for records matching
            given field

  Description :
  -> The program accepts a file name and integer as command line arguments
  -> The program loads n records from the given file into 
     an array of students
  -> Record = ID|Name|Address|DOB|CGPA|Mobile-No     
  -> Then, we use linear search to search if given ID matches any of the
     students' IDs

  Author : S. Pradeep Kumar
  Date : 12 - 09 - 2010
 
  Challenge : 
  * Loading 10^6 entries takes ~0.7 seconds
  * However, sorting them takes 7 seconds
  * Then, of course, binary search is quick
  * Linear search is pretty quick -
  * Around 7 seconds to search for 100 records in 10^6 records(incl. start time)

  Possible clues to tackling the issue : 
  * It takes just 0.7 seconds to load 10^6 records
  * So, iterating through the lot isn't what is slow
  * The constants in Quicksort running time must be what are causing the slowness
  * What are the other factors : 
  ** Maybe handling strings individually multiplies running time by length of string
  ** See how using a selector affects running time
  ** See how comparing just with ID instead of by Student changes the running time
  Possible Solution(s):
  * Use some different data structures (hash tables, binary search trees (?), etc.)
 */



#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

class student
{
private:
     string ID, name, address, dob, cgpa, mobile_no;
public:
     string get_id();
     void display();
     void set_student_details(string, string, string, string, string, string);
     bool is_match(string given_id);
     bool get_values_from_file(ifstream& infile);
};

class student_database
{
private:
     int num_students;
     student * student_records;
public:
     student_database(int n)
	  {
	       num_students = n;
	       student_records = new student[num_students];
	  }
     ~student_database()
	  {
	       delete []student_records;
	  }
     // 0: not exist 1: wrong-format
     int load_n_students_from_file(string file_name, long int n);
     bool lookup(string given_id, student &stud); 
};

int student_database::load_n_students_from_file(string file_name, long int n)
{
     long int i;
     bool flag = false;
     cout<<"Loading "<<n<<" students from file!\n";
     ifstream infile;
     
     infile.open(file_name.c_str());
     if(!infile){
	  cout<<"\nERROR : Given file does not exist!!\n";
	  return -1;
     }

     for(i=0; i<n; i++){
     	  if(!student_records[i].get_values_from_file(infile)){
     	       flag = true;
	       cout<<"\n ERROR : Not enough records in file!\n";
     	       break;
     	  }
     }

     infile.close();

     if(flag)
     	  return 1;
     return 0;
}

bool student_database::lookup(string key, student& stud)
{
     long int i;
     for(i=0; i<num_students; i++){
	  if(student_records[i].is_match(key)){
	       stud = student_records[i];
	       return true;
	  }

     }
     return false;
}


string student::get_id()
{
     return ID;
}

void student::display()
{
     cout<<"ID        : "<<ID<<endl; 
     cout<<"Name      : "<<name<<endl; 
     cout<<"Address   : "<<address<<endl; 
     cout<<"DOB       : "<<dob<<endl; 
     cout<<"CGPA      : "<<cgpa<<endl; 
     cout<<"Mobile_no : "<<mobile_no<<endl; 
}

void student::set_student_details(string given_id, string given_name, string given_address, string given_dob, string given_cgpa, string given_mobile_no)
{
     ID = given_id;
     name = given_name;
     address = given_address;
     dob = given_dob;
     cgpa = given_cgpa;
     mobile_no = given_mobile_no;
}

bool student::is_match(string key)
{
     return (ID == key);
}

bool student::get_values_from_file(ifstream& infile)
{
     string given_id,  given_name,  given_address,  given_dob,  given_cgpa,  given_mobile_no;

     if(infile.eof())
	  return false;
     getline(infile, given_id, '|');
     getline(infile, given_name, '|');
     getline(infile, given_address, '|');
     getline(infile, given_dob, '|');
     getline(infile, given_cgpa, '|');
     getline(infile, given_mobile_no);
     set_student_details(given_id, given_name, given_address, given_dob, given_cgpa, given_mobile_no);

     return true;
}

     
int get_test_inputs(string& key)
{
     cout<<"\nPlease enter ID of the student you wish to search for : ";
     do{
	  getline(cin, key);
     }while(key == "");
     

     if(key == "exit" || key == "EXIT")
	  return 1;
     cout<<"input : "<<key<<endl;

     return 0;
}

int main(int argc, char * argv[])
{
     student stud;
     long int n, load_val;
     string data_file_name, key;
     bool found;

    // Test if command-line arguments are valid
     if(argc != 3){
	  cout<<"Please enter exactly 2 arguments\n"
	      <<"Name of the file and\n"
	      <<"No of students records in the file\n";
     }
     else{
	  n = atoi(argv[2]);
	  if(n <= 0){
	       // If n is some non-numeric string or if n == 0
 	       cout<<"ERROR : Please enter a valid positive integer for n!\n";
	       return 0;
	  }
	  data_file_name = string(argv[1]);
	  cout<<"n : "<<n<<'\n'<<"File name : "<<data_file_name<<'\n';
     }

     
     // Create an empty database of size n
     student_database my_DB(n);

     // Load n records from given file
     load_val = my_DB.load_n_students_from_file(data_file_name, n);

     // If non-existent file / file with less than n records
     if(load_val == -1 || load_val == 1){
	  return 1;
     }
     
     // Input loop
     while(!get_test_inputs(key)){
	  found = my_DB.lookup(key, stud);
	  if(found)
	       stud.display();
	  else
	       cout<<"Student with ID : "<<key<<" not found!\n";
     }
     return 0;
}

     
      


     

/*
  TODO:
  * Load function
  * lookup function
  * get_input function

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
     vector<student> student_records;
public:
     int load_n_students_from_file(string file_name, long int n);// 0: not exist 1: wrong-format
     bool lookup(string given_id, student &stud); // Maybe change to field, index
};

int student_database::load_n_students_from_file(string file_name, long int n)
{
     long int i;
     bool flag = false;
     cout<<"Loading "<<n<<" students from file!\n";
     infile.open(data_file_name);
     if(!infile){
	  cout<<"\nERROR : Given file does not exist!!\n";
	  return -1;
     }

     for(i=0; i<n; i++){
     	  if(!student_records[i].get_values_from_file()){
     	       flag = true;
     	       break;
     	  }
     	  //cout<<"Value : "<<inp_students[i].get_values_from_file();
     	  cout<<"i : "<<i<<'\n';
     	  student_records[i].display();
     }
     infile.close();

     if(flag)
     	  return 1;
     return 0;
}

int load_n_students_from_file(int n, student inp_students[])
{
	  
     cout<<"Please enter 'exit' if you wish to terminate the program!\n";
     
     return 0;
}

bool student_database::lookup(string given_id, student &stud)
{
     cout<<"Looking up "<<given_id<<'\n';
     return true;
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

bool student::is_match(string given_id)
{
     return (ID == given_id);
}

bool student::get_values_from_file(ifstream& infile)
{
     string given_id,  given_name,  given_address,  given_dob,  given_cgpa,  given_mobile_no;

     if(infile.eof())
	  return false;
     // CHECK FOR ERROR / EOF
     getline(infile, given_id, '|');
     getline(infile, given_name, '|');
     getline(infile, given_address, '|');
     getline(infile, given_dob, '|');
     getline(infile, given_cgpa, '|');
     getline(infile, given_mobile_no);
     set_student_details(given_id, given_name, given_address, given_dob, given_cgpa, given_mobile_no);

     return true;
}

     

int main(int argc, char * argv[])
{
     student stud;
     long int n, load_val;
     string data_file_name;
     
    // Test if command-line arguments are valid
     if(argc != 3){
	  cout<<"Please enter exactly 2 arguments\n"
	      <<"Name of the file and\n"
	      <<"No of students records in the file\n";
     }
     else{
	  n = atoi(argv[2]);
	  if(n == 0){
 	       cout<<"ERROR : Please enter a valid positive integer for n!\n";
	       return 0;
	  }
	  data_file_name = string(argv[1]);
	  cout<<"n : "<<n<<'\n'<<"File name : "<<data_file_name<<'\n';
     }
     
     // student s;
     // s.set_student_details("24", "asnoeu", "htououe", "ontuaehoeau", "oaunesth", "aonsuth");
     // s.display();
     // cout<<endl<<"ID : "<<s.get_id()<<endl;
     // cout<<s.is_match("26");
     // cout<<s.is_match("24");
     
     
     
     student_database my_DB;
     load_val = my_DB.load_n_students_from_file(data_file_name, n);
     if(load_val == 1){
	  return 1;
     }
     
	  
     my_DB.lookup("HI", stud);
     
     // if(my_DB.load_n_students_from_file(argv[1], atoi(argv[2])))
     // 	  cout<<"ERROR : Bad File!\n";
     
     // get_input(&key);
     
     // if(my_DB.lookup(key, &stud))
     // 	  stud.display();
     // else
     // 	  cout<<"Student with ID : "<<key<<" NOT FOUND!\n";

     return 0;
}

     
      


     

#include <iostream>
#include <fstream>
#include <ctime>

#include <vector>
#include <cstring>
#include <string>
//#include <filesystem>

using namespace std;
//using std::filesystem::exists

class PSPOH
{
  /*
  const char var;
  PSPOH(int constant_value):var(constant_value)
  {
   cout << "Value is " << var << " \n";
  }
  */
 
}; //end class


int name_the_report(fstream& , char*);
int run_the_test(int);
int report_header(fstream& , char* , int );

/*User input for data resolution of the test.*/
int numsamples() {
  cout << "how many samples in this test? ";
  int runs;
  cin >> runs; //get number of sample runs 
  return runs;
}


int main()
{
  int runs = numsamples();


  cout << "\nStart test? y = yes , n = no" <<endl;
  char flag = 'n';
  
  while ( flag != 'y') {  cin >> flag;
  }
   
   /*%%%%%%%%%%%%-------------Test Procedure---------%%%%%%%%%%%%%*/
  if( (flag = 'y') ){
  char *fname = new char(1);
  fstream File0;

  //

  name_the_report(File0,fname);
  report_header(File0,fname,runs);
  
  run_the_test(runs); //execute test
 // File0 << "hello" ;
  File0.close();


  
  }//end flag

  return 0;

  } //end main


int report_header(fstream& file, char* filename, int runs)
{
 file << "report header called\n";

 char PSPOH_SN[ ] = "CMSPH2-BRD00490";
 file << "PSPOH Test" << PSPOH_SN << endl;
 file << filename;

 time_t tt; //delcaring argument time()
 struct tm * ti; //declaring variable to store localtime()
 time(&tt); //applying time
 ti = localtime(&tt);

 file << "\n" << asctime(ti); //print timestamp
 //filename << "\n" << "Measurement samples in this test: "<< runs << "\n";
 file.close();
 cout << "report header called\n";
return 1;  
}

int run_the_test(int runs) {
   cout << "input SCPI command: ";
   string msg;
   cin >> msg;
   
   for (int i = 1; i <= runs; ++i) {
     cout << "\n" << i << ". ";
    //PSPOH myobject('h');     
    // msg = "this is an SPI.write command\n";  
     cout << msg << " ";
     
     int n = msg.length(); //assigning size value to string
     char msg_arr[n+1]; //declaring array
     strcpy(msg_arr, msg.c_str()); //copying the contents to the char array
     
     /*print array*/
     for (int i = 0; i < n; i++)
        cout << msg_arr[i] << " ";
     
    }
    cout << "\n";
    return 1;
}//end test

 int name_the_report(fstream& file,char *fname)
 { 
  

  int filecount = 0;
  //bool exists = false;
  //vector<string> files_to_check = {"results0.txt"};
  //file.open(fname);
  // for (const auto &file : files_to_check ) {
  //  exists(file) ? cout << "Exists\n" : cout << "Doesn't exist \n" ;
  // }
   //fopen( (*fname).c_str(), "r"); // if it exists fopen will return NULL ptr

  //  if ( !file) { //file does not exist
  //       fclose(*fname);
  //       exists = true;
  //   } else {
  //       exists = false;
  //   }   

   string name1 = "results0.txt";
   fname = new char(name1.length());

   
   ifstream ifile;
   ifile.open("results0.txt");

   while (ifile)
   { //rename file with increment until it doesn't exist
     filecount++ ;
     //ifile.back() = filecount;

     sprintf(fname,"results%03d.txt",filecount);  //replace the report number with the increment
     cout << "\nName before increment is "<< name1 ;
     name1 = fname; //name the report 
     size_t i;
     
    //  for ( i = 0; i < name1.length(); i++) //string turned to char array
    //  {
    //   name1[i] = name1[i];
    //  }

     //ifile.open(name1);
     cout << " Filecount " << filecount << " fname " << fname << " name1 " << name1 << endl;
     
    }
    
    cout << "\nCreating new file..";
    fstream File1(fname); //create new test report
    File1.open(fname, ios::in | ios:: out | ios::trunc);
    File1 << "\n" ;
    File1 << "\nWorking with existing file"<<"\n---\n\n";
    
    cout << "success "<< fname << " created. \n";
    cout << "\nWorking with existing file"<<"\n---\n\n";
    cout<<"\n";
    
  
   return 0;
 }

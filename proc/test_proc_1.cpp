#include<iostream>
#include <cstring>

using namespace std;

class PSPOH
{
  private:
  const char var;
  
  public:
  PSPOH(int constant_value):var(constant_value)
  {
   // cout << "Value is " << var << " \n";
  }
}; //end class

/*User input for data resolution of the test.*/
int numsamples() {
 
  cout << "how many samples in this test? ";
  int runs;
  cin >> runs; //select number of sample runs
  
  return runs;
}

/*Test Procedure*/
int testrun(int runs) {
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
    
    return 1;
}//end testrun


int main()
{
  int runs = numsamples();
  cout << "\nStart test? y = yes , n = no" <<endl;
  char flag = 'n';
  
  while ( flag != 'y') {  
  cin >> flag;
  }
  
  testrun(runs);
   
  return 0;
}//end main

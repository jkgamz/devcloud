#include <iostream>
#include <vector>
using namespace std;

int main(){

  vector<int> test;

  for(int i=0; i<6; i++){
    test.push_back(i);
  }

  cout << "Test Size: " << test.size() << endl;
  
  cout << "Test: ";
  
  for(int i=0; i<test.size(); i++){
    cout << test[i] << " ";
  }

  while(test.size()>0){
    test.erase(test.begin());
  }

  cout << endl;

  cout << "Test Size: " << test.size() << endl;
  cout << "Test: ";

  for(int i=0; i<test.size(); i++){
    cout << test[i]<< " ";
  }
  
  return 0;
  
}

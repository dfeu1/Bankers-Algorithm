#include <iostream>
#include <fstream>
#include <string>

using namespace std;
 
int main()
{
    ifstream inFile;
    inFile.open("input.txt");

    const int resources = 3;
    const int processes = 5;

    int allocation[processes][resources]; 
    int max[processes][resources];
    int available[resources]; 

    for (int i = 0; i < processes; ++i){
        for (int j = 0; j < resources; ++j){
            inFile >> allocation[i][j];
        }
    }

    for (int i = 0; i < processes; ++i){
        for (int j = 0; j < resources; ++j){
            inFile >> max[i][j];
        }
    }    

    for (int i = 0; i < resources; ++i){
        inFile >> available[i];
    }
    inFile.close();


    int store[processes]; 
    int safeseq[processes];    
    int index = 0;

    for (int k = 0; k < processes; k++) {
        store[k] = 0;
    }


    int need[processes][resources];
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++)
            need[i][j] = max[i][j] - allocation[i][j];
    }

    for (int k = 0; k < 5; k++) {
        for (int i = 0; i < processes; i++) {
            if (store[i] == 0) {
                int flag = 0;
                for (int j = 0; j < resources; j++) {
                    if (need[i][j] > available[j]) { 
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {

                    safeseq[index++] = i;

                    for (int d = 0; d < resources; d++)
                        available[d] += allocation[i][d];
                        store[i] = 1;
                }
            }
        }
    }


  int flag = 1; 
  for (int i = 0; i < processes; i++){
    if(store[i] == 0) {
        flag = 0;
        cout << "The given sequence is not safe\n";
        break;
    }
  }
 
  if(flag == 1) {
    cout << "Safe Sequence:" << endl;
    for (int i = 0; i < processes - 1; i++)
        cout << " P" << safeseq[i] << ", ";

    cout << " P" << safeseq[processes - 1] << endl;
  }
}

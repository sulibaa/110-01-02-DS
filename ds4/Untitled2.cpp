# include <iostream>
# include <fstream>
# include <string.h>
#include <ctime>
# include <vector>
# include <iomanip>

using namespace std;

struct NODE{
    string symbol;
    int  count;  
};

int main(){   
 NODE temp;
 vector<NODE> gem_list;
 
 temp.symbol = 'a';
 temp.count = 0;
 gem_list.push_back(temp);
 gem_list.push_back(temp);
 
 // .. 經過幾次push_back
 
 for(int i=0; i<gem_list.size(); i++)
 cout<<gem_list[i].symbol<<" "<<gem_list[i].count<<endl;
 
    return 0;
}

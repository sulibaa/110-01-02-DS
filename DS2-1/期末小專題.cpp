// 以第一次作業做任務四延伸 
#include <string> 
#include <iostream> 
#include <fstream> 
#include <cstdlib> 
#include <iomanip> 
#include <cstring> 

#include <vector>
#include <cstdio>
#include <ctime>
#include <sstream>
#include <math.h>
#include <stack> 
#include <algorithm>

using namespace std;

fstream fin ;

struct Data{
	int num;
	int studentNum;
};

struct Tree{
	float num;
	vector<Data> maxheap;
};

char* Str2char(string s){							
	char* str = new char[s.length() + 1]; 
	for(int a = 0; a < s.length(); a++) str[a] = s[a];
	str[s.length()] = '\0' ;
	return str;
} // Str2char()

class Btree{
	
	vector<Data> inputlist ;
	
	public : void create( string Num ){
		inputlist.clear() ;
		
		string fileName = "input" + Num + ".txt" ;
    	fin.open( fileName.c_str() ) ;
    	
    	string s1,s2; // 讀整行並以tab區隔之
    	for(int i = 0; i < 3; i++) getline(fin,s1); // 前三行
    	for ( int a = 1 ; getline(fin, s1) ; a++ ) {
    		s2 = strtok(Str2char(s1), "\t");
			s2 = strtok(NULL, "\t");
			s2 = strtok(NULL, "\t");
			s2 = strtok(NULL, "\t");
			s2 = strtok(NULL, "\t");
			
			if ( isdigit(s2[0]) && !s2.length() > 2 || s2[1] != ' ' ) ;
			else{
				s2 = strtok(NULL, "\t");
				if ( isdigit(s2[0]) && !(s2.length() > 2 && s2[1] == ' ') ) ;
				else s2 = strtok(NULL, "\t");
			} // else
			
			Data temp;
			
			temp.num = a;
			temp.studentNum = atoi(s2.c_str());
			inputlist.push_back(temp);
			
    	} // while
    	
    	sort();
	} // create()
	
	void sort(){
		int btree_Size = 0;
		for( int a = 1 ; 1 ; a = a * 2 ){
			btree_Size++;
			if( a * 2 >  inputlist.size() ) break;
		} // for
		
		Tree btree[btree_Size] ;
		for( int a = 0 ; a < btree_Size ; a++ ){
			btree[a].num = (float)a ;
		} // for
		
		for( int a = 0 ; a < inputlist.size() ; a++ ){
			if( btree[0].maxheap.size() == 0 ){
				btree[0].maxheap.push_back(inputlist[a]) ;
			} // if
			else{
				if( inputlist[a].studentNum >= btree[0].maxheap[0].studentNum ){
					btree[0].maxheap.insert( btree[0].maxheap.begin(), inputlist[a] );
				} // if
				else {
					btree[0].maxheap.insert( btree[0].maxheap.end(), inputlist[a] );
				} // else
			} // else
			
			for( int btree_num = 0 ; btree_num < btree_Size - 1 ; btree_num++ ){
				if( btree[btree_num].maxheap.size() > pow(  2.0 , btree[btree_num].num ) ){
					if( btree[btree_num+1].maxheap.size() == 0 ){
						for( int a = btree[btree_num].maxheap.size()-1 ; a >= 0 ; a-- )
							btree[btree_num+1].maxheap.insert(btree[btree_num+1].maxheap.begin(), btree[btree_num].maxheap[a]);
						btree[btree_num].maxheap.clear();
					} // if
					else if( btree[btree_num].maxheap[0].studentNum >= btree[btree_num+1].maxheap[0].studentNum ){
						for( int a = btree[btree_num].maxheap.size()-1 ; a >= 0 ; a-- )
							btree[btree_num+1].maxheap.insert(btree[btree_num+1].maxheap.begin(), btree[btree_num].maxheap[a]);
						btree[btree_num].maxheap.clear();
					} // else if
					else{
						for( int a = btree[btree_num].maxheap.size()-1 ; a >= 0 ; a-- )
							btree[btree_num+1].maxheap.insert(btree[btree_num+1].maxheap.end(), btree[btree_num].maxheap[a]);
						btree[btree_num].maxheap.clear();
					} // else
				} // if
				else {
					break;
				} // else
			} // for
		
		} // for
		
		cout << "roots:" << endl;
		for( int a = 0 ; a < btree_Size ; a++ ){
			if( btree[a].maxheap.size() != 0 ){
				cout << "[level " << a+1 << "] ";
				cout << "[" << btree[a].maxheap[0].num << "] " << btree[a].maxheap[0].studentNum << endl;
			} // if
				
		} // for
		cout << "bottom: " << endl;
		cout << "[" << btree[btree_Size-1].maxheap[btree[btree_Size-1].maxheap.size()-1].num << "] ";
		cout << btree[btree_Size-1].maxheap[btree[btree_Size-1].maxheap.size()-1].studentNum << endl;
	} // sort()
	
}; // Btree

int main(){
  Btree btree ;
  string Num ;
  do {
	cout << endl << "########################################################" ;
	cout << endl << "Mission 4: binomial heap" ;
    cout << endl << "########################################################" ;
	
    cout << "\n\nInput a file number (e.g., 101, 102, 103, ...[0] Quit): " ;
    
    cin >> Num ;
    string fileName = "input" + Num + ".txt" ;
    fin.open( fileName.c_str() ) ;
    while ( !fin.is_open() ) {
        if (Num == "0") break;
        cout << endl << "### file does not exist! ###" << endl;
        cout << endl << "Input a file number (e.g., 101, 102, 103, ...[0] Quit): ";
        cin >> Num;
        fileName = "input" + Num + ".txt";
      	fin.open( fileName.c_str() ) ;
    } // while
    fin.close();
    if (Num == "0") break;
    
    btree.create( Num );
    
  } while (1);
  
  cout << endl << "Bye Bye!" << endl;
} // main()

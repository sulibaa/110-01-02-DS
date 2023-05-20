/* 
DS2-4 
�ҵ{�W��: ��Ƶ��c�P�t��k
�}�үZ��: ��T�G��
�½ұЮv: �d�y�E�б� 
10827102 �H�f�� 10827146 ���r�O 
*/

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

struct Data {
	char putID[10];
	char getID[10];
	float weight;
};

struct DataP{
	float weight;
	int address;
};

string int2str(int i) {
  	string s;
  	stringstream ss(s);
  	ss << i;

  	return ss.str();
}

char* Str2char(string s){							
	char* str = new char[s.length() + 1]; 
	for(int a = 0; a < s.length(); a++) str[a] = s[a];
	str[s.length()] = '\0' ;
	return str;
} // Str2char()

static bool compare(const Data& node1, const Data& node2) {
    	return node1.weight > node2.weight;
}  // compare

class ExternalSort { 
	public : int numOflist;				// �`�@���X���ɮ� (�Ȯɤ����� 
	public : int timesOfDivide;			// �ĴX�������� 
	public : vector<DataP> plist ;		// �D����
	
	
	/*
	�s�y�ƭӤ����� 
	*/
	public: void createlist( string Num ){				
		string finName ; 			// ��J�ɦW 
		string foutName ;			// ��X�ɦW 
		fstream fin ;				// ��J�� 
		fstream fout ;				// ��X��  
		Data temp ;					// �Ȧs��J 
		
		int buffer_size = 200 ;			// �}�C�j�p 
		Data outlist[buffer_size] ;		// ��ư}�C
		
		finName = "pairs" + Num + ".bin";
		fin.open( finName.c_str(), fstream::in | fstream::binary ) ;
		fin.seekg(0, fin.end) ;
    	int fileSize = fin.tellg() / sizeof(temp) ;
    	fin.seekg(0, fin.beg);
    	
		numOflist = 0 ;
		timesOfDivide = 0 ;
		while ( 1 ) {
			foutName = "sorted" + Num + "_" + int2str(timesOfDivide + 1) + "_" + int2str(numOflist + 1) + ".bin";
			
			if( fileSize >= buffer_size ){
				fin.read((char*)outlist, sizeof(outlist));
				fileSize = fileSize - buffer_size ;
				
				stable_sort(outlist, outlist + buffer_size, compare);
				
				fout.open(foutName.c_str(), fstream::out | fstream::binary );
				fout.write((char*)&outlist, sizeof(outlist));
				fout.close();
				numOflist++;
			} // if
			else{
				buffer_size = fileSize ;
				Data outlist_2[buffer_size] ;
				
				fin.read((char*)outlist_2, sizeof(outlist_2));
				stable_sort(outlist_2, outlist_2 + buffer_size, compare);
				
				fout.open(foutName.c_str(), fstream::out | fstream::binary );
				fout.write((char*)&outlist_2, sizeof(outlist_2));
				fout.close();
				numOflist++;
				break;
			} // else
			
		} // while
		
		timesOfDivide++ ; 
		fin.close() ;
	} // create a list()
	
	public: void merge( string Num ){
		cout << "start merge";
		system("pause");
		string finName1, finName2 ; 				// ��J�ɦW
		string outputFileName ;						// ��X�ɦW 
		fstream fin1, fin2 ;						// ��J�� 
		fstream fout ;								// ��X�� 
		int numOfRun = ( numOflist + 1 ) / 2 ; 		// �n�X�ִX�� 
		
		vector<Data> outlist ;			
					
		int buffer_size = 200 ;						// �}�C�j�p 
		Data outtemp1[buffer_size] ;				// ��ư}�C
		Data outtemp2[buffer_size] ;				// ��ư}�C
		vector<Data> temp1, temp2 ;					// �Ȧs��ư}�C
		
    	for ( int a = 1 ; a <= numOfRun ; a++ ) { 
      		int divideNum1 = a * 2 - 1 ; 			// �����ɽs��1 
      		int divideNum2 = a * 2 ; 				// �����ɽs��2
      		outputFileName = "sorted" + Num + "_" + int2str(timesOfDivide + 1) + "_" + int2str(a) + ".bin";
      		fout.open(outputFileName.c_str(), fstream::out | fstream::binary );
        
      		if ( divideNum2 <= numOflist ) { 	// �L��J�ɮ� �� �ѤU��@�ɮ� 
        		finName1 = "sorted" + Num + "_" + int2str(timesOfDivide)+ "_" + int2str(divideNum1) + ".bin";
        		finName2 = "sorted" + Num + "_" + int2str(timesOfDivide)+ "_" + int2str(divideNum2) + ".bin";
        		fin1.open(finName1.c_str(), ios::in | ios::binary);
        		fin2.open(finName2.c_str(), ios::in | ios::binary);
        		
        		fin1.seekg(0, fin1.end) ;
    			int fileSize1 = fin1.tellg() / sizeof(temp1) ;		// ��Ƥ@�`��� 
    			fin1.seekg(0, fin1.beg) ;
    			fin2.seekg(0, fin2.end) ;
    			int fileSize2 = fin2.tellg() / sizeof(temp2) ;		// ��ƤG�`��� 
    			fin2.seekg(0, fin2.beg) ;
        		
        		bool temp1_over = true ;		// temp1 200���w�ĪŤF 
        		bool temp2_over = true ;		// temp2 200���w�ĪŤF 
        		
        		while( 1 ){
        			if( fileSize1 >= buffer_size && temp1_over ){		// ��Ƥ@��200����w�� 
						fin1.read((char*)outtemp1, sizeof(outtemp1));
						fileSize1 = fileSize1 - buffer_size ;
						for( int a = 0 ; a < buffer_size ; a++ ){
							temp1.push_back(outtemp1[a]);
						} // for
						temp1_over = false;
					} // if
					else if( fileSize1 < buffer_size && temp1_over ){	// �Ѿl��Ƥ@����w��
						buffer_size = fileSize1 ;
						fileSize1 = 0;
						Data outtemp1_last[buffer_size] ;
						
						fin1.read((char*)outtemp1_last, sizeof(outtemp1_last));
						for( int a = 0 ; a < buffer_size ; a++ ){
							temp1.push_back(outtemp1_last[a]);
						} // for
						temp1_over = false;
					} //else if
					
					if( fileSize2 >= buffer_size && temp2_over ){		// ��ƤG��200����w�� 
						fin2.read((char*)outtemp2, sizeof(outtemp2));
						fileSize2 = fileSize2 - buffer_size ;
						for( int a = 0 ; a < buffer_size ; a++ ){
							temp2.push_back(outtemp2[a]);
						} // for
						temp2_over = false;
					} // if
					else if( fileSize2 < buffer_size && temp2_over ){	// �Ѿl��ƤG����w��
						buffer_size = fileSize2 ;
						fileSize2 = 0;
						Data outtemp2_last[buffer_size] ;
						
						fin2.read((char*)outtemp2_last, sizeof(outtemp2_last));
						for( int a = 0 ; a < buffer_size ; a++ ){
							temp2.push_back(outtemp2_last[a]);
						} // for
						temp2_over = false;
					} //else if
					
					while ( 1 ) {
        				if( temp1[0].weight >= temp2[0].weight ){
        					outlist.push_back(temp1[0]);
        					temp1.erase(temp1.begin());
						} // if
						else{
							outlist.push_back(temp2[0]);
							temp2.erase(temp2.begin());
						} // else
						
						if( temp1.size() == 0 ){
							temp1_over = true;
							break;
						} // if
						else if( temp2.size() == 0 ){
							temp2_over = true;
							break;
						} // else if
        			} // while()
        		
        			if( fileSize1 == 0 && temp1_over ) {			// ��Ƥ@���� 
        				while(1){
        					while(1){
        						outlist.push_back(temp2[0]);
								temp2.erase(temp2.begin());	
								if( temp2.size() == 0 ) break;
							} // while
						
							if( fileSize2 == 0 ) break;
						
						
							if( fileSize2 >= buffer_size ){
								fin2.read((char*)outtemp2, sizeof(outtemp2));
								fileSize2 = fileSize2 - buffer_size ;
								for( int a = 0 ; a < buffer_size ; a++ ){
									temp2.push_back(outtemp2[a]);
								} // for
							}
							else{
								buffer_size = fileSize2 ;
								fileSize2 = 0;
								Data outtemp2_last[buffer_size] ;
						
								fin2.read((char*)outtemp2_last, sizeof(outtemp2_last));
								for( int a = 0 ; a < buffer_size ; a++ ){
									temp2.push_back(outtemp2_last[a]);
								} // for
							}
						} // while
						
						break;
					} // if
        			else if( fileSize2 == 0 && temp2_over ) {	// ��ƤG���� 
        				while(1){
        					while(1){
        						outlist.push_back(temp1[0]);
								temp1.erase(temp1.begin());	
								if( temp1.size() == 0 ) break;
							} // while
						
							if( fileSize1 == 0 ) break;
						
						
							if( fileSize1 >= buffer_size ){
								fin1.read((char*)outtemp1, sizeof(outtemp1));
								fileSize1 = fileSize1 - buffer_size ;
								for( int a = 0 ; a < buffer_size ; a++ ){
									temp1.push_back(outtemp1[a]);
								} // for
							}
							else{
								buffer_size = fileSize1 ;
								fileSize1 = 0;
								Data outtemp1_last[buffer_size] ;
						
								fin1.read((char*)outtemp1_last, sizeof(outtemp1_last));
								for( int a = 0 ; a < buffer_size ; a++ ){
									temp1.push_back(outtemp1_last[a]);
								} // for
							}
						} // while
						
						break;
					} // else if
					
				} // while
				for( int a = 0 ; a < outlist.size() ; a++ ){
					fout.write((char*)&outlist[a], sizeof(outlist[a]));
				} // for
				
        		fin1.close();
        		fin2.close();
        		fout.close();
        		temp1.clear();
        		temp2.clear();
        		outlist.clear();
        		remove(finName1.c_str());
        		remove(finName2.c_str());
        		
      		} // if()
      		else {	// �ѳ�@�ɮ� 
        		finName1 = "sorted" + Num + "_" + int2str(timesOfDivide)+ "_" + int2str(divideNum1) + ".bin";

        		fin1.open(finName1.c_str(), ios::in | ios::binary);
        		fin1.read((char*)&temp1, sizeof(temp1));

        		while ( fin1 ) {
          			fout.write((char*)&temp1, sizeof(temp1));
          			fin1.read((char*)&temp1, sizeof(temp1));
        		} // while()

        		fin1.close();
        		fout.close();
        		temp1.clear();
        		outlist.clear();
        		remove(finName1.c_str());
      		} // else
    	} // for
    	
    	timesOfDivide++;
    	numOflist = numOfRun;
    	cout << endl << "Now there are " << numOflist << " runs." << endl;
    	if( numOflist == 1 ){ // �`�X�֧��� 
    		writefile(Num);
    		numOflist--;
		} // if
		else if( numOflist > 1 ) {
			cout << "let return to merge" << endl;
			return merge(Num);
			cout << "cannt show";
 		} // else
		
		cout << "done"; 
		system("PAUSE");
		
	} // merge()
	
	private : void writefile( string Num ){
		string finName ;
		string foutName ;
		fstream fin ;
		fstream fout ;	
		Data temp ;
								
		finName = "sorted" + Num + "_" + int2str(timesOfDivide)+ "_1.bin";
		fin.open(finName.c_str(), fstream::in | fstream::binary );
	
    	fin.read((char*)&temp, sizeof(temp));
		
		foutName = "sorted" + Num + ".bin";
		fout.open(foutName.c_str(), fstream::out | fstream::binary );
		
		
		while ( fin ) {
			if( temp.weight == 0) break;
			fout.write((char*)&temp, sizeof(temp));
			fin.read((char*)&temp, sizeof(temp));
		} // while
		
		fin.close();
		fout.close();
		remove(finName.c_str());
	
	} // writefile()
	
	public : void primaryIndex( string Num ){
		fstream fin ;				// ��J�� 
		string finName ;			// ��J�ɦW 
		Data temp ;					// �Ȧs��J
		DataP ptemp;				// �Ȧs����
		float weightnow ;  			// �ثe�v�� 
		
		plist.clear();
		
		finName = "sorted" + Num + ".bin";
		fin.open(finName.c_str(), fstream::in | fstream::binary );
		
		fin.read((char*)&temp, sizeof(temp));
		ptemp.weight = temp.weight;
		ptemp.address = 0;
		weightnow = ptemp.weight;
		plist.push_back(ptemp);
		for ( int a = 1 ; fin ; a++ ) {
			fin.read((char*)&temp, sizeof(temp));
			if( temp.weight != weightnow  ){
				ptemp.weight = temp.weight;
				ptemp.address = a;
				weightnow = ptemp.weight;
				plist.push_back(ptemp);
			} // if
		} // for
		
		cout << endl << endl << "<Primary index>: (key, offset)" << endl;
		for( int a = 0 ; a < plist.size() ; a++ ){
			cout << "[" << a+1 << "] (";
			cout << plist[a].weight << ", " << plist[a].address << ")" << endl;
		} // for
	} // primaryIndex()
	
	public : void search( string Num, float dWeight ){
		fstream fin ;				// ��J�� 
		string finName ;			// ��J�ɦW
		int dAddress;
		Data temp;
		size_t length;
		
		for( int a = 0; a < plist.size(); a++ ){
			if(plist[a].weight < dWeight){
				dAddress = plist[a].address;
				break;
			} // if
		} // for 
		
		finName = "sorted" + Num + ".bin";
		fin.open(finName.c_str(), fstream::in | fstream::binary );
		
		for( int a = 0; a < dAddress; a++ ){
			fin.read((char*)&temp, sizeof(temp));
			cout << endl << "[" << a+1 << "]";
			cout << "\t" << temp.putID << "\t";
			length = strlen(temp.putID);
			if( length < 8 ) cout << "\t";
			cout << temp.getID << "\t";
			length = strlen(temp.getID);
			if( length < 8 ) cout << "\t";
			cout << temp.weight;
		} // for
		
		fin.close();
		
	} // search()
	
}; // ExternalSort 


int main(){
  int command;
  bool done1 = false;
  ExternalSort ex;
  string Num;
  double internalSortTime = 0;
  double externalSortTime = 0;
  float weight = 0;
  string key;
  
  do {
  	cout << endl << "***********************************************" ;
	cout << endl << "On-machine Exercise 05                        *" ;
	cout << endl << "Mission 1: External Merge Sort on a Big File  *" ;
	cout << endl << "Mission 2: Construction of Primary Index      *" ;
	cout << endl << "***********************************************" << endl ;
	cout << endl << "########################################################" ;
	cout << endl << "Mission 1: External merge sort" ;
    cout << endl << "########################################################" ;

    fstream fin ;
    cout << "\n\nInput a file number (e.g., 501, 502, 503, ...[0] Quit): ";
    cin >> Num;
    string fileName;
    fileName = "pairs" + Num + ".bin";
    fin.open( fileName.c_str(), fstream::in | fstream::binary ) ;
    while ( !fin.is_open() ) {
        if (Num == "0") break;
        cout << endl << "### file does not exist! ###" << endl;
        cout << endl << "Input a file number (e.g., 501, 502, 503, ...[0] Quit): ";
        cin >> Num;
        fileName = "pairs" + Num + ".bin";
      	fin.open( fileName.c_str(), fstream::in | fstream::binary ) ;
    } // while
	fin.close();
	if (Num == "0") break;
	
	internalSortTime = clock();
	ex.createlist( Num );
	internalSortTime = clock() - internalSortTime;
	externalSortTime = clock();
	ex.merge( Num );
	cout << "a";
	externalSortTime = clock() - externalSortTime;
	cout << endl << "The execution time ...";
	cout << endl << "Total Execution Time = " << internalSortTime + externalSortTime << "ms\n";
	
	system("pause");
	cout << endl << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
	cout << endl << "Mission 2: Build the primary index";
	cout << endl << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
	
	ex.primaryIndex( Num );
	
	system("pause");
	cout << endl << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
	cout << endl << "Mission 3: Threshold search on primary index";
	cout << endl << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
	
	do{
		cout << endl << "\nPlease input a threshold in the range [0,1]:" << endl;
		cin >> weight;
		ex.search( Num, weight );
		cout << endl << "\n[0]Quit or [Any other key]continue?" << endl;
		cin >> key;
		
	} while(key != "0");
	
  } while (1);
  
  cout << endl << "Bye Bye!" << endl;
} // main()

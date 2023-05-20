/* 
DS2-4 
�ҵ{�W��: ��Ƶ��c�P�t��k
�}�үZ��: ��T�G��
�½ұЮv: �d�y�E�б� 
10827102 �H�f��
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
		vector<Data> outlist ;		// �s200����ư}�C 
		Data temp ;					// �Ȧs��J 
		
		numOflist = 0 ;
		timesOfDivide = 0 ;
		finName = "pairs" + Num + ".bin";
		fin.open( finName.c_str(), fstream::in | fstream::binary ) ;
		while ( fin ) {
			outlist.push_back( temp );
			fin.read((char*)&temp, sizeof(temp)) ;
			if( outlist.size() == 400 ) { // �ѼƩT�w�b200 
				WeightSort(outlist);
				foutName = "sorted" + Num + "_" + int2str(timesOfDivide + 1) + "_" + int2str(numOflist + 1) + ".bin";
				fout.open(foutName.c_str(), fstream::out | fstream::binary );
      			for ( int a = 0 ; a < outlist.size() ; a++ ){
      				fout.write((char*)&outlist[a], sizeof(outlist[a]));
				} // for
      
      			fout.close();
				outlist.clear();
				numOflist++;
			} // if 
		} // while
		if( outlist.size() != 0 ) {
			WeightSort(outlist);
			foutName = "sorted" + Num + "_" + int2str(timesOfDivide + 1) + "_" + int2str(numOflist + 1) + ".bin";
			fout.open(foutName.c_str(), fstream::out | fstream::binary );
      		for ( int a = 0 ; a < outlist.size() ; a++ ){
      			fout.write((char*)&outlist[a], sizeof(outlist[a]));
			} // for
			
			fout.close();
			outlist.clear();
			numOflist++;
		} // if
	
		timesOfDivide++ ; 
		fin.close() ;
		
	} // create a list()
	
	public: void merge( string Num ){
		string finName1, finName2 ; 				// ��J�ɦW
		string outputFileName ;						// ��X�ɦW 
		fstream fin1, fin2 ;						// ��J�� 
		fstream fout ;								// ��X�� 
		int numOfRun = ( numOflist + 1 ) / 2 ; 		// �n�X�ִX�� 
		Data temp1, temp2 ;							// �Ȧs��J
		
    	for ( int a = 1 ; a <= numOfRun ; a++ ) { 
      		int divideNum1 = a * 2 - 1 ; 			// �����ɽs��1 
      		int divideNum2 = a * 2 ; 				// �����ɽs��2
			   
      		outputFileName = "sorted" + Num + "_" + int2str(timesOfDivide + 1) + "_" + int2str(a) + ".bin";
      		fout.open(outputFileName.c_str(), fstream::out | fstream::binary );
        
      		if ( divideNum2 <= numOflist ) { 	// �L��J�ɮ� �� �ѤU��@�ɮ� 
        		finName1 = "sorted" + Num + "_" + int2str(timesOfDivide)+ "_" + int2str(divideNum1) + ".bin";
        		finName2 = "sorted" + Num + "_" + int2str(timesOfDivide)+ "_" + int2str(divideNum2) + ".bin";
        
        		fin1.open(finName1.c_str(), ios::in | ios::binary);
        		fin1.read((char*)&temp1, sizeof(temp1));
        		fin2.open(finName2.c_str(), ios::in | ios::binary);
        		fin2.read((char*)&temp2, sizeof(temp2));
				
				// merge start
        		while ( fin1 && fin2 ) {	// �䤤�@���ɮ�Ū��		
          			if ( temp1.weight >= temp2.weight ) {  
            			fout.write((char*)&temp1, sizeof(temp1));
            			fin1.read((char*)&temp1, sizeof(temp1));
          			} // if()
          			else {
            			fout.write((char*)&temp2, sizeof(temp2));
           				fin2.read((char*)&temp2, sizeof(temp2));
         			} // else
        		} // while()
				
				// �N�t�@�ө|��Ū�Ū��ɮ�Ū��
			
				while ( fin1 ) {
          			fout.write((char*)&temp1, sizeof(temp1));
         			fin1.read((char*)&temp1, sizeof(temp1));
        		} // while()
			
        		while ( fin2 ) {
          			fout.write((char*)&temp2, sizeof(temp2));
          			fin2.read((char*)&temp2, sizeof(temp2));
        		} // while()
			
				
        		fin1.close();
        		fin2.close();
        		fout.close();
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
        		remove(finName1.c_str());
      		} // else
    	} // for
    	
    	timesOfDivide++;
    	numOflist = numOfRun;
    	cout << endl << "Now there are " << numOflist << " runs." << endl;
    	if( numOflist == 1 ){ // �`�X�֧��� 
    		writefile(Num);
		} // if
		else{
			merge(Num);
		} // else
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
	
	/*
	�̷��v���Ѥj�Ӥp�i��Ƨ� 
	*/
	private: void WeightSort(vector<Data> &outlist){
		for ( int i = outlist.size() - 1 ; i > 0 ; i-- ) {
			for ( int j = 0 ; j < i ; j++ ) {
				if ( outlist[j].weight < outlist[j+1].weight ) {
					swap( outlist[j], outlist[j+1] ) ;
				} // if 
			} // for
		} // for
	} // sortWeight()
	
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
	
	public : void searchWeight( string Num, float dWeight ){
		fstream fin ;				// ��J�� 
		string finName ;			// ��J�ɦW
		int dAddress;
		Data temp;
		size_t length;
		
		int a = 0;
		for( ; a < plist.size(); a++ ){
			if(plist[a].weight >= dWeight){
				;
			} // if
			else{
				break;
			} // else
		} // for 
		dAddress = plist[a].address;
		
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
		searchID(Num,dAddress);
		
	} // searchWeight()
	
	private : void searchID( string Num, int dAddress ){
		fstream fin ;				// ��J�� 
		string finName ;			// ��J�ɦW
		Data temp;
		size_t length;
		string putID, getID;
		
		cout << endl;
		system("pause");
		cout << endl << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
		cout << endl << "Mission 4: Threshold & ID search on primary index";
		cout << endl << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
		cout << endl << "Please input a putID (\"*\" print all ) :" ;
		cin >> putID;
		cout << endl << "Please input a getID (\"*\" print all ) :" ;
		cin >> getID;
		
		finName = "sorted" + Num + ".bin";
		fin.open(finName.c_str(), fstream::in | fstream::binary );
		
		int n;
		for( int a = 0 ; a < dAddress ; a++ ){
			fin.read((char*)&temp, sizeof(temp));
			if( putID == "*" ){
				if( getID == "*" ){
					cout << endl << "[" << n+1 << "]";
					cout << "\t" << temp.putID << "\t";
					length = strlen(temp.putID);
					if( length < 8 ) cout << "\t";
					cout << temp.getID << "\t";
					length = strlen(temp.getID);
					if( length < 8 ) cout << "\t";
					cout << temp.weight;
				} // if
				else if( strcmp( Str2char(getID), temp.getID ) == 0 ){
					cout << endl << "[" << n+1 << "]";
					cout << "\t" << temp.putID << "\t";
					length = strlen(temp.putID);
					if( length < 8 ) cout << "\t";
					cout << temp.getID << "\t";
					length = strlen(temp.getID);
					if( length < 8 ) cout << "\t";
					cout << temp.weight;
				}
				n++;
			} // if
			else if( strcmp( Str2char(putID), temp.putID ) == 0 ){
				if( getID == "*" ){
					cout << endl << "[" << n+1 << "]";
					cout << "\t" << temp.putID << "\t";
					length = strlen(temp.putID);
					if( length < 8 ) cout << "\t";
					cout << temp.getID << "\t";
					length = strlen(temp.getID);
					if( length < 8 ) cout << "\t";
					cout << temp.weight;
				} // if
				else if( strcmp( Str2char(getID), temp.getID ) == 0 ){
					cout << endl << "[" << n+1 << "]";
					cout << "\t" << temp.putID << "\t";
					length = strlen(temp.putID);
					if( length < 8 ) cout << "\t";
					cout << temp.getID << "\t";
					length = strlen(temp.getID);
					if( length < 8 ) cout << "\t";
					cout << temp.weight;
				} // else if
				n++;
			} // else if
		} // for
		
		fin.close();
		
	} // searchID()
	
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
		ex.searchWeight( Num, weight );
		cout << endl << "\n[0]Quit or [Any other key]continue?" << endl;
		cin >> key;
		
	} while(key != "0");
	
  } while (1);
  
  cout << endl << "Bye Bye!" << endl;
} // main()

/* 
DS2-2
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

#define COLUMNS 6
#define MAX_LEN 10
#define BIG_INT 255

using namespace std ;

struct sTtemp {
	char sid[MAX_LEN] ;
	char sname[MAX_LEN] ;
	unsigned char score[COLUMNS] ;
	float average ;
};

typedef struct sT {
	int num, hnum;
	char sid[MAX_LEN] ;
	char sname[MAX_LEN] ;
	unsigned char score[COLUMNS] ;
	float average ;
	sT* next ;
} studentType ;

double searchtime = 0; // success search
double unStime = 0; // unsuccess search

class Hash {

	studentType* head = NULL ;
	studentType* now = NULL ;
	
	/*
	txt��bin 
	*/
	void TxtToBin( string fileName ) {
		fstream inFile, outFile ;
		inFile.open( ( "input" + fileName + ".txt" ).c_str(), fstream::in ) ;
		outFile.open( ( "input" + fileName + ".bin" ).c_str(), fstream::out | fstream::binary ) ;
		if ( outFile.is_open() ) {
			char rBuf[BIG_INT] ;
			while ( inFile.getline( rBuf, BIG_INT, '\n') ) {
				string temp ;
				studentType oneSt ;
				int cNo = 0, pre = 0, pos = 0 ;
				
				temp.assign( rBuf ) ;
				pos = temp.find_first_of( '\t', pre ) ;
				
				while ( pos != string::npos ) {
					switch ( ++cNo ) {
						case 1: strcpy( oneSt.sid, temp.substr( pre, pos - pre ).c_str() ) ;
							break ;
						case 2: strcpy( oneSt.sname, temp.substr( pre, pos - pre ).c_str() ) ;
							break ;
						default: oneSt.score[cNo-3] = atoi( temp.substr( pre, pos - pre ).c_str() ) ;
							break ;
					} // end switch
					
					pre = ++pos ;
					pos = temp.find_first_of( '\t', pre ) ;
				} // while
				
				pos = temp.find_last_of( '\t' ) ;
				oneSt.average = atof( temp.substr( pos + 1 ).c_str() ) ;
				outFile.write((char*)&oneSt, sizeof(oneSt)) ;
				
			} // while
		
			outFile.close() ;
		
	    } // if
	    
	    inFile.close() ;
		 
	} // TxtToBin()
	
	/*
	struct sTtemp��sT�A�Ω�Ū�G�i���� 
	*/ 
	void tempTooneSt( sTtemp temp, studentType &oneSt ){
		for( int a = 0 ; a <= 10 ; a++ ){
			oneSt.sid[a] = temp.sid[a] ;
		} // for
		for( int a = 0 ; a <= 10 ; a++ ){
			oneSt.sname[a] = temp.sname[a] ;
		} // for
		
		for( int a = 0 ; a <= 6 ; a++ ){
			oneSt.score[a] = temp.score[a] ;
		} // for
					
		oneSt.average = temp.average ;
	} // tempTooneSt()
		
	/*
	�P�_�O�_����� 
	*/
	bool isPnum( int n ) { 
   		int i = 1 ;
    	int counter = 0;

        while ( i <= n ) {
            if ( n%i == 0 ) {
               	counter = counter+1;
            } // if
            	
           	i = i+1;
        } // while

        if ( counter == 2 ) {
           	return true ;
       	} // if
        	
        else {
           	return false ;
       	} // else 
        	
	} // isPnum()
	
	/*
	�Ǹ�ASCII�s�X�ۭ� 
	*/ 
	long long idMultiply(studentType oneSt){
		long long sum = 1 ;
		for ( int i = 0; oneSt.sid[i] != '\0'; i++ ) {
			sum = sum * oneSt.sid[i] ;
		} // for
		return sum;
	} // idMultiply()
	
	/*
	unseccess search time
	*/ 
	void getunStime(int hashSize){
		for( int a = 0; a < hashSize ; a++ ){
			now = head;
			while(now->num != a){
				now = now->next;
			} // while
			while(now->sid[0] != '\0'){
				if(now->num >= hashSize-1){
					now = head;
				} // if
				else now = now->next;
				
				unStime++;
				
			} // while
		} // for
	} // getunStime()
	
	/*
	M1 
	Ū�J�G�i���ɫ�A�гy�����M���t�j�p�A�̦���J��ơA�}�l�i��u�ʱ��� 
	*/
	void linearProbing( string fileName, bool isBin){
		searchtime = 0;
		unStime = 0;
		fstream binFile ;
		sTtemp temp;
		studentType oneSt ;
		int stNo = 0 ;
		binFile.open( fileName.c_str(), fstream::in | fstream::binary ) ;
		if ( binFile.is_open() ) {
			binFile.seekg (0, binFile.end) ;
			if( isBin ) stNo = binFile.tellg() / sizeof(temp) ;
			else stNo = binFile.tellg() / sizeof(oneSt) ;
			binFile.seekg (0, binFile.beg) ;
			
			int hashSize = stNo * 1.2 ;
			hashSize++ ;
			while ( !isPnum( hashSize ) ) {
				hashSize++ ;
			} // while
			
			head = NULL;
			head = new studentType() ;
			now = head ;
			
			for( int a = 0 ; a < hashSize ; a++ ) {
				now->num = a ;  
				now->next = new studentType() ;
				now = now->next ;
			} // while
			
			for ( int i = 0; i < stNo; i++ ) {
				if( isBin ){
					binFile.read((char*)&temp, sizeof(temp)) ;
					tempTooneSt(temp, oneSt);
				}
				else{
					binFile.read((char*)&oneSt, sizeof(oneSt)) ;
				} 
				insertLP( stNo, hashSize, oneSt ) ;
			} // for
			
			getunStime(hashSize);
			searchtime = searchtime / stNo;
			unStime = unStime / hashSize;	
		} // if
		
		binFile.close() ;
		
	} // linearProbing()
	
	/*
	M1
	�N��Ʃ�i���w��ƭӦ�m��(key)�A�p�G��e��m�̦���ư���I�� 
	*/
	void insertLP( int dataSize, int hashSize, studentType oneSt ) {
		searchtime++;
		now = head ;
		
		int key = idMultiply(oneSt) % hashSize ;

		while ( now->num < hashSize ) {
			
			if ( now->num == key ) {
				if ( now->sid[0] == '\0' ) {
					for( int a = 0 ; a <= 10 ; a++ ){
						now->sid[a] = oneSt.sid[a] ;
					} // for
					for( int a = 0 ; a <= 10 ; a++ ){
						now->sname[a] = oneSt.sname[a] ;
					} // for
		
					for( int a = 0 ; a <= 6 ; a++ ){
						now->score[a] = oneSt.score[a] ;
					} // for
					
					now->average = oneSt.average ;
					now->hnum = key ;
					break ;
				} // if
				else{
					collisionLP( dataSize, oneSt, key, hashSize ) ;
					break;
				}
			} // if
			else 
				now = now->next ;
		} // while
		
	} // insert()
	
	/*
	M1
	�N�ؼЦ�m���ʤ@��A�p�٦���ƫh�A���I���A�����m�̨S����� 
	*/ 
	void collisionLP( int dataSize, studentType oneSt, int key, int hashSize ) {
		searchtime++;	
		int aim = ( key + 1 ) % hashSize ;
		if( aim < key ) now = head;
		while( now->num != aim ){
			now = now->next;
		} // while
		while( now->sid[0] != '\0' ){
			searchtime++;
			int aimtemp = aim;
			aim = ( aim + 1 ) % hashSize ;
			if( aim < aimtemp ) now = head;
			while( now->num != aim ){
				
				now = now->next;
			} // while
		} // while
		
		for( int a = 0 ; a <= 10 ; a++ ){
			now->sid[a] = oneSt.sid[a] ;
			now->sname[a] = oneSt.sname[a] ;
		} // for
		
		for( int a = 0 ; a <= 6 ; a++ ){
			now->score[a] = oneSt.score[a] ;
		} // for
		
		now->average = oneSt.average ;
		now->hnum = key ;
		
	} // collision()
	
	/*
	M1 
	�N���G�g�J��linearfile�� 
	*/ 
	void writelinearFile( string name ) {
		
		name = "linear" + name ;
		char* doubleName = (char*)name.data() ;
		ofstream out( doubleName ) ;
		
		now = head ;
		int i = 0 ;
		out << " --- Hash Table X --- (linear probing)" << endl ;
		while ( now->next != NULL ) {
			out << "[" << now->num << "]\t" ;
			if( now->sid[0] != '\0' ) out << now->hnum << ",\t" << now->sid << ",\t" << now->sname << ",\t" << now->average << endl ;
			else out << endl;
			now = now->next ;
		} // while
		
	} // writelinearFile()
	
	/*
	M2
	Ū�J�G�i���ɫ�A�гy�����M���t�j�p�A�̦���J��ơA�}�l�i���������� 
	*/ 
	void doubleHash( string fileName, bool isBin ) {
		searchtime = 0;
		fstream binFile ;
		sTtemp temp;
		studentType oneSt ;
		int stNo = 0 ;
		binFile.open( fileName.c_str(), fstream::in | fstream::binary ) ;
		if ( binFile.is_open() ) {
			binFile.seekg (0, binFile.end) ;
			if( isBin ) stNo = binFile.tellg() / sizeof(temp) ;
			else stNo = binFile.tellg() / sizeof(oneSt) ;
			binFile.seekg (0, binFile.beg) ;
			
			int hashSize = stNo * 1.2 ;
			hashSize++ ;
			while ( !isPnum( hashSize ) ) {
				hashSize++ ;
			} // while
			
			head = NULL;
			head = new studentType() ;
			now = head ;
			
			for( int a = 0 ; a < hashSize ; a++ ) {
				now->num = a ;  
				now->next = new studentType() ;
				now = now->next ;
			} // while
			
			for ( int i = 0; i < stNo; i++ ) {
				if( isBin ){
					binFile.read((char*)&temp, sizeof(temp)) ;
					tempTooneSt(temp, oneSt);
				}
				else{
					binFile.read((char*)&oneSt, sizeof(oneSt)) ;
				} 
				insertDH( stNo, hashSize, oneSt ) ;
			} // for
			
		} // if
		searchtime = searchtime / stNo;
		binFile.close() ;
		
	} // doubleHash()
	
	/*
	M2 
	�N��Ʃ�i���w��ƭӦ�m��(key)�A�p�G��e��m�̦���ư���I�� 
	*/
	void insertDH( int dataSize, int hashSize, studentType oneSt ) {
		searchtime++;
		now = head ;
		
		int key = idMultiply(oneSt) % hashSize ;

		while ( now->num < hashSize ) {
			
			if ( now->num == key ) {
				if ( now->sid[0] == '\0' ) {
					for( int a = 0 ; a <= 10 ; a++ ){
						now->sid[a] = oneSt.sid[a] ;
					} // for
					for( int a = 0 ; a <= 10 ; a++ ){
						now->sname[a] = oneSt.sname[a] ;
					} // for
		
					for( int a = 0 ; a <= 6 ; a++ ){
						now->score[a] = oneSt.score[a] ;
					} // for
					
					now->average = oneSt.average ;
					now->hnum = key ;
					break ;
				} // if
				else{
					collisionDH( dataSize, oneSt, key, hashSize ) ;
					break;
				}
			} // if
			else 
				now = now->next ;
		} // while
		
	} // insert()
	
	/*
	M2
	��X�B����� 
	�N�ؼЦ�m���ʨ��ơA�p�٦���ƫh�A���I���A�����m�̨S����� 
	*/ 
	void collisionDH( int dataSize, studentType oneSt, int key, int hashSize ) {
		searchtime++;
		int maxStep = dataSize / 3 ;
		maxStep++;
		while( !isPnum( maxStep ) ) {
			maxStep++ ;
		} // while
		int step = maxStep - ( ( idMultiply(oneSt) % maxStep ) ) ;
		
		int aim = ( key + step ) % hashSize ;
		if( aim < key ) now = head;
		while( now->num != aim ){
			now = now->next;
		} // while
		while( now->sid[0] != '\0' ){
			searchtime++;
			int aimtemp = aim;
			aim = ( aim + step ) % hashSize ;
			if( aim < aimtemp ) now = head;
			while( now->num != aim ){
				now = now->next;
			} // while
		} // while
		
		for( int a = 0 ; a <= 10 ; a++ ){
			now->sid[a] = oneSt.sid[a] ;
			now->sname[a] = oneSt.sname[a] ;
		} // for
		
		for( int a = 0 ; a <= 6 ; a++ ){
			now->score[a] = oneSt.score[a] ;
		} // for
		
		now->average = oneSt.average ;
		now->hnum = key ;
		
	} // collision()
			
	/*
	M2 
	�N���G�g�J��doublefile�� 
	*/ 
	void writeDoubleFile( string name ) {
		
		name = "double" + name ;
		char* doubleName = (char*)name.data() ;
		ofstream out( doubleName ) ;
		
		now = head ;
		int i = 0 ;
		out << " --- Hash Table Y --- (double hashing)" << endl ;
		while ( now->next != NULL ) {
			out << "[" << now->num << "]\t" ;
			if( now->sid[0] != '\0' ) out << now->hnum << ",\t" << now->sid << ",\t" << now->sname << ",\t" << now->average << endl ;
			else out << endl;
			now = now->next ;
		} // while
		
	} // writeDoubleFile()
	
	/*
	�ˬd�ɮ׺��� 
	*/
	string checkFileName( string fileName ){
		fstream inFile;
		inFile.open( ( "input" + fileName + ".txt" ).c_str() ) ;
		if ( inFile.is_open() ) {
			inFile.close();
			return "txt";
		} // if()
		inFile.open( ( "input" + fileName + ".bin" ).c_str() ) ;
		if ( inFile.is_open() ) {
			inFile.close();
			return "bin";
		} // if()
		else return "nothing";
	} // checkFileName()
		
	/*	
	void print( string fileName ) {
		
		now = head ;
		if(now->num == 0) cout << "name is:" << now->sname << "\n";
		cout << " --- Hash Table Y --- (double hashing)\n";
		while ( now != NULL ) {
			cout << now->num << " " << now->sid << " " << now->sname << " " << now->score << " " << now->average << endl ;
			now = now->next ;
		} // while
		
	} // print()
	*/

	public : int Mission1() {
		
		string fileName ;
		string type; // ��Ƨ����ɮפ����� 
		bool isBin = false;
		do {
			cout << "\nInput a file number (e.g., 301, 302, 303, ...[0] Quit): ";
			cin >> fileName ;
			if ( !fileName.compare( "0" ) )
				return 1;
			type = checkFileName( fileName ) ; // ��Ƨ�����bin�Atxt�εL���ɮ� 
			if( type == "txt" ){
				TxtToBin( fileName ) ;
				isBin = false;
				break;
			}
			else if( type == "bin" ){
				isBin = true;
				break;
			}
			else{
				cout << "### file does not exist! ###\n";	
			}
			
		} while (true);
		
		linearProbing( "input" + fileName + ".bin", isBin ) ;
		writelinearFile(fileName);
		
		cout << endl << "Hash Table X has been created." << endl;
		cout << "unsuccessful search: " << fixed << setprecision(4) << unStime << " comparisons on average" << endl;
		cout << "successful search: " << fixed << setprecision(4) << searchtime << " comparisons on average" << endl;
		
		return 1 ;
	} // Mission1()
	
	
	public : int Mission2() {
		
		string fileName ;
		string type; // ��Ƨ����ɮפ����� 
		bool isBin = false;
		do {
			cout << "\nInput a file number (e.g., 301, 302, 303, ...[0] Quit): ";
			cin >> fileName ;
			if ( !fileName.compare( "0" ) )
				return 1;
			type = checkFileName( fileName ) ; // ��Ƨ�����bin�Atxt�εL���ɮ� 
			if( type == "txt" ){
				TxtToBin( fileName ) ;
				isBin = false;
				break;
			}
			else if( type == "bin" ){
				isBin = true;
				break;
			}
			else{
				cout << "### file does not exist! ###\n";	
			}
			
		} while (true);
		
		doubleHash( "input" + fileName + ".bin", isBin ) ;
		//print( "input" + fileName + ".bin" ) ;
		writeDoubleFile(fileName) ;

		cout << endl << "Hash Table Y has been created." << endl; 
		cout << "successful search: " << fixed << setprecision(4) << searchtime << " comparisons on average" << endl;
		
		return 1;
	} // Mission2()

	
	public : int Mission3() {
		
		return 1 ;
	} // Mission3()
	


} ; // class mission



int main(void) {
	int command = -1 ;
	Hash mission ;
	
	while ( command != 0 ) {
		int N, M = 0 ;
		cout << endl << "**** Hash                  ****" ;
		cout << endl << "* 0. Quit                     *" ;
		cout << endl << "* 1. Linear probing           *" ;
		cout << endl << "* 2. Double hash              *" ;
		cout << endl << "*******************************" ;
		cout << endl << "Input a coommand(0, 1, 2): " ;
		cin >> command ;   
		
		if ( command == 0 ) // ���O��0 
		    return 0 ;
		else if ( command == 1 ) { // ���O��1 
		    if ( mission.Mission1() == 0 )
				return 0 ;	 
		} // command == 1
		
		else if ( command == 2 ) {  // ���O��2 
		    if ( mission.Mission2() == 0 )
				return 0 ; 
		} // command == 2
		
		else if ( command == 3 ) {
			 if ( mission.Mission3() == 0 )
				return 0 ; 
		} // command == 3
		
		
		else { // ���O�H�W���O 
			cout << endl << "Command does not exist!" << endl ;
		} // command == else
		
	}  // while
	
	return 0 ;
}  // main()


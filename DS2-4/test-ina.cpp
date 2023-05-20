//10827208 ���t�Z 10827248 �L�i�u
 
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
#include <queue>

using namespace std ;


struct sTread { // �G�i��Ū�ɥ� 
	char putID[10];
	char getID[10];
	float weight;

};


struct sT2 { // ��bsT����vector type 
	char getID[10];
	float weight;

};


struct sT { // �D�}�C��vector type 
	char putID[10];
	vector<sT2> samePut;

};




string fileName ;


class AdjList {


	vector<sT> head; // �D�}�C 
	vector<sT> head2; // ����2�s��queue 
	vector<sT> head3; // ����3�s��stack 
	string name;
	sT temp;
	sT2 temp2;
	
	int position;
	int nodeNum;


	void BubbleSort(vector<sT> &answer) { // �w�j�Ƨ�(�Q�I�s��) // �D�}�C�Ƨǥ� // �HputID���Ƨ� 
		int i, j;
		string line;
		for (i = answer.size() - 1; i > 0; i--) {
			for (j = 0; j <= i - 1; j++) {
				/*
				if ( answer[j].putID > answer[j+1].putID ) {
					swap(answer[j], answer[j+1]) ;
				} // if
				*/

				if (strcmp(answer[j].putID, answer[j + 1].putID) > 0)
				{
					swap(answer[j], answer[j + 1]);
				} // if()

				else
					;
			} // for

		} // for

	} // BubbleSort() 


	void BubbleSort2(vector<sT2> &answer) { // �w�j�Ƨ�(�Q�I�s��) // �Hweight���Ƨ� 
		int i, j;
		string line;
		for (i = answer.size() - 1; i > 0; i--) {
			for (j = 0; j <= i - 1; j++) {
				if (answer[j].weight < answer[j + 1].weight) {
					swap(answer[j], answer[j + 1]);
				} // if 

				else
					;
			} // for

		} // for

	} // BubbleSort() 
	
	void BubbleSort3(vector<sT2> &answer) { // �w�j�Ƨ�(�Q�I�s��) // �HID���Ƨ� 
		int i, j;
		string line;
		for (i = answer.size() - 1; i > 0; i--) {
			for (j = 0; j <= i - 1; j++) {
				if ( strcmp(answer[j].getID, answer[j + 1].getID ) > 0 ) {
					swap(answer[j], answer[j + 1]);
				} // if 

				else
					;
			} // for

		} // for

	} // BubbleSort()
	
	void BubbleSort4(vector<sT> &answer) { // �w�j�Ƨ�(�Q�I�s��) // �H�v�T�O���Ƨ� 
		int i, j;
		string line;
		for (i = answer.size() - 1; i > 0; i--) {
			for (j = 0; j <= i - 1; j++) {
				if ( answer[j].samePut.size() < answer[j + 1].samePut.size() ) {
					swap(answer[j], answer[j + 1]);
				} // if 

				else
					;
			} // for

		} // for

	} // BubbleSort()


	void ReadFile(string fileName) {

		fstream binFile;
		sTread oneSt;
		int stNo = 0;
		binFile.open(fileName.c_str(), fstream::in | fstream::binary);
		if (binFile.is_open()) {

			binFile.seekg(0, binFile.end);
			nodeNum = stNo = binFile.tellg() / sizeof(oneSt);
			binFile.seekg(0, binFile.beg);


			position = 0;

			binFile.read((char*)&oneSt, sizeof(oneSt)); // Ū�Ĥ@�����

			strcpy(temp.putID, oneSt.putID); // �s�o�T��ID
			head.insert(head.end(), temp);

			strcpy(temp2.getID, oneSt.getID); // �s�o�T��ID 
			temp2.weight = oneSt.weight;
			head[position].samePut.insert(head[position].samePut.end(), temp2);

			//cout << oneSt.putID << " " << oneSt.getID << " " << oneSt.weight << endl ; 

			int j = 0;
			for (int i = 1; i < stNo; i++) {

				binFile.read((char*)&oneSt, sizeof(oneSt));

				insert(oneSt);

			} // for



			BubbleSort2(head[position].samePut); // ��samePut 

		} // if

		binFile.close();

	} // ReadFile()



	void insert(sTread oneSt) {

		if (strcmp(head[position].putID, oneSt.putID) == 0) { // �o�T��ID�@�� 

			strcpy(temp2.getID, oneSt.getID); // �s���T��ID 
			temp2.weight = oneSt.weight;

			head[position].samePut.insert(head[position].samePut.end(), temp2);



		} // if

		else { // �|���n�J��ID 

			BubbleSort2(head[position].samePut); // ��samePut 
			position++;

			strcpy(temp.putID, oneSt.putID); // �s�o�T��ID
			head.insert(head.end(), temp);

			strcpy(temp2.getID, oneSt.getID); // �s���T��ID 
			temp2.weight = oneSt.weight;

			head[position].samePut.insert(head[position].samePut.end(), temp2);
		} // else


	} // insert()



	void CheckNoSendID() { // ��O�_�������L�T�� ���S�ǹL�T����(�S�b�D�}�C�W) 

		int i = 0;
		int j = 0;

		while (i < head.size()) {

			j = 0;
			while (j < head[i].samePut.size()) {


				if (!HavePutID(head[i].samePut[j].getID)) { // �S�ǹL��ƪ�������ID

					int same = 0;
					while (same < head.size()) { // ��쥿�T���a���i�h 
						if (strcmp(head[i].samePut[j].getID, head[same].putID) < 0)
							break;
						same++;
					} // while

					strcpy(temp.putID, head[i].samePut[j].getID);
					head.insert(head.begin() + same, temp); // ���J�D�}�C���w��m 



				} // if

				j++;
			} // while

			i++;

		} // while


	} // CheckNoSendID()
	
	
	
	void CheckNoSendID2() { // ��O�_�������L�T�� ���S�ǹL�T����(�S�b�D�}�C�W) 

		int i = 0;
		int j = 0;

		while (i < head2.size()) {

			j = 0;
			while (j < head2[i].samePut.size()) {


				if (!HavePutID(head2[i].samePut[j].getID)) { // �S�ǹL��ƪ�������ID

					int same = 0;
					while (same < head2.size()) { // ��쥿�T���a���i�h 
						if (strcmp(head2[i].samePut[j].getID, head2[same].putID) < 0)
							break;
						same++;
					} // while

					strcpy(temp.putID, head2[i].samePut[j].getID);
					head2.insert(head2.begin() + same, temp); // ���J�D�}�C���w��m 



				} // if

				j++;
			} // while

			i++;

		} // while


	} // CheckNoSendID2()



	bool HavePutID(char getID[10]) { // �P�_�D�}�C�O�_��putID
		int i = 0;
		while (i < head.size()) {
			if (strcmp(head[i].putID, getID) == 0)
				return true;
			else
				i++;

		} // while

		return false;

	} // HaveGetID()



	void BFS()
	{
		vector<sT2> queue ;
		head2.clear();
		int i = 0 ;
		while ( i < head.size()  ) {
			
			strcpy(temp.putID, head[i].putID); // �s�o�T��ID
			head2.push_back( temp );
			
			int j = 0 ;
			while ( j < head[i].samePut.size() ) { // �N�᭱�����T�̩�iqueue 
				queue.push_back(head[i].samePut[j]) ;	
				j++ ;
			} // while
			
			while ( queue.size() > 0 ) { // queue�̭����F�� 
				
				strcpy(temp2.getID, queue[0].getID); // �N���T��ID��ihead2 
				head2[i].samePut.push_back(temp2);
				BubbleSort3(head2[i].samePut); // �HID���Ƨ�
		
				int x = 0 ;
				bool done = false ;
				while ( x < head2.size() ) { // �P�_�O�_�w���s�n���v�T�O
					if ( strcmp(head2[x].putID, queue[0].getID) == 0 ) {
						done = true ;
						break ;
					} // if
						
					else
						x++ ;
					
				} // while
		
				int k = 0;
				while ( k < head.size() ) {
					if ( done ){ // ��done�L���v�T�O�C��
						j = 0 ;
						
						while ( j < head2[x].samePut.size() ) { // �N�᭱�����T�̩�ihead2
							bool havesame = false; 
							int z = 0;
							
							while ( z < head2[i].samePut.size() ) { // �ˬd�O�_���� 
								if ( strcmp( head2[x].samePut[j].getID, head2[i].samePut[z].getID ) == 0 ||
									strcmp( head2[x].samePut[j].getID, head2[i].putID ) == 0 ) {
									havesame = true;
									break;
								} // if
								
								z++;
							} // while
							
							z = 0;
							while ( z < queue.size() ){
								if ( strcmp( head2[x].samePut[j].getID, queue[z].getID ) == 0 )
									queue.erase( queue.begin() + z) ;
								z++;
							} // while
							
							if( !havesame ) // �S�����ƴN��i�h 
								head2[i].samePut.push_back(head2[x].samePut[j]) ;  
							j++ ;
						} // while
						
						break;
					} // if
					
					else if ( strcmp(head[k].putID, queue[0].getID) == 0 ) { // �M��U�@��PutID �@�˴N�O���F 
						j = 0 ;
						
						while ( j < head[k].samePut.size() ) { // �N�᭱�����T�̩�iqueue
							bool havesame = false; 
							int z = 0;
							while ( z < head2[i].samePut.size() ) { // �ˬd�O�_���� 
								if ( strcmp( head[k].samePut[j].getID, head2[i].samePut[z].getID ) == 0 ||
									strcmp( head[k].samePut[j].getID, head2[i].putID ) == 0) {
									havesame = true;
									break;
								} // if
								z++;
							} // while
							
							z = 0;
							while( z < queue.size() ) { // �ˬd�O�_���� 
								if ( strcmp( head[k].samePut[j].getID, queue[z].getID ) == 0 ) {
									havesame = true;
									break;
								} // if
								z++;
							} // while
							
							if( !havesame ) // �S�����ƴN��i�h 
								queue.push_back(head[k].samePut[j]) ;  
							j++ ;
						} // while
						
						break ;
					} // else if	
					else
						k++;

				} // while
				
				queue.erase( queue.begin() ) ; // �R���̤@�}�l�� 
				
			} // while
			
			i++ ;
			
		} // while
		
		BubbleSort4(head2); // �H�v�T�O���Ƨ� 

	}// BFS
	
	
	
	void DFS( float num )
	{
		vector<sT2> stack ;
		head3.clear();
		int i = 0 ;
		
		while ( i < head.size()  ) {
			
			strcpy(temp.putID, head[i].putID); // �s�o�T��ID
			head3.push_back( temp );
			
			int j = 0 ;
			while ( j < head[i].samePut.size() && head[i].samePut[j].weight >= num ) { // �N�᭱�����T�̩�istack 
				stack.push_back(head[i].samePut[j]) ;	
				j++ ;
			} // while
			
			
			
			while ( stack.size() > 0 ) { // stack�̭����F�� 
			
				int del = stack.size() - 1;	// �n�R������m
			
				strcpy(temp2.getID, stack[del].getID); // �N���T��ID��ihead3 
				head3[i].samePut.push_back(temp2);
				
				BubbleSort3(head3[i].samePut); // �HID���Ƨ�
				
				int k = 0;
				while ( k < head.size() ) {
					if ( strcmp(head[k].putID, stack[del].getID) == 0 ) { // �M��U�@��PutID �@�˴N�O���F 
						j = 0 ;
						
						while ( j < head[k].samePut.size() ) { // �N�᭱�����T�̩�istack
							bool havesame = false; 
							int z = 0;
							while ( z < head3[i].samePut.size() ) { // �ˬd�O�_���� 
								if ( strcmp( head[k].samePut[j].getID, head3[i].samePut[z].getID ) == 0 ||
									strcmp( head[k].samePut[j].getID, head3[i].putID ) == 0) {
									havesame = true;
									break;
								} // if
								z++;
							} // while
							
							z = 0;
							while( z < stack.size() ) { // �ˬd�O�_���� 
								if ( strcmp( head[k].samePut[j].getID, stack[z].getID ) == 0 ) {
									havesame = true;
									break;
								} // if
								z++;
							} // while
							
							if( !havesame && head[k].samePut[j].weight >= num ) // �S�����ƴN��i�h 
								stack.push_back(head[k].samePut[j]) ;  
							j++ ;
						} // while
						
						break ;
					} // if	
					else
						k++;

				} // while
				
				
				stack.erase( stack.begin() + del ) ; // �R��
				
			} // while
			
			i++ ;
			
		} // while
		
		BubbleSort4(head3); // �H�v�T�O���Ƨ�

	}// DFS
	
	

	void writeFile(string name) { // �g�� 
		name = "pairs" + name + ".adj";
		char* oname = (char*)name.data(); //�Nstring�নchar* 
		ofstream out(oname);
		out << "<<< There are " << head.size() << " IDs in total. >>>" << endl;
		cout << "<<< There are " << head.size() << " IDs in total. >>>" << endl;
		int i = 1;

		while (i <= head.size()) {

			//cout << i << ":" << head.size() << endl ;

			out << "[ " << i << "] " << head[i - 1].putID << ":" << endl;

			int j = 1;

			while (j <= head[i - 1].samePut.size()) {

				//cout << j << ":" << head[i].samePut.size() << endl ;

				out << "\t" << "( " << j << ") " << head[i - 1].samePut[j - 1].getID << ", " << head[i - 1].samePut[j - 1].weight;
				//cout << "\t" << "( " << j << ") " << head[i-1].samePut[j-1].getID << ", " << head[i-1].samePut[j-1].weight ;

				if (j % 10 == 0)
					out << endl;

				j++;


			} // while

			out << endl;

			i++;

		} // while

		out << "<<< There are " << nodeNum << " nodes in total. >>>" << endl;
		cout << "<<< There are " << nodeNum << " nodes in total. >>>" << endl;

		out.close();

	} // writeFile()
	
	void writeFileToCnt(string name) { // �g�� 
		name = "pairs" + name + ".cnt";
		char* oname = (char*)name.data(); //�Nstring�নchar* 
		ofstream out(oname);
		out << "<<< There are " << head.size() << " IDs in total. >>>" << endl;
		cout << "<<< There are " << head.size() << " IDs in total. >>>" << endl;
		int i = 1;

		while (i <= head2.size()) {

			//cout << i << ":" << head.size() << endl ;

			out << "[ " << i << "] " << head2[i - 1].putID << "(" << head2[i - 1].samePut.size()  << "):" << endl ;

			int j = 1;

			while (j <= head2[i - 1].samePut.size()) {

				//cout << j << ":" << head[i].samePut.size() << endl ;

				out << "\t" << "( " << j << ") " << head2[i - 1].samePut[j - 1].getID ;
				//cout << "\t" << "( " << j << ") " << head[i-1].samePut[j-1].getID << ", " << head[i-1].samePut[j-1].weight ;

				if (j % 10 == 0)
					out << endl;

				j++;


			} // while

			out << endl;

			i++;

		} // while

		out.close();

	} // writeFileToCnt()
	
	void writeFileToInf(string name) { // �g�� 
		name = "pairs" + name + ".inf";
		char* oname = (char*)name.data(); //�Nstring�নchar* 
		ofstream out(oname);
		out << "<<< There are " << head.size() << " IDs in total. >>>" << endl;
		cout << "<<< There are " << head.size() << " IDs in total. >>>" << endl;
		int i = 1;

		while (i <= head3.size()) {

			//cout << i << ":" << head.size() << endl ;

			out << "[ " << i << "] " << head3[i - 1].putID << "(" << head3[i - 1].samePut.size()  << "):" << endl ;

			int j = 1;

			while (j <= head3[i - 1].samePut.size()) {

				//cout << j << ":" << head[i].samePut.size() << endl ;

				out << "\t" << "( " << j << ") " << head3[i - 1].samePut[j - 1].getID ;
				//cout << "\t" << "( " << j << ") " << head[i-1].samePut[j-1].getID << ", " << head[i-1].samePut[j-1].weight ;

				if (j % 10 == 0)
					out << endl;

				j++;


			} // while

			out << endl;

			i++;

		} // while

		out.close();

	} // writeFileToInf()	



public: int Mission1() {
	
	head.clear();
	
	string iName; // input�� 
	cout << endl << "Input a file number ([0]: quit):";
	cin >> name;
	if (name == "0")
		return 0; // �����{��  
	iName = "pairs" + name + ".bin"; // ��W�� 
	char* inputName = (char*)iName.data(); //�Nstring�নchar* 
	fstream input; // �ŧiinput 
	input.open(inputName, ios::in); // �N�nŪ�J���ɮ׶}�� 
	while (!input) { //��S���o��input�� 
		cout << endl << "### " << inputName << " does not exist! ### " << endl;
		cout << endl << "Input a file number ([0]: quit):";
		name = "";
		iName = "";
		inputName = NULL;
		cin >> name;
		if (name == "0")
			return 0;
		iName = "pairs" + name + ".bin";
		inputName = (char*)iName.data();
		input.open(inputName, ios::in);
	} // while
	
	fileName = name ;


	ReadFile(inputName); // �ƥD�}�C 

	CheckNoSendID(); // �N�S�ǹL��ƪ�������ID��i�D�}�C 

	BubbleSort(head);

	writeFile(name);

	head2.clear() ;
	head3.clear() ;

	position = 0;
	return 1;
} // Mission1()



public: int Mission2() {
	
	float cT ;
	cT = clock() ;
    BFS();	 
    cT = clock() - cT ;
    
    cout << "\nTime: " << cT * 1000 / CLOCKS_PER_SEC << " ms\n" << endl ;
    
	writeFileToCnt(fileName) ; 

	
	position = 0;
	return 1;
} // Mission2()




public: int Mission3() {
	
	float num ;
	
	cout << "Input a real number in [0,1]:" ;
	cin >> num ;
	
	while ( num < 0 || num > 1 ) {
		cout << "### It is NOT in [0,1] ###" << endl ;
		cout << "Input a real number in [0,1]:" ;
		cin >> num ;
	} // while
	
	
	DFS( num );
	
	writeFileToInf(fileName) ; 

	
	position = 0;
	return 1;


	return 1;
} // Mission3()



}; // class mission



int main(void) {
	int command = -1;
	AdjList mission;

	while (command != 0) {
		int N, M = 0;
		cout << endl << "***** Influence on a graph  ****";
		cout << endl << "* 0. Quit                      *";
		cout << endl << "* 1. Build adjacency lists     *";
		cout << endl << "* 2. Compute influence values  *";
		cout << endl << "* 3. Estimate influence values *";
		cout << endl << "********************************";
		cout << endl << "Input a coommand(0, 1, 2, 3): ";
		cin >> command;

		if (command == 0) // ���O��0 
			return 0;
		else if (command == 1) { // ���O��1 
			if (mission.Mission1() == 0)
				return 0;
		} // command == 1

		else if (command == 2) {  // ���O��2 
			if (mission.Mission2() == 0)
				return 0;
		} // command == 2

		else if (command == 3) {
			if (mission.Mission3() == 0)
				return 0;
		} // command == 3


		else { // ���O�H�W���O 
			cout << endl << "Command does not exist!" << endl;
		} // command == else

	}  // while

	return 0;
}  // main()

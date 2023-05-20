//10827208 王宇凡 10827248 林虹吟
 
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


struct sTread { // 二進位讀檔用 
	char putID[10];
	char getID[10];
	float weight;

};


struct sT2 { // 放在sT內的vector type 
	char getID[10];
	float weight;

};


struct sT { // 主陣列之vector type 
	char putID[10];
	vector<sT2> samePut;

};




string fileName ;


class AdjList {


	vector<sT> head; // 主陣列 
	vector<sT> head2; // 任務2存放之queue 
	vector<sT> head3; // 任務3存放之stack 
	string name;
	sT temp;
	sT2 temp2;
	
	int position;
	int nodeNum;


	void BubbleSort(vector<sT> &answer) { // 泡沫排序(被呼叫用) // 主陣列排序用 // 以putID做排序 
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


	void BubbleSort2(vector<sT2> &answer) { // 泡沫排序(被呼叫用) // 以weight做排序 
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
	
	void BubbleSort3(vector<sT2> &answer) { // 泡沫排序(被呼叫用) // 以ID做排序 
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
	
	void BubbleSort4(vector<sT> &answer) { // 泡沫排序(被呼叫用) // 以影響力做排序 
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

			binFile.read((char*)&oneSt, sizeof(oneSt)); // 讀第一筆資料

			strcpy(temp.putID, oneSt.putID); // 存發訊者ID
			head.insert(head.end(), temp);

			strcpy(temp2.getID, oneSt.getID); // 存發訊者ID 
			temp2.weight = oneSt.weight;
			head[position].samePut.insert(head[position].samePut.end(), temp2);

			//cout << oneSt.putID << " " << oneSt.getID << " " << oneSt.weight << endl ; 

			int j = 0;
			for (int i = 1; i < stNo; i++) {

				binFile.read((char*)&oneSt, sizeof(oneSt));

				insert(oneSt);

			} // for



			BubbleSort2(head[position].samePut); // 排samePut 

		} // if

		binFile.close();

	} // ReadFile()



	void insert(sTread oneSt) {

		if (strcmp(head[position].putID, oneSt.putID) == 0) { // 發訊者ID一樣 

			strcpy(temp2.getID, oneSt.getID); // 存收訊者ID 
			temp2.weight = oneSt.weight;

			head[position].samePut.insert(head[position].samePut.end(), temp2);



		} // if

		else { // 尚未登入的ID 

			BubbleSort2(head[position].samePut); // 排samePut 
			position++;

			strcpy(temp.putID, oneSt.putID); // 存發訊者ID
			head.insert(head.end(), temp);

			strcpy(temp2.getID, oneSt.getID); // 存收訊者ID 
			temp2.weight = oneSt.weight;

			head[position].samePut.insert(head[position].samePut.end(), temp2);
		} // else


	} // insert()



	void CheckNoSendID() { // 找是否有接收過訊息 但沒傳過訊息者(沒在主陣列上) 

		int i = 0;
		int j = 0;

		while (i < head.size()) {

			j = 0;
			while (j < head[i].samePut.size()) {


				if (!HavePutID(head[i].samePut[j].getID)) { // 沒傳過資料的接收者ID

					int same = 0;
					while (same < head.size()) { // 找到正確的地方放進去 
						if (strcmp(head[i].samePut[j].getID, head[same].putID) < 0)
							break;
						same++;
					} // while

					strcpy(temp.putID, head[i].samePut[j].getID);
					head.insert(head.begin() + same, temp); // 插入主陣列指定位置 



				} // if

				j++;
			} // while

			i++;

		} // while


	} // CheckNoSendID()
	
	
	
	void CheckNoSendID2() { // 找是否有接收過訊息 但沒傳過訊息者(沒在主陣列上) 

		int i = 0;
		int j = 0;

		while (i < head2.size()) {

			j = 0;
			while (j < head2[i].samePut.size()) {


				if (!HavePutID(head2[i].samePut[j].getID)) { // 沒傳過資料的接收者ID

					int same = 0;
					while (same < head2.size()) { // 找到正確的地方放進去 
						if (strcmp(head2[i].samePut[j].getID, head2[same].putID) < 0)
							break;
						same++;
					} // while

					strcpy(temp.putID, head2[i].samePut[j].getID);
					head2.insert(head2.begin() + same, temp); // 插入主陣列指定位置 



				} // if

				j++;
			} // while

			i++;

		} // while


	} // CheckNoSendID2()



	bool HavePutID(char getID[10]) { // 判斷主陣列是否有putID
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
			
			strcpy(temp.putID, head[i].putID); // 存發訊者ID
			head2.push_back( temp );
			
			int j = 0 ;
			while ( j < head[i].samePut.size() ) { // 將後面的收訊者放進queue 
				queue.push_back(head[i].samePut[j]) ;	
				j++ ;
			} // while
			
			while ( queue.size() > 0 ) { // queue裡面有東西 
				
				strcpy(temp2.getID, queue[0].getID); // 將收訊者ID放進head2 
				head2[i].samePut.push_back(temp2);
				BubbleSort3(head2[i].samePut); // 以ID做排序
		
				int x = 0 ;
				bool done = false ;
				while ( x < head2.size() ) { // 判斷是否已有存好的影響力
					if ( strcmp(head2[x].putID, queue[0].getID) == 0 ) {
						done = true ;
						break ;
					} // if
						
					else
						x++ ;
					
				} // while
		
				int k = 0;
				while ( k < head.size() ) {
					if ( done ){ // 有done過的影響力列表
						j = 0 ;
						
						while ( j < head2[x].samePut.size() ) { // 將後面的收訊者放進head2
							bool havesame = false; 
							int z = 0;
							
							while ( z < head2[i].samePut.size() ) { // 檢查是否重複 
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
							
							if( !havesame ) // 沒有重複就放進去 
								head2[i].samePut.push_back(head2[x].samePut[j]) ;  
							j++ ;
						} // while
						
						break;
					} // if
					
					else if ( strcmp(head[k].putID, queue[0].getID) == 0 ) { // 尋找下一個PutID 一樣就是找到了 
						j = 0 ;
						
						while ( j < head[k].samePut.size() ) { // 將後面的收訊者放進queue
							bool havesame = false; 
							int z = 0;
							while ( z < head2[i].samePut.size() ) { // 檢查是否重複 
								if ( strcmp( head[k].samePut[j].getID, head2[i].samePut[z].getID ) == 0 ||
									strcmp( head[k].samePut[j].getID, head2[i].putID ) == 0) {
									havesame = true;
									break;
								} // if
								z++;
							} // while
							
							z = 0;
							while( z < queue.size() ) { // 檢查是否重複 
								if ( strcmp( head[k].samePut[j].getID, queue[z].getID ) == 0 ) {
									havesame = true;
									break;
								} // if
								z++;
							} // while
							
							if( !havesame ) // 沒有重複就放進去 
								queue.push_back(head[k].samePut[j]) ;  
							j++ ;
						} // while
						
						break ;
					} // else if	
					else
						k++;

				} // while
				
				queue.erase( queue.begin() ) ; // 刪除最一開始的 
				
			} // while
			
			i++ ;
			
		} // while
		
		BubbleSort4(head2); // 以影響力做排序 

	}// BFS
	
	
	
	void DFS( float num )
	{
		vector<sT2> stack ;
		head3.clear();
		int i = 0 ;
		
		while ( i < head.size()  ) {
			
			strcpy(temp.putID, head[i].putID); // 存發訊者ID
			head3.push_back( temp );
			
			int j = 0 ;
			while ( j < head[i].samePut.size() && head[i].samePut[j].weight >= num ) { // 將後面的收訊者放進stack 
				stack.push_back(head[i].samePut[j]) ;	
				j++ ;
			} // while
			
			
			
			while ( stack.size() > 0 ) { // stack裡面有東西 
			
				int del = stack.size() - 1;	// 要刪除的位置
			
				strcpy(temp2.getID, stack[del].getID); // 將收訊者ID放進head3 
				head3[i].samePut.push_back(temp2);
				
				BubbleSort3(head3[i].samePut); // 以ID做排序
				
				int k = 0;
				while ( k < head.size() ) {
					if ( strcmp(head[k].putID, stack[del].getID) == 0 ) { // 尋找下一個PutID 一樣就是找到了 
						j = 0 ;
						
						while ( j < head[k].samePut.size() ) { // 將後面的收訊者放進stack
							bool havesame = false; 
							int z = 0;
							while ( z < head3[i].samePut.size() ) { // 檢查是否重複 
								if ( strcmp( head[k].samePut[j].getID, head3[i].samePut[z].getID ) == 0 ||
									strcmp( head[k].samePut[j].getID, head3[i].putID ) == 0) {
									havesame = true;
									break;
								} // if
								z++;
							} // while
							
							z = 0;
							while( z < stack.size() ) { // 檢查是否重複 
								if ( strcmp( head[k].samePut[j].getID, stack[z].getID ) == 0 ) {
									havesame = true;
									break;
								} // if
								z++;
							} // while
							
							if( !havesame && head[k].samePut[j].weight >= num ) // 沒有重複就放進去 
								stack.push_back(head[k].samePut[j]) ;  
							j++ ;
						} // while
						
						break ;
					} // if	
					else
						k++;

				} // while
				
				
				stack.erase( stack.begin() + del ) ; // 刪除
				
			} // while
			
			i++ ;
			
		} // while
		
		BubbleSort4(head3); // 以影響力做排序

	}// DFS
	
	

	void writeFile(string name) { // 寫檔 
		name = "pairs" + name + ".adj";
		char* oname = (char*)name.data(); //將string轉成char* 
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
	
	void writeFileToCnt(string name) { // 寫檔 
		name = "pairs" + name + ".cnt";
		char* oname = (char*)name.data(); //將string轉成char* 
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
	
	void writeFileToInf(string name) { // 寫檔 
		name = "pairs" + name + ".inf";
		char* oname = (char*)name.data(); //將string轉成char* 
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
	
	string iName; // input的 
	cout << endl << "Input a file number ([0]: quit):";
	cin >> name;
	if (name == "0")
		return 0; // 結束程式  
	iName = "pairs" + name + ".bin"; // 改名稱 
	char* inputName = (char*)iName.data(); //將string轉成char* 
	fstream input; // 宣告input 
	input.open(inputName, ios::in); // 將要讀入的檔案開啟 
	while (!input) { //當沒有這個input檔 
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


	ReadFile(inputName); // 排主陣列 

	CheckNoSendID(); // 將沒傳過資料的接收者ID放進主陣列 

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

		if (command == 0) // 指令為0 
			return 0;
		else if (command == 1) { // 指令為1 
			if (mission.Mission1() == 0)
				return 0;
		} // command == 1

		else if (command == 2) {  // 指令為2 
			if (mission.Mission2() == 0)
				return 0;
		} // command == 2

		else if (command == 3) {
			if (mission.Mission3() == 0)
				return 0;
		} // command == 3


		else { // 不是以上指令 
			cout << endl << "Command does not exist!" << endl;
		} // command == else

	}  // while

	return 0;
}  // main()

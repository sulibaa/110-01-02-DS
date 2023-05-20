// 10827111�K���� 10827102�H�f��
# include <iostream>
# include <fstream>
# include <string.h>
#include <ctime>
# include <vector>
# include <iomanip>

using namespace std;

bool quit = false;

struct Table{
	int OID = 0;
	int Arrival = 0;
	int Duration = 0;
	int TimeOut = 0;
};


class Mission {
 private:
 	int listLength, listSize;
 	int OID, Arrival, Duration, TimeOut;
 	int gap_of_shell_sort;
 	Table *changing_list;
 	Table *swap_list;
	
 public:
 	Mission(){ // Length = �`����	Size = �ثe�ƥ� 
 		listLength = 100, listSize = 0;
 		int OID = 0, Arrival = 0, Duration = 0, TimeOut = 0;
 		int gap_of_shell_sort = 0;
 		changing_list = new Table[listLength];
 		swap_list = new Table[listLength];
 		
	}
 	
  	void mission1(){
  		string file_number;
  		int Reading_data_times = 0, Sorting_data_times = 0, Writing_data_times = 0; // Ū��  �Ƨ�  �g�� 
  		clock_t start, stop; // �p�ɾ�
	   
  		cout << "\n" << "Input a file number (e.g., 401, 402, 403, ...): ";
  		cin >> file_number;
  		start = clock(); // Ū�ɭp�ɶ}�l 
  		string input_number = "input" + file_number + ".txt";
    	char* inputfile_name = new char[input_number.length()]; 
    	for ( int a = 0 ; a < input_number.length() ; a++ ) inputfile_name[a] = input_number[a];
    	ifstream fin;
    	fin.open(inputfile_name);
    
  		if( !fin ){ // �O�_������ 
  			cout << "\n" << "### " << inputfile_name << " does not exist! ###";
  			return getcommand();
		} // if 
		stop = clock(); // Ū�ɭp�ɵ���
		Reading_data_times = start - stop; // Ū�ɮɶ� 
	
		string sorted_number = "sorted" + file_number + ".txt";
		char* sortedfile_name = new char[sorted_number.length()];
		for ( int a = 0 ; a < sorted_number.length() ; a++ ) sortedfile_name[a] = sorted_number[a]; // ��sorted401.txt���W 
		ofstream fout(sortedfile_name); // �гysorted401.txt 
	
		
	
		string temp;
		getline(fin,temp); // ��0��D�Ʀr 		
		while(!fin.eof()){
			if(listSize == listLength) expansion_ListLength(); // ��Ƥ����n�X�R 
			fin >> OID >> Arrival >> Duration >> TimeOut;
	//		cout << OID << Arrival << Duration << TimeOut;
			changing_list[listSize].OID = OID; 
			changing_list[listSize].Arrival = Arrival;
			changing_list[listSize].Duration = Duration;
			changing_list[listSize].TimeOut = TimeOut;
			listSize++;
		} // while
		
		if(changing_list[listSize-1].OID == changing_list[listSize-2].OID ) listSize--; // ����input�|�h�@��"\n" 
		
		/*for(int i=0;i < listSize;i++)
			cout << changing_list[i].Arrival << "\n"; */
			
		start = clock(); // �Ƨǭp�ɶ}�l
		shell_sort(); // �ƺ��Ƨ� 
		stop = clock(); // �Ƨǭp�ɵ���
		Sorting_data_times = start - stop; // �ƧǮɶ� 
		
		start = clock(); // �g�ɭp�ɶ}�l
		fout << "OID" << "\t" << "Arrival" << "\t" << "Duration" << "\t" << "TimeOut" << "\n";
		for(int i = 0; i < listSize; i++){
			fout << changing_list[i].OID << "\t" << changing_list[i].Arrival << "\t" << changing_list[i].Duration << "\t" << changing_list[i].TimeOut << "\n";
		}
		stop = clock(); // �g�ɭp�ɵ���
		Writing_data_times = start - stop; // �g�ɮɶ� 
		
///////////////////////////////////////////////////////////////////////////////////////////////// mission1_print

		fin.close();
    	fin.open(inputfile_name);
		cout << "*** There are " << listSize << " jobs in total.\n\n";
		bool is_frist = true;
		for(int i = 0;i < listSize+1;i++){
			string s;
			getline(fin,s);
			if(is_frist) {
				cout << "   " << "\t" << s << "\n";
				is_frist = false;
			} // if
			else{
				cout << "(" << i << ")" << "\t" << s << "\n";
			}
		} // for
		
		system("pause");
		
		fout.close();
		fin.close();
		fin.open(sortedfile_name);
		cout << "\nh = " << gap_of_shell_sort << "\n";
		is_frist = true;
		for(int i = 0;i < listSize+1;i++){
			string s;
			getline(fin,s);
			if(is_frist) {
				cout << "   " << "\t" << s << "\n";
				is_frist = false;
			} // if
			else{
				cout << "(" << i << ")" << "\t" << s << "\n";
			}
		} // for
		
		system("pause");
		
		cout << "\nReading data: " << Reading_data_times << "ms\n\n";
		cout << "Sorting data:: " << Sorting_data_times << "ms\n\n";
		cout << "Writing data: " << Writing_data_times << "ms\n\n";
		
		system("pause");
		fin.close();
		fout.close();
		listSize = 0; // ��l�� 
		
  	} // mission1
  
  	void mission2(){

 	 } // mission2
 	 
 	void expansion_ListLength(){ //�X�R���� 
 		Table *tempList = changing_list;
 		changing_list = new Table[listLength * 10];
 		for(int a = 0;a < listLength; a++) changing_list[a] = tempList[a];
 		delete [] tempList;
 		listLength = listLength * 10;
	 } // expansion_ListLength()
 	 
 	
 	void shell_sort(){ // �ƺ��Ƨ� 
 		gap_of_shell_sort = listSize/2;
  	  	for(int h = listSize/2; h > 0 ; h = h/2){
  	  		for(int gap = h;gap < listSize; gap++){
  	  			int loc = gap;
				int nextA = changing_list[gap].Arrival;
				int nextO = changing_list[gap].OID;
				swap_list[0] = changing_list[gap];
				for(;(loc >= h) && ((changing_list[loc-h].Arrival > nextA) || (changing_list[loc-h].Arrival == nextA && changing_list[loc-h].OID > nextO)); loc = loc - h){
					changing_list[loc] = changing_list[loc-h];
				} // for
				changing_list[loc] = swap_list[0];
			} // for
		} // for
	} // shell_sort()
  
  
  	void getcommand(){  
   		int choice;
   		cout << "\n" ;
   		printf("**** Simulate FIFO Queues by SQF *****\n");
    	printf("* 0. Quit                            *\n");
    	printf("* 1. Sort a file                     *\n");
    	printf("* 2. Simulate one FIFO queue         *\n");
    	printf("**************************************\n");
    	printf("Input a command(0, 1, 2): ");
    	cin >> choice;
   	 	if(choice == 1) mission1();
    	else if(choice == 2) mission2();
   	 	else if(choice == 0) quit = true;
    	else getcommand();
  	} // getcommand
};

int main(){
 Mission mission ;
 mission.getcommand();
  while(!quit){
   mission.getcommand();
  } // while()
 
  return 0;
} // main

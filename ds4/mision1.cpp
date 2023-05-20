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

struct Table_Abort{
  int OID;
  int Delay;
  int Abort;
};

struct Table_Timeout{
  int OID;
  int Departure;
  int Delay;
};

class Mission {
 private:
 	int listLength, listSize;
 	int OID, Arrival, Duration, TimeOut;
 	int QueueLength, QueueSize, Queuenum;
 	int abortLength, abortSize;
 	int timeoutLength, timeoutSize;
 	int cooking_times; // ���ȤG�ثe�ɶ� 
 	int abort_num;
 	int timeout_num;
 	Table *changing_list,*swap_list,*Queue, now_list;
	Table_Abort *abort_list;
	Table_Timeout *timeout_list;
	bool firstQue, firstOrder;
	int now;
	
 public:
 	Mission(){ // Length = �`����	Size = �ثe�ƥ� 
 		listLength = 100, listSize = 0;
 		OID = 0, Arrival = 0, Duration = 0, TimeOut = 0;
 		QueueLength = 3, QueueSize = 0, Queuenum = 0;
 		abortLength = 100, abortSize = 0;
 		timeoutLength = 100, timeoutSize = 0;
 		cooking_times = 0; 
 		abort_num = 1;
 		timeout_num = 1;
 		changing_list = new Table[listLength];
 		swap_list = new Table[listLength];
 		Queue = new Table[QueueLength];
 		now_list ;
 		abort_list = new Table_Abort[abortLength];
 		timeout_list = new Table_Timeout[timeoutLength];
 		firstQue = false;
 		firstOrder = false;
 		now = 0; // �ثe�b�ĴX��
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
  			cout << "\n" << "### " << inputfile_name << " does not exist! ###\n";
  			return getcommand();
		} // if 
		stop = clock(); // Ū�ɭp�ɵ���
		Reading_data_times = stop - start ; // Ū�ɮɶ� 
	
		string sorted_number = "sorted" + file_number + ".txt";
		char* sortedfile_name = new char[sorted_number.length()];
		for ( int a = 0 ; a < sorted_number.length() ; a++ ) sortedfile_name[a] = sorted_number[a]; // ��sorted401.txt���W 
		ofstream fout(sortedfile_name); // �гysorted401.txt 
	
		
	
		string temp;
		getline(fin,temp); // ��0��D�Ʀr 		
		while(!fin.eof()){
			if(listSize == listLength) expansion_ListLength("changing_list"); // ��Ƥ����n�X�R 
			fin >> OID >> Arrival >> Duration >> TimeOut;
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
		Sorting_data_times = stop - start ; // �ƧǮɶ� 
		
		start = clock(); // �g�ɭp�ɶ}�l
		fout << "OID" << "\t" << "Arrival" << "\t" << "Duration" << "\t" << "TimeOut" << "\n";
		for(int i = 0; i < listSize; i++){
			fout << changing_list[i].OID << "\t" << changing_list[i].Arrival << "\t" << changing_list[i].Duration << "\t" << changing_list[i].TimeOut << "\n";
		}
		stop = clock(); // �g�ɭp�ɵ���
		Writing_data_times = stop - start; // �g�ɮɶ� 
		
///////////////////////////////////////////////////////////////////////////////////////////////// mission1_print

		fin.close();
    	fin.open(inputfile_name);
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
		
		cout << "\nReading data: " << Reading_data_times << "ms\n\n";
		cout << "Sorting data:: " << Sorting_data_times << "ms\n\n";
		cout << "Writing data: " << Writing_data_times << "ms\n\n";
		
		
		fout.close();
		fin.close();
		fin.open(sortedfile_name);
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
		fin.close();
		fout.close();
		listSize = 0; // ��l�� 
		
  	} // mission1
  
  
  
  	void mission2(){
  		string file_number;
  		cout << "\n" << "Input a file number (e.g., 401, 402, 403, ...): ";
  		cin >> file_number;
  		string input_number = "sorted" + file_number + ".txt";
    	char* inputfile_name = new char[input_number.length()]; 
    	for ( int a = 0 ; a < input_number.length() ; a++ ) inputfile_name[a] = input_number[a];
    	ifstream fin;
    	fin.open(inputfile_name);
    
  		if( !fin ){ // �O�_������ 
  			cout << "\n" << "### " << inputfile_name << " does not exist! ###\n";
  			return getcommand();
		} // if 
		
		string temp;
		getline(fin,temp); // ��0��D�Ʀr 		
		while(!fin.eof()){
			if(listSize == listLength) expansion_ListLength("changing_list"); // ��Ƥ����n�X�R 
			fin >> OID >> Arrival >> Duration >> TimeOut;
			if(Arrival + Duration <= TimeOut){ // �W�ɭq��h�� 
				changing_list[listSize].OID = OID; 
				changing_list[listSize].Arrival = Arrival;
				changing_list[listSize].Duration = Duration;
				changing_list[listSize].TimeOut = TimeOut;
				listSize++;
			} // if
		} // while
		
		if(changing_list[listSize-1].OID == changing_list[listSize-2].OID ) listSize--; // ����input�|�h�@��"\n"
		 
		now_list = changing_list[0]; // ��Ĥ@�����
		cooking_times = changing_list[0].Arrival + changing_list[0].Duration; // �Ĥ@�������ɶ�
		now++; 
	    update_QueueSize();
		while( now < listSize ||  QueueSize > 0 || now_list.OID != 99999) { 
	      if ( beforeCooking() ) {
		    Cooking();// �B�z�q��e�ˬd�O�_�W��
			InsertQueue(); 
			update_QueueSize();
	      } // if()
	      
	      if( Queue[0].OID != 0 ) { // QUEUE�̦����
		    now_list = Queue[0];   // �qQueue���Ĥ@�Ӯ���⤤  
		    takefrom_Queue();
		    update_QueueSize();
	      } // if()
	      else{ // QUEUE�̨S��ơA��@����ƨ�⤤
	      	if( now < listSize ){ // �P�_�O�_���Ƨ� 
	      	  now_list = changing_list[now]; 
		      cooking_times = changing_list[now].Arrival; 
			  now++; 	
			} // if()
			else{ // �⤤�L��� && QUEUE�̨S���
			  now_list.OID = 99999;	
			} // 
	      }	// else()
		} // while()
		
		int totaldelay = 0;
		float Failure_Percentage = 0;
		for(int i = 0;i < abortSize;i++){
		//	cout << abort_list[i].OID << "\n";
			Failure_Percentage++;
			totaldelay = totaldelay + abort_list[i].Delay;
		} // for
		for(int i = 0;i < timeoutSize;i++){
		//	cout << timeout_list[i].OID << "\n";
			Failure_Percentage++;
			totaldelay = totaldelay + timeout_list[i].Delay;
		} // for
		// cout << Failure_Percentage << "  " << listSize << "\n";
		Failure_Percentage = Failure_Percentage / listSize * 100;
		
///////////////////////////////////////////////////////////////////////////////////////////////// mission2_print		
		
		fin.close();
    	fin.open(inputfile_name);
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
		
		string output_number = "output" + file_number + ".txt";
		char* outputfile_name = new char[output_number.length()];
		for ( int a = 0 ; a < output_number.length() ; a++ ) outputfile_name[a] = output_number[a]; // ��output401.txt���W 
		ofstream fout(outputfile_name); // �гyoutput401.txt 
		
		fout << "\t" << "[Abort List]\n" << "\t" << "OID" << "\t" << "Delay" << "\t" << "Abort\n";
		for(int i = 0;i < abortSize;i++)
			fout << "[" << i+1 << "]" << "\t" << abort_list[i].OID << "\t" << abort_list[i].Delay << "\t" << abort_list[i].Abort << "\n";
		fout << "\t" << "[Timeout List]\n" << "\t" << "OID" << "\t" << "Delay" << "\t" << "Abort\n";
		for(int i = 0;i < timeoutSize;i++)
			fout << "[" << i+1 << "]" << "\t" << timeout_list[i].OID << "\t" << timeout_list[i].Delay << "\t" << timeout_list[i].Departure << "\n";
		fout << "[Total Delay]\n" << totaldelay << " min.\n";
		fout << "[Failure Percentage]\n" << fixed << setprecision(2) << Failure_Percentage << " %";
		
		fin.close();
		fout.close();
		listSize = 0; // ��l�� 
	} // mission2
	
	
	
	
	
	void update_QueueSize(){ // ��s�ثeQueueSize�j�p
	  int num = 0;
	  for( int a = 0 ; a < QueueLength ; a++ ) if( Queue[a].OID == 0) num++;
	  if( num == 3 ) QueueSize = 0; 
	  else if( num == 2 ) QueueSize = 1;
	  else if( num == 1 ) QueueSize = 2;
	  else QueueSize = 3;
	} // update_QueueSize
	
	void takefrom_Queue(){	//  �qQueue�����@�ӫ�A�᭱���� 
	  for( int k = 0 ; k < QueueSize - 1 ; k++ ) Queue[k] = Queue[k+1];
	  Queue[QueueSize-1].OID = 0; // �N�̫�@���k0 
	  Queue[QueueSize-1].Arrival = 0;
	  Queue[QueueSize-1].Duration = 0;
	  Queue[QueueSize-1].TimeOut = 0;
    } // takefrom_Queue
	
	void InsertQueue(){
	  while( now < listSize && changing_list[now].Arrival < cooking_times ){ // arrival�O�_�p��cooking_times
	  	if( QueueSize < 3 ){  // �P�_�O�_���s���T����ƦbQUEUE 
		  Queue[QueueSize].OID = changing_list[now].OID;
		  Queue[QueueSize].Arrival = changing_list[now].Arrival;
		  Queue[QueueSize].Duration = changing_list[now].Duration;
		  Queue[QueueSize].TimeOut = changing_list[now].TimeOut; 		
	  	  now++, QueueSize++;
		} // if()
		else { // �ĤT�������iabort 
		  if( abortSize == abortLength ) expansion_ListLength("Abort"); // �X�RABORT�Ŷ� 
		  abort_list[abortSize].OID = changing_list[now].OID;
		  abort_list[abortSize].Delay = 0;
		  abort_list[abortSize].Abort = changing_list[now].Arrival;
		  now++, abortSize++;	
		} // else if()
	  } // while()	
	} // InsertQueue()
	
	void Cooking(){ // �B�z�q��
	  int delay = cooking_times;
	  if( !firstQue ) firstQue = true;
	  else cooking_times = cooking_times + now_list.Duration;
	  
	  if( now_list.TimeOut < cooking_times ){ // �����o�{�W�� ���TIMEOUT 
	    int delayTime = delay - now_list.Arrival;  // DELAY = ��C���X�q�檺���m�ɨ� - �U��ɨ� 
	    if( timeoutSize == timeoutLength ) expansion_ListLength("Timeout"); // �P�_TIMEOUT���S���Ŷ��s 
		timeout_list[timeoutSize].OID = now_list.OID;
		timeout_list[timeoutSize].Departure = cooking_times;
		timeout_list[timeoutSize].Delay = delayTime;  
		timeoutSize++;
	  } // if() 
	} // Cooking()
	
	bool beforeCooking(){ // �B�z�q��e�ˬd�O�_�W�� 
		if( !firstOrder ){
	  		firstOrder = true;
	  		if( now_list.TimeOut < cooking_times ){  
	    		int delayTime = cooking_times - now_list.Arrival;// DELAY = QUEUE TIME(�����ɨ�ABORT = �X�q�檺���m�ɨ�) - Arrival 
				if( abortSize == abortLength ) expansion_ListLength("Abort"); // �P�_ABORT���S���Ŷ��s 
		  		abort_list[abortSize].OID = now_list.OID;
		  		abort_list[abortSize].Delay = delayTime; 
		  		abort_list[abortSize].Abort = cooking_times;
		  		abortSize++;	
		  		return false;
	    	} // if()	
	    	return true;
	  	} // if()
	  	else{
			if( now_list.TimeOut <= cooking_times ){  
	    		int delayTime = cooking_times - now_list.Arrival;// DELAY = QUEUE TIME(�����ɨ�ABORT = �X�q�檺���m�ɨ�) - Arrival 
		  		if( abortSize == abortLength ) expansion_ListLength("Abort"); // �X�RABORT�Ŷ� 
		  		abort_list[abortSize].OID = now_list.OID;
		  		abort_list[abortSize].Delay = delayTime; 
		  		abort_list[abortSize].Abort = cooking_times;
		  		abortSize++;	
		  		return false;
	    	} // if()	
	    	return true;
		} // else
	} // beforeCooking()	

 	 
 	void expansion_ListLength(string choice){ //�X�R���� 
 		if(choice == "changing_list"){ // changing_list
 			Table *tempList = changing_list;
 			changing_list = new Table[listLength * 10];
 			for(int a = 0;a < listLength; a++) changing_list[a] = tempList[a];
 			delete [] tempList;
 			listLength = listLength * 10;
 		} // if
      	else if( choice == "Abort" ){  // Abort  
        	Table_Abort *tempList = abort_list;
	    	abort_list = new Table_Abort[abortLength*5];	
	    	for( int k = 0 ; k < abortLength ; k++ ) abort_list[k] = tempList[k];
	    	delete [] tempList;
	    	abortLength = abortLength * 5;
	  	} // else if
	  	else if( choice == "Timeout" ){  // Timeout 
	    	Table_Timeout *tempList = timeout_list;
	    	timeout_list = new Table_Timeout[timeoutLength*5];	
	    	for( int k = 0 ; k < timeoutLength ; k++ ) timeout_list[k] = tempList[k];
	    	delete [] tempList;
	    	timeoutLength = timeoutLength * 5;
	  	} // else if
	 } // expansion_ListLength
 	 
 	
 	void shell_sort(){ // �ƺ��Ƨ� 
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

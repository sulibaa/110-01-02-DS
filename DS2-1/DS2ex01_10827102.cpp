// 10827102�H�f��
# include <iostream>
# include <fstream>
# include <string.h>
# include <iomanip>
# include <stdlib.h>

using namespace std;

bool quit = false;

struct item{
	string item_class; // max or min
	int school_num;
	int student_num;
};

class Mission {
 private:
	int listLength, listSize;
	int school_num, student_num;
	string item_class;
	item *list;

 public:
 	Mission(){
 		listLength = 100, listSize = 0;
 		school_num = 0, student_num = 0;
 		item_class;
 		list = new item[listLength];
	}
 	
  	void mission1(){
  		listSize = 0, listLength = 100;
  		string file_number;
  		cout << "\n" << "Input a file number ([0] Quit): ";
  		cin >> file_number;
  		string input_number = "input" + file_number + ".txt";
    	char* file_name = new char[input_number.length()]; 
    	for ( int a = 0 ; a < input_number.length() ; a++ ) file_name[a] = input_number[a];
    	ifstream fin;
    	fin.open(file_name);
    
  		if( !fin ){ // �O�_������ 
  			cout << "\n" << "### " << input_number << " does not exist! ###\n";
  			return mission1();
		} // if 
		
		string s1,s2; // Ū���åHtab�Ϲj�� 
		int node_num; // listSize���i�ܰʡA�Hnum���N�� 
		int Parent_node_num; // ���`�I
		for(int i = 0; i < 3; i++)getline(fin,s1); // �e�T��
		
		while (getline(fin, s1)) {
			if(listSize == listLength) expand_ListLength(); // ����X�R
			
		 	s2 = strtok(String_To_charPtr(s1), "\t");
			s2 = strtok(NULL, "\t");
			s2 = strtok(NULL, "\t");
			s2 = strtok(NULL, "\t");
			s2 = strtok(NULL, "\t");
			
			if ( isdigit(s2[0]) && !s2.length() > 2 || s2[1] != ' ' ) ;
			else{
				s2 = strtok(NULL, "\t");
				if ( isdigit(s2[0]) && !(s2.length() > 2 && s2[1] == ' ') ) ;
				else s2 = strtok(NULL, "\t");
			}
			
			list[listSize].school_num = listSize+1;
			list[listSize].student_num = String_To_Int(s2);
			
			//cout << list[listSize].student_num << "\n";
			
			if(listSize != 0){
				node_num = listSize; // �l�`�I��m
				
				 
		    	while(node_num != 0){
                    Parent_node_num = (node_num-1)/2; // ���`�I��m
		    		if(list[Parent_node_num].student_num >= list[node_num].student_num) break; // ���`�I��l�`�I�j 
		    		
					Swap(Parent_node_num,node_num); // �l���洫					 
					node_num = Parent_node_num; //�����`�I��

				} // while()
			}
		
			listSize++;
		}
		
		
		cout << "<max heap>\n";
		cout << "root: [" << list[0].school_num << "] " << list[0].student_num << "\n";
		cout << "bottom: [" << list[listSize-1].school_num << "] " << list[listSize-1].student_num << "\n";
		int leftmost_num;
		for(int i = 0;i <= listSize-1;i = i*2+1)leftmost_num = i;
		cout << "leftmost bottom: [" << list[leftmost_num].school_num << "] " << list[leftmost_num].student_num << "\n";
		
		fin.close();
  	} // mission1
  
  	void mission2(){
  		listSize = 1, listLength = 100;
  		string file_number;
  		cout << "\n" << "Input a file number ([0] Quit): ";
  		cin >> file_number;
  		string input_number = "input" + file_number + ".txt";
    	char* file_name = new char[input_number.length()]; 
    	for ( int a = 0 ; a < input_number.length() ; a++ ) file_name[a] = input_number[a];
    	ifstream fin;
    	fin.open(file_name);
    
  		if( !fin ){ // �O�_������ 
  			cout << "\n" << "### " << input_number << " does not exist! ###\n";
  			return mission2();
		} // if 
		
		string s1,s2; // Ū���åHtab�Ϲj��
		int level = 1; // node�����h 
		int node_num; // listSize���i�ܰʡA�Hnum���N�� 
		int Parent_node_num; // ���`�I
		for(int i = 0; i < 3; i++)getline(fin,s1); // �e�T��
		
		while (getline(fin, s1)) {
			if(listSize == listLength) expand_ListLength(); // ����X�R
			
		 	s2 = strtok(String_To_charPtr(s1), "\t");
			s2 = strtok(NULL, "\t");
			s2 = strtok(NULL, "\t");
			s2 = strtok(NULL, "\t");
			s2 = strtok(NULL, "\t");
			
			if ( isdigit(s2[0]) && !s2.length() > 2 || s2[1] != ' ' ) ;
			else{
				s2 = strtok(NULL, "\t");
				if ( isdigit(s2[0]) && !(s2.length() > 2 && s2[1] == ' ') ) ;
				else s2 = strtok(NULL, "\t");
			}
			
			list[listSize].school_num = listSize;
			list[listSize].student_num = String_To_Int(s2);
			if(listSize == 1) list[listSize].item_class = "min";
			else if(listSize == 2) {
				list[listSize].item_class = "max"; // �e�ⵧ���� 
				if(list[1].student_num > list[2].student_num) Swap(1,2);
			} 
			
			if(listSize > 2){
				node_num = listSize; // �l�`�I��m
				Parent_node_num = (node_num-1)/2; // ���`�I��m
				
				if(list[Parent_node_num].item_class == "min"){ // �̤p��n 
					if(list[listSize-1].item_class == "max") level++; //�s���@�h 
					list[listSize].item_class = "min"; // ������min
					int c_node_num = 1; // �����`�I 
					for(int a = 1;a < level;a++) c_node_num = c_node_num * 2;
					c_node_num = ( ( node_num + c_node_num ) - 1 ) / 2 ; // �����I�L��ơA�P����`�I��� 
					if(list[c_node_num].student_num < list[node_num].student_num) {
						Swap(c_node_num,node_num);
						while(c_node_num > 2){
                    		Parent_node_num = (c_node_num-1)/2; // ���`�I��m
		    				if(list[Parent_node_num].student_num <= list[c_node_num].student_num) break; // ���`�I��l�`�I�p 
		    		
							Swap(Parent_node_num,c_node_num); // �l���洫					 
							c_node_num = Parent_node_num; //�����`�I��

						}
					} 
					while(node_num > 1){
                    	Parent_node_num = (node_num-1)/2; // ���`�I��m
		    			if(list[Parent_node_num].student_num <= list[node_num].student_num) break; // ���`�I��l�`�I�p 
		    		
						Swap(Parent_node_num,node_num); // �l���洫					 
						node_num = Parent_node_num; //�����`�I��

					}
					
				}
				else{ // �̤j��n 
					list[listSize].item_class = "max"; // ������max 
					int c_node_num = 1; // �����`�I 
					for(int a = 1;a < level;a++) c_node_num = c_node_num * 2;
					c_node_num = node_num - c_node_num;
					if(list[c_node_num].student_num > list[node_num].student_num) {
						Swap(c_node_num,node_num);
						while(c_node_num > 1){
                    		Parent_node_num = (c_node_num-1)/2; // ���`�I��m
		    				if(list[Parent_node_num].student_num <= list[c_node_num].student_num) break; // ���`�I��l�`�I�p 
		    		
							Swap(Parent_node_num,c_node_num); // �l���洫					 
							c_node_num = Parent_node_num; //�����`�I��

						}
					}
					while(node_num > 2){
                    	Parent_node_num = (node_num-1)/2; // ���`�I��m
		    			if(list[Parent_node_num].student_num >= list[node_num].student_num) break; // ���`�I��l�`�I�j 
		    		
						Swap(Parent_node_num,node_num); // �l���洫					 
						node_num = Parent_node_num; //�����`�I��

					} // while()
				}
			}
			for(int a = 1; a < listSize; a++)cout << list[a].student_num << "\n";
			system("pause");
			listSize++;
		}
		
		
		cout << "<DEAP>\n";
		cout << "bottom: [" << list[listSize-1].school_num << "] " << list[listSize-1].student_num << "\n";
		int leftmost_num;
		for(int i = 0;i <= listSize-1;i = i*2+1)leftmost_num = i;
		cout << "leftmost bottom: [" << list[leftmost_num].school_num << "] " << list[leftmost_num].student_num << "\n";
		
		fin.close();
	} // mission2
	
	void mission3(){
		cout << "not yet" << "\n";
	} // mission3 
	
	void expand_ListLength(){ //�X�R��� 
 		item *tempList = list;
 		list = new item[listLength * 10];
 		for(int a = 0;a < listLength; a++) list[a] = tempList[a];
 		delete [] tempList;
 		listLength = listLength * 10;
	 } // expansion_ListLength
	 
	void Swap(int num1,int num2){
		item *templist = new item;
		templist->school_num = list[num1].school_num;
		templist->student_num = list[num1].student_num;
		list[num1].school_num = list[num2].school_num;
		list[num1].student_num = list[num2].student_num;
		list[num2].school_num = templist->school_num;
		list[num2].student_num = templist->student_num;
		
	} 
	
	char* String_To_charPtr(string s){
		char* fileName = new char[s.length() + 1]; 
		for(int a = 0; a < s.length(); a++) fileName[a] = s[a];
		fileName[s.length()] = '\O' ;
		return fileName;
	}
	
	int String_To_Int(string s){
		int re = 0;
		for(int a = 0;a < s.length(); a++){
			re = re * 10;
			if(s[a] == '0') re = re + 0;
			else if(s[a] == '1') re = re + 1;
			else if(s[a] == '2') re = re + 2;
			else if(s[a] == '3') re = re + 3;
			else if(s[a] == '4') re = re + 4;
			else if(s[a] == '5') re = re + 5;
			else if(s[a] == '6') re = re + 6;
			else if(s[a] == '7') re = re + 7;
			else if(s[a] == '8') re = re + 8;
			else if(s[a] == '9') re = re + 9;
		}
		
		return re;
	}
	
  	void getcommand(){  
   		int choice;
   		cout << "\n" ;
   		printf("**** Heap Construction *****\n");
    	printf("* 0. QUIT                  *\n");
    	printf("* 1. Build a max heap      *\n");
    	printf("* 2. Build a DEAP          *\n");
    	cout << "*************************************" << "\n";
    	printf("Input a command(0, 1, 2): ");
    	cin >> choice;
   	 	if(choice == 1) mission1();
    	else if(choice == 2) mission2();
    	else if(choice == 3) mission3();
   	 	else if(choice == 0) quit = true;
    	else {
    		cout << "\n" << "Command does not exist!" << "\n";
		  	getcommand();
		}
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

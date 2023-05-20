// 10827111�K���� 10827102�H�f��
# include <iostream>
# include <fstream>
# include <string.h>
# include <vector>
# include <iomanip>
# include <stdlib.h>

using namespace std;

bool quit = false;

struct tree {
	string name, type1, type2, num, total, hp, attack, defense, spA, spD, speed, generation, legendary;
	int n; // �ĴX����� 
	tree *left = NULL;
	tree *right = NULL;
};

struct pokemon_data { // ���_�_������� 
	string name, type1, type2, num, total, hp, attack, defense, spA, spD, speed, generation, legendary;
	int n; // �ĴX����� 
};

class Mission {
 private:
 	string name, type1, type2, num, total, hp, attack, defense, spA, spD, speed, generation, legendary;
 	int listLength, listSize, listSize2;
 	int n;
 	bool had_mission1, had_mission2;
 	pokemon_data *list;
 	pokemon_data *list2;
	pokemon_data *remove_root; 
 	tree *tree1;
 	tree *tree2;
 	tree *treerun;

 public:
 	Mission(){ // Length = �`����	Size = �ثe�ƥ� 
 		string name, type1, type2, num, total, hp, attack, defense, spA, spD, speed, generation, legendary;
 		listLength = 100, listSize = 0, listSize2 = 0;
 		n = 0;
 		had_mission1 = false;
 		had_mission2 = false;
 		list = new pokemon_data[listLength];
 		list2 = new pokemon_data[listLength]; // �n�Q�R���ëO�d���}�C 
 		remove_root = new pokemon_data; // �n�O�d�I�R������� 
		tree1 = new tree; // ���Ȥ@���� 
		// tree2 = new tree; // ���ȤG����	
		treerun	= tree1; // ��treerun�]��
	}
 	
  	void mission1(){
  		list = new pokemon_data[listLength];
  		tree1 = new tree;
  		n = 0;
  		treerun = tree1;
  		listSize = 0; // ��l��
		
  		string file_number;
  		cout << "\n" << "Input a file number (e.g., 601, 602, 603, ...): ";
  		cin >> file_number;
  		string input_number = "input" + file_number + ".txt";
    	char* inputfile_name = new char[input_number.length()]; 
    	for ( int a = 0 ; a < input_number.length() ; a++ ) inputfile_name[a] = input_number[a];
    	ifstream fin;
    	fin.open(inputfile_name);
    
  		if( !fin ){ // �O�_������ 
  			cout << "\n" << "### " << inputfile_name << " does not exist! ###\n";
  			return getcommand();
		} // if 
		
		string temp;
		getline(fin,temp); // ��0�欰���D�A�]���L��
		while(!fin.eof()){
			if(listSize == listLength) expansion_ListLength(); // �ʺA�}�C��Ƥ����A�W�[�}�C��� 
			getline(fin,temp); // ���Ʀr�M��r�V���A���i����Ū��
			if(temp == "\0") break; // ����h�]�@���j�� 
			put_into_list(temp); // �N�Ʀr�P��r�V�X���@����O�s�i�}�C�� 
			listSize++;
		} // while 
	
	  	bool found = false; // �O�_���𪺳̩��h  
		put_into_tree1(); // �Nlist[n]����ƽƻs��tree1�� 
		n++;
		int level = 0, maxlevel = 0; // �h�ƩM�̤j�h�� 
		while(n < listSize){ // �`����L���
			// cout << n  << "\n";
			level = 1;
			treerun = tree1; // �^��𪺶}�Y 
			found = false; 
			while(!found){ // ���ک������� 
				if(atoi(list[n].hp.c_str()) < atoi(treerun->hp.c_str())){ // hp�p��ثe��� 
					if(treerun->left == NULL){ // ����쩳 
						treerun->left = new tree;  // ����s�W�Ŷ�
						treerun = treerun->left; // �e���s�W�Ŷ� 
						put_into_tree1();  // �Nlist[n]����ƽƻs��tree1��
						n++;
						found = true; // ����y
					}
					else {
						treerun = treerun->left; // �����٨S�쩳 
					}
				}
				else if(atoi(list[n].hp.c_str()) >= atoi(treerun->hp.c_str())){ // hp�j�󵥩�ثe��� 
					if(treerun->right == NULL){ // �k��쩳 
						treerun->right = new tree;  // �k��s�W�Ŷ� 
						treerun = treerun->right; // �e���s�W�Ŷ� 
						put_into_tree1();  // �Nlist[n]����ƽƻs��tree1��
						n++;
						found = true; // ����y 
					}
					else {
						treerun = treerun->right; // �k���٨S�쩳 
					}
					
				}
				
				level++;
			}
			
			if(level > maxlevel) maxlevel = level; // ��̤j�h�Ƥj�N�]���̤j�h�� 
		}
		
		print_list(1); // �L�X�ɮ� 
		
		cout << "HP tree height = " << maxlevel << "\n";
		
		treerun = tree1;
		while(treerun->left != NULL){
			treerun = treerun->left;
		}
		cout << "Leftmost node:" << "\n";
		print_node(); // �L�X�̥����`�I 
		treerun = tree1;
		while(treerun->right != NULL){
			treerun = treerun->right;
		}
		cout << "Rightmost node:" << "\n";
		print_node(); // �L�X�̥k���`�I 
		had_mission1 = true; // �]�L�@�����Ȥ@�A�i�H������ȤG 
		return getcommand();
  	} // mission1
  
  
  
  	void mission2(){
  		if(had_mission1 == false){ // �|��������Ȥ@ 
  			cout << "\n" << "----- Execute Mission 1 first! -----" << "\n";
			return getcommand(); 	
		}
  		int flor = 0;
  		int place = 0;
  		bool even = false;
  		// cout << listSize; 
  		if ( listSize % 2 == 0 ) {
		  place = ( listSize - 1 ) / 2;
		  even = true; 
  		} //
		else place = ( listSize - 2 ) / 2;
  		for ( int a = 1 ; a <= listSize ; a = a*2 ) flor++;
  		//cout << flor ; 
  		int temp = flor;
  		while ( temp>0 ) {
		
  			for( int a = place ; a >= 0 ; a--) {
  				if ( even == true ) {
  					if (atoi(list[a].hp.c_str()) < atoi(list[a * 2 + 1].hp.c_str()) ) swap(list[a], list[a * 2 + 1]);
			  	}
  				else {
  					if (atoi(list[a].hp.c_str()) < atoi(list[a * 2 + 1].hp.c_str()) && atoi(list[a * 2 + 1].hp.c_str()) >= atoi(list[a * 2 + 2].hp.c_str()) ) swap(list[a], list[a * 2 + 1]);
  					else if (atoi(list[a].hp.c_str()) < atoi(list[a * 2 + 2].hp.c_str()) ) swap(list[a], list[a * 2 + 2]);
				  }
  				even = false;
			  }
			  
			temp--;
			if ( listSize % 2 == 0 ) even = true;
          }
  	
  	    print_list(2) ;
  	    cout << "HP heap high = " << flor << endl << "Leftmost node : " << endl;
  	    
  	    int leftmost = 1;
  	    while ( flor - 1 > 0 ) {
  	    	leftmost = leftmost*2;
  	    	flor--;
		  }
		  
		cout << "\t" << "#" << "\t" << "Name" << "\t""\t""\t" << "Type 1" << "\t""\t" << "HP" << "\t" << "Attack" << "\t" << "Defense" << endl;
		cout << "[" << leftmost-1 << "]" << "\t" << list[leftmost-1].num << "\t" << list[leftmost-1].name;
		if(list[leftmost-1].name.length() <= 7) cout << "\t""\t""\t";
		else cout << "\t""\t";
		cout << list[leftmost-1].type1;
		if(list[leftmost-1].type1.length() <= 7) cout << "\t""\t";
		else cout << "\t"; 
		cout << list[leftmost-1].hp << "\t" << list[leftmost-1].attack << "\t" << list[leftmost-1].defense << "\n";
		
		
		cout << "Bottom : " << endl;
		cout << "\t" << "#" << "\t" << "Name" << "\t""\t""\t" << "Type 1" << "\t""\t" << "HP" << "\t" << "Attack" << "\t" << "Defense" << endl;
		cout << "[" << listSize-1 << "]" << "\t" << list[listSize-1].num << "\t" << list[listSize-1].name;
		if(list[listSize-1].name.length() <= 7) cout << "\t""\t""\t";
		else cout << "\t""\t";
		cout << list[listSize-1].type1;
		if(list[listSize-1].type1.length() <= 7) cout << "\t""\t";
		else cout << "\t"; 
		cout << list[listSize-1].hp << "\t" << list[listSize-1].attack << "\t" << list[listSize-1].defense << "\n";
		
		listSize2 = listSize;
		list2 = new pokemon_data[listSize2];
		list2 = list; // �ƻs���ȤG�}�C 
		had_mission2 = true; // �]�L�@�����ȤG�~�������ȤT 
		return getcommand();
		
	} // mission2
	
	void mission3(){
		if(!had_mission1){ // �|��������Ȥ@ 
			cout <<	"\n" << "----- Execute Mission 1 first! -----" << "\n";
			return getcommand();
		}
		else if(listSize2 == 0){ // �|��������ȤG 
			cout <<	"\n" << "----- Execute Mission 2 first! -----" << "\n";
			return getcommand();
		}
		
		remove_root = new pokemon_data;
		put_into_remove_root(); // �O�droot���
		list2[0] = list2[listSize2-1]; // �̫�@�����root 
		listSize2--; // �}�C�j�p��@ 
		int flor = 0;
		for ( int a = 1 ; a <= listSize2 ; a = a*2 ) flor++; // level
  		
  		for(int i = 0;i < listSize2-1;i = i * 2 ){
  			if(atoi(list2[i/2].hp.c_str()) > atoi(list2[i+1].hp.c_str()) && atoi(list2[i/2].hp.c_str()) > atoi(list2[i+1].hp.c_str()) ) break; // �񥪥k���䳣�j 
  			else if(atoi(list2[i+1].hp.c_str()) > atoi(list2[i+2].hp.c_str()) ){ // ������j 
  				swaplist(i,1); // �洫�ⵧ��� 
  				i = i + 1;
  				
			}
			else{ // �k����j 
				swaplist(i,2); // �洫�ⵧ��� 
				i = i + 2;
			}
		}
  	
  		cout << "The remove root:" << "\n";
  		cout << "\t" << "#" << "\t" << "Name" << "\t""\t""\t" << "Type 1" << "\t""\t" << "HP" << "\t" << "Attack" << "\t" << "Defense" << endl;
  		cout << "\t" << remove_root->num << "\t" << remove_root->name; 
		if(remove_root->name.length() <= 7) cout << "\t""\t""\t";
		else cout << "\t""\t"; 
		cout << remove_root->type1 << "\t""\t" << remove_root->hp << "\t" << remove_root->attack << "\t" << remove_root->defense << endl;
  		cout << "\n";
  		
  		if(listSize2 == 0) return getcommand();
  		
  	    print_list(3) ; // �L�Xlist2 
  	    cout << "HP heap high = " << flor << endl << "Leftmost node : " << endl;
  	    
  	    int leftmost = 1;
  	    while ( flor - 1 > 0 ) {
  	    	leftmost = leftmost*2;
  	    	flor--;
		}
		  
		cout << "\t" << "#" << "\t" << "Name" << "\t""\t""\t" << "Type 1" << "\t""\t" << "HP" << "\t" << "Attack" << "\t" << "Defense" << endl;
		cout << "[" << leftmost-1 << "]" << "\t" << list2[leftmost-1].num << "\t" << list2[leftmost-1].name;
		if(list2[leftmost-1].name.length() <= 7) cout << "\t""\t""\t";
		else cout << "\t""\t";
		cout << list2[leftmost-1].type1;
		if(list2[leftmost-1].type1.length() <= 7) cout << "\t""\t";
		else cout << "\t"; 
		cout << list2[leftmost-1].hp << "\t" << list2[leftmost-1].attack << "\t" << list2[leftmost-1].defense << "\n";
		
		
		cout << "Bottom : " << endl;
		cout << "\t" << "#" << "\t" << "Name" << "\t""\t""\t" << "Type 1" << "\t""\t" << "HP" << "\t" << "Attack" << "\t" << "Defense" << endl;
		cout << "[" << listSize2-1 << "]" << "\t" << list2[listSize2-1].num << "\t" << list2[listSize2-1].name;
		if(list2[listSize2-1].name.length() <= 7) cout << "\t""\t""\t";
		else cout << "\t""\t";
		cout << list2[listSize2-1].type1;
		if(list2[listSize2-1].type1.length() <= 7) cout << "\t""\t";
		else cout << "\t"; 
		cout << list2[listSize2-1].hp << "\t" << list2[listSize2-1].attack << "\t" << list2[listSize2-1].defense << "\n";
		
		return getcommand();
	}

	void expansion_ListLength(){  
		pokemon_data *tempList = list;
 		list = new pokemon_data[listLength * 10];
 		for(int a = 0;a < listLength; a++) list[a] = tempList[a];
 		delete [] tempList;
 		listLength = listLength * 10;
	}
	
	void put_into_list(string line){
		int i = 0; // counter 
		list[listSize].n = listSize + 1;
		for(;line[i] != '\t';i++ ) list[listSize].num = list[listSize].num + line[i];
		i++;
		for(;line[i] != '\t';i++ ) list[listSize].name = list[listSize].name + line[i];
		i++;
		for(;line[i] != '\t';i++ ) list[listSize].type1 = list[listSize].type1 + line[i];
		i++;
		for(;line[i] != '\t';i++ ) list[listSize].type2 = list[listSize].type2 + line[i];
		i++;
		for(;line[i] != '\t';i++ ) list[listSize].total = list[listSize].total + line[i];
		i++;
		for(;line[i] != '\t';i++ ) list[listSize].hp = list[listSize].hp + line[i];
		i++;
		for(;line[i] != '\t';i++ ) list[listSize].attack = list[listSize].attack + line[i];
		i++;
		for(;line[i] != '\t';i++ ) list[listSize].defense = list[listSize].defense + line[i];
		i++;
		for(;line[i] != '\t';i++ ) list[listSize].spA = list[listSize].spA + line[i];
		i++;
		for(;line[i] != '\t';i++ ) list[listSize].spD = list[listSize].spD + line[i];
		i++;
		for(;line[i] != '\t';i++ ) list[listSize].speed = list[listSize].speed + line[i];
		i++;
		for(;line[i] != '\t';i++ ) list[listSize].generation = list[listSize].generation + line[i];
		i++;
		for(;line[i] != '\0';i++ ) list[listSize].legendary = list[listSize].legendary + line[i];
	}
	
	void put_into_tree1(){
		treerun->num = list[n].num;
		treerun->name = list[n].name;
		treerun->type1 = list[n].type1;
		treerun->type2 = list[n].type2;
		treerun->total = list[n].total;
		treerun->hp = list[n].hp;
		treerun->attack = list[n].attack;
		treerun->defense = list[n].defense;
		treerun->spA = list[n].spA;
		treerun->spD = list[n].spD;
		treerun->speed = list[n].speed;
		treerun->generation = list[n].generation;
		treerun->legendary = list[n].legendary;
		treerun->n = list[n].n;
		
	}
	
	void put_into_remove_root(){
		remove_root->num = list2[0].num;
		remove_root->name = list2[0].name;
		remove_root->type1 = list2[0].type1;
		remove_root->hp = list2[0].hp;
		remove_root->attack = list2[0].attack;
		remove_root->defense = list2[0].defense;
	} 
	
	void print_list(int mission_num){
		cout << "\t" << "#" << "\t" << "Name" << "\t""\t""\t" << "Type 1" << "\t""\t" << "HP" << "\t" << "Attack" << "\t" << "Defense" << "\n";
		if(mission_num == 3){
			for(int i = 0; i < listSize2; i++){
				cout << "[" << i << "]" << "\t" << list2[i].num << "\t" << list2[i].name;
				if(list2[i].name.length() <= 7) cout << "\t""\t""\t";
				else cout << "\t""\t";
				cout << list2[i].type1;
				if(list2[i].type1.length() <= 7) cout << "\t""\t";
				else cout << "\t"; 
				cout << list2[i].hp << "\t" << list2[i].attack << "\t" << list2[i].defense << "\n";  
			}
		}
		else{
			for(int i = 0; i < listSize; i++){
				if(mission_num == 1)cout << "[" << i+1 << "]" << "\t" << list[i].num << "\t" << list[i].name;
				else if(mission_num == 2)cout << "[" << i << "]" << "\t" << list[i].num << "\t" << list[i].name;
				if(list[i].name.length() <= 7) cout << "\t""\t""\t";
				else cout << "\t""\t";
				cout << list[i].type1;
				if(list[i].type1.length() <= 7) cout << "\t""\t";
				else cout << "\t"; 
				cout << list[i].hp << "\t" << list[i].attack << "\t" << list[i].defense << "\n";  
			}
		}
	}
	
	void print_node(){
		cout << "\t" << "#" << "\t" << "Name" << "\t""\t""\t" << "Type 1" << "\t""\t" << "HP" << "\t" << "Attack" << "\t" << "Defense" << "\n";
		cout << "[" << treerun->n << "]" << "\t" << treerun->num << "\t" << treerun->name;
		if(treerun->name.length() <= 7) cout << "\t""\t""\t";
		else cout << "\t""\t";
		cout << treerun->type1;
		if(treerun->type1.length() <= 7) cout << "\t""\t";
		else cout << "\t";
		cout << treerun->hp << "\t" << treerun->attack << "\t" << treerun->defense << "\n";
	}
	
	swaplist(int i, int num){
		pokemon_data *temp = new pokemon_data;
		temp->num = list2[i/2].num;
		temp->name = list2[i/2].name;
		temp->type1 = list2[i/2].type1;
		temp->hp = list2[i/2].hp;
		temp->attack = list2[i/2].attack;
		temp->defense = list2[i/2].defense;
		list2[i/2].num = list2[i+num].num;
		list2[i/2].name = list2[i+num].name;
		list2[i/2].type1 = list2[i+num].type1;
		list2[i/2].hp = list2[i+num].hp;
		list2[i/2].attack = list2[i+num].attack;
		list2[i/2].defense = list2[i+num].defense;
		list2[i+num].num = temp->num;
		list2[i+num].name = temp->name;
		list2[i+num].type1 = temp->type1;
		list2[i+num].hp = temp->hp;
		list2[i+num].attack = temp->attack;
		list2[i+num].defense = temp->defense;
		
	}
  
  	void getcommand(){  
   		int choice;
   		cout << "\n" ;
   		printf("****** Pokemon Tree and Heap ******\n");
    	printf("* 0. Quit                         *\n");
    	printf("* 1. Read a file to build BST     *\n");
    	printf("* 2. Transform it into Max Heap   *\n");
    	cout << "* 3. Delete max from Max Heap     *" << "\n";
    	printf("***********************************\n");
    	printf("Input a command(0, 1, 2, 3): ");
    	cin >> choice;
   	 	if(choice == 1) mission1();
    	else if(choice == 2) mission2();
    	else if(choice == 3) mission3();
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

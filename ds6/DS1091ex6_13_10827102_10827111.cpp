// 10827111袁本誠 10827102沈柏融
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
	int n; // 第幾筆資料 
	tree *left = NULL;
	tree *right = NULL;
};

struct pokemon_data { // 神奇寶貝的資料 
	string name, type1, type2, num, total, hp, attack, defense, spA, spD, speed, generation, legendary;
	int n; // 第幾筆資料 
};

class Mission {
 private:
 	string name, type1, type2, num, total, hp, attack, defense, spA, spD, speed, generation, legendary;
 	int listLength, listSize;
 	int n;
 	bool had_mission1;
 	pokemon_data *list;
 	tree *tree1;
 	tree *tree2;
 	tree *treerun;

 public:
 	Mission(){ // Length = 總長度	Size = 目前數目 
 		string name, type1, type2, num, total, hp, attack, defense, spA, spD, speed, generation, legendary;
 		listLength = 100, listSize = 0;
 		n = 0;
 		had_mission1 = false;
 		list = new pokemon_data[listLength];
		tree1 = new tree; // 任務一的樹 
		// tree2 = new tree; // 任務二的樹	
		treerun	= tree1; // 讓treerun跑動
	}
 	
  	void mission1(){
  		list = new pokemon_data[listLength];
  		tree1 = new tree;
  		n = 0;
  		treerun = tree1;
  		listSize = 0; // 初始化
		
  		string file_number;
  		cout << "\n" << "Input a file number (e.g., 601, 602, 603, ...): ";
  		cin >> file_number;
  		string input_number = "input" + file_number + ".txt";
    	char* inputfile_name = new char[input_number.length()]; 
    	for ( int a = 0 ; a < input_number.length() ; a++ ) inputfile_name[a] = input_number[a];
    	ifstream fin;
    	fin.open(inputfile_name);
    
  		if( !fin ){ // 是否有此檔 
  			cout << "\n" << "### " << inputfile_name << " does not exist! ###\n";
  			return getcommand();
		} // if 
		
		string temp;
		getline(fin,temp); // 第0行為標題，因此無視
		while(!fin.eof()){
			if(listSize == listLength) expansion_ListLength(); // 動態陣列格數不夠，增加陣列格數 
			getline(fin,temp); // 有數字和文字混雜，不可直接讀取
			if(temp == "\0") break; // 防止多跑一次迴圈 
			put_into_data(temp); // 將數字與文字混合的一行分別存進陣列裡 
			listSize++;
		} // while 
	
	  	bool found = false; // 是否找到樹的最底層  
		put_into_tree1(); // 將list[n]的資料複製到tree1裡 
		n++;
		int level = 0, maxlevel = 0; // 層數和最大層數 
		while(n < listSize){ // 循環到無資料
			// cout << n  << "\n";
			level = 1;
			treerun = tree1; // 回到樹的開頭 
			found = false; 
			while(!found){ // 到樹根底部停止 
				if(atoi(list[n].hp.c_str()) < atoi(treerun->hp.c_str())){ // hp小於目前樹根 
					if(treerun->left == NULL){ // 左邊到底 
						treerun->left = new tree;  // 左邊新增空間
						treerun = treerun->left; // 前往新增空間 
						put_into_tree1();  // 將list[n]的資料複製到tree1裡
						n++;
						found = true; // 找到瞜
					}
					else {
						treerun = treerun->left; // 左邊還沒到底 
					}
				}
				else if(atoi(list[n].hp.c_str()) >= atoi(treerun->hp.c_str())){ // hp大於等於目前樹根 
					if(treerun->right == NULL){ // 右邊到底 
						treerun->right = new tree;  // 右邊新增空間 
						treerun = treerun->right; // 前往新增空間 
						put_into_tree1();  // 將list[n]的資料複製到tree1裡
						n++;
						found = true; // 找到瞜 
					}
					else {
						treerun = treerun->right; // 右邊還沒到底 
					}
					
				}
				
				level++;
			}
			
			if(level > maxlevel) maxlevel = level; // 比最大層數大就設為最大層數 
		}
		
		print_file(1); // 印出檔案 
		
		cout << "HP tree height = " << maxlevel << "\n";
		
		treerun = tree1;
		while(treerun->left != NULL){
			treerun = treerun->left;
		}
		cout << "Leftmost node:" << "\n";
		print_node(); // 印出最左側節點 
		treerun = tree1;
		while(treerun->right != NULL){
			treerun = treerun->right;
		}
		cout << "Rightmost node:" << "\n";
		print_node(); // 印出最右側節點 
		had_mission1 = true; // 跑過一次任務一，可以執行任務二 
		return getcommand();
  	} // mission1
  
  
  
  	void mission2(){
  		if(had_mission1 == false){ // 尚未執行任務一 
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
  	
  	    print_file(2) ;
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

	} // mission2

	void expansion_ListLength(){  
		pokemon_data *tempList = list;
 		list = new pokemon_data[listLength * 10];
 		for(int a = 0;a < listLength; a++) list[a] = tempList[a];
 		delete [] tempList;
 		listLength = listLength * 10;
	}
	
	void put_into_data(string line){
		int i = 0; // 計數器 
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
	
	void print_file(int mission_num){
		cout << "\t" << "#" << "\t" << "Name" << "\t""\t""\t" << "Type 1" << "\t""\t" << "HP" << "\t" << "Attack" << "\t" << "Defense" << "\n";
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
  
  	void getcommand(){  
   		int choice;
   		cout << "\n" ;
   		printf("****** Pokemon Tree and Heap ******\n");
    	printf("* 0. Quit                         *\n");
    	printf("* 1. Read a file to build BST     *\n");
    	printf("* 2. Transform it into Max Heap   *\n");
    	printf("***********************************\n");
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

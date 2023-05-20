/* 
DS2-2
�ҵ{�W��: ��Ƶ��c�P�t��k
�}�үZ��: ��T�G��
�½ұЮv: �d�y�E�б� 
10827102 �H�f�� 10827146 ���r�O 
*/
# include <iostream>
# include <fstream>
# include <string.h>
# include <iomanip>
# include <stdlib.h>
# include <vector>

using namespace std;

char* String_To_charPtr(string s);

ifstream fin;

struct Tdata{
	string SchoolName;				// �ǮզW��
	int sequence;					// �Ǹ�  
	string DepartmentName;			// ��t�W�� 
	string type;					// �i�קO 
	string level;					// ���� 
	string StudentNum;				// �ǥͼ� 
};

struct data{
	int sequence;					// �Ǹ�  
	string DepartmentName;			// ��t�W�� 
	string type;					// �i�קO 
	string level;					// ���� 
	string StudentNum;				// �ǥͼ� 
};

struct AVLdata{
	int sequence;					// �Ǹ�  
	string SchoolName;				// �ǮզW�� 
	string type;					// �i�קO 
	string level;					// ���� 
	string StudentNum;				// �ǥͼ� 
};

struct School {
  	string SchoolName;				// �ǮզW�� 
  	vector<data> AllOfDepartment;	// �U�ج�t 	
};

struct Department {
	string DepartmentName;				// ��t�W�� 
	vector<AVLdata> AllOfSchool;	// �U�ؾǮ� 
};

vector<Tdata> temp;					// �Ȧs�ɮװT��
vector<School> M1temp;				// �X�֦P�Ǯ� 
vector<Department> AVLtemp;			// �X�֦P��t
vector<Tdata> searchSchooltemp;		// �j�M
vector<Tdata> M3temp;				// �j�M

char* String_To_charPtr(string s){
	char* str = new char[s.length() + 1]; 
	for(int a = 0; a < s.length(); a++) str[a] = s[a];
	str[s.length()] = '\0' ;
	return str;
}

class Mission1 {
  public:
  	vector<School> StoreSpace;		// �̦h�s��檺�Ŷ�
	vector<Mission1*> node;			// [0] �V�W [1~4] �V�U 
	
	Mission1(){
 		StoreSpace.clear();
 		for ( int i = 0 ; i <= 4 ; i++ ) node.push_back(NULL);
	}
	
  	/*
  	�}�ɨóB�z temp M1temp AVLtemp 
	*/ 
  	bool OpenFile(string Name) {
  		temp.clear();
  		M1temp.clear();
  		StoreSpace.clear();
  		node.clear();
    	char* fileName = new char[Name.length()]; 
    	for ( int a = 0 ; a < Name.length() ; a++ ) fileName[a] = Name[a];
  		fin.open(fileName);
  		if (! fin.is_open() ) {  // open fail
    		return false;
  		} // if

    	string str;
    	for(int i = 0; i < 3; i++) getline(fin,str); // �e�T��
    	AddtoTemp();
	
  		return true;
	} // OpenFile()
	
	/*
  	�Ѥp��j�ƦC�ثeclass����� 
	*/ 
	void Sort(){
		if ( StoreSpace.size() == 2 ) {
			if ( StoreSpace[0].SchoolName > StoreSpace[1].SchoolName ){
				School s = StoreSpace[0];
				StoreSpace[0] = StoreSpace[1];
				StoreSpace[1] = s;
			} // if()
		} // if ()
		else if ( StoreSpace.size() == 3 ) {
			if ( StoreSpace[2].SchoolName > StoreSpace[1].SchoolName
				 && StoreSpace[1].SchoolName > StoreSpace[0].SchoolName ) ;
			else if ( StoreSpace[2].SchoolName > StoreSpace[0].SchoolName ) {
				School s = StoreSpace[1];
				StoreSpace[1] = StoreSpace[2];
				StoreSpace[2] = s;
			} // else if()
			else {
				School s = StoreSpace[2];
				StoreSpace[2] = StoreSpace[1];
				StoreSpace[1] = StoreSpace[0];
				StoreSpace[0] = s;
			} // else()
		} // else if()
	} // Sort()
	
	/*
  	�NM1temp���StoreSpace
  	�ñƦC 
	*/ 
	void M1tempToStoreSpace( School s ){
		StoreSpace.push_back(s);
		Sort();
	} // M1tempToStoreSpace()
	
	/*
  	�N��Ʃ�mtemp 
	*/ 
	void AddtoTemp() {
		string s1,s2;
		int n = 1;
		while( getline(fin, s1) ) {
			s2 = strtok(String_To_charPtr(s1), "\t");
			s2 = strtok(NULL, "\t");
			Tdata t;
			t.SchoolName = s2;
			t.sequence = n;
			s2 = strtok(NULL, "\t");
			t.DepartmentName = strtok(NULL, "\t");
			t.type = strtok(NULL, "\t");
			t.level = strtok(NULL, "\t");
			t.StudentNum = strtok(NULL, "\t");
			if(t.StudentNum[0] == '\"'){
				string chars = ",\"";
				t.StudentNum.erase(0, t.StudentNum.find_first_not_of(chars));
				t.StudentNum.erase(1, t.StudentNum.find_first_not_of(chars)+1);
				t.StudentNum.erase(t.StudentNum.find_last_not_of(chars)+1);
			} // if
			temp.push_back(t);
			n++;
		} // while()
		
	} // AddtoTemp()

	/*
  	�Ntemp��Ƥ@�P�Ǯվ�z���mM1temp 
	*/ 
	void temptoM1temp() {
		int NOfS = 0; // �Ǯյ���
		for( int a = 0 ; a < temp.size() ; a++ ) {
			if ( a != 0 && temp[a].SchoolName == M1temp[NOfS-1].SchoolName ){		// �ۦP�Ǯ� 
				NOfS--;
				School s;
				data d;
				d.sequence = temp[a].sequence;
				d.DepartmentName = temp[a].DepartmentName;
				d.type = temp[a].type;
				d.level = temp[a].level;
				d.StudentNum = temp[a].StudentNum;
				M1temp[NOfS].AllOfDepartment.push_back(d);
			} // if()
			else{																	// ���P�Ǯ� 
				School s;
				data d;
				s.SchoolName = temp[a].SchoolName;
				d.sequence = temp[a].sequence;
				d.DepartmentName = temp[a].DepartmentName;
				d.type = temp[a].type;
				d.level = temp[a].level;
				d.StudentNum = temp[a].StudentNum;
				s.AllOfDepartment.push_back(d);
				M1temp.push_back(s);
			} // else()
			NOfS++;
		}
		
	} // temptoM1temp()
	
	/*
  	��StoreSpace�̸�ƶW�L�ⵧ�ɡA�H��23��W�h�A�i�����
	[0]���V�W���`�I [1-4]����l�`�I
	���ήɱN�����ȩ�[0]���ʡA�Y[0]���ɸ�Ƥ]�W�L�T���A���i����� 
	*/
	void split() {
		int SizeNum;
		if ( !node[0] ) { 	// ���W�L�`�I 
			Mission1 *up  = new Mission1();
			Mission1 *next = new Mission1();
			SizeNum = StoreSpace.size();
			next->StoreSpace.push_back(StoreSpace[SizeNum-1]);
			StoreSpace.pop_back();
			SizeNum = StoreSpace.size();
			up->StoreSpace.push_back(StoreSpace[SizeNum-1]);
			StoreSpace.pop_back();
			next->node[0] = up;
			node[0] = up;
			up->node[1] = this, up->node[2] = next;
			
			if ( node[3] && node[4] ) {
				next->node[2] = node[4];
				next->node[1] = node[3];
				node[3]->node[0] = next;
				node[4]->node[0] = next;
				node[3] = node[4] = NULL;
			} // if()
		} // if()
		else {	// ���W���`�I 
			Mission1 *next = new Mission1();
			next->node[0] = node[0];
			SizeNum = StoreSpace.size();
			next->StoreSpace.push_back(StoreSpace[SizeNum-1]);
			StoreSpace.pop_back();
			SizeNum = StoreSpace.size();
			node[0]->StoreSpace.push_back(StoreSpace[SizeNum-1]);
			StoreSpace.pop_back();
			node[0]->Sort();
			
			if ( node[3] && node[4] ) {
				next->node[2] = node[4];
				next->node[1] = node[3];
				node[3]->node[0] = next;
				node[4]->node[0] = next;
				node[3] = node[4] = NULL;
			} // if()
			
			if ( this == node[0]->node[1] && node[0]->StoreSpace.size() == 2 ){
				node[0]->node.insert(node[0]->node.begin() +  2, next);
				node[0]->node.pop_back();
			} // if()
			else if( this == node[0]->node[2] && node[0]->StoreSpace.size() == 2 ){
				node[0]->node.insert(node[0]->node.begin() +  3, next);
				node[0]->node.pop_back();
			} // else if()
			else if( node[0]->StoreSpace.size() == 3 ){
				if( this == node[0]->node[1] ) 
					node[0]->node.insert( node[0]->node.begin() + 2, next );
				else if( this == node[0]->node[2] )
					node[0]->node.insert( node[0]->node.begin() + 3, next );
				else if( this == node[0]->node[3] )
					node[0]->node.insert( node[0]->node.begin() + 4, next );
					
				node[0]->node.pop_back();
				node[0]->split();
			} // else if()
			
		} // else()
	} // split()
	
};

class Tree23{
  private:
  	Mission1 *root; // ��� 
  	Mission1 *now; 	// �]�ʪ��`�I 
  	
  public:
  	void Creat23Tree(){
  		root = new Mission1();
		now = root;
		root->M1tempToStoreSpace( M1temp[0] );
		
		for ( int a = 1 ; a < M1temp.size() ; a++ ){
			Insert(a);
		}
		
	} // Creat23Tree()
	
	/*
  	�q��ڶ}�l�M��
	�H�զW����ǡA����j��Τp��now���w����ơA���j���k�A���p�h�Ϥ�
	����j�M��𪺳̩��h�A���J�ñƧ�
	�ˬd�O�_�ŦX23��W�h�A�H�ϫh���� 
	*/
	void Insert(int n){
		now = root;
		while( now->node[1] != NULL ){			// �̫�@�h 
			if( now->StoreSpace.size() < 2 ){  								// 1����� 
				if( M1temp[n].SchoolName < now->StoreSpace[0].SchoolName ){
					now = now->node[1];
				}
				else{;
					now = now->node[2];
				}
			} // if()
			else{															// 2����� 
				if( M1temp[n].SchoolName < now->StoreSpace[0].SchoolName ){
					now = now->node[1];
				}
				else if( M1temp[n].SchoolName > now->StoreSpace[0].SchoolName 
						 && M1temp[n].SchoolName < now->StoreSpace[1].SchoolName ){
					now = now->node[2];
				}
				else {
					now = now->node[3];
				} // esle() 
			} // else()
		} // while()
		
		if( now->StoreSpace.size() < 2 ){
			now->M1tempToStoreSpace( M1temp[n] );
		} // if()
		else{
			now->M1tempToStoreSpace( M1temp[n] );
		   	now->split();
			while( root->node[0] ) root = root->node[0];
		} // else()
		
		root->Sort();
		
	} // Insert()
	
	void Search(string schoolName){
		now = root;
		searchSchooltemp.clear();
		
		while( now != NULL ){
			if( now->StoreSpace.size() < 2 ){  								// 1����� 
				if(schoolName == now->StoreSpace[0].SchoolName){
					tempTosearchSchooltemp(0);
					break;
				} // if
				else if(schoolName < now->StoreSpace[0].SchoolName){
					now = now->node[1];
				} // else if
				else{
					now = now->node[2];
				} // else
			} // if()
			else{
				if(schoolName == now->StoreSpace[0].SchoolName){
					tempTosearchSchooltemp(0);
					break;
				} // if
				if(schoolName == now->StoreSpace[1].SchoolName){
					tempTosearchSchooltemp(1);
					break;
				} // else if													// 2����� 
				else if(schoolName < now->StoreSpace[0].SchoolName){
					now = now->node[1];
				} // if
				else if(schoolName > now->StoreSpace[0].SchoolName 
						 && schoolName < now->StoreSpace[1].SchoolName){
					now = now->node[2];
				}
				else {
					now = now->node[3];
				} // esle() 
			} // else()
		} // while() 
	} // Search()
	
	void tempTosearchSchooltemp(int n){
		Tdata one;
		int a = 0;
		for(int d = 0; d < now->StoreSpace[n].AllOfDepartment.size(); d++){
			for(a = 0; a < temp.size(); a++){
				if(temp[a].sequence == now->StoreSpace[n].AllOfDepartment[d].sequence){
					one = temp[a];
					searchSchooltemp.push_back(one);
					break;
				} // if
			} // for
		} // for
		
	} // tempTosearchSchooltemp()
	
	/*
  	���o�� 
	*/
	int getMaxLevel(){
		int maxlevel = 1;
		now = root;
		while( now->node[1] ){
			now = now->node[1];
			maxlevel++;
		} // while()
		
		return maxlevel;
	} // getMaxlevel
	
	/*
  	�L�Xroot����� 
	*/
	void PrintRoot(){
		int num = 1;
		if( root->StoreSpace.size() == 1 ){
			for ( int a = 0 ; a < root->StoreSpace[0].AllOfDepartment.size() ; a++){
				cout << num << ": [";
				cout << root->StoreSpace[0].AllOfDepartment[a].sequence;
				cout << "] ";
				cout << root->StoreSpace[0].SchoolName << ", ";
				cout << root->StoreSpace[0].AllOfDepartment[a].DepartmentName << ", ";
				cout << root->StoreSpace[0].AllOfDepartment[a].type << ", ";
				cout << root->StoreSpace[0].AllOfDepartment[a].level << ", ";
				cout << root->StoreSpace[0].AllOfDepartment[a].StudentNum << "\n";
				num++;
			} // for()
		}
		else if( root->StoreSpace.size() == 2 ){
			if( root->StoreSpace[0].AllOfDepartment[0].sequence < root->StoreSpace[1].AllOfDepartment[0].sequence ) {
				for( int a = 0 ; a < root->StoreSpace.size() ; a++ ){
					for ( int b = 0 ; b < root->StoreSpace[a].AllOfDepartment.size() ; b++){
						cout << num << ": [";
						cout << root->StoreSpace[a].AllOfDepartment[b].sequence;
						cout << "] ";
						cout << root->StoreSpace[a].SchoolName << ", ";
						cout << root->StoreSpace[a].AllOfDepartment[b].DepartmentName << ", ";
						cout << root->StoreSpace[a].AllOfDepartment[b].type << ", ";
						cout << root->StoreSpace[a].AllOfDepartment[b].level << ", ";
						cout << root->StoreSpace[a].AllOfDepartment[b].StudentNum << ", \n";
						num++;
					} // for()
			
				} // for()
			} // if
			else {
				for( int a = root->StoreSpace.size()-1 ; a >= 0 ; a-- ){
					for ( int b = 0 ; b < root->StoreSpace[a].AllOfDepartment.size() ; b++){
						cout << num << ": [";
						cout << root->StoreSpace[a].AllOfDepartment[b].sequence;
						cout << "] ";
						cout << root->StoreSpace[a].SchoolName << ", ";
						cout << root->StoreSpace[a].AllOfDepartment[b].DepartmentName << ", ";
						cout << root->StoreSpace[a].AllOfDepartment[b].type << ", ";
						cout << root->StoreSpace[a].AllOfDepartment[b].level << ", ";
						cout << root->StoreSpace[a].AllOfDepartment[b].StudentNum << ", \n";
						num++;
					} // for()
			
				} // for()
			}
		}
	} // PrintRoot()
  	
};
	
class Mission2{
  public:
  	Department department;
  	Mission2 *left ;
  	Mission2 *right ;
  	Mission2 *up;
  	
  	Mission2(){
  		left = NULL;
  		right = NULL;
  		up = NULL;
	} // Mission2
	
	/*
  	�Ntemp��ƨ̦P��t��z���mAVLtemp 
	*/ 
	void temptoAVLtemp(){
		AVLtemp.clear();
		bool IsSame = false;
		int dpNum = 0; 
		int totaldpNum = 0;
		Department dp;
		AVLdata AVLd;
		dp.DepartmentName = temp[0].DepartmentName;
		AVLd.SchoolName = temp[0].SchoolName;
		AVLd.sequence = temp[0].sequence;
		AVLd.type = temp[0].type;
		AVLd.level = temp[0].level;
		AVLd.StudentNum = temp[0].StudentNum;
		dp.AllOfSchool.push_back(AVLd);
		AVLtemp.push_back(dp);
		totaldpNum++;
		for( int a = 1 ; a < temp.size() ; a++ ) {
			IsSame = false;
			dpNum = 0;
			for ( int b = 0 ; b < totaldpNum ; b++ ) {
				dpNum =  b;
				if( AVLtemp[b].DepartmentName == temp[a].DepartmentName ){
					IsSame = true;
					break;
				} // if()
			} // for()
			if ( IsSame ){				// �ۦP��t 
				Department dp;
				AVLdata AVLd;
				//cout << "same  "; 
				AVLd.SchoolName = temp[a].SchoolName;
				AVLd.sequence = temp[a].sequence;
				AVLd.type = temp[a].type;
				AVLd.level = temp[a].level;
				AVLd.StudentNum = temp[a].StudentNum;
				AVLtemp[dpNum].AllOfSchool.push_back(AVLd);
			} // if()
			else{						// ���P��t 
				Department dp;
				AVLdata AVLd;
				dp.DepartmentName = temp[a].DepartmentName;
				AVLd.SchoolName = temp[a].SchoolName;
				AVLd.sequence = temp[a].sequence;
				AVLd.type = temp[a].type;
				AVLd.level = temp[a].level;
				AVLd.StudentNum = temp[a].StudentNum;
				dp.AllOfSchool.push_back(AVLd);
				AVLtemp.push_back(dp);
				totaldpNum++;
			} // else()
		} // for() 
	} // temptoAVLtemp()
	
	void AVLtempToDepartment( Department d ){
		department= d;
	} // AVLtempToDepartment()
	
	/*
  	�q�ثe��J��Ƥ���m�V�W�M��A��쥭���I�ƭȹH��AVL��W�h�ɡA�i����w��V������ 
	*/ 
	void rotate() {
		if( this->BalancePiont() == 2 && this->left->BalancePiont() >=0 ){						//LL
			this->LL();						
		} // if()
		else if( this->BalancePiont() == -2 && this->right->BalancePiont() <=0 ){				//RR
			this->RR();						
		} // if()
		else if( this->BalancePiont() == -2 && this->right->BalancePiont() >=0 ){				//Rl
			this->RL();						
		} // if()
		else if( this->BalancePiont() == 2 && this->left->BalancePiont() <=0 ){					//lR
			this->LR();						
		} // if()
		else {
			if( this->up != NULL )
				this->up->rotate();
		} // else
	} // rotate()
	
	/*
  	���������I�ƭ� 
	*/ 
	int BalancePiont(){
		int leftP = this->left->hight(); 
		int rightP = this->right->hight(); 
		
		return leftP - rightP;
	} // BP()
	
	/*
  	�� 
	*/
	int hight(){
		if(this == NULL) return 0;
        int leftDepth = this->left->hight() + 1;
        int rightDepth = this->right->hight() + 1;
        
        if( leftDepth >  rightDepth )
        	return leftDepth;
        else 	
        	return rightDepth;
	} //  hight()
	
	void LL(){
		Mission2 *temp;
		
    	temp = this->left;
    	this->left = temp->left;
    	temp->left = temp->right;
    	temp->right = this->right;
    	this->right = temp;
    	if( this->left != NULL ) this->left->up = this;
    	if( temp->right != NULL ) temp->right->up = temp;
    	Department d;
    	d = this->department;
    	this->department = temp->department;
    	temp->department = d;
	} // LL()
	
	void LR(){
		this->left->RR();
		this->LL();
	} // LR()
	
	void RL(){
		this->right->LL();
		this->RR();
	} // RL()
	
	void RR(){
		Mission2 *temp;
		
		temp = this->right;
		this->right = temp->right;
		temp->right = temp->left;
		temp->left = this->left;
		this->left = temp;
		
		if( temp->left != NULL ) temp->left->up = temp;
    	if( this->right != NULL ) this->right->up = this;
		
		Department d;
    	d = this->department;
    	this->department = temp->department;
    	temp->department = d;
	} // RR()
	
};

class AVLTree{
  private:
  	Mission2 *root;
  	Mission2 *now;
  	
  public:
  	void CreatAVLTree(){
  		root = new Mission2();
		now = root;
		root->AVLtempToDepartment( AVLtemp[0] );
		
		for ( int a = 1 ; a < AVLtemp.size() ; a++ ){
			Insert(a);
		}
		
	} // CreatAVLTree()
	
	/*
  	�q��ڶ}�l�M��
	�H��t����ǡA����j��Τp��now���w����ơA���j���k�A���p�h�Ϥ�
	����j�M��𪺳̩��h�ô��J 
	*/
	void Insert(int n){
		now = root;
		while( now->left != NULL || now->right != NULL ){			// �̫�@�h 
			if( AVLtemp[n].DepartmentName < now->department.DepartmentName ){ 
				if(now->left == NULL) break;			
				now = now->left;
			} // if()
			else{	
				if(now->right == NULL) break;						
				now = now->right;
			} // else()
		} // while()
		
		if( AVLtemp[n].DepartmentName < now->department.DepartmentName ){
			Mission2 *temp; 
			temp = now;
			now->left = new Mission2;
			now = now->left;
			now->up = temp;
			
		}
		else{
			Mission2 *temp; 
			temp = now;
			now->right = new Mission2;
			now = now->right;
			now->up = temp;
		} // 
	
		now->AVLtempToDepartment( AVLtemp[n] );
		now->rotate();

	} // Insert()
	
	void Search(string dpName){
		now = root;
		
		while( now->left != NULL || now->right != NULL ){
			if(dpName == now->department.DepartmentName){
				tempToM3temp();
				break;
			} // if
			else if(dpName < now->department.DepartmentName){
				if(now->left == NULL) break;
				now = now->left;
			} // else if
			else if(dpName > now->department.DepartmentName){
				if(now->right == NULL) break;
				now = now->right;
			} // else if
		} // while() 
	} // Search()
	
	void tempToM3temp(){
		Tdata one;
		int a = 0;
		for(int d = 0; d < now->department.AllOfSchool.size(); d++){
			a = d;
			for(a = 0; a < temp.size(); a++){
				if(now->department.AllOfSchool[d].sequence == temp[a].sequence){
					one = temp[a];
					M3temp.push_back(one);
					a = temp.size();
				} // if
			} // for
		} // for
		
	} // tempTosearchSchooltemp()
	
	/*
  	�� 
	*/
	int getMaxLevel(){
		return root->hight();
	} // getMaxLevel()
	
	/*
  	 �L�Xroot����� 
	*/
	void PrintRoot(){
		int num = 1;
		for ( int a = 0 ; a < root->department.AllOfSchool.size() ; a++){
			cout << num << ": [";
			cout << root->department.AllOfSchool[a].sequence;
			cout << "] ";
			cout << root->department.AllOfSchool[a].SchoolName << ", ";
			cout << root->department.DepartmentName << ", ";
			cout << root->department.AllOfSchool[a].type << ", ";
			cout << root->department.AllOfSchool[a].level << ", ";
			cout << root->department.AllOfSchool[a].StudentNum << "\n";
			num++;
		} // for()
	} 
	
};

class Mission3{
	private:
		
	public:
		void Search(Tree23 tree23, AVLTree avltree){
			M3temp.clear();
			
			string sName;
			string dName;
			bool hasName = false;
			
			cout << "Enter a college name to search [*]: ";
			cin >> sName;
			if(sName == "*"){
				searchSchooltemp = temp;
			} // if
			else{
				tree23.Search(sName);
				hasName = true;
			} // else
			
			cout << "Enter a department name to search [*]: ";
			cin >> dName;
			if(dName == "*"){
				M3temp = searchSchooltemp;
			} // if
			else if(hasName == true){ // ������
				Tdata one;
				for(int a = 0; a < searchSchooltemp.size(); a++){
					if(searchSchooltemp[a].DepartmentName == dName){
						one = searchSchooltemp[a];
						M3temp.push_back(one);
					} // if
				} // for
			} // else if
			else{
				avltree.Search(dName);
			} // else
		} // Search()
		
		void print(){
			int num = 1;
			for ( int a = 0 ; a < M3temp.size() ; a++){
				cout << num << ": [";
				cout << M3temp[a].sequence;
				cout << "] ";
				cout << M3temp[a].SchoolName << ", ";
				cout << M3temp[a].DepartmentName << ", ";
				cout << M3temp[a].type << ", ";
				cout << M3temp[a].level << ", ";
				cout << M3temp[a].StudentNum << "\n";
				num++;
			} // for()
		} // print()
	
}; // class Mission3

int main(){
  int command;
  bool M1Done = false;
  bool M2Done = false;
  
  do {
  START:
  	cout << "\n*** Search Tree Utilities **\n";
  	cout << "* 0. QUIT                  *\n";
  	cout << "* 1. Build 2-3 tree        *\n";
  	cout << "* 2. Build AVL tree        *\n";
  	cout << "* 3. Intersection Query    *\n";
  	cout << "*************************************" << "\n";
  	cout << "Input a command(0, 1, 2, 3): ";
    
    cin >> command;
    switch (command) {
      case 0: {
        cout << endl << "Bye Bye!" << endl;
        break;
      } // case 0


      // ���Ȥ@:
      /*
      Ū�J�ɮ׸�ƥh���e�T���A�x�s��l��ƨ�temp�� (temp������vector 
      �A�Ntemp��ƨ̾ڦP�ǮթΦP��t���O�ƻs�s�J M1temp & AVLtemp (�P������vector
	  �HM1temp��Ƥ@���@����m��23�𤺨ñƧ� 
	  �̫�L�X�� & root��m����� 
      */
      case 1: {
      	string Num;
      	Mission1 mission1;
      	Mission2 mission2;
      	Tree23 tree23;
      	cout << "\nInput a file number (e.g., 201, 202, 203, ...[0] Quit): ";
      	cin >> Num;
      	while (! mission1.OpenFile("input" + Num + ".txt")) {
          if (Num == "0") goto START;
          cout << "### input" + Num + ".txt does not exist! ###\n";
          cout << "Input a file number (e.g., 201, 202, 203, ...[0] Quit): ";
          cin >> Num;
        } // while
		
		mission1.temptoM1temp();
		mission2.temptoAVLtemp();
		tree23.Creat23Tree();
	
		cout << "Tree height = " << tree23.getMaxLevel() << "\n";
		tree23.PrintRoot();
		M1Done = true;

		fin.close();
        break;
      } // case 1


      // ���ȤG:
      /*
	  �HAVLtemp��Ƥ@���@����m��AVL�𤺨ñƧ� 
	  �̫�L�X�� & root��m����� 
      */
      case 2: {
      	AVLTree avltree;
      	if( !M1Done ){
      		cout << "### Choose 1 first. ###\n";
      		goto START;
		} // if
		
		avltree.CreatAVLTree();
      	cout << "Tree height = " << avltree.getMaxLevel() << "\n";
		avltree.PrintRoot();
		
		M2Done = true;
		
      	break;
      } // case 2
      
      case 3: {
      	if( !M1Done ){
      		cout << "### Choose 1 first. ###\n";
      		goto START;
		} // if
		else if( !M2Done ){
			cout << "### Choose 2 first. ###\n";
      		goto START;
		} // else if
		
		Tree23 tree23;
		tree23.Creat23Tree();
		AVLTree avltree;
		avltree.CreatAVLTree();
		
		Mission3 merge;
		merge.Search(tree23, avltree);
		merge.print();
      	
		break;
	  } // case 3

      default: {
        cout << "Command does not exist!\n";
        break;
      } // default
    } // switch
  } while (command != 0);
} // main()

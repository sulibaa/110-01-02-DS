//10827208 王宇凡 10827248 林虹吟

#include <string>
#include <iostream> // cin cout 
#include <fstream> 
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <iomanip> 
#include <ctime>
#include <sstream> // string to int 
#include <math.h>
#include <stack> 
#include<algorithm> // max, min

#define PTR_NUM 3
#define SCHOOL_NUM PTR_NUM-1 
using namespace std;

// 任務一 
typedef struct slotT { // a slot in a tree node
	vector<int> sid ; // same key's id
	string school ; // school name
} slotType;

typedef struct nT { // a tree node
	slotType data[SCHOOL_NUM] ; // sort school name
	nT *link[PTR_NUM] ;
	nT *parent ;
} nodeType;

typedef struct pointT { // a point on the search path
	nodeType *pnode ; // parent node
	int pidx ; // point id
} pointType;  

typedef struct bT{ // received from a split
	slotType slot ; // schoolName & id
	nodeType *link ; // pointer link to child on a right
} blockType;  



struct expression2{ 
	int num ; // 資料序號 
	string sid ; // 學校代碼 
	string school ; // 學校名稱 
	string did ; //科系代碼 
	string dname ; // 科系名稱 
	string type ; // 日間/進修別 
	string level ; // 等級別 
	string snum ; // 學生數 
	string tnum ; // 教師數 
	string gnum ; // 上學年度畢業生數 
	string place ; // 縣市名稱 
	string stype ; // 體系別 
}; 

int newId ; 
string newSchool ;
nodeType *root = NULL ; 

char*  fileName ;

expression2 tmp ;
vector<expression2> newdata ; // 存全部資料

vector<int> tttree ;
vector<int> AVLtree ;
vector<int> sameId ;
vector<expression2> answer ;


// 任務二
typedef struct cT {
	int number;     // id [1]~
	string school_id;
	string school_name; // chinese or english 
	string depart_id;
	string depart_name;  // chinese or english
	string typeE;  // advanced studies E1
	string typeC; //  advanced studies C1
	string rankE; // graduated level E1
	string rankC;  // graduated level ( chinese or not chinese(4+x) )
	int student_num;
	int teacher_num;
	int graduate_num;
	string city_id;
	string city_name;
	string pt_id;
	string pt_name;
} collegeType;

typedef struct BTNode
{
	string key;
	int height;
	vector <int> datanumbers;
	BTNode* leftchild;
	BTNode* rightchild;
	// BTNode* parent;
} BTNodeType;

class StringTest {
public:
	void stringtestprint();

};

class TxtToVector {
	cT cSet;
	vector <collegeType> schoolData;
	ifstream readfile; 
	ofstream outputfile; 
	string fileID;
	string name; // file head
public:
	bool getFileID(); // open file if it exists
	void getAll();    // file content sort to vector
	void countLine(); // print out line in file
	void printTest(); // print test vector which is schoolData vector
	void printTest(vector <collegeType> vectorprint); // print test by call vector
	void skipthreelines(string inputline); // skip three lines
	void vectorclear(); // clear schoolData vector
	vector <collegeType> returnschoolData(); // return vector from schoolData
	void txtoutputtest(vector <collegeType> vectorprint); // output text file from schoolData
};


class AVLTree
{
	BTNodeType* root;	// tree root
	vector <collegeType> schoolDataVector; // save data to vector
	bool isHeightUpdate;
	// collegeType schoolData;	
public:
	BTNodeType* leftRotation(BTNodeType* pNode); // right to left
	BTNodeType* rightRotation(BTNodeType* pNode);
	BTNodeType* leftRightRotation(BTNodeType* pNode);
	BTNodeType* rightLeftRotation(BTNodeType* pNode);
	int height();
	int height(BTNodeType* pNode);
	BTNodeType* insertNode(BTNodeType* pNode, int count);
	void buildRootNewNode();
	void buildAVLTree();
	void setschoolData(vector <collegeType> set);
	void printResult();
	vector<int> searchAVLtree( string sKey ) ;

};


class Tree {
	
	int count = 0 ;
	
	
	void Read( string line ) { // 將新資料放在newdata，學校名稱放在temp
	
		string data;
		int j = 0 ;
		count++ ;
		
		while ( line[j] != '\t' ) { // 存sid 
			data = data + line[j] ;
			j++ ;
		} // while
		
		tmp.sid = data ;
		data = "\0" ;
		j++ ;
		
		while ( line[j] != '\t' ) { // 存school 
			data = data + line[j] ;
			j++ ;
		} // while
		tmp.school = data ;
		newSchool = data ;
		data = "" ;
		j++ ;
		while ( line[j] != '\t' ) { // 存did 
			data = data + line[j] ;
			j++ ;
		} // while
		tmp.did = data ;
		data = "" ;
		j++ ;
		while ( line[j] != '\t' ) { // 存dname 
			data = data + line[j] ;
			j++ ;
		} // while
		tmp.dname = data ;
		data = "" ;
		j++ ;
		while ( line[j] != '\t' ) { // 存type
			data = data + line[j] ;
			j++ ;
		} // while
		tmp.type = data ;
		data = "" ;
		j++ ;
		while ( line[j] != '\t' ) { // 存level
			data = data + line[j] ;
			j++ ;
		} // while
		tmp.level = data ;
		data = "" ;
		j++ ;
		while ( line[j] != '\t' ) { // 存snum
			data = data + line[j] ;
			j++ ;
		} // while
			
		tmp.snum = data ;
		data = "" ;
		j++ ;
		while ( line[j] != '\t' ) { // 存tnum 
			data = data + line[j] ;
			j++ ;
		} // while
		tmp.tnum = data ;
		data = "" ;
		j++ ;
		while ( line[j] != '\t' ) { // 存gnum
			data = data + line[j] ;
			j++ ;
		} // while
		tmp.gnum = data ;
		data = "\0" ;
		j++ ;
		while ( line[j] != '\t' ) { // 存place
			data = data + line[j] ;
			j++ ;
		} // while
		tmp.place = data ;
		data = "" ;
		j++ ;
		while ( line[j] != '\0' ) { // 存stype
			data = data + line[j] ;
			j++ ;
		} // while
		tmp.stype = data ;
		data = "" ;
		j++ ;
		line = "" ;
		
		newId = count ;
		tmp.num = count ;

		newdata.insert( newdata.end(), tmp ) ;

		
	} // Read()
	


	void twoThreeTree( char* inputName ) {  
		string data = "\0" ;
		string line ;
		string garbage ;

		ifstream in( inputName ) ; // 叫出要讀的檔案  
		getline( in, garbage ) ;
		getline( in, garbage ) ;
		getline( in, garbage ) ;

		while ( getline( in, line )  ) {
			
			Read( line ) ;
			insert23tree( newId, newSchool ) ; //  
			data = "" ;
			line = "" ;
		} // while
		
		
	} // twoThreeTree()
	
	
	
	void insert23tree( int newId, string newSchool ) {
		slotType newSlot ;
		newSlot.sid.push_back( newId ) ;
		newSlot.school = newSchool ;
		if ( root == NULL ) {
			root = createNode( NULL, NULL, NULL, newSlot ) ;
		} // if
		
		else {
			stack<pointType> aPath ; // keep the search path
			pointType curP ; // last-visited node at the top of stack
			blockType blockUp ; // a data block received from a split
			
			searchPath( root, newSchool, aPath ) ; // find a matched position on 23 tree
			
			if ( !aPath.empty() ) {
				curP = aPath.top() ; // reference to the last-visited node
				if ( ( curP.pnode->data[curP.pidx].sid.size() ) && // size 1 = true
				   ( !newSchool.compare( curP.pnode->data[curP.pidx].school ) ) ) {
				   	// duplicaate key, insert it directly
					curP.pnode->data[curP.pidx].sid.push_back(newId) ;     
				} // if
				
				else if ( !curP.pnode->data[SCHOOL_NUM-1].sid.size() ) {
					// at least one unused slot
					insertLeaf( newSlot, curP ) ;
					
				} // else if
				
				else{
					// split a full leaf
					splitLeaf( newSlot, curP, blockUp ) ;
					if ( curP.pnode->parent == NULL ) { 
						// root is split, create a new root
						root = createRoot( curP.pnode, blockUp.link, blockUp.slot ) ;
					} // if
					
					else {
						// continue splitting a non-leaf for an insertion
						while ( true ) { // repeat untill the insertion is terminated 
							aPath.pop() ; // delete the current node
							curP = aPath.top() ; // the next parent for an insertion
							if ( !curP.pnode->data[SCHOOL_NUM-1].sid.size() ) { 
								// at least one unused slot
								insertNonleaf( blockUp, curP ) ; // add a slot into a non-leaf
								break ;
							} // if
							
							else {
								// split a full non-leaf
								splitNonleaf( curP, blockUp ) ;
								if ( curP.pnode->parent == NULL ) {
									// root is split, create a new root
									root = createRoot( curP.pnode, blockUp.link, blockUp.slot ) ;
									break ;
								} // if
								
							} // else
							
						}  
						
					} // else
						
				} // else
			} // if
			
		} // else
		
		
		
	} // insert23tree()
	
	
	
	nodeType *createNode( nodeType *left, nodeType *right, nodeType *pnode, slotType newS ) { // create a node with one record inserted
		nodeType *newNode = NULL ;
		
		try {
			newNode = new nodeType;
 	 		newNode->data[0].sid = newS.sid;
 	 		newNode->data[1].sid.clear();
 	 		newNode->data[0].school = newS.school;
 	  		newNode->data[1].school = "";
 	  		newNode->parent = pnode;
 	  		newNode->link[0] = left;
 	 		newNode->link[1] = right;
 	  		newNode->link[2] = NULL;
		} // try
		
		catch ( std::bad_alloc& ba ) {
			
			std::cerr << endl << "bad_alloc caught: " << ba.what() << endl ;			
		} // catch
		
		return newNode ;
	} // createNode()
	
	
	
	nodeType *createRoot( nodeType *left, nodeType *right, slotType oneSlot ) {
		nodeType *newRoot = createNode( left, right, NULL, oneSlot ) ;    
		left->parent = newRoot ; // set their parent as the new root
		right->parent = newRoot ;
		return newRoot ;
	} // createRoot()



	void searchPath( nodeType *cur, string newSchool, stack<pointType> &path ) { // find a matched position on 23 tree // 任務一 
		pointType oneP ;
		int pos ;
		while ( cur != NULL ) {
			oneP.pnode = cur ;
			for ( pos = 0; pos < SCHOOL_NUM; pos++ ) {
				
				if ( ( !cur->data[pos].sid.size() ) || // unused slot name > school 
				 	( ( newSchool.compare( cur->data[pos].school ) ) < 0 ) ) { // newSchool < school
					// search the next level
					
					break ;
				
				} // if
				
				else if ( !newSchool.compare( cur->data[pos].school ) ) { // newSchool == school
					oneP.pidx = pos ; // put parent node idx
					path.push(oneP) ;
				
					return ;
				} // else if
				
			} // for
			
			oneP.pidx = pos ; // store the parent node id
			path.push(oneP) ;
			cur = cur->link[pos] ; // recursive search the next level
		} // while
		
	} // searchPath()
	


	void insertLeaf( slotType newS, pointType &aLeaf ) { // add a record into a leaf
		for ( int i = SCHOOL_NUM-1; i >= aLeaf.pidx; i-- ) { // scan from right to left
		 
			if ( i > aLeaf.pidx ) { // shift an existing record to the right
				aLeaf.pnode->data[i].sid = aLeaf.pnode->data[i-1].sid ;
				aLeaf.pnode->data[i].school = aLeaf.pnode->data[i-1].school ;
			} // if
		
			else if ( i == aLeaf.pidx ) { // save the new record in a new slot
				aLeaf.pnode->data[i].sid = newS.sid ;
				aLeaf.pnode->data[i].school = newS.school ;
			} // else if
		
			else
				break ;
				
		} // for
		
				
	} // insertLeaf()



	void insertNonleaf( const blockType oneB, pointType &goal ) { // add a record into a non-leaf // 插入父節點 
		// find the position on goal.pnode to insert oneB
		for ( int i = SCHOOL_NUM-1; i >= goal.pidx; i-- ) { // scan from right to left
		 
			if ( i > goal.pidx ) { // shift an existing record to the right
				goal.pnode->data[i].sid = goal.pnode->data[i-1].sid ;
				goal.pnode->data[i].school = goal.pnode->data[i-1].school ;
			} // if
		
			else if ( i == goal.pidx ) { // save the new record in a new slot
				goal.pnode->data[i].sid = oneB.slot.sid ;
				goal.pnode->data[i].school = oneB.slot.school ;	
				if ( goal.pidx == 0 ) { // 在左子樹 
					goal.pnode->link[2] = goal.pnode->link[1] ; // 右移 
					goal.pnode->link[1] = oneB.link ; 
				} // if
				
				else
					goal.pnode->link[2] = oneB.link ; 
					
			} // else if
		
			else
				break ;
				
		} // for
		
		
		
	} // insertNonleaf



	void splitLeaf( slotType newS , pointType aLeaf, blockType &aBlock ) { // split a non-leaf for an insertion
		slotType buf[PTR_NUM] ; // a buffer to keep a full node plus a new record
		int idx = 0 ; // index of the full node
		for ( int i = 0; i < PTR_NUM; i++ ) { 
			// fill in the entire buffer
			buf[i].sid = ( i == aLeaf.pidx ) ? newS.sid : aLeaf.pnode->data[idx].sid ;
			buf[i].school = ( i == aLeaf.pidx ) ? newS.school : aLeaf.pnode->data[idx++].school ;
		} // for 
		
		aLeaf.pnode->data[0].sid = buf[0].sid ; // leave only the leftmost record
		aLeaf.pnode->data[0].school = buf[0].school ;
		
		for ( int i = 1; i < SCHOOL_NUM; i++ ) // the remains: unused slots
			aLeaf.pnode->data[i].sid.clear() ;
		
		aBlock.link = createNode( NULL, NULL, aLeaf.pnode->parent, buf[2] ) ; // create a sibling node on the right
		aBlock.slot.sid = buf[1].sid ; // block to move upwards
		aBlock.slot.school = buf[1].school ;
		
	} // splitLeaf()



	void splitNonleaf( pointType goal, blockType &oneB ) { // split a non-leaf for an insertion 
		slotType buf[PTR_NUM] ; // a buffer to keep a full node plus a new reocord
		nodeType *ptr[PTR_NUM+1] ; // a buffer to keep pointers of children
		int idx = 0 ; // index of the full node
		for ( int i = 0; i < PTR_NUM; i++ ) {
			// fill in the entire buffer
			buf[i].sid = ( i == goal.pidx ) ? oneB.slot.sid : goal.pnode->data[idx].sid ;
			buf[i].school = ( i == goal.pidx ) ? oneB.slot.school : goal.pnode->data[idx++].school ;
		} // for
		
		// put the sorted records in buf into three places: goal.pnode, oneB, a new sibling node
		if ( goal.pidx == 0 ) { 
			ptr[0] = goal.pnode->link[0] ;
			ptr[1] = oneB.link ;
	  	 	ptr[2] = goal.pnode->link[1] ;
	  	 	ptr[3] = goal.pnode->link[2] ;
		} // if
		
		else if ( goal.pidx == 1 ) {
			ptr[0] = goal.pnode->link[0] ;
	   	 	ptr[1] = goal.pnode->link[1] ;
	    	ptr[2] = oneB.link ;
	    	ptr[3] = goal.pnode->link[2] ;
		} // else if
		
		else if ( goal.pidx == 2 ) {
	    	ptr[0] = goal.pnode->link[0] ;
	    	ptr[1] = goal.pnode->link[1] ;
	    	ptr[2] = goal.pnode->link[2] ;
	    	ptr[3] = oneB.link ;
		} // else if
	
		goal.pnode->link[0] = ptr[0] ;
		goal.pnode->link[1] = ptr[1] ;
		goal.pnode->link[2] = NULL ;
	
	
		for ( int i = 1 ; i < SCHOOL_NUM ; i++ )
			goal.pnode->data[i].sid.clear() ;
	
		goal.pnode->data[0].sid = buf[0].sid ; // put smallest record on goal.pnode
		goal.pnode->data[0].school = buf[0].school ;
	
		oneB.link = createNode( ptr[2],ptr[3], goal.pnode->parent, buf[2] ) ;
		
		
		oneB.slot.sid = buf[1].sid ; // block to move upwards
		oneB.slot.school = buf[1].school ;
		
	} // splitNonleaf()


	
	void free23tree( nT *&root ) { // release the space of 23 tree
		if ( root != NULL ) {
			free23tree( root->link[0] ) ; // recursively traverse the leftmost subtree
			for ( int i = 0; i < SCHOOL_NUM; i++ ) { // scan the slots in a node from left to right
				if ( !root->data[i].sid.size() ) { // the remaining slots are also unused
					break ;
				} // if
				
				free23tree( root->link[i+1] ) ;
			} // for
			
			delete root ; // post-order tree traversal
		} // if
		
	} // free23tree()
	



	void printTreeHeight() {
		int i = 0 ;
		nodeType *now  = root ;
		while ( now != NULL ) {
			i++ ;
			now = now->link[0] ; 
			
		} // while
		
		cout << "Tree height= " << i << endl ;
		
	} // printTreeHeight()



	void PrintRoot() {
		int i = 0 ;
		int k = 0 ;
		nodeType *now  = root ;  
		vector<expression2> temp ;
		while ( k < 2 ) { //
			//cout << now->data[k].sid.size() << endl ;
			i = 0 ;
			if ( now->data[k].sid.size() > 0 ) {
				while ( i < now->data[k].sid.size() ) {
					
					int j = 0 ;
					while ( now->data[k].sid[i] != newdata[j].num ) { 
						j++ ;
						
					} // while
					
					
					temp.push_back( newdata[j] ) ;
					
					i++ ;
					
				} // while
				
			} // if
			
			k++ ;
		} // while
		
		BubbleSort( temp ) ;
		
		i = 0 ;
		while ( i < temp.size() ) {
			cout << i+1 << ": [" << temp[i].num << "] " << temp[i].school << ", " 
			 			<< temp[i].dname<< ", " << temp[i].type<< ", " << temp[i].level 
			 	 		<< ", " << temp[i].snum << endl ;
			i++ ;
			
		} // while
		
		
	} // PrintRoot()
	
	
	
	void BubbleSort( vector<expression2> &answer ) { // 泡沫排序(被呼叫用) 
		int i, j ;
		string line ;
		for ( i = answer.size() - 1 ; i > 0 ; i-- ) {
			for ( j = 0 ; j <= i - 1 ; j++ ) {
				if ( answer[j].num > answer[j+1].num ) {
					swap(answer[j], answer[j+1]) ;
				} // if 

				else
				;
			} // for
			
		} // for
		
	} // BubbleSort() 
		
		
	
	public: vector<int> search23tree( string sKey ) {
		stack<pointType> aPath ;
		vector<int> ridS ;
		
		searchPath(root, sKey, aPath) ;
		
		if ( !aPath.empty() ) {
			pointType curP = aPath.top() ;
			if ( !sKey.compare( curP.pnode->data[curP.pidx].school ) ) {
				ridS = curP.pnode->data[curP.pidx].sid ;
				
			} // if
			
			
		} // if
		
		return ridS ; 
	} // search23tree()
	
	
	
	void printSameDepartment( string newDepartment ) {
		int i = 0 ;

		while ( i < newdata.size() ) { 
			
			if ( newdata[i].dname == newDepartment ) {
				answer.push_back( newdata[i] ) ;
			} // if
						
			i++ ;
			
		} // while
		
		
		BubbleSort( answer ) ;
		
		i = 0 ;
		while ( i < answer.size() ) {
			cout << i+1 << ": [" << answer[i].num << "] " << answer[i].school << ", " 
			 			<< answer[i].dname<< ", " << answer[i].type<< ", " << answer[i].level 
			 	 		<< ", " << answer[i].snum << endl ;
			i++ ;
			
		} // while
		
	} // printSameDepartment()
	
	
	
	void printSameSchool( string newSchool ) {
		int i = 0 ;

		while ( i < newdata.size() ) { 
			
			if ( newdata[i].school == newSchool ) {
				answer.push_back( newdata[i] ) ;
			} // if
						
			i++ ;
			
		} // while
		
		BubbleSort( answer ) ;
		
		i = 0 ;
		while ( i < answer.size() ) {
			cout << i+1 << ": [" << answer[i].num << "] " << answer[i].school << ", " 
			 			<< answer[i].dname<< ", " << answer[i].type<< ", " << answer[i].level 
			 	 		<< ", " << answer[i].snum << endl ;
			i++ ;
			
		} // while
		
	} // printSameDepartment()
	
	
	
	void printAll() {
		int i = 0 ;
		while ( i < newdata.size() ) {
			cout << i+1 << ": [" << newdata[i].num << "] " << newdata[i].school << ", " 
			 			<< newdata[i].dname<< ", " << newdata[i].type<< ", " << newdata[i].level 
			 	 		<< ", " << newdata[i].snum << endl ;
			i++ ;
			
		} // while
		
	} // printAll()
	
	
	



	public : int Mission1() {
		
		
		free23tree( root ) ;
		newdata.clear() ;
		root = NULL ;	
		
		
		string name ; 
		string iName ; // input的 
		cout << endl << "Input a file number ([0]: quit):" ;
		cin >> name ;
		if ( name == "0" )
			return 0 ; // 結束程式  
		iName = "input" + name + ".txt" ; // 名稱改成input.輸入的數字 
		char* inputName = (char*)iName.data() ; //將string轉成char* 
		fileName = inputName ;
		fstream input ; // 宣告input 
		input.open( inputName, ios::in ) ; // 將要讀入的檔案開啟 
		while ( !input ) { //當沒有這個input檔 
			cout << endl << "### " << inputName << " does not exist! ### " << endl ;
			cout << endl << "Input a file number ([0]: quit):" ;
			name = "" ;  
			iName = "" ;
			inputName = NULL ;
			cin >> name ;
			if ( name == "0" )
			    return 0 ; 
			iName = "input" + name + ".txt" ;
			inputName = (char*)iName.data() ;
			input.open( inputName, ios::in ) ;
		} // while
		
		
		
		twoThreeTree( inputName ) ;  
		printTreeHeight() ;
		PrintRoot() ;
		

		count = 0 ;
		
		return 1 ;
	} // Mission1()
	


	
	vector<int> searchSameId( vector<int> tttree, vector<int> AVLtree ) {
		int i, j = 0 ;
		//cout << endl << tttree.size() << endl ;
		
		while ( i < tttree.size() ) { // i < tttree.size()
			j = 0 ;
			
			while ( j < AVLtree.size() ) { // j < AVLtree.size()
				
				if ( tttree[i] == AVLtree[j] ) {
					sameId.push_back( AVLtree[j] ) ;
					break ;
				} // if
				
				j++ ;
			} // while
			
			i++ ;
			
		} // while
		
		return sameId ;
		
		
	} // searchSameId()
	
	
	void printSameId( vector<int> sameId ) {
		vector<expression2> temp ;
		int i = 0 ;
		
		while( i < sameId.size() ) {
			
			int j = 0 ;
			while ( sameId[i] != newdata[j].num ) { 
				j++ ;
						
			} // while
					
			temp.push_back( newdata[j] ) ;
			i++ ;
			
		} // while
		
		BubbleSort( temp ) ;
		
		i = 0 ;
		while ( i < temp.size() ) {
			cout << i+1 << ": [" << temp[i].num << "] " << temp[i].school << ", " 
			 			<< temp[i].dname<< ", " << temp[i].type<< ", " << temp[i].level 
			 	 		<< ", " << temp[i].snum << endl ;
			i++ ;
			
		} // while
		
		
	} // printSameId() 
	
	
} ; // class Tree


class ProcessCommand {
public:
	void command();
};

void StringTest::stringtestprint()
{
	string a = "日";
	string b;
	b = a;
	a = "職";
	string c = "修";
	cout << endl << a.size();
	cout << endl << b.size();
	cout << endl << c.size();
}

void ProcessCommand::command() {
	int command; 
	bool isDoC1 = false;
	bool isDoC2 = false;
	TxtToVector sdata; 
	Tree mission1 ;
	AVLTree avltree; 
	Tree mission3 ;

	do {
		vector<collegeType> schoolData;

		cout << endl << "*** Search Tree Utilities ***";
		cout << endl << "* 0. QUIT                   *";
		cout << endl << "* 1. Build 2-3 tree         *";
		cout << endl << "* 2. Build AVL tree         *";
		cout << endl << "* 3. Intersection Query     *";
		cout << endl << "Input a choice(0, 1, 2, 3):";
		cin >> command;

		switch (command) {
		case 0:
			break;
		case 1:
			
			isDoC1 == false ;
			isDoC2 == false ;

			mission1.Mission1() ;
			isDoC1 = true;
		
			


			break;

		case 2:
			
			if ( isDoC1 == false ) {
				cout << "### Choose 1 first. ###" << endl ;
				break ;
			} // if
			
			
			if ( sdata.getFileID() ) {
				
				sdata.vectorclear();
				
				schoolData.clear();
				
				sdata.getAll();
				
				schoolData = sdata.returnschoolData();
				

			}
			
			// if (isDoC1 == true ) {
				// sdata.printTest();
				schoolData = sdata.returnschoolData();
				// sdata.printTest(schoolData);
				avltree.setschoolData(schoolData);
				avltree.buildAVLTree();
				avltree.printResult();
				isDoC2 = true;
				
		
			break;

		case 3:
			
			if ( isDoC1 == false ) {
				cout << "### Choose 1 first. ###" << endl ;
				break ;
			} // if
			
			else if ( isDoC2 == false ) {
				cout << "### Choose 2 first. ###" << endl ;
				break ;
			} // else if
			
			if (sdata.getFileID()) {

				string newSchool ;
				string newDepartment ;
				
				cout << "Enter a college name to search [*]: " << endl ;
				cin >> newSchool ;
				cout << "Enter a department name to search [*]: " << endl ;
				cin >> newDepartment ;
				
					
				if ( newSchool != "*" && newDepartment != "*" ) {
					tttree = mission3.search23tree( newSchool ) ;
					AVLtree = avltree.searchAVLtree( newDepartment ) ;
					sameId = mission3.searchSameId( tttree, AVLtree ) ;
					mission3.printSameId( sameId ) ; 
					sameId.clear() ;
					tttree.clear() ;
					AVLtree.clear() ;
				} // if
				
				else if ( newSchool == "*" && newDepartment == "*" ) {
					mission3.printAll() ; 
				} // else if
				
				else if ( newSchool == "*" ) {
					mission3.printSameDepartment( newDepartment ) ; 
					answer.clear() ;
				} // else if
				
				else if ( newDepartment == "*" ) {
					mission3.printSameSchool( newSchool ) ; 
					answer.clear() ;
				} // else if	
				

		
			}
			
			break;
		case 4:
			if (sdata.getFileID()) {
				// sdata.countLine();
				// sdata.printTest();
				sdata.getAll();
				// sdata.printTest();
				schoolData = sdata.returnschoolData();
				sdata.printTest(schoolData);
				sdata.txtoutputtest(schoolData);
				sdata.vectorclear();
			}
			break;
		default:
			cout << endl << "Command does not exist!" << endl;
		} // end switch
		
		
		
	} while (command != 0); // '0': stop the program
}

bool TxtToVector::getFileID() {
	
	name = fileName ;
	cout << fileName;
	readfile.open(name.c_str());
	
	return true;
	

}

void TxtToVector::skipthreelines(string inputline) {

	for (int count = 0; count < 3; count++) {
		getline(readfile, inputline);
		// cout << endl << inputline;
	}  //忽略前三行

}



void TxtToVector::countLine() {
	int count = 0;
	string inputline;
	skipthreelines(inputline);//忽略前三行

	while (getline(readfile, inputline)) {
		count++;
		cout << endl << "[" << count << "]" << inputline;
	}  //標記資料順序和輸出資料
	readfile.close();


} //檢查行數用

void TxtToVector::printTest() {
	for (int count = 0; count < schoolData.size(); count++) {
		cout << endl << "[" << schoolData[count].number << "]";
		cout << "\t" << schoolData[count].school_id;
		cout << "\t" << schoolData[count].school_name;
		cout << "\t" << schoolData[count].depart_id;
		cout << "\t" << schoolData[count].depart_name;
		if (schoolData[count].typeE != "null") {
			cout << "\t" << schoolData[count].typeE;
			cout << "\t" << schoolData[count].typeC;
		}
		else
			cout << "\t" << "\t";
		if (schoolData[count].rankE != "null") {
			cout << "\t" << schoolData[count].rankE;
			cout << "\t" << schoolData[count].rankC;
		}

		cout << "\t" << schoolData[count].student_num;
		cout << "\t" << schoolData[count].teacher_num;
		cout << "\t" << schoolData[count].graduate_num;
		cout << "\t" << schoolData[count].city_id;
		cout << "\t" << schoolData[count].city_name;
		cout << "\t" << schoolData[count].pt_id;
		cout << "\t" << schoolData[count].pt_name;

	}
}

void TxtToVector::printTest(vector <collegeType> vectorprint) {
	for (int count = 0; count < vectorprint.size(); count++) {
		cout << endl << "[" << vectorprint[count].number << "]";
		cout << "\t" << vectorprint[count].school_id;
		cout << "\t" << vectorprint[count].school_name;
		cout << "\t" << vectorprint[count].depart_id;
		cout << "\t" << vectorprint[count].depart_name;
		if (vectorprint[count].typeE != "null") {
			cout << "\t" << vectorprint[count].typeE;
			cout << "\t" << vectorprint[count].typeC;
		}
		else
			cout << "\t" << "\t";
		if (vectorprint[count].rankE != "null") {
			cout << "\t" << vectorprint[count].rankE;
			cout << "\t" << vectorprint[count].rankC;
		}

		cout << "\t" << vectorprint[count].student_num;
		cout << "\t" << vectorprint[count].teacher_num;
		cout << "\t" << vectorprint[count].graduate_num;
		cout << "\t" << vectorprint[count].city_id;
		cout << "\t" << vectorprint[count].city_name;
		cout << "\t" << vectorprint[count].pt_id;
		cout << "\t" << vectorprint[count].pt_name;

	}
	
	

}

void TxtToVector::getAll() {

	string inputline, inputstring; //輸入一行資料和子資料
	string copystring;
	int inputnumber; // 輸入數字資料
	int lastindex; // 輸入字串的最後一個字
	int count = 0; // 編序號
	char check, check02; //檢查用字元
	bool type = true, rank = true;
	// bool lostdata01 = false, lostdata02 = false; //檢查資料缺漏用
	skipthreelines(inputline); //忽略前三行
	readfile >> inputstring;    // 先讀取第一行資料的id方便eof的檢查
	while (!readfile.eof()) {
		count++;
		cSet.number = count;
		// cout << endl << "[" << count << "]";
		// if(inputstring.size() > 0 )
		cSet.school_id = inputstring;
		// cout << "\t" << cSet.school_id;

		readfile >> inputstring;
		cSet.school_name = inputstring;
		// cout << "\t" << cSet.school_name;

		readfile >> inputstring;
		cSet.depart_id = inputstring;
		// cout << "\t" << cSet.depart_id;

		readfile >> inputstring;
		cSet.depart_name = inputstring;
		// cout << "\t" << cSet.depart_name;

		readfile >> inputstring; // 可能讀取到進修別、等級代號或是學生數
		if (inputstring.size() >= 2) // 學生數
		{
			type = false;
			rank = false;
			copystring = inputstring; // 學生數複製
			readfile >> inputstring; //  老師數
		}
		else // 進修別、等級代號或學生數<10
		{
			check = inputstring[0];
			if (check >= '0' && check <= '9') // 等級別代號或學生數
			{
				type = false;
				copystring = inputstring; // 等級別代號或學生數複製
				readfile >> inputstring; // 等級別中文或老師數
				check02 = inputstring[0];
				if ((check02 >= '0' && check02 <= '9') || check02 == '"')
				{
					rank = false;

				}
				else
				{
					rank = true;
				}

			}
			else  // 進修別代號或等級別代號
			{
				copystring = inputstring; //進修別代號或等級別代號複製
				readfile >> inputstring; // 進修別中文或等級別中文
				if (inputstring.size() == 2)
				{
					type = true;
					cSet.typeE = copystring;
					cSet.typeC = inputstring;
					readfile >> inputstring;
					copystring = inputstring;
					readfile >> inputstring;
					if (copystring.size() == 1 && (inputstring.size() == 4 || inputstring.size() == 3 || inputstring.size() == 6))
					{
						rank = true;

					}

					else
					{
						rank = false;
					}


				}
				else
				{
					type = false;
					if (copystring.size() == 1 && (inputstring.size() == 4 || inputstring.size() == 3 || inputstring.size() == 6))
					{
						rank = true;

					}

					else
					{
						rank = false;
					}

				}
			}

		}

		if (type == false && rank == false)
		{
			check = copystring[0];
			if (check == '"')
			{
				lastindex = copystring.size() - 1;
				copystring.erase(lastindex, 1); // delete "
				copystring.erase(2, 1);  // delete ,
				copystring.erase(0, 1); // delete "

			}
			stringstream convert(copystring);
			convert >> inputnumber;
			cSet.student_num = inputnumber;
			check = inputstring[0];
			if (check == '"') {
				lastindex = inputstring.size() - 1;
				inputstring.erase(lastindex, 1); // delete "
				inputstring.erase(2, 1);  // delete ,
				inputstring.erase(0, 1); // delete "
			}

			stringstream convert2(inputstring);
			convert2 >> inputnumber;
			cSet.teacher_num = inputnumber;
		}
		else if (type == false && rank == true)
		{
			cSet.typeE = "null";
			cSet.typeC = "null";
			cSet.rankE = copystring;
			cSet.rankC = inputstring;
			readfile >> inputstring; // 學生數
			check = inputstring[0];
			if (check == '"') {
				lastindex = inputstring.size() - 1;
				inputstring.erase(lastindex, 1); // delete "
				inputstring.erase(2, 1);  // delete ,
				inputstring.erase(0, 1); // delete "
			}

			stringstream convert(inputstring);
			convert >> inputnumber;
			cSet.student_num = inputnumber;

			readfile >> inputstring; // 老師數
			check = inputstring[0];
			if (check == '"') {
				lastindex = inputstring.size() - 1;
				inputstring.erase(lastindex, 1); // delete "
				inputstring.erase(2, 1);  // delete ,
				inputstring.erase(0, 1); // delete "
			}

			stringstream convert2(inputstring);
			convert2 >> inputnumber;
			cSet.teacher_num = inputnumber;

		}
		else if (type == true && rank == false)
		{

			// cSet.typeE = copystring;
			// cSet.typeC = inputstring;
			cSet.rankE = "null";
			cSet.rankC = "null";
			// readfile >> inputstring; // 學生數
			check = copystring[0];
			if (check == '"') {
				lastindex = copystring.size() - 1;
				copystring.erase(lastindex, 1); // delete "
				copystring.erase(2, 1);  // delete ,
				copystring.erase(0, 1); // delete "
			}

			stringstream convert(copystring);
			convert >> inputnumber;
			cSet.student_num = inputnumber;

			check = inputstring[0];
			if (check == '"') {
				lastindex = inputstring.size() - 1;
				inputstring.erase(lastindex, 1); // delete "
				inputstring.erase(2, 1);  // delete ,
				inputstring.erase(0, 1); // delete "
			}

			stringstream convert2(inputstring);
			convert2 >> inputnumber;
			cSet.teacher_num = inputnumber;



		}
		else // if( type == true && rank == true )
		{
			cSet.rankE = copystring;
			cSet.rankC = inputstring;
			readfile >> inputstring; // 學生數
			check = inputstring[0];
			if (check == '"') {
				lastindex = inputstring.size() - 1;
				inputstring.erase(lastindex, 1); // delete "
				inputstring.erase(2, 1);  // delete ,
				inputstring.erase(0, 1); // delete "
			}

			stringstream convert(inputstring);
			convert >> inputnumber;
			cSet.student_num = inputnumber;
			readfile >> inputstring; // 老師數
			check = inputstring[0];
			if (check == '"') {
				lastindex = inputstring.size() - 1;
				inputstring.erase(lastindex, 1); // delete "
				inputstring.erase(2, 1);  // delete ,
				inputstring.erase(0, 1); // delete "
			}

			stringstream convert2(inputstring);
			convert2 >> inputnumber;
			cSet.teacher_num = inputnumber;
		}




		readfile >> inputstring; // 畢業學生數
		check = inputstring[0];
		lastindex = inputstring.size() - 1;
		if (check == '"') {
			inputstring.erase(lastindex, 1); // delete "
			inputstring.erase(2, 1);  // delete ,
			inputstring.erase(0, 1); // delete "
		}


		stringstream convert(inputstring);
		convert >> inputnumber;
		cSet.graduate_num = inputnumber;
		// cout << "\t" << cSet.graduate_num;


		readfile >> inputstring;
		cSet.city_id = inputstring;
		// cout << "\t" << cSet.city_id;

		readfile >> inputstring;
		cSet.city_name = inputstring;
		// cout << "\t" << cSet.city_name;

		readfile >> inputstring;
		cSet.pt_id = inputstring;
		// cout << "\t" << cSet.pt_id;

		readfile >> inputstring;
		cSet.pt_name = inputstring;


		schoolData.push_back(cSet);
		readfile >> inputstring;









	}

	readfile.close();


}



void TxtToVector::vectorclear() {
	schoolData.clear();

}

void TxtToVector::txtoutputtest(vector <collegeType> vectorprint) {
	string outputname = "output";
	outputname.append(fileID.c_str());
	outputname.append(".txt");
	outputfile.open(outputname.c_str());
	for (int count = 0; count < vectorprint.size(); count++) {
		// outputfile << "[" << vectorprint[count].number << "]";
		outputfile << vectorprint[count].school_id;
		outputfile << "\t" << vectorprint[count].school_name;
		outputfile << "\t" << vectorprint[count].depart_id;
		outputfile << "\t" << vectorprint[count].depart_name;
		if (vectorprint[count].typeE != "null") {
			outputfile << "\t" << vectorprint[count].typeE;
			outputfile << "\t" << vectorprint[count].typeC;
		}
		else
			outputfile << "\t" << "\t";
		if (vectorprint[count].rankE != "null") {
			outputfile << "\t" << vectorprint[count].rankE;
			outputfile << "\t" << vectorprint[count].rankC;
		}

		outputfile << "\t" << vectorprint[count].student_num;
		outputfile << "\t" << vectorprint[count].teacher_num;
		outputfile << "\t" << vectorprint[count].graduate_num;
		outputfile << "\t" << vectorprint[count].city_id;
		outputfile << "\t" << vectorprint[count].city_name;
		outputfile << "\t" << vectorprint[count].pt_id;
		outputfile << "\t" << vectorprint[count].pt_name;
		outputfile << endl;
	}

	outputfile.close();
}

vector <collegeType> TxtToVector::returnschoolData() {
	return schoolData;
}


BTNodeType* AVLTree::leftRotation( BTNodeType* pNode ) //RR
{
	BTNodeType* rorightchild = pNode->rightchild;
	pNode->rightchild = rorightchild->leftchild;
	rorightchild->leftchild = pNode;


	if ( height(pNode-> leftchild) > height(pNode-> rightchild) )
	{
		pNode->height = height(pNode->leftchild) + 1;
	}
	else if (height(pNode->leftchild) <= height(pNode->rightchild))
	{
		pNode->height = height(pNode->rightchild) + 1;
	}

	if (height(rorightchild->leftchild) > height(rorightchild->rightchild))
	{
		rorightchild->height = height(rorightchild->leftchild) + 1;
	}
	else if (height(rorightchild->leftchild) <= height(rorightchild->rightchild))
	{
		rorightchild->height = height(rorightchild->rightchild) + 1;
	}

	return rorightchild;

}

BTNodeType* AVLTree:: rightRotation(BTNodeType* pNode) //LL
{
	BTNodeType* roleftchild = pNode->leftchild;
	pNode->leftchild = roleftchild->rightchild;
	roleftchild->rightchild = pNode;


	if (height(pNode->leftchild) > height(pNode->rightchild))
	{
		pNode->height = height(pNode->leftchild) + 1;
	}
	else if (height(pNode->leftchild) <= height(pNode->rightchild))
	{
		pNode->height = height(pNode->rightchild) + 1;
	}

	if (height(roleftchild->leftchild) > height(roleftchild->rightchild))
	{
		roleftchild->height = height(roleftchild->leftchild) + 1;
	}
	else if (height(roleftchild->leftchild) <= height(roleftchild->rightchild))
	{
		roleftchild->height = height(roleftchild->rightchild) + 1;
	}

	return roleftchild;

}



BTNodeType* AVLTree::leftRightRotation(BTNodeType* pNode) //LR
{

	pNode->leftchild = leftRotation(pNode->leftchild);
	return  rightRotation( pNode );

}

BTNodeType* AVLTree::rightLeftRotation(BTNodeType* pNode) //RL
{

	pNode->rightchild = rightRotation(pNode->rightchild);
	return  leftRotation( pNode );

}

int AVLTree::height(BTNodeType* pNode)
{
	if (pNode != NULL)
		return pNode->height;
	else
		return -1;
}

int AVLTree::height()
{
	return height(root);
}


BTNodeType* AVLTree::insertNode(BTNodeType* pNode, int count )
{
	if ( pNode == NULL )
	{
		pNode = new BTNodeType;
		pNode->key = schoolDataVector[count].depart_name;
		pNode->datanumbers.push_back(schoolDataVector[count].number);
		pNode->leftchild = NULL;
		pNode->rightchild = NULL;
		// pNode->parent = NULL;
		isHeightUpdate = true;
	}
	else if (pNode->key < schoolDataVector[count].depart_name)
	{
		pNode->rightchild = insertNode(pNode->rightchild, count);
		if (height(pNode->rightchild) - height(pNode->leftchild) == 2 )
		{
			if (pNode->rightchild->key < schoolDataVector[count].depart_name )
			{
				pNode = leftRotation(pNode); //RR
			}

			else 
			{
				pNode = rightLeftRotation(pNode);  //RL
			}
		}
	}
	else if ( pNode->key > schoolDataVector[count].depart_name)
	{
		pNode->leftchild = insertNode(pNode->leftchild, count);
		if (height(pNode->leftchild) - height(pNode-> rightchild) == 2)
		{
			if (pNode->leftchild->key > schoolDataVector[count].depart_name)
			{
				pNode = rightRotation(pNode);  // LL
			}

			else 
			{
				pNode = leftRightRotation(pNode);  // LR
			}
		}
	}
	else if (pNode->key == schoolDataVector[count].depart_name)
	{
		pNode->datanumbers.push_back(schoolDataVector[count].number);
		isHeightUpdate = false;
		// 不需要更新高度
	}
	
	// pNode->height = max(height(pNode->leftchild), height(pNode->rightchild)) + 1;

	if ( isHeightUpdate == false )
	{
		;
	}
	else if ( height( pNode->leftchild ) > height(pNode->rightchild ) )
	{
		pNode->height = height(pNode->leftchild) + 1;
	}
	else // if ( height( pNode->leftchild ) < height(pNode->rightchild ) )
	{
		pNode->height = height(pNode->rightchild) + 1;
	}

	return pNode;
}

void AVLTree::buildRootNewNode()
{
	root = new BTNodeType;
	root->key = schoolDataVector[0].depart_name;
	root->datanumbers.push_back(schoolDataVector[0].number);
	root->leftchild = NULL;
	root->rightchild = NULL;
	// root->parent = NULL;
	root->height = 0;
}


void AVLTree::buildAVLTree()
{
	root = NULL; // intial root
	for (int count = 0; count < schoolDataVector.size(); count++)
	{
		if (root == NULL)
		{
			buildRootNewNode();
		}
		else
		{
			root = insertNode(root, count);
		}
	}

}
void AVLTree::setschoolData(vector <collegeType> set)
{
	schoolDataVector = set;
}

void AVLTree::printResult()
{
	int h = height();
	int count = 0;
	cout << endl << "Tree height = " << h+1;
	for ( int count01 = 0 ; count01 < root->datanumbers.size(); count01++ )
	{
		for ( int count02 = 0 ; count02 < schoolDataVector.size(); count02++)
		{
			if (  root->datanumbers[count01] == schoolDataVector[count02].number )
			{
				count++;
				
				
				cout << endl << count << ": " << "[" << schoolDataVector[count02].number << "] ";
				cout << schoolDataVector[count02].school_name << ", " << schoolDataVector[count02].depart_name;
				if (schoolDataVector[count02].typeE == "null")
				{
					cout << ", ";
				}
				else
				{
					cout << ", " << schoolDataVector[count02].typeE<<"	"<< schoolDataVector[count02].typeC;
				}

				if (schoolDataVector[count02].rankE == "null")
				{
					cout << ", ";
				}
				else
				{
					cout << ", " << schoolDataVector[count02].rankE << " " << schoolDataVector[count02].rankC;
				}

				cout << ", " << schoolDataVector[count02].student_num;
				
			}
		}

	}
	
	schoolDataVector.clear() ;
}

vector<int> AVLTree:: searchAVLtree( string sKey ) {

	vector<int> ridS ;
	BTNodeType* cur = root ;

	while ( cur != NULL ) {
		
		if ( !sKey.compare( cur->key ) ) {
			ridS = cur->datanumbers ;
			break ;
			
		} // if
			
		else if ( sKey.compare( cur->key ) < 0 ) {
			cur = cur->leftchild ;
		} // else if
			
		else {
			cur = cur->rightchild ;
			
		} // else
			
				 
	} // while
	

 	return ridS ;
} // searchAVLtree()
	
int main()
{
	ProcessCommand c;
	c.command();
	// StringTest str;
	// str.stringtestprint();
	return 0;
}



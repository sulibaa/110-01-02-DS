#include <iostream> // cout, endl
#include <fstream> // open, is_open, close, ignore
#include <string> // string, find_last_of, substr
#include <vector> // vector, push_back
#include <cstdlib> // system, atoi
#include <iomanip> // setw
#include <stdio.h>
#include <string.h>
#include <time.h>

using namespace std ;

typedef struct college_data { 

    string wholeline;  
    int serialnum ;
    int sernum2 ;
    int sNO;        //學生數量 

} type;

typedef vector<college_data> Data;

Data data;
Data data2;
Data data2temp;

string file_name ;
string the_num_of_file; //每一個檔案的編號  
ifstream fin;
ofstream fout; 
int L = 0 ;
bool fileerror = false ;

int Judge(int p) {
    while (p > 3)  p/=2;
    return p ; 
} // judge

int MinPartner(int p) {
    int i = p, s = 1;
    while(p > 3) {
		p /= 2, s *= 2;
	}	
    return i-s ;
} // minpartner

int MaxPartner(int p) {
    if(p == 2) return 2;
    int i = p, s = 1;
    while(p > 3)    p /= 2, s *= 2 ;
   // if( i + s > L ) return ( i + s ) / 2 ;
    return i+s ;
} //maxpartner

void MinInsert(vector<int> &Deap,int S, int N) {
	
    int P=S/2;
    while(P > 1 && Deap[P] > N)   Deap[S]=Deap[P], S=P, P=S/2;
    Deap[S] = N;
    
} // mininsert

void MaxInsert(vector<int> &Deap,int S, int N) {
	
    int P=S/2;
    while(P > 1 && Deap[P]< N)   Deap[S]=Deap[P], S=P, P=S/2;
    Deap[S] = N;
    
} // maxinsert

void Deap_Insert( vector<int> &Deap, int N ) {
    L++;
    
    if( L==2 )  {
        Deap[2] = N ;
        return ;
    } // if
    
    int p = L, i ;
    switch( Judge(p) ) {
            case 3:/*right */
                i = MinPartner(p) ;
               // if( N < Deap[i] )     Deap[p] = Deap[i], MinInsert( i, N ) ;
               // else MaxInsert( Deap, p, N ) ;
                break;
            case 2:/*left */
                i = MaxPartner(p);
                //if( N > Deap[i] )     //Deap[p] = Deap[i], MaxInsert( i, N ) ;
                //else MinInsert( Deap, p, N );
                break;
        }
} // deap_insert

/*void Delete_Max() {
    int p = L , t = Deap[L--];
	int a, b, i;
    for( a = 3; a*2 <= L; a = b ) {
        a *= 2 ;
        if( a < L && Deap[a] < Deap[a+1] )  
			b = a + 1 ;
        else b = a ;
        Deap[a/2] = Deap[b] ;
    }
       
    i = MinPartner(a);
    int biggest = i ;
    if(2*i <= L) {
            biggest =2 * i ;
            if (((2*i + 1) <= L) && (Deap[2*i] < Deap[2*i+1]))
                biggest++;
        }
    if(t < Deap[biggest]) {
            Deap[a] = Deap[biggest];
            MinInsert(biggest, t);
        }
    else MaxInsert( Deap, a, t);
} //delete_max

void Delete_Min() {
	
    int p = L, t = Deap[L--];
	int a, b, i;
    for( a = 2; a * 2 <= L ; a = b ) {
            a * = 2 ;
            if(a < L && Deap[a] > Deap[a+1] )
                b = a + 1 ;
            else b = a;
            Deap[a/2] = Deap[b] ;
    }
    
    i= MaxPartner(a);
    if( t > Deap[i] ) {
            Deap[a]=Deap[i];
            MaxInsert( Deap, i, t);
        }
    else MinInsert( Deap, a, t);
} */// delete_min

void Deap() {
	
}

void swap(int &p1, int &p2){
    int temp = p1;
    p1 = p2;
    p2 = temp;
} //swap 

void max_heapify(std::vector<int> &array, int i, int n) {
	
    int j, temp, temp2;
    temp = array[i];
    //temp2 = data[i-1].serialnum ;
    j = 2 * i;
    
    while (j <= n) {
        if (j < n && array[j+1] > array[j])
            j = j + 1;
        if (temp > array[j])
            break;
        else if (temp <= array[j]) {
            array[j / 2] = array[j];
            //data[(j-1)/ 2].serialnum = data[j-1].serialnum ;
            j = 2 * j;
        }
    } // while
    
    array[j/2] = temp;
    //data[(j-1)/ 2].serialnum = temp2 ; 
    return;
}

void min_heapify(std::vector<int> &array, int i, int n) {
	
    int j, temp, temp2;
    temp = array[i];
    //temp2 = data[i-1].serialnum ;
    j = 2 * i;
    
    while (j <= n) {
        if (j < n && array[j+1] < array[j])
            j = j + 1;
        if (temp < array[j])
            break;
        else if (temp >= array[j]) {
            array[j / 2] = array[j];
            //data[(j-1)/ 2].serialnum = data[j-1].serialnum ;
            j = 2 * j;
        }
    } // while
    
    array[j/2] = temp;
    //data[(j-1)/ 2].serialnum = temp2 ; 
    return;
}

void BuildMaxHeap(std::vector<int> &array){

    for (int i = (int)array.size()/2; i >= 1 ; i--) {
        max_heapify(array, i, (int)array.size() - 1 );     
    }
}

void BuildMinHeap(std::vector<int> &array){

    for (int i = (int)array.size()/2; i >= 1 ; i--) {
        min_heapify(array, i, (int)array.size() - 1 );     
    }
}


void HeapSort(std::vector<int> &array){
	
    array.insert(array.begin(), 0);                     // 將index(0)閒置

    BuildMaxHeap(array);                                // 將array調整成Max Heap

    int size = (int)array.size() -1;                    // size用來記錄「目前要處理的矩陣」之長度
    for (int i = (int)array.size() -1; i >= 2; i--) {
        swap(array[1], array[i]);                      // 將最大值放到array的最後一個位置
        size--;
        //MaxHeapify(array, 1, size);                     // 調整「忽略最後一個位置」的矩陣
    }

    array.erase(array.begin());                         // 將index(0)刪除
}

void checkserial(std::vector<int> &array) {
	
	int a = 1 , b = 0 , num ;
	while ( a <= sizeof(array) ) {
		while ( b < data.size() ) {
			if ( array[a] == data[b].sNO ){
				num = data[b].serialnum ;
			}
			b++ ;
		}
		a++ ;
	}
	cout << num << endl ;
}

void Maxheapresult(std::vector<int> &array, int a) {
		
		//checkserial(array) ;
		cout << endl ;
		cout << "<Max Heap>" << endl ;
		cout << "Root :" << "[" << data[1].sernum2 << "]" << " " << array[1] << endl ;
		cout << "Bottom :" << "[" << data[a-1].sernum2 << "]" << " " << array[a-1] << endl ;
		int n = 0 ;
		int b = 1 ;
		while ( b < sizeof(array)/2 ) {
			b = b * 2 ;
			n++ ;
			//cout << b << endl ;
		}
		cout << "Leftmost Bottom :" << "[" << data[b+1].sernum2 << "]" << " " << array[b+1] << endl ;
}

void Minheapresult(std::vector<int> &array, int a) {
		
		//checkserial(array) ;
		cout << endl ;
		cout << "<Min Heap>" << endl ;
		cout << "Root :" << "[" << data[1].sernum2 << "]" << " " << array[1] << endl ;
		cout << "Bottom :" << "[" << data[a-1].sernum2 << "]" << " " << array[a-1] << endl ;
		int n = 0 ;
		int b = 1 ;
		while ( b < sizeof(array)/2 ) {
			b = b * 2 ;
			n++ ;
			//cout << b << endl ;
		}
		cout << "Leftmost Bottom :" << "[" << data[b+1].sernum2 << "]" << " " << array[b+1] << endl ;
}

bool fileexist() {
	string one = "input" ;
	string two = ".txt" ;
	cout << "Input a file: " ;
	the_num_of_file = "" ;
	cin >> the_num_of_file;
	file_name = "" ;
	file_name = one + the_num_of_file + two;
	fin.open(file_name);  //打開input檔案
	 
		if ( !fin.is_open() ) {
			cout << "File does not exist !" << endl ;
	 		fileerror = true ;
	 		return false;
		} 
}

bool read_and_save() { // 在讀取並儲存file裏的資料 
	 
	int check = 0;
	fileexist() ;
	
	if ( fileerror == true ) return false ;
	
	char ch;
	
	while( ch != '\n' ) {
		fin.get(ch); 
	} // end while 
	
	fin.get(ch);
	 
	while( ch != '\n' ) {
	    fin.get(ch); 
	} // end while 
	 
	fin.get(ch);
	 
	while( ch != '\n' ) {
	    fin.get(ch); 
	} // end while 
	 
	// 丟掉開頭的三行

	while ( fin.peek() != EOF ) {
	 	
	 	college_data temp;
	 	
	 	check = 0;
	 	
	 	while ( check <= 10 && !fin.eof() ) {
	 		
	 		string blocks ;
			  
            fin.get(ch);

	 		while ( ch != '\t' && ch != '\n' && !fin.eof() ) {
	 			
	 			blocks = blocks + ch;
	 			fin.get(ch);
	 			
			} // end while
			 
			 temp.wholeline = temp.wholeline + blocks;
			 
			if ( ch == '\t' ) temp.wholeline = temp.wholeline + "\t";
			else if ( ch == '\n' ) temp.wholeline = temp.wholeline + "\n";
			else if ( fin.eof() && ch != '\n' ) temp.wholeline = temp.wholeline + "\n";
	 		
	 		if ( check == 6 ) {
	 			if ( blocks[0] == '\"' ) {
	 				string ex;
	 				for( int i = 0; i < blocks.length(); i++ ) {
	 					if ( '0' <= blocks[i] && blocks[i] <= '9' ) ex = ex + blocks[i];
					 } // end for
					 
					 blocks = ex;
					 
				 } // end if
			 } // end if
	 	
	 	    if ( check == 6 ) temp.sNO = atoi( blocks.c_str() );
	 		  
	 	    check++;
			
	 	} // end while
	 	
        //cout << temp.wholeline ;
        fout.close();
        data.push_back(temp);
        data2.push_back(temp);
        data2temp.push_back(temp);
 		temp.wholeline.clear() ;
 		
	} // end while
	
	int a = 0; 
	while ( a < data.size() ) {
		data[a].serialnum = a + 1 ;
    //	cout << data[a].serialnum << " " ;
    //	cout << data[a].sNO << endl ;
    	a++ ;
	} // while output
	
	//data.clear() ;
	//data2.clear() ;
	//data2temp.clear() ;
	
} // read_and_save()

void choice() {
		cout << endl ;
		cout << "*******   Heap Construction   *******" << endl ;
	    cout << "* 0. QUIT                           *" << endl ;
	    cout << "* 1. Build a Max Heap               *" << endl ;
	    cout << "* 2. Build a Deap                   *" << endl ;
	    cout << "* 3. Build a Min - Max heap         *" << endl ;
	    cout << "* 4. Build a Min Heap               *" << endl ;
	    cout << "*************************************" << endl ;
	    cout << "Input a choice(0, 1, 2, 3, 4): " ;
}  

int main() {	
  bool end = false;
  string cmd;
  while( !end ) {
  	choice() ;
  	cin >> cmd;
  	cout << endl;
  	if( cmd.size() == 1 && cmd[0] == '1' ){        // 輸入1 
  	  //mission1();
  	  read_and_save() ;
  	  vector<int> array ;
  	  int a = 1 ;
  	  array.push_back(0) ;
  	  while ( a <= data.size() ) {
  	  	array.push_back(data[a-1].sNO) ;
  	  	//cout << array[a] << endl ;
  	  	a++ ;
		}
		
  	  BuildMaxHeap(array) ;
  	  
  	  a = 1 ;
  	  int n = 0 ;
  	  while ( a <= data.size() ) {
  	  	//array.push_back(data[a].sNO) ;
  	  	while ( n < data.size() ) {
  	  		if ( array[a] == data[n].sNO ) {
  	  			data[a].sernum2 = data[n].serialnum ;
  	  			cout << "[" << data[n].serialnum << "]" << "\t";
				}
			n++ ;	
			}
		
  	  	//cout << a << " " ;
  	  	cout << array[a] << endl ;
  	  	a++ ;
  	  	n = 0 ;
		}
		
		Maxheapresult(array,a) ;	
		
    } // if()
    else if( cmd.size() == 1 && cmd[0] == '2' ){   // 輸入2 
      //mission2();
    	read_and_save() ;
    	vector<int> Deap ;
  		int a = 1 ;
  		Deap.push_back(0) ;
  		while ( a <= data.size() ) {
  	  		Deap.push_back(data[a-1].sNO) ;
  	  		//cout << array[a] << endl ;
  	  		a++ ;
		}
		
		Deap_Insert(Deap,a) ;
		
	} // else if() 
	else if( cmd.size() == 1 && cmd[0] == '4' ){   // 輸入4
	
		read_and_save() ;
  	  vector<int> array ;
  	  int a = 1 ;
  	  array.push_back(0) ;
  	  while ( a <= data.size() ) {
  	  	array.push_back(data[a-1].sNO) ;
  	  	//cout << array[a] << endl ;
  	  	a++ ;
		}
		
  	  BuildMinHeap(array) ;
  	  
  	  a = 1 ;
  	  int n = 0 ;
  	  while ( a <= data.size() ) {
  	  	//array.push_back(data[a].sNO) ;
  	  	while ( n < data.size() ) {
  	  		if ( array[a] == data[n].sNO ) {
  	  			data[a].sernum2 = data[n].serialnum ;
  	  			cout << "[" << data[n].serialnum << "]" << "\t";
				}
			n++ ;	
			}
		
  	  	//cout << a << " " ;
  	  	cout << array[a] << endl ;
  	  	a++ ;
  	  	n = 0 ;
		}
		
		Minheapresult(array,a) ;
	}
	else if( cmd.size() == 1 && cmd[0] == '0' ){   // 輸入0 
	
      end = true;
      
    } // else if()
    
    else printf( "Command does not exist!\n" ); 
    
  }	// while()
} // main()

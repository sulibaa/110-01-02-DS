// 10827111袁本誠 10827102沈柏融 
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <time.h>


using namespace std;

bool quit = false;  
clock_t start, end;

typedef struct hibiki{
	string a, b, c, d, e, f, g="\0", h="\0", i, j, k, l,student;
	int teacher=0, graduate=0 ;
};


class Mission {
 public:
  
void Merge(vector<struct hibiki> &arr, int front, int mid, int end){

    // 利用 std::vector 的constructor, 
    // 把array[front]~array[mid]放進 LeftSub[]
    // 把array[mid+1]~array[end]放進 RightSub[]
    vector<struct hibiki> left, right;
    
    left.assign(arr.begin()+front, arr.begin()+mid+1);
    right.assign(arr.begin()+mid+1, arr.begin()+end+1);
	
    int idxLeft = 0, idxRight = 0;
    int a =  front;
    while (idxLeft < left.size() && idxRight < right.size()) {
        if (left[idxLeft].graduate >= right[idxRight].graduate ) {
            arr[a] = left[idxLeft];
            idxLeft++;
        }
        else{
            arr[a] = right[idxRight];
            idxRight++;
        }
        
        a++;
    }
    
    
    while(idxLeft<left.size()){
    	arr[a] = left[idxLeft];
    	a++;
    	idxLeft++;
	}
}

void MergeSort(vector<struct hibiki> &arr, int front, int end){
                                         // front與end為矩陣範圍
    if (front < end) {                   // 表示目前的矩陣範圍是有效的
        int mid = front+(end-front)/2;         // mid即是將矩陣對半分的index
        //cout<<mid<<endl;
        MergeSort(arr, front, mid);    // 繼續divide矩陣的前半段subarray
        MergeSort(arr, mid+1, end);    // 繼續divide矩陣的後半段subarray
        Merge(arr, front, mid, end);   // 將兩個subarray做比較, 並合併出排序後的矩陣
    }
}



void newQuicksort(vector<struct hibiki> &arr, int left, int right)
{
    int pivot, i, j;

    if (left >= right) { 
    	return; 
	}

    int mid = left + ( right - left )/2 ; 
    pivot = arr[mid].graduate;

    i = left + 1;
    j = right;

    while (1)
    {
        while (i <= right)
        {
            if (arr[i].graduate < pivot)
            {
                break;
            }

            i = i + 1;
        }

        while (j > left)
        {
            if (arr[j].graduate > pivot)
            {
                break;
            }

            j = j - 1;
        }

        if (i > j) {
		 break; 
		}

        swap(arr[i], arr[j]);
 }
    swap(arr[left], arr[j]);
    newQuicksort(arr, left, j - 1);
    newQuicksort(arr, j + 1, right);
}


void Quicksort(vector<struct hibiki> &arr, int left, int right)
{
    int pivot, i, j;

    if (left >= right) { 
    	return; 
	}

    pivot = arr[right].graduate;

    i = left + 1;
    j = right;

    while (1)
    {
        while (i <= right)
        {
            if (arr[i].graduate < pivot)
            {
                break;
            }

            i = i + 1;
        }

        while (j > left)
        {
            if (arr[j].graduate > pivot)
            {
                break;
            }

            j = j - 1;
        }

        if (i > j) {
		 break; 
		}

        swap(arr[i], arr[j]);
 }
    swap(arr[left], arr[j]);
    Quicksort(arr, left, j - 1);
    Quicksort(arr, j + 1, right);
}
  

  void mission1(){
   string text, bubble, select;
   fstream file;
   cout << "\n" << "Input 501, 502, ...[0]Quit):";
   cin >> text;
   if(text == "0") getcommand(); // 0就是重新輸入指令 
   else {
   	bubble = "bubble" + text + ".txt";
   	select = "select" + text + ".txt";
    text = "input" + text + ".txt";
    file.open(text.c_str(), ios::in);
    if(!file.is_open()) {
     cout << "\n" << "### " << text << " does not exist! ###\n";
     mission1();
    }
    else {
	 string temp;
	 for(int b = 0; b != 3 ; b++) getline( file,temp );
	 vector<struct hibiki> save, save2;
	 hibiki ouo;
	 while(!file.eof()){
	 	file>>ouo.a, file>>ouo.b, file>>ouo.c, file>>ouo.d, file>>ouo.e;
		if(isdigit(ouo.e[0])){
			ouo.student = ouo.e;
			ouo.e = ouo.f = ouo.g = ouo.h = "\0";
			file>>ouo.teacher, file>>ouo.graduate, file>>ouo.i, file>>ouo.j, file>>ouo.k, file>>ouo.l;
		}
		else {
			file>>ouo.f, file>>ouo.g;
			if( ouo.g[0] == '0' ){
				ouo.student = ouo.g;
				ouo.g = ouo.h = "\0";
				file>>ouo.teacher, file>>ouo.graduate, file>>ouo.i, file>>ouo.j, file>>ouo.k, file>>ouo.l;
			}
			else{
				file>>ouo.h, file>>ouo.student, file>>ouo.teacher, file>>ouo.graduate;
		        file>>ouo.i, file>>ouo.j, file>>ouo.k, file>>ouo.l;
			}
		}
	 	save.push_back(ouo);
	 }
	 
	 save2.assign( save.begin(), save.end() );
     // 選擇排序 
	 
	 start = clock();
	 for(int a = 0; a < save.size()-1 ;a++){
	 	for(int b = a+1; b<save.size();b++){
	 		if(save[a].graduate < save[b].graduate) swap(save[a],save[b]);
		}
     }
	 end = clock();
	 cout<< "SelectSort need : " << end-start << endl;  
	 //write(select, save);
	 fstream sel;
     sel.open(select.c_str(), ios::out);
     for( int a = 0 ; a < save.size() ; a++ ) {
     	sel<<save[a].a, sel<<"\t", sel<<save[a].b, sel<<"\t", sel<<save[a].c, sel<<"\t";
		sel<<save[a].d, sel<<"\t", sel<<save[a].e, sel<<" ", sel<<save[a].f, sel<<"\t";
		sel<<save[a].g, sel<<" ", sel<<save[a].h, sel<<"\t", sel<<save[a].student, sel<<"\t";
		sel<<save[a].teacher, sel<<"\t", sel<<save[a].graduate, sel<<"\t", sel<<save[a].i, sel<<" ";
		sel<<save[a].j, sel<<"\t", sel<<save[a].k, sel<<" ", sel<<save[a].l, sel<<"\n";
	 }
	 sel.close();
	 
	 /* 
int a = save.size();
	 for( int b = 0 ; b < a ; b++){
	 	cout << save[b].graduate << endl; 
	 }  // 測試沒存錯 
	 */ 
	 
	 // 泡泡排序 
	 start = clock();
	 for( int a=save2.size() ; a != 1 ; a-- ) {
	 	for( int b=0 ; b < a ; b++) {
	 		if( save2[b].graduate < save2[b+1].graduate ) swap(save2[b], save2[b+1]);
		}
	 }
	 end = clock();
	 cout<< "BubbleSort need : " << end-start << endl;  
	 //write(bubble, save2);
	 fstream bub;
	 bub.open(bubble.c_str(), ios::out);
     for( int a = 0 ; a < save.size() ; a++ ) {
     	bub<<save2[a].a, bub<<"\t", bub<<save2[a].b, bub<<"\t", bub<<save2[a].c, bub<<"\t";
		bub<<save2[a].d, bub<<"\t", bub<<save2[a].e, bub<<" ", bub<<save2[a].f, bub<<"\t";
		bub<<save2[a].g, bub<<" ", bub<<save2[a].h, bub<<"\t", bub<<save2[a].student, bub<<"\t";
		bub<<save2[a].teacher, bub<<"\t", bub<<save2[a].graduate, bub<<"\t", bub<<save2[a].i, bub<<" ";
		bub<<save2[a].j, bub<<"\t", bub<<save2[a].k, bub<<" ", bub<<save2[a].l, bub<<"\n";
	 }
	 
	 bub.close();
    
   } 
  }
  } 
  
  void mission2(){
   string text2, merge, quick;
   fstream file2;
   cout << "\n" << "Input 501, 502, ...[0]Quit):";
   cin >> text2;
   if(text2 == "0") getcommand(); // 0就是重新輸入指令 
   else {
   	merge = "merge" + text2 + ".txt";
   	quick = "quick" + text2 + ".txt";
    text2 = "input" + text2 + ".txt";
    file2.open(text2.c_str(), ios::in);
    if(!file2.is_open()) {
     cout << "\n" << "### " << text2 << " does not exist! ###\n";
     mission2();
    }
    else {
	 string copytemp2;
	 for(int b = 0; b != 3 ; b++) getline( file2,copytemp2 );
	 vector<struct hibiki> save3, save4;
	 hibiki o3o;
	 while(!file2.eof()){
	 	file2>>o3o.a, file2>>o3o.b, file2>>o3o.c, file2>>o3o.d, file2>>o3o.e;
		if(isdigit(o3o.e[0])){
			o3o.student = o3o.e;
			o3o.e = o3o.f = o3o.g = o3o.h = "\0";
			file2>>o3o.teacher, file2>>o3o.graduate, file2>>o3o.i, file2>>o3o.j, file2>>o3o.k, file2>>o3o.l;
		}
		else {
			file2>>o3o.f, file2>>o3o.g;
			if( o3o.g[0] == '0' ){
				o3o.student = o3o.g;
				o3o.g = o3o.h = "\0";
				file2>>o3o.teacher, file2>>o3o.graduate, file2>>o3o.i, file2>>o3o.j, file2>>o3o.k, file2>>o3o.l;
			}
			else{
				file2>>o3o.h, file2>>o3o.student, file2>>o3o.teacher, file2>>o3o.graduate;
		        file2>>o3o.i, file2>>o3o.j, file2>>o3o.k, file2>>o3o.l;
			}
		}
	 	save3.push_back(o3o);
	 }
	 save4.assign( save3.begin(), save3.end() );
	 
	 start = clock();
	 MergeSort(save3, 0, save3.size()-1);
	 end = clock();
	 fstream mer; 
	 mer.open(merge.c_str(), ios::out);
	 for( int a = 0 ; a < save3.size() ; a++ ) {
     	mer<<save3[a].a, mer<<"\t", mer<<save3[a].b, mer<<"\t", mer<<save3[a].c, mer<<"\t";
		mer<<save3[a].d, mer<<"\t", mer<<save3[a].e, mer<<" ", mer<<save3[a].f, mer<<"\t";
		mer<<save3[a].g, mer<<" ", mer<<save3[a].h, mer<<"\t", mer<<save3[a].student, mer<<"\t";
		mer<<save3[a].teacher, mer<<"\t", mer<<save3[a].graduate, mer<<"\t", mer<<save3[a].i, mer<<" ";
		mer<<save3[a].j, mer<<"\t", mer<<save3[a].k, mer<<" ", mer<<save3[a].l, mer<<"\n";
	 }
	 cout<< "MergeSort need : " << end-start << endl;  
	 
	 start = clock();
	 Quicksort(save4, 0, save4.size()-1);
	 end = clock();
	 fstream q; 
	 q.open(quick.c_str(), ios::out);
	 for( int a = 0 ; a < save4.size() ; a++ ) {
     	q<<save4[a].a, q<<"\t", q<<save4[a].b, q<<"\t", q<<save4[a].c, q<<"\t";
		q<<save4[a].d, q<<"\t", q<<save4[a].e, q<<" ", q<<save4[a].f, q<<"\t";
		q<<save4[a].g, q<<" ", q<<save4[a].h, q<<"\t", q<<save4[a].student, q<<"\t";
		q<<save4[a].teacher, q<<"\t", q<<save4[a].graduate, q<<"\t", q<<save4[a].i, q<<" ";
		q<<save4[a].j, q<<"\t", q<<save4[a].k, q<<" ", q<<save4[a].l, q<<"\n";
	 }
	 cout<< "QuickSort need : " << end-start << endl;  
	 
	}
   }
  }
  
  void mission3(){
   string text3, newbubble, newquick;
   fstream file3;
   cout << "\n" << "Input 501, 502, ...[0]Quit):";
   cin >> text3;
   if(text3 == "0") getcommand(); // 0就是重新輸入指令 
   else {
   	newbubble = "newbubble" + text3 + ".txt";
   	newquick = "newquick" + text3 + ".txt";
    text3 = "input" + text3 + ".txt";
    file3.open(text3.c_str(), ios::in);
    if(!file3.is_open()) {
     cout << "\n" << "### " << text3 << " does not exist! ###\n";
     mission3();
    }
    else {
	 string temp3;
	 for(int b = 0; b != 3 ; b++) getline( file3,temp3 );
	 vector<struct hibiki> save5, save6;
	 hibiki quq;
	 while(!file3.eof()){
	 	file3>>quq.a, file3>>quq.b, file3>>quq.c, file3>>quq.d, file3>>quq.e;
		if(isdigit(quq.e[0])){
			quq.student = quq.e;
			quq.e = quq.f = quq.g = quq.h = "\0";
			file3>>quq.teacher, file3>>quq.graduate, file3>>quq.i, file3>>quq.j, file3>>quq.k, file3>>quq.l;
		}
		else {
			file3>>quq.f, file3>>quq.g;
			if( quq.g[0] == '0' ){
				quq.student = quq.g;
				quq.g = quq.h = "\0";
				file3>>quq.teacher, file3>>quq.graduate, file3>>quq.i, file3>>quq.j, file3>>quq.k, file3>>quq.l;
			}
			else{
				file3>>quq.h, file3>>quq.student, file3>>quq.teacher, file3>>quq.graduate;
		        file3>>quq.i, file3>>quq.j, file3>>quq.k, file3>>quq.l;
			}
		}
	 	save5.push_back(quq);
	 }
	 
	 save6.assign( save5.begin(), save5.end() );
	 
	 bool finish = false;
	 start = clock();
	 
	 for( int a=save5.size() ; a != 1 && !finish ; a-- ) {
	 	finish = true;
	 	for( int b=0 ; b < a ; b++) {
	 		if( save5[b].graduate < save5[b+1].graduate ) {
			 swap(save5[b], save5[b+1]);
			 finish = false;
			}
		}
	 }
	 
	 //bubbleSort(save5);
	 
	 end = clock();
	 cout<< "New BubbleSort need : " << end-start << endl;  
	 //write(select, save);
	 fstream nb;
     nb.open(newbubble.c_str(), ios::out);
     for( int a = 0 ; a < save5.size() ; a++ ) {
     	nb<<save5[a].a, nb<<"\t", nb<<save5[a].b, nb<<"\t", nb<<save5[a].c, nb<<"\t";
		nb<<save5[a].d, nb<<"\t", nb<<save5[a].e, nb<<" ", nb<<save5[a].f, nb<<"\t";
		nb<<save5[a].g, nb<<" ", nb<<save5[a].h, nb<<"\t", nb<<save5[a].student, nb<<"\t";
		nb<<save5[a].teacher, nb<<"\t", nb<<save5[a].graduate, nb<<"\t", nb<<save5[a].i, nb<<" ";
		nb<<save5[a].j, nb<<"\t", nb<<save5[a].k, nb<<" ", nb<<save5[a].l, nb<<"\n";
	 }
	 nb.close();
	 
	 /* 
int a = save.size();
	 for( int b = 0 ; b < a ; b++){
	 	cout << save[b].graduate << endl; 
	 }  // 測試沒存錯 
	 */ 
	 
	 // 泡泡排序 
	 start = clock();
	 newQuicksort(save6, 0, save6.size()-1);
	 end = clock();
	 cout<< "new Quicksort need : " << end-start << endl;  
	 //write(bubble, save2);
	 fstream nq;
	 nq.open(newquick.c_str(), ios::out);
     for( int a = 0 ; a < save6.size() ; a++ ) {
     	nq<<save6[a].a, nq<<"\t", nq<<save6[a].b, nq<<"\t", nq<<save6[a].c, nq<<"\t";
		nq<<save6[a].d, nq<<"\t", nq<<save6[a].e, nq<<" ", nq<<save6[a].f, nq<<"\t";
		nq<<save6[a].g, nq<<" ", nq<<save6[a].h, nq<<"\t", nq<<save6[a].student, nq<<"\t";
		nq<<save6[a].teacher, nq<<"\t", nq<<save6[a].graduate, nq<<"\t", nq<<save6[a].i, nq<<" ";
		nq<<save6[a].j, nq<<"\t", nq<<save6[a].k, nq<<" ", nq<<save6[a].l, nq<<"\n";
	 }
	 
	 nq.close();
   } 
  }
  }
  
  void getcommand(){ //做1或2或3的指令 
   int choice;
   cout << "\n" ;
    printf("*** File Object Manipulator  ***\n");
    printf("* 0. Quit                      *\n");
    printf("* 1. Copy (Read & Save a file) *\n");
    printf("* 2. FILTER (Reduce a file)    *\n");
    printf("********************************\n");
    printf("Input a choice(0, 1, 2, 3): ");
    cin >> choice;
    if(choice == 1) mission1();
    else if(choice == 2) mission2();
    else if(choice == 3) mission3();
    else if(choice == 0) quit = true;
    else;
  }
};

int main(){
 Mission mission ;
 mission.getcommand();
  while(!quit){
   mission.getcommand();
  }
 
  system("pause");
  return 0;
}


/*
     while(!list.eof()) {
      list >> test;
      if (end==14) {
      	save.push_back(test+"\n");
      	end = -1;
	  }
      else save.push_back(test+"\t");
      //cout<<test<<endl;
      //cout<<save[a];
      a++;
      end++;
	 } // while
*/	 

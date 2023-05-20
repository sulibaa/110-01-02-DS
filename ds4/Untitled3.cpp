// §Æº¸±Æ§Ç 
# include <iostream>
# include <fstream>
# include <string.h>
#include <ctime>
# include <vector>
# include <iomanip>

using namespace std;



void swap(int *a, int *b){
  int temp;
  temp = *a;
  *a = *b;
  *b= temp;
};
 
int shell_sort(int A[], int n){
  int span, i;
  span = n/2;
  cout << span <<"\n";
  while(span>=1){
    for(i = span; i<n; ++i){
    	int loc = i;
    	int nextItem = A[i];
        for(;(loc >= span) && (A[loc-span] > nextItem); loc = loc-span)
          A[loc] = A[loc-span];
        A[loc] = nextItem;
    }
    span = span/2;
  }
};
 
int main(){
  int count = 5, i;
  //scanf("%d", &count);
  int list[count] = {5,4,3,2,1};
  //printf("Numbers to be sorted: ");
  //for(i = 0; i<count; i++){
  //  scanf("%d", &list[i]);
  //  printf("%d ", list[i]);
  //}
  //printf("\n");
  shell_sort(list, count);
  printf("Numbers Sorted: ");
  for(i = 0; i<count; i++){
    printf("%d ", list[i]);
  }
  return 0;
}

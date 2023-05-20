// ®ðªw±Æ§Çªk 
#include <iostream> 

using namespace std;

int main(){
	int num[100];
	int N;
	int i, j, temp;
	
	cin >> N;
	for(i = 0; i < N; i++ )
		cin >> num[i];
		
	for(i = N; i > 0; i--){
		for(j = 0; j < i-1; j++){
			if(num[j] > num[j+1]){
				temp = num[j];
				num[j] = num[j+1];
				num[j+1] = temp;
			}
		}
	}
	
	for(i = 0; i < N; i++){
		cout << num[i] << " ";
	}
}

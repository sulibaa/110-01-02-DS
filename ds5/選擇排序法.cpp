// ¿ï¾Ü±Æ§Çªk
#include <iostream> 

using namespace std;

int main(){
	int num[100];
	int N;
	int i, j, temp;
	
	cin >> N;
	for(i = 0; i < N; i++ )
		cin >> num[i];
		
	for(i = 0; i < N; i++){
		for(j = i + 1; j < N; j++){
			if(num[i] > num[j]){
				temp = num[i];
				num[i] = num[j];
				num[j] = temp;
			}
		}
	}
	
	for(i = 0; i < N; i++){
		cout << num[i] << " ";
	}
}

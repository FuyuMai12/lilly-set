#include <iostream>
#include <math.h>

using namespace std;

int prime[501];
void sang (){
	prime[0] = prime[1] = 0;
	for(int i = 2; i < 500; i++){
		prime[i] = 1;
	}
	for(int i = 2; i <= sqrt(500); i++){
		if(prime[i]){
			for(int j = i * i; j < 500; j += i){
				prime[j] = 0;
			}
		}
	}
}

int legendre (int n, int p){
	int exp = 0;
    while (n){
        exp += n / p;
        n /= p;
    }
    return exp;
}

int main(){
	int n, k;
	while (cin >> n >> k){
		if(k == 0 || k == n){
			cout << 1 << endl;
			continue;
		}
		sang();
		long long uoc = 1;
		for(int i = 2; i <= 500; i++){
			if(prime[i]){
				int exp = legendre(n, i) - legendre(k, i) - legendre(n - k, i);
				uoc *= (exp + 1);
			}
		}
		cout << uoc << endl;
	}
	return 0;
}

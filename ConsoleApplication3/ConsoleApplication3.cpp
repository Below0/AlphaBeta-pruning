#include <iostream>
#include <cstdio>
#include <malloc.h>
#include <vector>
#include <climits>
#include <cmath>
#include <algorithm>

using namespace std;
#define STONE_SIZE sizeof(bool)*N
bool* stones;
bool* check;
int N, M;

void makeList(int num) {
	check = (bool*)malloc(sizeof(bool) * (N+1));
	memset(check, true, sizeof(bool) * (N + 1));
	for (int i = 2; i <= num; i++) {  // 나누는 값 : i

		for (int j = 2; j <= num; j++) {
			if (j != i && j % i == 0) {  // 자신과 같지않고 0으로 떨어지면 소수아님
				check[j] = false;
			}
		}
	}
}
int cntPos(int last) {
	int cnt = 0;
	if (last == 1) {
		for (int i = 0; i < N; i++) {
			if (stones[i]) cnt++;
		}
	}
	else {
		int temp = 2;
		while (last * temp < N) { // 마지막의 배수 중 가능한 수
			if (stones[last * temp]) cnt++;
		}
		for (int i = 2; i < last; i++) {
			if (check[i] && last % i == 0 && stones[i - 1]) cnt++;
		}
	}
	return cnt;
}
float evaluate(bool player, int last) {
	int cnt = cntPos(last);
	float result;
	if (stones[0]) result = 0;
	else if (player) { // MAX 일때
		if (last == 1) {
			if (cnt % 2 == 0) result = -0.5;
			else result = 0.5;
		}
		else if (check[last]) {
			if (cnt % 2 == 0) result = -0.7;
			else result = 0.7;
		}
		else {
			if (cnt % 2 == 0) result = -0.6;
			else result = 0.6;
		}
	}
	else { 	// MIN일때
		if (last == 1) {
			if (cnt % 2 == 0) result = 0.5;
			else result = -0.5;
		}
		else if (check[last]) {
			if (cnt % 2 == 0) result = 0.7;
			else result = -0.7;
		}
		else {
			if (cnt % 2 == 0) result = 0.6;
			else result = -0.6;
		}
	}
	return result;
}

float minmax(int depth, bool player, int last, float a, float b) {
	vector<int> v;
	float temp;
	for (int i = 0; i < N; i++) {
		if (stones[i]) v.push_back(i + 1);
	}
	if (player) {
		for (int i = 0; i < v.size(); i++) {
			stones[v[i] - 1] = false;
			a = max(a, minmax(depth + 1, false, v[i], a, b));
			stones[v[i] - 1] = true;
			if (a >= b) break;
		}
		return b;
	}
	else {
		for (int i = 0; i < v.size(); i++) {
			stones[v[i] - 1] = false;
			b = min(b,minmax(depth + 1, true, v[i], a, b));
			stones[v[i] - 1] = true;
			if (a >= b) break;
		}
		return a;
	}
}


int main(){
	int t, last = 0;
	float res;
	bool start;
	scanf("%d %d", &N, &M);
	stones = (bool*)malloc(STONE_SIZE);
	memset(stones, true, STONE_SIZE);
	makeList(N);
	for (int i = 0; i < M; i++) {
		scanf("%d", &t);
		if (i == M - 1) last = t;
		stones[t - 1] = false;
	}
	if (M % 2 == 0) start = true; // MAX
	else start = false;
	res = minmax(0,start,last,INT_MIN,INT_MAX);
	cout << res << endl;
	return 0;
}

/*
소수의 연속합
하나 이상의 연속된 소수의 합으로 나타낼 수 있는 자연수들이 있다. 몇 가지 자연수의 예를 들어 보면 다음과 같다.

3 : 3 (한 가지)
41 : 2+3+5+7+11+13 = 11+13+17 = 41 (세 가지)
53 : 5+7+11+13+17 = 53 (두 가지)
하지만 연속된 소수의 합으로 나타낼 수 없는 자연수들도 있는데, 20이 그 예이다. 
7+13을 계산하면 20이 되기는 하나 7과 13이 연속이 아니기에 적합한 표현이 아니다. 
또한 한 소수는 반드시 한 번만 덧셈에 사용될 수 있기 때문에, 3+5+5+7과 같은 표현도 적합하지 않다.

자연수가 주어졌을 때, 이 자연수를 연속된 소수의 합으로 나타낼 수 있는 경우의 수를 구하는 프로그램을 작성하시오.

입력
첫째 줄에 자연수 N이 주어진다. (1 ≤ N ≤ 4,000,000)

출력
첫째 줄에 자연수 N을 연속된 소수의 합으로 나타낼 수 있는 경우의 수를 출력한다.
*/



#include <iostream>

using namespace std;

int isprime(int num)
{
    for (int i = 2; i*i <= num; i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main(void)
{
    int N = 0;
    int arr[1000000];   //소수들의 배열
    int primeCount = 0;
    int ptr1, ptr2;
    int sum = 0;
    int caseCount = 0;
    
    cin >> N;
    
    //소수 구하기
    for (int i = 2; i <= 4000000; i++) {
        if (isprime(i)) {
            arr[primeCount] = i;
            primeCount++;
        }
    }
    
    ptr1 = 0;
    ptr2 = 0;
    
    sum = arr[ptr2];
    
    while (ptr1 < primeCount && ptr2 < primeCount && arr[ptr1] <= N && arr[ptr2] <= N) {
        if (sum == N) {
            caseCount++;
            sum -= arr[ptr1];
            ptr1++;
        }
        
        else if (sum < N) {
            ptr2++;
            
            if (ptr2 >= primeCount) {
                break;
            }
            
            sum += arr[ptr2];
        }
        
        else if (sum > N) {
            sum -= arr[ptr1];
            ptr1++;
        }
    }
    
    cout << caseCount;
    
    
    return 0;
}

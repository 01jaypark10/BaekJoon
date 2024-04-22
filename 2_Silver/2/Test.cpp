#include <iostream>
#include <vector>

using namespace std;

void printStar(int y, int x, int num) {
    // Base condition for spaces
    if ((y / num) % 3 == 1 && (x / num) % 3 == 1) {
        cout << ' ';
    } else {
        // If num is 1, print star
        if (num / 3 == 0)
            cout << '*';
        else
            // Recursively divide the problem
            printStar(y, x, num / 3);
    }
}

int main() {
    int N;
    cin >> N;

    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            printStar(y, x, N);
        }
        cout << '\n';
    }

    return 0;
}

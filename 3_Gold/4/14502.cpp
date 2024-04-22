/*
연구소

인체에 치명적인 바이러스를 연구하던 연구소에서 바이러스가 유출되었다. 
다행히 바이러스는 아직 퍼지지 않았고, 바이러스의 확산을 막기 위해서 연구소에 벽을 세우려고 한다.
연구소는 크기가 N×M인 직사각형으로 나타낼 수 있으며, 직사각형은 1×1 크기의 정사각형으로 나누어져 있다. 
연구소는 빈 칸, 벽으로 이루어져 있으며, 벽은 칸 하나를 가득 차지한다. 
일부 칸은 바이러스가 존재하며, 이 바이러스는 상하좌우로 인접한 빈 칸으로 모두 퍼져나갈 수 있다. 
새로 세울 수 있는 벽의 개수는 3개이며, 꼭 3개를 세워야 한다.

벽을 3개 세운 뒤, 바이러스가 퍼질 수 없는 곳을 안전 영역이라고 한다. 위의 지도에서 안전 영역의 크기는 27이다.
연구소의 지도가 주어졌을 때 얻을 수 있는 안전 영역 크기의 최댓값을 구하는 프로그램을 작성하시오.

입력
첫째 줄에 지도의 세로 크기 N과 가로 크기 M이 주어진다. (3 ≤ N, M ≤ 8)
둘째 줄부터 N개의 줄에 지도의 모양이 주어진다. 
0은 빈 칸, 1은 벽, 2는 바이러스가 있는 위치이다. 
2의 개수는 2보다 크거나 같고, 10보다 작거나 같은 자연수이다.
빈 칸의 개수는 3개 이상이다.

출력
첫째 줄에 얻을 수 있는 안전 영역의 최대 크기를 출력한다.
*/


#include <iostream>

using namespace std;

int lab[8][8];
int N, M;

struct Coordinate {
    int x, y;
};

class Virus {
    Coordinate virLocation[64];
    int currentLab[8][8];
    int numOfVirus;

    public:
    Virus();
    void FindVirus();   //연구실의 바이러스 위치를 리턴
    void InitCurrLab();    //현재 연구실 상태를 원래 상태로 초기화
    void Spread();
    void SpreadVirus(int curX, int curY); //현재 연구실 상태에서 바이러스를 퍼트림
    void Print();
    
};

Virus::Virus() {
    numOfVirus = 0;
    Virus::InitCurrLab();
    Virus::FindVirus();
}

void Virus::FindVirus()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (currentLab[i][j] == 2)
            {
                virLocation[numOfVirus].y = i;
                virLocation[numOfVirus].x = j;
                numOfVirus++;
            }
        }
    }
}

void Virus::InitCurrLab()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            currentLab[i][j] = lab[i][j];
        }   
    }
}

void Virus::Spread()
{
    for (int i = 0; i < numOfVirus; i++)
    {
        SpreadVirus(virLocation[i].x, virLocation[i].y);
    }
}

void Virus::SpreadVirus(int curX, int curY)
{   
    //현재위치가 아직 바이러스에 감염되지 않았다면
    if (currentLab[curY][curX] == 0)
    {   
        currentLab[curY][curX] = 2; //현재위치를 감염시킴
    }
    

    if (curX > 0 && currentLab[curY][curX - 1] == 0)
    {
        Virus::SpreadVirus(curY ,curX - 1);
    }

    if (curX < M - 1 &&  currentLab[curY][curX + 1] == 0)
    {
        Virus::SpreadVirus(curY, curX + 1);
    }
        

    if (curY > 0 && currentLab[curY - 1][curX] == 0)
    {
        Virus::SpreadVirus(curY - 1, curX);
    }

    if (curY < N - 1 && currentLab[curY + 1][curX] == 0)
    {
        Virus::SpreadVirus(curY + 1, curX);
    }
}

void Virus::Print()
{
    cout << '\n' << '\n';
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cout << currentLab[i][j] << ' ';
        }
        cout << '\n';
    }
}

int CountSafeArr(int arr[8][8], int n, int m); //연구실의 현재 안전구역 넓이 리턴


int main(void)
{
    int currentLab[8][8];
    Virus vir;

    cin >> N >> M;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> lab[i][j];
        }
    }

    vir.InitCurrLab();

    vir.Print();

    vir.Spread();

    vir.Print();

    return 0;
}




//연구실의 현재 안전구역 넓이 리턴
int CountSafeArr(int arr[8][8], int n, int m)
{
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (arr[i][j] == 0)
            {
                count++;
            }
        }
    }
    return count;
}






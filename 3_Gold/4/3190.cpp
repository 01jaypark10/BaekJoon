/*
뱀

'Dummy' 라는 도스게임이 있다. 이 게임에는 뱀이 나와서 기어다니는데, 사과를 먹으면 뱀 길이가 늘어난다.
뱀이 이리저리 기어다니다가 벽 또는 자기자신의 몸과 부딪히면 게임이 끝난다.

게임은 NxN 정사각 보드위에서 진행되고, 몇몇 칸에는 사과가 놓여져 있다.
보드의 상하좌우 끝에 벽이 있다.
게임이 시작할때 뱀은 맨위 맨좌측에 위치하고 뱀의 길이는 1이다.
뱀은 처음에 오른쪽을 향한다.

뱀은 매 초마다 이동을 하는데 다음과 같은 규칙을 따른다.

먼저 뱀은 몸길이를 늘려 머리를 다음칸에 위치시킨다.
만약 벽이나 자기자신의 몸과 부딪히면 게임이 끝난다.
만약 이동한 칸에 사과가 있다면, 그 칸에 있던 사과가 없어지고 꼬리는 움직이지 않는다.
만약 이동한 칸에 사과가 없다면, 몸길이를 줄여서 꼬리가 위치한 칸을 비워준다. 즉, 몸길이는 변하지 않는다.
사과의 위치와 뱀의 이동경로가 주어질 때 이 게임이 몇 초에 끝나는지 계산하라.

입력
첫째 줄에 보드의 크기 N이 주어진다. (2 ≤ N ≤ 100) 다음 줄에 사과의 개수 K가 주어진다. (0 ≤ K ≤ 100)

다음 K개의 줄에는 사과의 위치가 주어지는데, 첫 번째 정수는 행, 두 번째 정수는 열 위치를 의미한다. 사과의 위치는 모두 다르며, 맨 위 맨 좌측 (1행 1열) 에는 사과가 없다.

다음 줄에는 뱀의 방향 변환 횟수 L 이 주어진다. (1 ≤ L ≤ 100)

다음 L개의 줄에는 뱀의 방향 변환 정보가 주어지는데, 정수 X와 문자 C로 이루어져 있으며, 게임 시작 시간으로부터 X초가 끝난 뒤에 왼쪽(C가 'L') 또는 오른쪽(C가 'D')로 90도 방향을 회전시킨다는 뜻이다.
X는 10,000 이하의 양의 정수이며, 방향 전환 정보는 X가 증가하는 순으로 주어진다.

출력
첫째 줄에 게임이 몇 초에 끝나는지 출력한다.
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class coordinate
{
private:
    int x;
    int y;

public:
    coordinate()
    {
        x = 0;
        y = 0;
    }

    coordinate(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    void setX(int x) { this->x = x; }

    void setY(int y) { this->y = y; }

    int getX() { return x; }

    int getY() { return y; }
};

class Board
{
private:
    /*
    board value
    0 : 빈공간, 1 : 뱀이 차지하고 있는 공간, 2 : 사과가 위치하고 있는 공간
    */
    int **board;
    int size;
    queue<coordinate> snake;
    int curSnakeX, curSnakeY; // 현재 뱀의 머리 위치의 x, y좌표
    int snakeTailX, snakeTailY;
    int snakeDirection; // 뱀이 현재 바라보고 있는 방향 0: 동, 1: 남, 2: 서, 3: 북
    int totalTime;

public:
    Board(int N);

    // 현재 보드 상태 출력
    void printBoard();

    void setCurSnakeX(int x) { this->curSnakeX = x; }
    void setCurSnakeY(int y) { this->curSnakeY = y; }
    void setSnakeTailX(int x) { this->snakeTailX = x; }
    void setSnakeTailY(int y) { this->snakeTailY = y; }
    void increaseTotalTime() { totalTime++; } // 소요시간 1초 증가
    // 뱀의 진행 방향 수정 (성공시 1, 실패시 -1을 리턴)
    //  L = 왼쪽으로 90도 회전, R = 오른쪽으로 90도 회전
    int setDirection(char C);

    int getCurSnakeX() { return this->curSnakeX; }
    int getCurSnakeY() { return this->curSnakeY; }
    int getSnakeTailX() { return this->snakeTailX; }
    int getSnakeTailY() { return this->snakeTailY; }
    int getDirection() { return this->snakeDirection; }
    int getTotalTime() { return this->totalTime; }
    int getSnakeDirection() { return this->snakeDirection; }
    int getSize() { return this->size; }

    // 사과의 위치를 입력받아 보드에 세팅
    void setApple(int K);

    // 뱀이 현재 방향으로 이동할 수 있는지 없는지 확인 (이동 가능시 1, 불가능시 0 리턴)
    // 이 함수는 뱀이 '보드의 경계를 나가는지 나가지 않는지 유무만 확인'
    // 뱀이 겹쳐서 아웃되는 상황은 고려되지 않음!
    int isSnakeCanMove();
    // direction 방향으로 1칸 이동
    void goToDirection();
    // 현재 direction 방향으로 X초만큼 이동 (이동 성공시 1, 중간에라도 이동 불가시 -1 리턴)
    int move(int x);
};

int main(void)
{
    int N, K, L; // 보드의 크기, 사과의 개수
    int X;
    char C;
    int totalTime = 0; // 게임이 끝나기까지 걸린 시간

    queue<coordinate> snake;

    cin >> N;
    Board b(N);

    cin >> K;
    b.setApple(K);

    b.printBoard();

    cin >> L;

    for (int i = 0; i < L; i++)
    {
        cin >> X >> C;
        for (int j = 0; j < X; j++)
        {
            if (b.move(X) == -1)
            {
                cout << b.getTotalTime();
                return 0;
            }

            b.setDirection(C);
        }
    }

    cout << b.getTotalTime();
}

Board::Board(int N)
{
    size = N;
    board = new int *[N];
    for (int i = 0; i < N; i++)
        board[i] = new int[N];

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            board[i][j] = 0;
    }

    curSnakeX = 0;
    curSnakeY = 0;
    board[0][0] = 1; // 뱀의 초기위치를 (0,0)으로 설정
    totalTime = 0;
    snakeDirection = 0;
    snakeTailX = 0;
    snakeTailY = 0;

    coordinate *temp;
    temp = new coordinate(0, 0);
    snake.push(*temp);
    delete temp;
}

void Board::setApple(int K)
{
    int appleX, appleY;
    for (int i = 0; i < K; i++)
    {
        cin >> appleY >> appleX;
        board[appleY - 1][appleX - 1] = 2;
    }
}

int Board::setDirection(char C)
{
    if (C == 'L')
    {
        snakeDirection = (snakeDirection + 3) % 4;
        return 1;
    }

    else if (C == 'D')
    {
        snakeDirection = (snakeDirection + 1) % 4;
        return 1;
    }

    return -1;
}

void Board::printBoard()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << '\n';
    }
}

int Board::isSnakeCanMove()
{
    switch (getSnakeDirection())
    {
    case 0:
        return (getCurSnakeX() < getSize() - 1);

    case 1:
        return (getCurSnakeY() < getSize() - 1);

    case 2:
        return (getCurSnakeX() > 0);

    case 3:
        return (getCurSnakeY() > 0);
    default:
        return 0;
    }
}

void Board::goToDirection()
{
    switch (getSnakeDirection())
    {
    case 0:
        setCurSnakeX(getCurSnakeX() + 1);
        break;

    case 1:
        setCurSnakeY(getCurSnakeY() + 1);
        break;

    case 2:
        setCurSnakeX(getCurSnakeX() - 1);
        break;

    case 3:
        setCurSnakeY(getCurSnakeY() - 1);
        break;

    default:
        break;
    }
}

int Board::move(int x)
{
    coordinate *temp;
    coordinate toDelete;
    temp = new coordinate();
    for (int i = 0; i < x; i++)
    {
        increaseTotalTime();

        // 뱀이 다음 칸으로 움직일 수 있다면
        if (isSnakeCanMove())
        {
            goToDirection(); // 이동
            // 뱀이 이동한 곳이 빈 공간이라면
            if (board[getCurSnakeY()][getCurSnakeX()] == 0)
            {
                board[getCurSnakeY()][getCurSnakeX()] = 1; // 보드에 뱀의 영역으로 세팅

                // 뱀의 정보 queue에 푸쉬
                temp->setX(getCurSnakeX());
                temp->setY(getCurSnakeY());
                snake.push(*temp);

                // 뱀의 꼬리 하나 삭제
                toDelete = snake.front();
                snake.pop();
                board[toDelete.getY()][toDelete.getX()] = 0;
            }

            // 뱀이 이동한 곳이 사과라면
            else if (board[getCurSnakeY()][getCurSnakeX()] == 2)
            {
                board[getCurSnakeY()][getCurSnakeX()] = 1; // 보드에 뱀의 영역으로 세팅

                // 뱀의 정보 queue에 푸쉬
                temp->setX(getCurSnakeX());
                temp->setY(getCurSnakeY());
                snake.push(*temp);

                // 사과이므로 꼬리를 삭제하지 않음
            }

            // 뱀이 이동한 곳에 자신의 몸통이 있다면
            else if (board[getCurSnakeY()][getCurSnakeX()] == 1)
            {
                delete temp;
                return -1;
            }
        }

        // 다음 칸으로 이동할 수 없다면
        else
        {
            delete temp;
            return -1;
        }
    }
    delete temp;
    return 1;
}
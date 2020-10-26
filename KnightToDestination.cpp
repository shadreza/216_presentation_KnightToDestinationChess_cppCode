#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

int HowManyIterations = 0;
static int NumberOfRowAndCol = 8;
static int DoubleNumberOfRowAndCol = 64;
int Board[8][8];
int PlayBoardCost[8][8];
int PlayBoardPathX[8][8];
int PlayBoardPathY[8][8];
int DirectionX[8] = {+2, +2, -2, -2, +1, +1, -1, -1};
int DirectionY[8] = {+1, -1, +1, -1, +2, -2, +2, -2};
int HowManyDirecions = 8;
int TotalOccupiedSpace = 0;
int IsKnightSet = 0;
int IsDestinationSet = 0;
int KnightPositionRow = -1;
int KnightPositionCollumn = -1;
int DestinationPositionRow = -1;
int DestinationPositionCollumn = -1;
queue<pair<int, int>> QueuePositionSet;
int ElementsInTheQueue = 0;

void BoardNullify()
{
    for (int i = 0; i < NumberOfRowAndCol; i++)
    {
        for (int j = 0; j < NumberOfRowAndCol; j++)
        {
            Board[i][j] = 0;
        }
    }
}

void ShowBoard()
{
    for (int i = 0; i < NumberOfRowAndCol; i++)
    {
        for (int j = 0; j < NumberOfRowAndCol; j++)
        {

            if (i == KnightPositionRow && j == KnightPositionCollumn)
            {
                cout << " K ";
            }

            else if (i == DestinationPositionRow && j == DestinationPositionCollumn)
            {
                cout << " D ";
            }

            else
            {
                if (Board[i][j] == 1)
                {
                    cout << " X ";
                }
                else
                {
                    cout << " . ";
                }
            }
        }
        cout << endl;
    }
}

void SetObstacles()
{
    cout << "How many obstacles?\t";
    int NumberOfObstacles;
    cin >> NumberOfObstacles;
    for (int i = 0; i < NumberOfObstacles; i++)
    {
        if (TotalOccupiedSpace == NumberOfRowAndCol * NumberOfRowAndCol)
        {
            cout << "Board Is Full\n";
            return;
        }
        cout << "Obstacle_" << i + 1 << " on which Row?\t";
        int Row;
        cin >> Row;
        cout << "Obstacle_" << i + 1 << " on which Collumn?\t";
        int Collumn;
        cin >> Collumn;
        if (Row < 1 || Row > NumberOfRowAndCol || Collumn < 1 || Collumn > NumberOfRowAndCol || Board[Row - 1][Collumn - 1] == 1)
        {
            cout << "Obstacle insertion Unsuccessful. Want To Reattempt for this iteration?(y/n)\n";
            getchar();
            string ans;
            getline(cin, ans);
            if (ans[0] == 'Y' || ans[0] == 'y' || ans[0] == '1')
            {
                i--;
            }
        }
        else
        {
            Board[Row - 1][Collumn - 1] = 1;
            TotalOccupiedSpace++;
            cout << "Obstacle insertion Successful\n";
        }
    }
}

void SetKnightPosition()
{
    if (TotalOccupiedSpace == DoubleNumberOfRowAndCol)
    {
        cout << "Board Is Full\nUnsuccessful to Land Knight\n";
        return;
    }
    else
    {
        cout << "On which Row Does The Knight Land?\t";
        int Row;
        cin >> Row;
        cout << "On which Collumn Does The Knight Land?\t";
        int Collumn;
        cin >> Collumn;
        if (Row < 1 || Row > NumberOfRowAndCol || Collumn < 1 || Collumn > NumberOfRowAndCol)
        {
            cout << "Out Of Board";
            SetKnightPosition();
        }
        else if (Board[Row - 1][Collumn - 1] == 1)
        {
            cout << "This Space is Already Occupied\nUnsuccessful to Land Knight.\n";
        }
        else
        {
            Board[Row - 1][Collumn - 1] = 1;
            KnightPositionRow = Row - 1;
            KnightPositionCollumn = Collumn - 1;
            IsKnightSet++;
            TotalOccupiedSpace++;
            cout << "The Knight Has Successfully Landed\n";
        }
    }
}

void ChangeKnightPosition()
{
    if (TotalOccupiedSpace == NumberOfRowAndCol * NumberOfRowAndCol)
    {
        cout << "Board Is Full\nUnsuccessful to Land Knight\n";
        return;
    }
    else
    {
        cout << "On which Row Does The Knight Land?\t";
        int Row;
        cin >> Row;
        cout << "On which Collumn Does The Knight Land?\t";
        int Collumn;
        cin >> Collumn;
        if (Row < 1 || Row > NumberOfRowAndCol || Collumn < 1 || Collumn > NumberOfRowAndCol)
        {
            cout << "Out Of Board";
            ChangeKnightPosition();
        }
        else if (Board[Row - 1][Collumn - 1] == 1)
        {
            cout << "This Space is Already Occupied\nUnsuccessful to Change Knight's Position.\n";
        }
        else
        {
            Board[KnightPositionRow][KnightPositionCollumn] = 0;
            Board[Row - 1][Collumn - 1] = 1;
            KnightPositionRow = Row - 1;
            KnightPositionCollumn = Collumn - 1;
            IsKnightSet++;
            cout << "The Knight Has Successfully Changed Position\n";
        }
    }
}

void SetDestinationPosition()
{
    cout << "On which Row Is The Destination?\t";
    int Row;
    cin >> Row;
    cout << "On which Collumn Is The Destination?\t";
    int Collumn;
    cin >> Collumn;
    if (Row < 1 || Row > NumberOfRowAndCol || Collumn < 1 || Collumn > NumberOfRowAndCol)
    {
        cout << "Destination is out of Board. Attemp Unsuccessful\n";
    }
    else
    {
        DestinationPositionRow = Row - 1;
        DestinationPositionCollumn = Collumn - 1;
        cout << "Destination Has Landed Successfully\n";
    }
}

void ChangeDestinationPosition()
{
    cout << "On which Row Is The Destination?\t";
    int Row;
    cin >> Row;
    cout << "On which Collumn Is The Destination?\t";
    int Collumn;
    cin >> Collumn;
    if (Row < 1 || Row > NumberOfRowAndCol || Collumn < 1 || Collumn > NumberOfRowAndCol)
    {
        cout << "Destination is out of Board. Attemp Unsuccessful\n";
    }
    else
    {
        if (Row == DestinationPositionRow && Collumn == DestinationPositionCollumn)
        {
            cout << "You have Targetted the same destination. Want to change?(y/n)";
            getchar();
            string ans;
            getline(cin, ans);
            if (ans[0] == 'Y' || ans[0] == 'y' || ans[0] == '1')
            {
                ChangeDestinationPosition();
            }
            else
            {
                return;
            }
        }
        else
        {
            DestinationPositionRow = Row - 1;
            DestinationPositionCollumn = Collumn - 1;
            cout << "Destination Has Landed Successfully\n";
        }
    }
}

void RemoveObstacles()
{
    if (TotalOccupiedSpace == 0 || (TotalOccupiedSpace == 1 && IsKnightSet > 0))
    {
        cout << "There are no obstacles. Obstacle removal unsuccessful.\n";
        return;
    }
    cout << "Obstacle removal from which Row?\t";
    int Row;
    cin >> Row;
    cout << "Obstacle removal from which Collumn?\t";
    int Collumn;
    cin >> Collumn;
    if (Row < 1 || Row > NumberOfRowAndCol || Collumn < 1 || Collumn > NumberOfRowAndCol || Board[Row - 1][Collumn - 1] == 0)
    {
        cout << "Obstacle insertion Unsuccessful. Want To Reattempt for this iteration?(y/n)\n";
        getchar();
        string ans;
        getline(cin, ans);
        if (ans[0] == 'Y' || ans[0] == 'y' || ans[0] == '1')
        {
            RemoveObstacles();
        }
    }
    else
    {
        Board[Row - 1][Collumn - 1] = 0;
        TotalOccupiedSpace--;
        cout << "Obstacle removal Successful\n";
    }
}

void PlayBoardInitialize()
{
    for (int i = 0; i < NumberOfRowAndCol; i++)
    {
        for (int j = 0; j < NumberOfRowAndCol; j++)
        {
            PlayBoardCost[i][j] = -1;
            PlayBoardPathX[i][j] = -1;
            PlayBoardPathY[i][j] = -1;
        }
    }
}

void Show()
{
    for (int i = 0; i < NumberOfRowAndCol; i++)
    {
        for (int j = 0; j < NumberOfRowAndCol; j++)
        {
            cout << "(" << PlayBoardPathX[i][j] << "," << PlayBoardPathY[i][j] << ")"
                 << " ";
        }
        cout << endl;
    }

    cout << endl;

    for (int i = 0; i < NumberOfRowAndCol; i++)
    {
        for (int j = 0; j < NumberOfRowAndCol; j++)
        {
            cout << PlayBoardCost[i][j] << " ";
        }
        cout << endl;
    }
}

bool IsMoveValid(int x, int y)
{
    if (x >= 0 && x < NumberOfRowAndCol && y >= 0 && y < NumberOfRowAndCol)
    {
        if (Board[x][y] == 0)
        {
            return true;
        }
    }
    return false;
}

void EmptyTheQueue()
{
    while (!QueuePositionSet.empty())
    {
        QueuePositionSet.pop();
    }
}

void PlayingWithQueue()
{
    PlayBoardCost[KnightPositionRow][KnightPositionCollumn] = 0;
    PlayBoardPathX[KnightPositionRow][KnightPositionCollumn] = KnightPositionRow;
    PlayBoardPathY[KnightPositionRow][KnightPositionCollumn] = KnightPositionCollumn;
    while (!QueuePositionSet.empty())
    {
        int row = QueuePositionSet.front().first;
        int col = QueuePositionSet.front().second;
        for (int i = 0; i < HowManyDirecions; i++)
        {
            if (IsMoveValid(row + DirectionX[i], col + DirectionY[i]))
            {
                if (PlayBoardCost[row + DirectionX[i]][col + DirectionY[i]] == -1)
                {
                    HowManyIterations++;
                    PlayBoardCost[row + DirectionX[i]][col + DirectionY[i]] = PlayBoardCost[row][col] + 1;
                    PlayBoardPathX[row + DirectionX[i]][col + DirectionY[i]] = row;
                    PlayBoardPathY[row + DirectionX[i]][col + DirectionY[i]] = col;
                    //cout << row + DirectionX[i] << "," << col + DirectionY[i] << "-> " << PlayBoardPathX[row + DirectionX[i]][col + DirectionY[i]] << "," << PlayBoardPathY[row + DirectionX[i]][col + DirectionY[i]] << endl;
                    QueuePositionSet.push(make_pair(row + DirectionX[i], col + DirectionY[i]));
                    ElementsInTheQueue++;
                    if (row + DirectionX[i] == DestinationPositionRow && col + DirectionY[i] == DestinationPositionCollumn)
                    {
                        return;
                    }
                }
            }
        }
        QueuePositionSet.pop();
        ElementsInTheQueue--;
    }
}

void PathFinder()
{
    stack<pair<int, int>> PathVector;
    int row, col;
    row = DestinationPositionRow;
    col = DestinationPositionCollumn;
    PathVector.push(make_pair(row, col));
    for (int i = 0; i < PlayBoardCost[DestinationPositionRow][DestinationPositionCollumn]; i++)
    {
        int TmpRow = row;
        row = PlayBoardPathX[row][col];
        col = PlayBoardPathY[TmpRow][col];
        PathVector.push(make_pair(row, col));
    }
    while (!PathVector.empty())
    {
        cout << "(" << PathVector.top().first + 1 << "," << PathVector.top().second + 1 << ")";
        PathVector.pop();
        if (PathVector.size() != 0)
        {
            cout << "->";
        }
    }
    cout << endl;
}

void Play()
{
    PlayBoardInitialize();
    HowManyIterations = 0;
    if (KnightPositionCollumn == -1 || KnightPositionRow == -1)
    {
        cout << "Please Set The Knight Position\n";
        return;
    }
    else if (DestinationPositionCollumn == -1 || DestinationPositionRow == -1)
    {
        cout << "Please Set The Destination Position\n";
        return;
    }
    else
    {
        QueuePositionSet.push(make_pair(KnightPositionRow, KnightPositionCollumn));
        ElementsInTheQueue++;
        PlayingWithQueue();
        cout << "\nTotal " << HowManyIterations << " Iterations Were Needed" << endl;
        if (PlayBoardCost[DestinationPositionRow][DestinationPositionCollumn] == -1)
        {
            cout << "Knight Can not Go to Destination\n";
        }
        else
        {
            cout << "Total Optimal Steps: " << PlayBoardCost[DestinationPositionRow][DestinationPositionCollumn] << endl;
            EmptyTheQueue();
            PathFinder();
        }
        cout << "Game Done!\n\n";
    }
}

void Options()
{
    cout << "\nYour Options Are:\n";
    cout << "\n1.Set Knight Position";
    cout << "\n2.Set Destination Position";
    cout << "\n3.Set Obstacles";
    cout << "\n4.Remove Obstacles";
    cout << "\n5.Change Knight Position";
    cout << "\n6.Change Destination Position";
    cout << "\n7.Let The Knight Play";
    cout << "\n8.Exit";
    cout << "\n\nEnter Your Choice:\t";
    int inp;
    cin >> inp;
    if (inp == 1)
    {
        SetKnightPosition();
    }
    else if (inp == 2)
    {
        SetDestinationPosition();
    }
    else if (inp == 3)
    {
        SetObstacles();
    }
    else if (inp == 4)
    {
        RemoveObstacles();
    }
    else if (inp == 5)
    {
        ChangeKnightPosition();
    }
    else if (inp == 6)
    {
        ChangeDestinationPosition();
    }
    else if (inp == 7)
    {
        Play();
    }
    else if (inp == 8)
    {
        cout << "\nTerminating The Program\n";
        return;
    }
    else
    {
        cout << "Invalid Input\n";
    }
    cout << endl;
    ShowBoard();
    Options();
}

int main()
{
    BoardNullify();
    Options();
    return 0;
}

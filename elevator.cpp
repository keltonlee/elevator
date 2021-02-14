#include <curses.h>
#include <cmath>
#include <iostream>
#include <time.h>
#include <windows.h>

using namespace std;

//***電梯class***//
class elevator
{
private:
    int ID;
    int NumOfPeople;
    bool UpOrDown; //0=down 1=up
    int NowFloor;
    int NextFloor;
    int PeopleInElevator[10];
    int StayTime;
    int InOutNum; //The number of people who get into or get out the elevator
    int Milage;
    int state;
public:
    elevator()
    {
        NumOfPeople = 0;
        NowFloor = 1;
        for (int i = 0; i < 10; i++)
        {
            PeopleInElevator[i] = 0;
        }
        StayTime = 2;
        InOutNum = 0;
        Milage = 0;
    }
    void setarrPIE(const int i, const int &floor)
    {
        PeopleInElevator[i] = floor;
    }
    int getarrPIE(const int i)
    {
        return PeopleInElevator[i];
    }
    void setUpOrDown(bool updown)
    {
        UpOrDown = updown;
    }
    void setNumOfPeople(int peoplenum)
    {
        NumOfPeople = peoplenum;
    }
    void setNowFloor(int floor)
    {
        NowFloor = floor;
    }
    void setNextFloor(int floor)
    {
        NextFloor = floor;
    }
    int getID()
    {
        return ID;
    }
    int getNumOfPeople()
    {
        return NumOfPeople;
    }
    int getNowFloor()
    {
        return NowFloor;
    }
    int getNextFloor()
    {
        return NextFloor;
    }
    bool getUpOrDown()
    {
        return UpOrDown;
    }
    void setION(const int n)
    {
        InOutNum = n;
    }
    int getION()
    {
        return InOutNum;
    }
    void setStayTime(const int n)
    {
        if (n<2)
            StayTime=2;
        else
            StayTime = n;
    }
    int getStayTime()
    {
        return StayTime;
    }
    void resetStayTime()
    {
        StayTime = 2;
        InOutNum = 0;
    }
    void countMilage()
    {
        Milage += (NumOfPeople + 3);
    }
    void setMilage(int mile)
    {
        Milage = mile;
    }
    int getMilage()
    {
        return Milage;
    }
    void setID(const int n)
    {
        ID=n;
    }
};

//***人class***//

const int randomFloor[11] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
const int StayOrLeave[5] = {0, 0, 0, 0, 1};

class people
{
private:

    int **arr;
    int numberofpeople;

public:

    people();
    void generate();      //生成人
    void deleteID(const int ID);     //刪除編號 "ID" 的人
    void Displacement(const int ID); //讓編號 "ID" 的人移動
    int getNumberofpeople();         //獲得目前總人數
    void setID();
    void setCurrentfloor(const int &ID, const int floor);
    void setDestination(const int &ID, const int floor);
    void setStaytime(const int &ID, const int t);
    void setState(const int &ID, const bool state); //設定下個狀態:0離開1停留˙
    void setPosition(const int &ID, const int p);   //設定目前位置:1樓層2等電梯3電梯內
    void setElevator(const int &ID, const int eleID);
    int getID(const int i);
    int getCurrentfloor(const int ID);
    int getDestination(const int ID);
    int getStaytime(const int ID);
    int getState(const int ID);
    int getPosition(const int ID);
    int getElevator(const int ID);
};

people::people()
{
    arr = new int *[150];
    for (int i = 0; i < 150; i++)
    {
        arr[i] = new int[7](); //儲存"ID"、"當前樓層"、"目標樓層"、"待多久"、"目前位置"、"下個狀態(繼續停留或準備離開)"、"使用哪台電梯"
    }
    numberofpeople = 0;
}
void people::generate()
{
    int f = rand() % 11;
    setID();
    setCurrentfloor(getID(numberofpeople), 1);
    setDestination(getID(numberofpeople), randomFloor[f]);
    setStaytime(getID(numberofpeople), rand() % 61 + 20);
    setPosition(getID(numberofpeople), 2);
    setState(getID(numberofpeople), 1);
    numberofpeople++;
}
void people::deleteID(const int ID)
{
    for (int i = ID - 1; i < 149; i++)
    {
        for (int j = 1; j < 7; j++)
        {
            arr[i][j] = arr[i + 1][j];
        }
    }
    for (int i = 0; i < 7; i++)
    {
        arr[150][i] = 0;
    }
    numberofpeople--;
}
int people::getNumberofpeople()
{
    return numberofpeople;
}
void people::setID()
{
    arr[numberofpeople][0] = numberofpeople + 1;
}
void people::setCurrentfloor(const int &ID, const int floor)
{
    arr[ID - 1][1] = floor;
}
void people::setDestination(const int &ID, const int floor)
{
    arr[ID - 1][2] = floor;
}
void people::setStaytime(const int &ID, const int t)
{
    arr[ID - 1][3] = t;
}
void people::setPosition(const int &ID, const int p)
{
    arr[ID - 1][4] = p;
}
void people::setState(const int &ID, const bool state)
{
    arr[ID - 1][5] = state;
}
void people::setElevator(const int &ID, const int eleID)
{
    arr[ID - 1][6] = eleID;
}
int people::getID(const int i)
{
    return arr[i][0];
}
int people::getCurrentfloor(const int ID)
{
    return arr[ID - 1][1];
}
int people::getDestination(const int ID)
{
    return arr[ID - 1][2];
}
int people::getStaytime(const int ID)
{
    return arr[ID - 1][3];
}
int people::getPosition(const int ID)
{
    return arr[ID - 1][4];
}
int people::getState(const int ID)
{
    return arr[ID - 1][5];
}
int people::getElevator(const int ID)
{
    return arr[ID - 1][6];
}
void people::Displacement(const int ID)
{
    setPosition(ID, 2); //將位置設為2:等電梯
    int n = rand() % 5;
    setState(ID, StayOrLeave[n]); //決定下個狀態 (80%)0:離開 (20%)1:到其他樓層
    if (getState(ID) == 0)
    {
        setDestination(ID, 1);
    }
    else if (getState(ID) == 1)
    {
        int n = rand() % 10;
        int t = rand() % 61 + 20;
        int floor[10];
        for (int i = 2; i < 13; i++)
        {
            int cnt = 0;
            if (i == getCurrentfloor(ID))
                continue;
            else
                floor[cnt] = i;
            cnt++;
        }
        setDestination(ID, floor[n]);
        setStaytime(ID, t);
    }
}

//顯示部分
int floortoline(int floor)
{
    return  25-2*floor;
}
void printback()
{
    mvaddstr(1,1,"CF\n\n BF\n\n AF\n\n 9F\n\n 8F\n\n 7F\n\n 6F\n\n 5F\n\n 4F\n\n 3F\n\n 2F\n\n 1F");
    refresh();
}
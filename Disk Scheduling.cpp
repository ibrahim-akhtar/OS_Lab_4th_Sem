// Disk Allocation
#include <vector>
#include <limits>
#include <iostream>
using namespace std;
void mysort(vector<int> &vec, bool isAscending)
{
    for (int i = 0; i < vec.size(); ++i)
    {
        for (int j = i + 1; j < vec.size(); ++j)
        {
            bool shouldExchange = false;
            if (isAscending && vec[i] > vec[j])
                shouldExchange = true;
            else if (!isAscending && vec[i] < vec[j])
                shouldExchange = true;
            if (shouldExchange)
            {
                int temp = vec[i];
                vec[i] = vec[j];
                vec[j] = temp;
            }
        }
    }
}
int myabs(int val)
{
    int isPos = (int)(val >= 0);
    return (isPos * val + (1 - isPos) * (-val));
}
int FCFS(vector<int> tracks, int pos)
{
    int movement = 0;
    cout << pos << " >> ";
    for (auto &track : tracks)
    {
        movement += myabs(track - pos);
        pos = track;
        cout << track << " >> ";
    }
    cout << " |\n";
    return movement;
}
int SSTF(vector<int> tracks, int pos)
{
    int movement = 0;
    int len = tracks.size();
    cout << pos << " >> ";
    for (int __i = 0; __i < len; ++__i)
    {
        int chosen = -1;
        int minDist = std::numeric_limits<int>::max();
        for (int j = 0; j < tracks.size(); ++j)
        {
            auto &track = tracks[j];
            if (myabs(track - pos) < minDist)
            {
                minDist = myabs(track - pos);
                chosen = j;
            }
        }
        movement += myabs(tracks[chosen] - pos);
        pos = tracks[chosen];
        cout << tracks[chosen] << " >> ";
        tracks.erase(tracks.begin() + chosen);
    }
    cout << " |\n";
    return movement;
}
int SCAN(vector<int> tracks, int pos, int maxl, int minl, bool isRight)
{
    int movement = 0;
    mysort(tracks, true);
    cout << pos << " >> ";
    int start = -1;
    for (int i = 0; i < tracks.size(); ++i)
    {
        if (tracks[i] > pos)
        {
            start = i;
            break;
        }
    }
    if (isRight)
    {
        if (start == 0)
        {
            movement += myabs(tracks.back() - pos);
        }
        else
        {
            movement += maxl - pos;
            movement += maxl - tracks[0];
        }
        for (int i = start; i < tracks.size(); ++i)
        {
            cout << tracks[i] << " >> ";
        }
        cout << maxl << " >> ";
        for (int i = start - 1; i >= 0; i--)
        {
            cout << tracks[i] << " >> ";
        }
        cout << " |\n";
        return movement;
    }
    else
    {
        if (start == tracks.size() - 1)
        {
            movement += myabs(pos - tracks[0]);
        }
        else
        {
            movement += pos - minl;
            movement += tracks.back() - minl;
        }
        return movement;
    }
}
int CSCAN(vector<int> tracks, int pos, int maxl, int minl, bool isRight)
{
    int movement = 0;
    mysort(tracks, true);
    cout << pos << " >> ";
    int start = -1;
    for (int i = 0; i < tracks.size(); ++i)
    {
        if (tracks[i] > pos)
        {
            start = i;
            break;
        }
    }
    if (isRight)
    {
        if (start == 0)
        {
            movement += myabs(tracks.back() - pos);
        }
        else
        {
            movement += maxl - pos;
            movement += maxl - minl;
            movement += tracks[start - 1] - minl;
        }
        for (int i = start; i < tracks.size(); ++i)
        {
            cout << tracks[i] << " >> ";
        }
        cout << maxl << " >> " << minl << " >> ";
        for (int i = 0; i < start; i++)
        {
            cout << tracks[i] << " >> ";
        }
        cout << " |\n";
        return movement;
    }
    else
    {
        if (start == tracks.size() - 1)
        {
            movement += myabs(pos - tracks[0]);
        }
        else
        {
            movement += pos - minl;
            movement += maxl - minl;
            movement += maxl - tracks[start];
        }
        return movement;
    }
}
int LOOK(vector<int> tracks, int pos, int maxl, int minl, bool isRight)
{
    int movement = 0;
    mysort(tracks, true);
    int start = -1;
    for (int i = 0; i < tracks.size(); ++i)
    {
        if (tracks[i] > pos)
        {
            start = i;
            break;
        }
    }
    cout << pos << " >> ";
    if (isRight)
    {
        if (start == 0)
        {
            movement += myabs(tracks.back() - pos);
        }
        else
        {
            movement += tracks.back() - pos;
            movement += tracks.back() - tracks[0];
        }
        for (int i = start; i < tracks.size(); ++i)
        {
            cout << tracks[i] << " >> ";
        }
        for (int i = start - 1; i >= 0; i--)
        {
            cout << tracks[i] << " >> ";
        }
        cout << " |\n";
        return movement;
    }
    else
    {
        if (start == tracks.size() - 1)
        {
            movement += myabs(pos - tracks[0]);
        }
        else
        {
            movement += pos - tracks[0];
            movement += tracks.back() - tracks[0];
        }
        return movement;
    }
}
int CLOOK(vector<int> tracks, int pos, int maxl, int minl, bool isRight)
{
    int movement = 0;
    mysort(tracks, true);
    int start = -1;
    for (int i = 0; i < tracks.size(); ++i)
    {
        if (tracks[i] > pos)
        {
            start = i;
            break;
        }
    }
    cout << pos << " >> ";
    if (isRight)
    {
        if (start == 0)
        {
            movement += myabs(tracks.back() - pos);
        }
        else
        {
            movement += tracks.back() - pos;
            movement += tracks.back() - tracks[0];
            movement += tracks[start - 1] - tracks[0];
        }
        for (int i = start; i < tracks.size(); ++i)
        {
            cout << tracks[i] << " >> ";
        }
        for (int i = 0; i < start; i++)
        {
            cout << tracks[i] << " >> ";
        }
        cout << " |\n";
        return movement;
    }
    else
    {
        if (start == tracks.size() - 1)
        {
            movement += myabs(pos - tracks[0]);
        }
        else
        {
            movement += pos - tracks[0];
            movement += tracks.back() - tracks[0];
            movement += tracks.back() - tracks[start];
        }
        return movement;
    }
}
int main()
{
    std::cout << "\nProgram By Md Ibrahim Akhtar 21BCS007\n";
    int initial;
    cout << "Enter initial position: ";
    cin >> initial;
    int inputLength;
    cout << "Enter length of array: ";
    cin >> inputLength;
    vector<int> inputs(inputLength);
    cout << "Enter element of array: ";
    for (int &input : inputs)
        cin >> input;
    cout << "Input array is: \n\t";
    for (int input : inputs)
        cout << input << "\t";
    cout << "\n";
    int choice;
    while (1)
    {
        cout << "\nEnter:\n\t";
        cout << "1 to perform FCFS Scheduling:\n\t";
        cout << "2 to perform SSTF Scheduling:\n\t";
        cout << "3 to perform SCAN Scheduling:\n\t";
        cout << "4 to perform CSCAN Scheduling:\n\t";
        cout << "5 to perform LOOK Scheduling:\n\t";
        cout << "6 to perform CLOOK Scheduling:\n\t";
        cout << "7 to exit:\n";
        cin >> choice;
        int totalMovements = -1;
        switch (choice)
        {
        case 1:
            totalMovements = FCFS(inputs, initial);
            break;
        case 2:
            totalMovements = SSTF(inputs, initial);
            break;
        case 3:
            totalMovements = SCAN(inputs, initial, 199, 0, true);
            break;
        case 4:
            totalMovements = CSCAN(inputs, initial, 199, 0, true);
            break;
        case 5:
            totalMovements = LOOK(inputs, initial, 199, 0, true);
            break;
        case 6:
            totalMovements = CLOOK(inputs, initial, 199, 0, true);
            break;
        case 7:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Enter valid choice!\n";
            break;
        }
        if (totalMovements >= 0)
        {
            cout << "\n\tTotal Movements = " << totalMovements;
        }
    }
    return 0;
}

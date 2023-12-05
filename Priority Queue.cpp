// Priority Queue
#include <iostream>
using namespace std;
struct Process
{
    int pid;
    int priority;
    int burst_time;
    int completion;
};
struct Pnode
{
    Process process;
    Pnode *next;
};
Process processIn()
{
    Process process;
    int val;
    std::cout << "\nEnter process id: ";
    std::cin >> val;
    process.pid = val;
    std::cout << "Enter priority: ";
    std::cin >> val;
    process.priority = val;
    std::cout << "Enter burst time: ";
    std::cin >> val;
    process.burst_time = val;
    return process;
}
int main()
{
    std::cout << "\nProgram by Md Ibrahim Akhtar 21BCS007\n";
    int n;
    std::cout << "\nEnter number of processes: ";
    std::cin >> n;
    Pnode *processes = nullptr;
    Pnode *curr = nullptr;
    for (int i = 0; i < n; ++i)
    {
        if (curr == nullptr)
        {
            processes = new Pnode;
            processes->process = processIn();
            processes->next = nullptr;
            curr = processes;
        }
        else
        {
            curr->next = new Pnode;
            curr = curr->next;
            curr->process = processIn();
            curr->next = nullptr;
        }
    }
    Pnode *start = processes;
    Pnode *prevstart = nullptr;
    while (start->next != nullptr)
    {
        curr = start;
        Pnode *prev = nullptr;
        Pnode *minp = curr;
        Pnode *minprev = nullptr;
        while (curr != nullptr)
        {
            if (curr->process.priority < minp->process.priority)
            {
                minp = curr;
                minprev = prev;
            }
            prev = curr;
            curr = curr->next;
        }
        if (prevstart == nullptr)
        {
            processes = minp;
        }
        else
        {
            prevstart->next = minp;
        }
        if (minprev != nullptr)
        {
            minprev->next = minp->next;
            minp->next = start;
            prevstart = minp;
        }
        else
        {
            start = start->next;
            prevstart = start;
        }
    }
    curr = processes;
    std::cout << std::endl
              << " ";
    while (curr != nullptr)
    {
        std::cout << "P" << curr->process.pid << "\t";
        curr = curr->next;
    }
    std::cout << std::endl;
    int time = 0;
    while (processes != nullptr)
    {
        std::cout << time << "\t";
        time += processes->process.burst_time;
        auto temp = processes->next;
        delete (processes);
        processes = temp;
    }
    cout << "\t" << time << endl;
}
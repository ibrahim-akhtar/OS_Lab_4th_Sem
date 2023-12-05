// SJF Scheduling
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
struct Job
{
    int id;
    int arrival;
    int burst;
    int completion;
};
struct JobNode
{
    Job job;
    JobNode *next;
};
void insertJob(JobNode **jobs, Job job)
{
    if (*jobs == nullptr)
    {
        *jobs = new JobNode();
        (*jobs)->job = job;
        (*jobs)->next = nullptr;
        return;
    }
    JobNode *prev = nullptr;
    JobNode *curr = *jobs;
    while (curr != nullptr && curr->job.burst < job.burst)
    {
        prev = curr;
        curr = curr->next;
    }
    if (prev == nullptr)
    {
        auto temp = new JobNode();
        temp->job = job;
        temp->next = *jobs;
        *jobs = temp;
    }
    else
    {
        prev->next = new JobNode();
        prev->next->job = job;
        prev->next->next = curr;
    }
}
void removeJob(JobNode **jobs, Job job)
{
    JobNode *prev = nullptr;
    JobNode *curr = *jobs;
    while (curr != nullptr && curr->job.id != job.id)
    {
        prev = curr;
        curr = curr->next;
    }
    if (prev == nullptr)
    {
        auto temp = (*jobs);
        *jobs = temp->next;
        delete (temp);
    }
    else
    {
        if (curr == nullptr)
        {
            std::cout << "No job with job id: " << job.id << " found!" << std::endl;
            return;
        }
        prev->next = curr->next;
        delete (curr);
    }
}
Job chooseJob(JobNode *jobs, int time)
{
    while (jobs != nullptr)
    {
        if (jobs->job.arrival <= time)
        {
            return jobs->job;
        }
        jobs = jobs->next;
    }
    Job notFound;
    notFound.id = -1;
    return notFound;
}
void printJobs(JobNode *jobs)
{
    while (jobs != nullptr)
    {
        std::cout << "P" << jobs->job.id << std::endl;
        jobs = jobs->next;
    }
}
Job inputJob()
{
    Job job;
    std::cout << "Enter job id: ";
    std::cin >> job.id;
    std::cout << "Enter burst time: ";
    std::cin >> job.burst;
    std::cout << "Enter arrival time: ";
    std::cin >> job.arrival;
    return job;
}
static bool comp(Job &one, Job &two)
{
    return one.id < two.id;
}
int main()
{
    std::cout << "\nProgram By Md Ibrahim Akhtar 21BCS007\n";
    JobNode *jobs = nullptr;
    int n;
    std::cout << "Enter number of jobs: ";
    std::cin >> n;
    for (int i = 0; i < n; ++i)
    {
        insertJob(&jobs, inputJob());
    }
    int time = 0;
    std::string timeStr = "";
    std::string process = "";
    std::vector<Job> completed;
    while (jobs != nullptr)
    {
        Job job = chooseJob(jobs, time);
        if (job.id != -1)
        {
            timeStr += std::to_string(time) + " ";
            process += " P" + std::to_string(job.id) + " ";
            time += job.burst;
            removeJob(&jobs, job);
            job.completion = time;
            completed.push_back(job);
        }
        else
        {
            if (time == 0)
                timeStr += "0";
            time += 1;
        }
    }
    timeStr += std::to_string(time);
    std::cout << process << std::endl
              << timeStr << std::endl
              << std::endl;
    std::sort(completed.begin(), completed.end(), comp);
    std::cout << "Process\tBurst\tArrival\tWaiting\tCompletion\n";
    for (auto proc : completed)
    {
        std::cout << proc.id << "\t" << proc.burst << "\t" << proc.arrival << "\t"
                  << proc.completion - proc.arrival - proc.burst << "\t" << proc.completion << std::endl;
    }
    return 0;
}

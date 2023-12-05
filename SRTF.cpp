// shortest remaining time first
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
struct Job
{
    int id;
    int arrival;
    int burst;
    int completion;
    int response = -1;
    int exec = 0;
};
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
void printJobs(Job *jobs, int n)
{
    for (int i = 0; i < n; ++i)
        std::cout << "P" << jobs[i].id << "\t";
}
static bool comp(Job &one, Job &two)
{
    if (one.burst - one.exec == two.burst - two.exec)
        return one.id > two.id;
    else
        return one.burst - one.exec > two.burst - two.exec;
}
void sort(Job *jobs, int n)
{
    for (int i = 0; i < n; ++i)
        for (int j = i; j < n; ++j)
            if (comp(jobs[i], jobs[j]))
            {
                auto temp = jobs[i];
                jobs[i] = jobs[j];
                jobs[j] = temp;
            }
}
Job *chooseJob(Job *jobs, int n, int time)
{
    for (int i = 0; i < n; ++i)
    {
        if (jobs[i].arrival <= time)
        {
            return jobs + i;
        }
    }
    return nullptr;
}
void removeJob(std::vector<Job> &jobs, Job *job_ptr)
{
    int index = job_ptr - &jobs[0];
    jobs.erase(std::next(jobs.begin(), index));
}
int main()
{
    std::cout << "\nProgram By Md Ibrahim Akhtar 21BCS007\n";
    int n;
    std::cout << "Enter number of jobs: ";
    std::cin >> n;
    std::vector<Job> jobs(n);
    for (int i = 0; i < n; ++i)
        jobs[i] = inputJob();
    sort(jobs.data(), jobs.size());
    int time = 0;
    std::string timeStr = "";
    std::string process = "";
    std::vector<Job> completed;
    int lastid = -1;
    while (jobs.size() != 0)
    {
        Job *job_ptr = chooseJob(jobs.data(), n, time);
        if (job_ptr != nullptr)
        {
            if (job_ptr->response == -1)
                job_ptr->response = time;
            if (job_ptr->id != lastid)
            {
                timeStr += std::to_string(time) + " ";
                process += " P" + std::to_string(job_ptr->id) + " ";
                lastid = job_ptr->id;
            }
            time += 1;
            job_ptr->exec += 1;
            if (job_ptr->burst <= job_ptr->exec)
            {
                n -= 1;
                job_ptr->completion = time;
                completed.push_back(*job_ptr);
                removeJob(jobs, job_ptr);
            }
            sort(jobs.data(), n);
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
    std::sort(completed.begin(), completed.end(), [](Job &job1, Job &job2)
              { return job1.id < job2.id; });
    std::cout << "Process\tBurst\tArrival\tWaiting\tRes\tTAT\tCompletion\n";
    for (auto proc : completed)
    {
        std::cout << proc.id << "\t" << proc.burst << "\t" << proc.arrival << "\t"
                  << proc.completion - proc.arrival - proc.burst << "\t"
                  << proc.response << "\t" << proc.completion - proc.arrival
                  << "\t" << proc.completion << std::endl;
    }
    return 0;
}
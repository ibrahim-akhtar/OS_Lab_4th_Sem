//Memory Allocation
#include <iostream>
#include <vector>
#include <limits>
void printStats(const std::vector<int> &blocks, const std::vector<int> &processes, const std::vector<int> &allocations, const std::vector<bool> &taken)
{
    int internalFrag = 0;
    for (int i = 0; i < allocations.size(); ++i)
    {
        if (allocations[i] != -1)
        {
            std::cout << "Process " << i << " of size " << processes[i] << " is allocated to block " << allocations[i] << " of size " << blocks[allocations[i]] << std::endl;
            internalFrag += blocks[allocations[i]] - processes[i];
        }
        else
            std::cout << "Process " << i << " of size " << processes[i] << " was not allocated" << std::endl;
    }
    std::cout << "Internal Fragmentation = " << internalFrag << std::endl;
    int externalFrag = 0;
    for (int j = 0; j < blocks.size(); ++j)
    {
        externalFrag += taken[j] ? 0 : blocks[j];
    }
    std::cout << "External Fragmentation = " << externalFrag;
}
void bestFit(const std::vector<int> &blocks, const std::vector<int> &
                                                 processes)
{
    // return index of block allocated for each process, if not allocated index is -1
    std::vector<int> allocations;
    std::vector<bool> taken(blocks.size(), false);
    for (int i = 0; i < processes.size(); ++i)
    {
        int minSizeDiff = std::numeric_limits<int>::max();
        int minBlock = -1;
        for (int j = 0; j < blocks.size(); ++j)
        {
            int diff = blocks[j] - processes[i];
            if (diff >= 0 && taken[j] == false)
            {
                if (diff < minSizeDiff)
                {
                    minBlock = j;
                    minSizeDiff = diff;
                }
            }
        }
        if (minBlock != -1)
            taken[minBlock] = true;
        allocations.push_back(minBlock);
    }
    printStats(blocks, processes, allocations, taken);
}
void worstFit(const std::vector<int> &blocks, const std::vector<int> &
                                                  processes)
{
    // return index of block allocated for each process, if not allocated index is -1
    std::vector<int> allocations;
    std::vector<bool> taken(blocks.size(), false);
    for (int i = 0; i < processes.size(); ++i)
    {
        int maxSizeDiff = std::numeric_limits<int>::min();
        int maxBlock = -1;
        for (int j = 0; j < blocks.size(); ++j)
        {
            int diff = blocks[j] - processes[i];
            if (diff >= 0 && taken[j] == false)
            {
                if (diff > maxSizeDiff)
                {
                    maxBlock = j;
                    maxSizeDiff = diff;
                }
            }
        }
        if (maxBlock != -1)
            taken[maxBlock] = true;
        allocations.push_back(maxBlock);
    }
    printStats(blocks, processes, allocations, taken);
}
void firstFit(const std::vector<int> &blocks, const std::vector<int> &
                                                  processes)
{
    // return index of block allocated for each process, if not allocated index is -1
    std::vector<int> allocations;
    std::vector<bool> taken(blocks.size(), false);
    for (int i = 0; i < processes.size(); ++i)
    {
        int blockIndex = -1;
        for (int j = 0; j < blocks.size(); ++j)
        {
            int diff = blocks[j] - processes[i];
            if (diff >= 0 && taken[j] == false)
            {
                blockIndex = j;
                break;
            }
        }
        if (blockIndex != -1)
            taken[blockIndex] = true;
        allocations.push_back(blockIndex);
    }
    printStats(blocks, processes, allocations, taken);
}
void nextFit(const std::vector<int> &blocks, const std::vector<int> &
                                                 processes)
{
    // return index of block allocated for each process, if not allocated index is -1
    std::vector<int> allocations;
    std::vector<bool> taken(blocks.size(), false);
    int blockStart = 0;
    for (int i = 0; i < processes.size(); ++i)
    {
        int blockIndex = -1;
        for (int j = blockStart; j < blocks.size(); ++j)
        {
            int diff = blocks[j] - processes[i];
            if (diff >= 0 && taken[j] == false)
            {
                blockIndex = j;
                break;
            }
        }
        if (blockIndex != -1)
        {
            taken[blockIndex] = true;
            blockStart = blockIndex;
        }
        allocations.push_back(blockIndex);
    }
    printStats(blocks, processes, allocations, taken);
}
int main()
{
    std::cout << "\nProgram By Md Ibrahim Akhtar 21BCS007\n";
    int num_blocks, num_process;
    std::cout << "Enter the number of blocks: ";
    std::cin >> num_blocks;
    std::cout << "Enter the number of processes: ";
    std::cin >> num_process;
    std::vector<int> blocks(num_blocks);
    std::vector<int> process(num_process);
    int i = 0;
    for (auto &block : blocks)
    {
        std::cout << "Enter size of block " << i << " in kilobytes: ";
        std::cin >> block;
        i++;
    }
    i = 0;
    for (auto &pro : process)
    {
        std::cout << "Enter size of process " << i << " in kilobytes: ";
        std::cin >> pro;
        i++;
    }
    std::cout << "BLOCKS: ";
    for (auto block : blocks)
        std::cout << block << " ";
    std::cout << std::endl;
    std::cout << "PROCESSES: ";
    for (auto pro : process)
        std::cout << pro << " ";
    std::cout << std::endl;
    while (1)
    {
        std::cout << "Enter:\n\t1 for best fit\n\t2 for worst fit\n\t3 for first fit\n\t4 for next fit\n\t5 to exit\n";
        int opt = 0;
        std::cin >> opt;
        switch (opt)
        {
        case 1:
            std::cout << "BEST FIT: \n";
            bestFit(blocks, process);
            std::cout << std::endl;
            break;
        case 2:
            std::cout << "WORST FIT: \n";
            worstFit(blocks, process);
            std::cout << std::endl;
            break;
        case 3:
            std::cout << "FIRST FIT: \n";
            firstFit(blocks, process);
            std::cout << std::endl;
            break;
        case 4:
            std::cout << "NEXT FIT: \n";
            nextFit(blocks, process);
            std::cout << std::endl;
            break;
        case 5:
            std::cout << "\nexiting...\n";
            return 0;
        default:
            std::cout << "Enter valid option!\n";
            break;
        }
    }
    return 0;
}

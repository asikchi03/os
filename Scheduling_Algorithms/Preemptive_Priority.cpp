#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Process {
public:
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;

    Process(int _id, int _arrival_time, int _burst_time) :
        id(_id), arrival_time(_arrival_time), burst_time(_burst_time), remaining_time(_burst_time) {}

    // Comparison function for sorting by remaining time
    static bool compareByRemainingTime(const Process& p1, const Process& p2) {
        return p1.remaining_time > p2.remaining_time; // Sort by remaining time in ascending order
    }
};

void preemptiveSRTF(vector<Process>& processes) {
    int n = processes.size();
    priority_queue<Process, vector<Process>, decltype(&Process::compareByRemainingTime)> ready_queue(&Process::compareByRemainingTime);
    int current_time = 0;

    cout << "Order of execution: ";
    while (!ready_queue.empty() || !processes.empty()) {
        while (!processes.empty() && processes.front().arrival_time <= current_time) {
            ready_queue.push(processes.front());
            processes.erase(processes.begin());
        }
        if (!ready_queue.empty()) {
            Process current_process = ready_queue.top();
            ready_queue.pop();

            cout << current_process.id << " ";
            current_time += 1; // Assuming time quantum is 1 unit
            current_process.remaining_time -= 1;

            if (current_process.remaining_time > 0) {
                ready_queue.push(current_process);
            }
        } else {
            current_time += 1;
        }
    }

    cout << endl;
}

int main() {
    vector<Process> processes;
    processes.push_back(Process(1, 0, 6));
    processes.push_back(Process(2, 1, 8));
    processes.push_back(Process(3, 2, 7));
    processes.push_back(Process(4, 3, 3));

    preemptiveSRTF(processes);

    return 0;
}

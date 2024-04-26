#include <bits/stdc++.h>
using namespace std;

class Process {
public:
    int id, AT, BT, vis;
};

bool comparator(Process& p1, Process& p2) {
    return p1.AT < p2.AT;
}

void arrivedProcesses(vector<Process>& processes, int currTime, queue<int>& q) {
    for (int i = 0; i < processes.size(); i++) {
        int idx = processes[i].id;
        if (currTime >= processes[i].AT && processes[idx].vis == 0) {
            q.push(idx);
            processes[idx].vis = 1;
        }
    }
}

int main() {
    int n;
    std::cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        processes[i].id = i;
        std::cout << "Enter the arrival time and burst time for Process " << i + 1 << ": ";
        cin >> processes[i].AT >> processes[i].BT;
    }
    vector<Process> proc(processes.begin(), processes.end());

    int quantum1 = 8, quantum2 = 12;
    sort(processes.begin(), processes.end(), comparator);

    int completedTask = 0, time = 0;
    queue<int> q1, q2, q3;
    vector<int> completionTime(processes.size());

    arrivedProcesses(processes, time, q1);
    while (completedTask != processes.size()) {
        if(q1.empty()){
            time++;
            arrivedProcesses(processes, time, q1);
        }else if(!q1.empty()) {
            while (!q1.empty()) {
                int idx = q1.front();
                q1.pop();
                if (proc[idx].BT <= quantum1) {
                    time += proc[idx].BT;
                    completionTime[idx] = time;
                    completedTask++;
                } else {
                    time += quantum1;
                    proc[idx].BT -= quantum1;
                    q2.push(idx);
                }
                arrivedProcesses(processes, time, q1);
            }
        }
        if (q1.empty() && !q2.empty()) {
            while (!q2.empty()) {
                int idx = q2.front();
                q2.pop();
                if (proc[idx].BT <= quantum2) {
                    time += proc[idx].BT;
                    completionTime[idx] = time;
                    completedTask++;
                } else {
                    time += quantum2;
                    proc[idx].BT -= quantum2;
                    q3.push(idx);
                }
                arrivedProcesses(processes, time, q1);
                if(!q1.empty()){
                    break;
                }
            }
        }
        if (q1.empty() && q2.empty() && !q3.empty()) {
            while (!q3.empty()) {
                int idx = q3.front();
                q3.pop();
                time += proc[idx].BT;
                completionTime[idx] = time;
                completedTask++;
                arrivedProcesses(processes, time, q1);
                if(!q1.empty()){
                    break;
                }
            }
        }
    }
    cout << "Completion Time of each process is: " << endl;
    for (int i = 0; i < completionTime.size(); i++) {
        cout << completionTime[i] << " ";
    }
    cout << endl;
    return 0;
}

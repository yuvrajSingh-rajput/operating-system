#include <iostream>
#include <vector>
#include <queue>
#include<algorithm>
using namespace std;

class Process {
public:
    int proc, AT, BT;
};

bool comparator(Process &p1, Process &p2){
    return p1.AT > p2.AT;
}

void arrivedProcess(const vector<Process>& processes, queue<int>& q, vector<bool>& vis, int currTime) {
    for (int i = 0; i < processes.size(); i++) {
        if (currTime >= processes[i].AT && !vis[i]) {
            q.push(i);
            vis[i] = true;
        }
    }
}

void RoundRobin(vector<Process>& processes, int quantum, int choice) {
    int time = 0, completedTask = 0;
    queue<int> q;
    vector<int> completionTime(processes.size());
    vector<bool> vis(processes.size(), false);

    while (completedTask < processes.size()) {
        arrivedProcess(processes, q, vis, time);
        if(q.empty()){
            time++;
        }else{
            int index = q.front(), k = quantum;
            q.pop();
            bool flag = false;
            while(k > 0){
                processes[index].BT -= 1;
                k--;
                time++;
                if(processes[index].BT == 0){
                    completedTask ++;
                    flag = true;
                    completionTime[index] = time;
                    break;
                }
                arrivedProcess(processes, q, vis, time);
            }
            if(!flag){
                q.push(index);
            }
        }
    }
    vector<int> turnAroundTime;
    for(int i = 0; i < processes.size(); i++){
        turnAroundTime.push_back(completionTime[i] - processes[i].AT);
    }
    if(choice == 1){
        reverse(turnAroundTime.begin(), turnAroundTime.end());
    }
    cout << "Turnaround time for each process: ";
    for(auto &it : turnAroundTime){
        cout << it << " ";
    }
    cout << endl;
}

int main() {
    int n; 
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        processes[i].proc = i + 1;
        cout << "Enter the arrival time and burst time for Process " << i + 1 << ": ";
        cin >> processes[i].AT >> processes[i].BT;
    }

    int quantum;
    cout << "Enter the time quantum for processes: ";
    cin >> quantum;

    int choice;
    cout << "Enter 0 for same arrival time and 1 for different arrival time: ";
    cin >> choice;

    sort(processes.begin(), processes.end(), comparator);
    RoundRobin(processes, quantum, choice);

    return 0;
}

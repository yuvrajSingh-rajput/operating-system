#include<bits/stdc++.h>
using namespace std;

pair<bool, int> isSafe(vector<vector<int>>& needMatrix, vector<int>& available, vector<bool>& vis){
    for(int i = 0; i < needMatrix.size(); i++){
        bool flag = true;
        if(vis[i])  continue;
        for(int j = 0; j < available.size(); j++){
            if(available[j] < needMatrix[i][j]){
                flag = false;
                break;
            }
        }
        if(flag) return{true, i};
    }
    return {false, -1};
}

void displaySafeSequence(vector<int>& ans){
    cout << "The safe sequence is given by: ";
    for(int i = 0; i < ans.size(); i++){
        if(i == ans.size() - 1){
            cout << "P"<< ans[i] << endl;
        }else{
            cout << "P"<< ans[i] << " -> ";
        }
    }
}

int main(){
    int n;
    cout << "Enter the number of process: ";
    cin >> n;
    int instance;
    cout << "Enter the number of instances: ";
    cin >> instance;
    vector<vector<int>> allocation(n, vector<int>(instance));
    cout << "Enter the allocation for each process: ";
    for(int i = 0; i < n; i++){
        cout << "P"<< i + 1 << ": ";
        for(int j = 0; j < instance; j++){
            cin >> allocation[i][j];
        }
    }
    vector<vector<int>> max(n, vector<int>(instance));
    for(int i = 0; i < n; i++){
        cout << "P"<< i + 1 << ": ";
        for(int j = 0; j < instance; j++){
            cin >> max[i][j];
        }
    }
    vector<vector<int>> needMatrix(n, vector<int>(instance));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < instance; j++){
            needMatrix[i][j] = max[i][j] - allocation[i][j];
        }
    }
    vector<int> available(instance), ans;
    cout << "Enter the available resource: ";
    for(int i = 0; i < instance; i++){
        cin >> available[i];
    }
    vector<bool> vis(instance, false);
    int completed = 0;
    while(true){
        pair<bool, int> it = isSafe(needMatrix, available, vis);
        if(it.first){
            completed++;
            ans.push_back(it.second);
            vis[it.second] = true;
            for(int i = 0; i < instance; i++){
                available[i] += allocation[it.second][i];
            }
        }else{
            cout << "|DEADLOCK OCCURED|\n";
            return 1;
        }
        if(completed == n){
            break;
        }
    }
    displaySafeSequence(ans);
    return 0;
}

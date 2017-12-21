#include <iostream>
#include <sstream>
#include <cstdlib>
using namespace std;

bool p[10];
int initiatorID = -1;
int coordinatorID = -1;
int number;

void buildRing(int init_id = -1){
    int alive_processes[number], alive_count=0;

    for(int i =0; i<number; i++)
    {
         if(p[i] == true){
            alive_processes[alive_count] = i;
            alive_count++;
        }
    }

    if(alive_count == 0) {
        cout << "No Processes Alive";
        coordinatorID = -1;
        initiatorID = -1;
    }
    else {
        int initiator_index;
        if(init_id == -1) {
            initiator_index = rand()%alive_count;
            initiatorID = alive_processes[initiator_index];
        } else {
            initiatorID = init_id;
            for(int i = 0;i<alive_count;i++) 
                if(alive_processes[i] == init_id){
                    initiator_index = i;
                    break;
                }
        }
        cout << "Initiator ID: " << initiatorID << endl;

        int curr = initiator_index;
        do {
            int next = (curr + 1)%alive_count;
            cout<<"\nmsg from "<<alive_processes[curr]<<" -> "<<alive_processes[next];
            curr = next;
        } while(alive_processes[curr] != initiatorID);

        coordinatorID = alive_processes[alive_count-1];
        cout << "Coordinator ID: " << coordinatorID << endl;
    }

}

void status() {
    cout << "\nNumber Of Processes: " << number << endl;
    for (int i = 0; i < number; i++) {
        cout << i << "->";
        if (p[i] == true)
            cout << "Alive";
        else
            cout << "Dead";
        if (i == initiatorID)
            cout << "  -> INITIATOR";
        if (i == coordinatorID)
            cout << "  -> COORDINATOR";
        cout << endl;
    }
}

void crashProcess() {
    int ID;
    cout << "Enter ID of the process to crash\n";
    cin >> ID;
    if( p[ID] == true ){
        p[ID] = false;
        if (ID == coordinatorID)
            buildRing();
        status();
    }
    else
        cout << "\nProcess Already Dead\n";
}

void recoverProcess() {
    int ID;
    cout << "Enter ID of the process to recover\n";
    cin >> ID;
    if( p[ID] == false ){
        p[ID] = true;
        buildRing(ID);
        status();
    }
    else
        cout << "\nProcess Already Active\n";
}

int main() 
{

    cout << "Enter the number of processes\n";
    cin >> number;
    // p = new bool[number];

    for (int j = 0;j < number; j++) {
        p[j] = true;
    }
    
    buildRing();
    status();

    int choice;
    while (true) {
        cout << "\nEnter Choice\n";
        cout << "1. Crash Process\n2. Recover Process\n3. Exit\n";
        cin >> choice;
        switch (choice) {
            case 1:
                crashProcess();
                break;
            case 2:
                recoverProcess();
                break;
            case 3:
                return 0;
            default:
                cout << "Wrong Choice";
        }
    }

    return 0;
}
#include <iostream>
using namespace std;

void fifo(int sequence[], int n, int nf) {
    int p[nf], index = 0, pgfaultcnt = 0;
    for (int i = 0; i < nf; i++) p[i] = -1; // Initialize frames

    cout << "\nFIFO Page Replacement:\n";
    for (int i = 0; i < n; i++) {
        bool hit = false;
        for (int j = 0; j < nf; j++) {
            if (p[j] == sequence[i]) {
                hit = true;
                break;
            }
        }
        if (!hit) {
            p[index] = sequence[i];
            index = (index + 1) % nf;
            pgfaultcnt++;
            for (int j = 0; j < nf; j++) {
                if (p[j] != -1) cout << " " << p[j];
            }
            cout << " (Page Fault)";
        } else {
            cout << " Page Hit";
        }
        cout << endl;
    }
    cout << "\nTotal number of page faults: " << pgfaultcnt << endl;
}

void optimal(int sequence[], int n, int nf) {
    int p[nf], pgfaultcnt = 0;
    for (int i = 0; i < nf; i++) p[i] = -1; // Initialize frames

    cout << "\nOptimal Page Replacement:\n";
    for (int i = 0; i < n; i++) {
        bool hit = false;
        for (int j = 0; j < nf; j++) {
            if (p[j] == sequence[i]) {
                hit = true;
                break;
            }
        }
        if (!hit) {
            int farthest = -1, replaceIndex = 0;
            for (int j = 0; j < nf; j++) {
                int nextUse = 0;
                for (int k = i + 1; k < n; k++) {
                    if (p[j] == sequence[k]) {
                        nextUse = k;
                        break;
                    }
                    if (k == n - 1) nextUse = n;
                }
                if (nextUse > farthest) {
                    farthest = nextUse;
                    replaceIndex = j;
                }
            }
            p[replaceIndex] = sequence[i];
            pgfaultcnt++;
            for (int j = 0; j < nf; j++) {
                if (p[j] != -1) cout << " " << p[j];
            }
            cout << " (Page Fault)";
        } else {
            cout << " Page Hit";
        }
        cout << endl;
    }
    cout << "\nTotal number of page faults: " << pgfaultcnt << endl;
}

void lru(int sequence[], int n, int nf) {
    int p[nf], pgfaultcnt = 0;
    for (int i = 0; i < nf; i++) p[i] = -1; // Initialize frames

    cout << "\nLRU Page Replacement:\n";
    for (int i = 0; i < n; i++) {
        bool hit = false;
        for (int j = 0; j < nf; j++) {
            if (p[j] == sequence[i]) {
                hit = true;
                break;
            }
        }
        if (!hit) {
            int leastRecent = i, replaceIndex = 0;
            for (int j = 0; j < nf; j++) {
                for (int k = i - 1; k >= 0; k--) {
                    if (p[j] == sequence[k]) {
                        if (k < leastRecent) {
                            leastRecent = k;
                            replaceIndex = j;
                        }
                        break;
                    }
                }
            }
            p[replaceIndex] = sequence[i];
            pgfaultcnt++;
            for (int j = 0; j < nf; j++) {
                if (p[j] != -1) cout << " " << p[j];
            }
            cout << " (Page Fault)";
        } else {
            cout << " Page Hit";
        }
        cout << endl;
    }
    cout << "\nTotal number of page faults: " << pgfaultcnt << endl;
}

int main() {
    int n, nf;
    cout << "\nEnter length of page reference sequence: ";
    cin >> n;
    int sequence[n];
    cout << "\nEnter the page reference sequence: ";
    for (int i = 0; i < n; i++) cin >> sequence[i];
    cout << "\nEnter number of frames: ";
    cin >> nf;

    int choice;
    char cont;
    do {
        cout << "\nSelect Page Replacement Algorithm:\n1. FIFO\n2. Optimal\n3. LRU\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                fifo(sequence, n, nf);
                break;
            case 2:
                optimal(sequence, n, nf);
                break;
            case 3:
                lru(sequence, n, nf);
                break;
            default:
                cout << "Invalid choice." << endl;
                break;
        }

        cout << "\nDo you want to run another algorithm? (y/n): ";
        cin >> cont;
    } while (cont == 'y' || cont == 'Y');

    cout << "Exiting program. Thank you!" << endl;
    return 0;
}
/*Enter length of page reference sequence: 7

Enter the page reference sequence: 1 2 3 4 1 2 5

Enter number of frames: 3

Select Page Replacement Algorithm:
1. FIFO
2. Optimal
3. LRU
Enter your choice: 1

FIFO Page Replacement:
 1 (Page Fault)
 1 2 (Page Fault)
 1 2 3 (Page Fault)
 2 3 4 (Page Fault)
 2 3 4 Page Hit
 3 4 1 (Page Fault)
 4 1 5 (Page Fault)

Total number of page faults: 6

Do you want to run another algorithm? (y/n): y

*/

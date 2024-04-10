#include <iostream>
#include <vector>
using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int bubbleSort(vector<int> &arr) {
    int n = arr.size();
    int numSwaps = 0;
    
    for (int i = 0; i < n; ++i) {
        int numberOfSwaps = 0;
        
        for (int j = 0; j < n - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                numberOfSwaps++;
            }
        }
        
        numSwaps += numberOfSwaps;
        
        if (numberOfSwaps == 0) {
            break;
        }
    }
    
    return numSwaps;
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    int numSwaps = bubbleSort(arr);
    
    cout << "Array is sorted in " << numSwaps << " swaps." << endl;
    cout << "First Element: " << arr.front() << endl;
    cout << "Last Element: " << arr.back() << endl;
    
    return 0;
}


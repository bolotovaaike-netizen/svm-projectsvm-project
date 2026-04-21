/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <algorithm> 

using namespace std;

//  Чтение CSV 
vector<int> readCSV(const string& filename) {
    vector<int> numbers;
    ifstream file(filename);
    string line;
    if (!file.is_open()) {
        cout << "HATA" << endl;
        return numbers;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        while (getline(ss, value, ',')) {
            numbers.push_back(stoi(value));
        }
    }
    file.close();
    return numbers;
}

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

//  (Bubble Sort) 
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) swap(arr[j], arr[j+1]);
        }
    }
}

// Brute Force поиск слова 
int countWordInText(const string& filename, const string& word) {
    ifstream file(filename);
    string temp;
    int count = 0;
    while (file >> temp) {
        if (temp == word) count++;
    }
    return count;
}

int main() {
    // Проверка компиляции
    cout << "Hello World" << endl;

   
    vector<int> numbers = readCSV("numbers.csv");

    
    vector<int> arr1 = numbers;
    auto start = chrono::high_resolution_clock::now();
    mergeSort(arr1, 0, arr1.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    cout << "Merge Sort время: " << chrono::duration<double>(end - start).count() << " секунд\n";

    
    vector<int> arr2 = numbers;
    start = chrono::high_resolution_clock::now();
    bubbleSort(arr2);
    end = chrono::high_resolution_clock::now();
    cout << "Bubble Sort время: " << chrono::duration<double>(end - start).count() << " секунд\n";

   
    vector<string> words = {"Alice", "Rabbit", "Queen"};
    for (string w : words) {
        start = chrono::high_resolution_clock::now();
        int count = countWordInText("alice_in_wonderland (1)", w);
        end = chrono::high_resolution_clock::now();
        cout << "Слово \"" << w << "\" встречается " << count
             << " раз. Время: " << chrono::duration<double>(end - start).count() << " секунд\n";
    }

    return 0;
}
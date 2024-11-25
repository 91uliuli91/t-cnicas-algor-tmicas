#include <iostream>
#include <vector>
#include <chrono> 
#include <algorithm> 

using namespace std;


void printSudoku(const vector<vector<int>>& board) {
    cout << "+-------+-------+-------+" << endl;
    for (int i = 0; i < 9; i++) {
        cout << "| ";
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == 0)
                cout << ". "; 
            else
                cout << board[i][j] << " ";
            
            if ((j + 1) % 3 == 0) cout << "| ";
        }
        cout << endl;
        if ((i + 1) % 3 == 0) cout << "+-------+-------+-------+" << endl;
    }
}

bool isSafe(const vector<vector<int>>& board, int row, int col, int num) {
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == num || board[i][col] == num)
            return false;
    }

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[startRow + i][startCol + j] == num)
                return false;
        }
    }
    return true;
}

void insertionSort(vector<int>& nums) {
    for (size_t i = 1; i < nums.size(); i++) {
        int key = nums[i];
        int j = i - 1;
        while (j >= 0 && nums[j] > key) {
            nums[j + 1] = nums[j];
            j--;
        }
        nums[j + 1] = key;
    }
}

void merge(vector<int>& nums, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = nums[left + i];
    for (int i = 0; i < n2; i++) R[i] = nums[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) nums[k++] = L[i++];
        else nums[k++] = R[j++];
    }

    while (i < n1) nums[k++] = L[i++];
    while (j < n2) nums[k++] = R[j++];
}

void mergeSort(vector<int>& nums, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(nums, left, mid);
        mergeSort(nums, mid + 1, right);
        merge(nums, left, mid, right);
    }
}

void quickSort(vector<int>& nums, int low, int high) {
    if (low < high) {
        int pivot = nums[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; j++) {
            if (nums[j] <= pivot) {
                i++;
                swap(nums[i], nums[j]);
            }
        }
        swap(nums[i + 1], nums[high]);
        int pi = i + 1;

        quickSort(nums, low, pi - 1);
        quickSort(nums, pi + 1, high);
    }
}

bool solveSudokuWithQuickSort(vector<vector<int>>& board) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == 0) {
                vector<int> candidates;
                for (int num = 1; num <= 9; num++) {
                    if (isSafe(board, row, col, num)) {
                        candidates.push_back(num);
                    }
                }
                quickSort(candidates, 0, candidates.size() - 1); 

                for (int num : candidates) {
                    board[row][col] = num;
                    if (solveSudokuWithQuickSort(board)) {
                        return true;
                    }
                    board[row][col] = 0;
                }
                return false;
            }
        }
    }
    return true;
}

bool solveSudokuWithInsertion(vector<vector<int>>& board) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == 0) {
                vector<int> candidates;
                for (int num = 1; num <= 9; num++) {
                    if (isSafe(board, row, col, num)) {
                        candidates.push_back(num);
                    }
                }
                insertionSort(candidates); 

                for (int num : candidates) {
                    board[row][col] = num;
                    if (solveSudokuWithInsertion(board)) {
                        return true;
                    }
                    board[row][col] = 0;
                }
                return false;
            }
        }
    }
    return true;
}

bool solveSudokuWithMergeSort(vector<vector<int>>& board) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == 0) {
                vector<int> candidates;
                for (int num = 1; num <= 9; num++) {
                    if (isSafe(board, row, col, num)) {
                        candidates.push_back(num);
                    }
                }
                mergeSort(candidates, 0, candidates.size() - 1); 

                for (int num : candidates) {
                    board[row][col] = num;
                    if (solveSudokuWithMergeSort(board)) {
                        return true;
                    }
                    board[row][col] = 0;
                }
                return false;
            }
        }
    }
    return true;
}

bool solveSudokuBasic(vector<vector<int>>& board) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (isSafe(board, row, col, num)) {
                        board[row][col] = num;
                        if (solveSudokuBasic(board)) {
                            return true;
                        }
                        board[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

int main() {
    vector<vector<int>> initial = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    cout << "Sudoku inicial:" << endl;
    printSudoku(initial);

    vector<vector<int>> boardWithQuickSort = initial;
    auto startQuickSort = chrono::high_resolution_clock::now();
    solveSudokuWithQuickSort(boardWithQuickSort);
    auto endQuickSort = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedQuickSort = endQuickSort - startQuickSort;

    vector<vector<int>> boardWithInsertion = initial;
    auto startInsertion = chrono::high_resolution_clock::now();
    solveSudokuWithInsertion(boardWithInsertion);
    auto endInsertion = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedInsertion = endInsertion - startInsertion;

    vector<vector<int>> boardWithMergeSort = initial;
    auto startMergeSort = chrono::high_resolution_clock::now();
    solveSudokuWithMergeSort(boardWithMergeSort);
    auto endMergeSort = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedMergeSort = endMergeSort - startMergeSort;

    vector<vector<int>> boardBasic = initial;
    auto startBasic = chrono::high_resolution_clock::now();
    solveSudokuBasic(boardBasic);
    auto endBasic = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedBasic = endBasic - startBasic;

    cout << "\nTiempo con QuickSort: " << elapsedQuickSort.count() << " segundos." << endl;
    cout << "Tiempo con Insertion Sort: " << elapsedInsertion.count() << " segundos." << endl;
    cout << "Tiempo con Merge Sort: " << elapsedMergeSort.count() << " segundos." << endl;
    cout << "Tiempo sin ordenar: " << elapsedBasic.count() << " segundos." << endl;

    vector<pair<double, string>> times = {
        {elapsedQuickSort.count(), "QuickSort"},
        {elapsedInsertion.count(), "Insertion Sort"},
        {elapsedMergeSort.count(), "Merge Sort"},
        {elapsedBasic.count(), "Sin Ordenar"}
    };

    sort(times.begin(), times.end());

    cout << "\nAlgoritmo más óptimo: " << times.front().second << endl;
    cout << "Tiempos de ejecución (de menor a mayor):" << endl;
    for (const auto& time : times) {
        cout << time.second << ": " << time.first << " segundos." << endl;
    }

    cout << "\nSudoku resuelto con " << times.front().second << ":" << endl;
    printSudoku(boardWithQuickSort);  

    return 0;
}

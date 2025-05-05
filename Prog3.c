#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Merge two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    
    int L[n1], R[n2];
    
    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    
    // Merge the temp arrays back into arr[l..r]
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge Sort function
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;  // Find the middle point
        
        // Recursively sort the first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        
        // Merge the sorted halves
        merge(arr, l, m, r);
    }
}

// Function to generate a random array of size n
void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000000;  // Random number between 0 and 999999
    }
}

int main() {
    srand(time(0));  // Seed for random number generator
    
    FILE *outfile = fopen("results.csv", "w");
    if (outfile == NULL) {
        printf("Error opening file for writing\n");
        return 1;
    }
    
    // Write CSV header
    fprintf(outfile, "n,TimeTaken(ms)\n");
    
    // Run the program for varying n values (greater than 5000)
    for (int n = 5000; n <= 10000; n += 500) {
        int *arr = (int *)malloc(n * sizeof(int));
        if (arr == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
        
        // Generate random array
        generateRandomArray(arr, n);
        
        // Record start time
        clock_t start = clock();
        
        // Perform merge sort
        mergeSort(arr, 0, n - 1);
        
        // Record end time
        clock_t end = clock();
        
        // Calculate the time taken in milliseconds
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
        
        // Write the result to the CSV file
        fprintf(outfile, "%d,%.2f\n", n, time_taken);
        
        // Free the allocated memory
        free(arr);
    }
    
    // Close the file
    fclose(outfile);
    
    printf("Results have been saved to 'results.csv'.\n");
    
    return 0;
}

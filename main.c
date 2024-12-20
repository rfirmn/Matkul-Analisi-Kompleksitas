#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_NUMBERS 1000
#define MIN_VALUE 5
#define MAX_VALUE 20

// Struct untuk menyimpan angka dan totalnya
typedef struct {
    int numbers[MAX_NUMBERS];
    int count;
} Box;

// Fungsi untuk mengurutkan angka menggunakan bubble sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Fungsi untuk mengurutkan angka menggunakan quick sort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        int pi = i + 1;

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Fungsi untuk menampilkan isi Box
void displayBox(Box boxes[], int boxIndex, int totalBoxes) {
    if (boxIndex < 0 || boxIndex >= totalBoxes) {
        printf("Box tidak ditemukan!\n");
        return;
    }

    printf("Isi Box %d:\n", boxIndex + 1);
    for (int i = 0; i < boxes[boxIndex].count; i++) {
        printf("%d ", boxes[boxIndex].numbers[i]);
    }
    printf("\nTotal angka: %d\n", boxes[boxIndex].count);
}

// Fungsi untuk menampilkan semua angka dari array "angka"
void displayAllNumbers(int angka[], int totalNumbers) {

    for (int i = 0; i < totalNumbers; i++) {
        printf("%d ", angka[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    int angka[MAX_NUMBERS];
    for (int i = 0; i < MAX_NUMBERS; i++) {
        angka[i] = rand() % (MAX_VALUE - MIN_VALUE + 1) + MIN_VALUE;
    }

    int angka2[MAX_NUMBERS];

    memcpy(angka2, angka, MAX_NUMBERS);

    Box boxes[10]; // Maksimal 10 box
    int totalBoxes = 0;
    int currentIndex = 0; // Menyimpan indeks terakhir yang dimasukkan

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Masukkan angka ke dalam box\n");
        printf("2. Urutkan angka \n");
        printf("3. Tampilkan isi Box\n");
        printf("4. Tampilkan semua angka\n");
        printf("5. Angka yang belum masuk\n");
        printf("6. Keluar");
        printf("Masukkan pilihan: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1: {
            if (totalBoxes >= 10) {
                printf("Maksimal box sudah tercapai!\n");
                break;
            }

            if (currentIndex >= MAX_NUMBERS) {
                printf("Semua angka sudah dimasukkan ke dalam box!\n");
                break;
            }

            Box box;
            box.count = 0;

            for (int i = currentIndex; i < MAX_NUMBERS; i++) {
                box.numbers[box.count++] = angka[i];
                currentIndex++;
                if (box.count >= 100) { // Membagi rata angka ke dalam 10 box
                    break;
                }
            }

            boxes[totalBoxes++] = box;
            printf("Angka berhasil dimasukkan ke dalam Box %d.\n", totalBoxes);
            break;
        }
        case 2: {
            clock_t start = clock();
            bubbleSort(angka, MAX_NUMBERS);
            clock_t end = clock();

            printf("Waktu Bubble Sort: %.2f ms\n", (double)(end - start) * 1000 / CLOCKS_PER_SEC);

            clock_t start1 = clock();
            quickSort(angka2, 0, MAX_NUMBERS - 1);
            clock_t end1 = clock();

            printf("Waktu Quick Sort: %.2f ms\n", (double)(end1 - start1) * 1000 / CLOCKS_PER_SEC);
            break;
        }
        case 3: {
            int boxIndex;
            printf("Masukkan nomor Box yang ingin dilihat (1-%d): ", totalBoxes);
            scanf("%d", &boxIndex);
            displayBox(boxes, boxIndex - 1, totalBoxes);
            break;
        }
        case 4: {
            displayAllNumbers(angka, MAX_NUMBERS);
            break;
        }
        case 5:{
            if (currentIndex == MAX_NUMBERS){
                printf("Semua angka sudah dimasukkan");
                break;
            }
            for(int i = currentIndex; i <= MAX_NUMBERS - 1; i++){
                printf("%i ", angka[i]);
            }
        }
            break;
        case 6: {
            printf("Keluar dari program.\n");
            break;
        }
        default:
            printf("Pilihan tidak valid.\n");
            break;
        }
    } while (choice != 6);

    return 0;
}

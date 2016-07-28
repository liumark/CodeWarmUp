#include <stdio.h>
#include <stdlib.h>

#define NUM_ELEM 20
static int a[NUM_ELEM];
static int cnt=0;

typedef struct node {
    int value;
    struct node* next;
} ListElem;

ListElem* mList;
//ListElem* mHead;

ListElem* createElem() {
    ListElem* retVal = (ListElem *)malloc(sizeof(ListElem));
    retVal->value = -1;
    retVal->next = NULL;

    return retVal;
}

void assignList(int* arr, int n) {
    //int i;
    mList = createElem();
    ListElem* tmp = mList;
    
    for (int i = 0; i < n; i++) {
        tmp->value = arr[i];
        tmp->next = createElem();
        tmp = tmp->next;
    }
}

void swap(int* x, int* y) {
    if (*x != *y) {
        *x ^= *y;
        *y ^= *x;
        *x ^= *y;
    }
}

void insert_sort(int* arr, int n) {
    //ListElem* tmp = mList;

    for (int i = 1; i < n; i++) {
//            printf("%d %d\n", arr[i], arr[i-1]);
        for (int j = i; j > 0 && arr[j-1U] > arr[j]; --j) {
//            printf("do swap\n");
            int tmp = arr[j];
            arr[j] = arr[j-1U];
            arr[j-1U] = tmp;
        }
    }
}

void insert_q_sort(int* arr, int n) {
    for (int i = 1; i < n; i++) {
        int tmp = arr[i];
        int left = 0;
        int right = i;
        while (left < right) {
            int middle = (left + right)/2;
            if (tmp < arr[middle])
                right = middle;
            else
                left = middle + 1;
        }

        for (int j = i; j > left; --j) {
            int tmp = arr[j];
            arr[j] = arr[j-1];
            arr[j-1] = tmp;
        }
    }
}

void bubble_sort(int* arr, int n) {
    for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j < i; ++j) {
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
                //int tmp = arr[j];
                //arr[j] = arr[j+1];
                //arr[j+1] = tmp;
            }
        }
    }
}

/*https://en.wikipedia.org/wiki/Quicksort
 *The steps of quick sort are:
 *  1. Pick an element, called a pivot, from the array.
 *  2. Partitioning: reorder the array so that all elements with values less than the pivot come 
 *     before the pivot, while all elements with values greater than the pivot come after it (equal 
 *     values can go either way). After this partitioning, the pivot is in its final position. This 
 *     is called the partition operation.
 *  3. Recursively apply the above steps to the sub-array of elements with smaller values and 
 *     separately to the sub-array of elements with greater values.*/
//Note: As a start point, the left index should be the array start
void quick_sort(int* arr, int left, int right) {
    int i, pivot;

    //The index of left must be greater than the index of right
    if (left >= right) return;

    swap(&arr[left], &arr[(left + right)/2]);
    pivot = left;
    //The loop start should be pivot plus one since we want to keep the pivot
    for (i = left + 1; i < right; i++)
        if (arr[i] < arr[left])
            swap(&arr[++pivot], &arr[i]);

    swap(&arr[left], &arr[pivot]);
    for (int k = 0; k < NUM_ELEM; k++) printf("%d ", arr[k]);
    printf("\n pivot=%d\n",pivot);
    quick_sort(arr, left, pivot -1);
    quick_sort(arr, pivot + 1, right);
    
}

void quick_sort1(int* arr, int left, int right) {
    int i, p, pivot;
    int cutoff = 2;
    cnt++;

    if (right - left + 1 > cutoff) {
        p = (left + right)/2;
        swap(&arr[p], &arr[right]);
        pivot = arr[right];
        int i = left;
        int j = right -1;
        for (;;) {
            while (i < j && arr[i] < pivot) ++i;
            while (i < j && arr[j] > pivot) --j;
            if (i >= j) break;
            swap(&arr[i++], &arr[j--]);
        }
        if (arr[i] > pivot) swap(&arr[i], &arr[right]);
    for (int k = 0; k < NUM_ELEM; k++) printf("%d ", arr[k]);
    printf("\n pivot=%d count=%d left=%d right=%d\n",i,cnt,left,right);
        if (left < i) quick_sort1(arr, left, i - 1);
        if (right > i) quick_sort1(arr, i + 1, right);
    }
}

void quick_sort2(int* arr, int left, int right) {
    int i, pivot, tmp;
    //cnt++;

    //The index of left must be greater than the index of right
    if (left >= right) return;

    pivot = left;
    //The loop start should be pivot plus one since we want to keep the pivot
    for (i = left + 1; i <= right; i++)//include the right edge item
        //The movement of array item is more than just swap since the pivot has to be moved
        if (arr[i] <= arr[pivot]) {//include the right edge item
            tmp = arr[i];
            if (i > (pivot + 1)) {
                arr[i] = arr[pivot + 1];
                arr[pivot+1] = arr[pivot];
            //    arr[pivot] = tmp;
            } else {
                arr[i] = arr[pivot];
            }
            arr[pivot] = tmp;
            pivot++;
        }

    //for (int k = 0; k < NUM_ELEM; k++) printf("%d ", arr[k]);
    //printf("\n pivot=%d count=%d left=%d right=%d\n",pivot,cnt,left,right);
    if (pivot == left) pivot++;//In case the most left item is the smallest one, the pivot must still be moved
    quick_sort2(arr, left, pivot -1);
    quick_sort2(arr, pivot + 1, right);
       
}

int partition_lomuto(int* arr, int lo, int hi) {
    int pivot = arr[hi];
    int i = lo;
    for (int j = lo; j <= (hi - 1); j++) {
        if (arr[j] <= pivot) {
            //printf("swap a[%d] a[%d]\n",i,j);
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[hi]);
    return i;
}

void qsort_lomuto(int* arr, int lo, int hi) {
    int p;
    cnt++;
    if (lo < hi) {
        p = partition_lomuto(arr, lo, hi);
        //for (int k = 0; k < NUM_ELEM; k++) printf("%d ", arr[k]);
        //printf("\n pivot=%d count=%d left=%d right=%d\n",p,cnt,lo,hi);
        qsort_lomuto(arr, lo, p - 1);
        qsort_lomuto(arr, p + 1, hi);
    }
}

int partition_hoare(int* arr, int lo, int hi) {
    int pivot = arr[lo];
    int i = lo - 1;
    int j = hi + 1;
    for (;;) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        //if (i >= j) return j;
        //printf("swap a[%d] a[%d]\n",i,j);
        //Consider the case when 2 items are equal
        if (arr[i] == pivot) i = (i > hi) ? hi : i++;
        if (arr[j] == pivot) j = (j < lo) ? lo : j--;
        if (i >= j) return (j>=0) ? j : 0;
        printf("swap a[%d] a[%d] pivot=%d\n",i,j,pivot);
        swap(&arr[i], &arr[j]);
    }
}

//The algorithm has endless loop on the edge, the problem is the
//partition function when the item has equal value
void qsort_hoare(int* arr, int lo, int hi) {
    int p;
    if (lo < hi) {
        p = partition_hoare(arr, lo, hi);
        for (int k = 0; k < NUM_ELEM; k++) printf("%d ", arr[k]);
        printf("\n p=%d count=%d left=%d right=%d\n",p,cnt,lo,hi);
        qsort_hoare(arr, lo, p - 1);
        qsort_hoare(arr, p + 1, hi);
    }
}

void genArr() {
    int i;
    for (i = 0; i < NUM_ELEM; i++) {
        a[i] = rand()%NUM_ELEM;
    }
}

int main() {
    //int a[15] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 4, 18, 12, 11, 14, 17};
    genArr();

    assignList(a, NUM_ELEM);

    ListElem* tmp = mList;

    printf("Assign LinkList: \n");
    while (tmp->next != NULL) {
        printf("%d ", tmp->value);
        tmp = tmp->next;
    }
    printf("\n");

    //insert_sort(a, NUM_ELEM);
    //insert_q_sort(a, NUM_ELEM);
    //bubble_sort(a, NUM_ELEM);
    //quick_sort1(a, 0, NUM_ELEM - 1);
    //qsort_lomuto(a, 0, NUM_ELEM - 1);
    qsort_hoare(a, 0, NUM_ELEM - 1);
    printf("Insert Sort result:\n");
    for (int i = 0; i < NUM_ELEM; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}

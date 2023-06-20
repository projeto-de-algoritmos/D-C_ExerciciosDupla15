/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
typedef struct {
    int value;
    int frequency;
} Element;

int compare(const void* a, const void* b) {
    return ((Element*)b)->frequency - ((Element*)a)->frequency;
}

void merge(Element* arr, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Element* L = (Element*)malloc(n1 * sizeof(Element));
    Element* R = (Element*)malloc(n2 * sizeof(Element));

    for (i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i].frequency >= R[j].frequency) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(Element* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void findTopKFrequentUtil(int* nums, int left, int right, int k, Element* elements, int* count) {
    if (left == right) {
        int i;
        for (i = 0; i < *count; i++) {
            if (elements[i].value == nums[left]) {
                elements[i].frequency++;
                break;
            }
        }
        if (i == *count) {
            elements[*count].value = nums[left];
            elements[*count].frequency = 1;
            (*count)++;
        }
        return;
    }

    int mid = left + (right - left) / 2;
    findTopKFrequentUtil(nums, left, mid, k, elements, count);
    findTopKFrequentUtil(nums, mid + 1, right, k, elements, count);
}

int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    // Conta a frequencia de cada elemento
    Element* elements = (Element*)malloc(numsSize * sizeof(Element));
    int count = 0;

    findTopKFrequentUtil(nums, 0, numsSize - 1, k, elements, &count);

    // Organiza os elementos com base na freuqencia usando merge sort
    mergeSort(elements, 0, count - 1);

    // Retorna o top k elementos mais frequentes
    *returnSize = k;
    int* result = (int*)malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        result[i] = elements[i].value;
    }

    free(elements);
    return result;
}
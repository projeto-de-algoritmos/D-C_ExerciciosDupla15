/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortArray(int* nums, int numsSize, int* returnSize) {
    int* result = (int*)malloc(numsSize * sizeof(int));
    *returnSize = numsSize;

    for (int i = 0; i < numsSize; i++)
        result[i] = nums[i];

    mergeSort(result, numsSize);

    return result;
}

void merge(int array[], int left[], int leftSize, int right[], int rightSize) {
    int i = 0, j = 0, k = 0;

    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j])
            array[k++] = left[i++];
        else
            array[k++] = right[j++];
    }

    while (i < leftSize)
        array[k++] = left[i++];

    while (j < rightSize)
        array[k++] = right[j++];
}

void mergeSort(int array[], int size) {
    if (size < 2)
        return;

    int mid = size / 2;
    int *left = (int*)malloc(mid * sizeof(int));
    int *right = (int*)malloc((size - mid) * sizeof(int));

    for (int i = 0; i < mid; i++)
        left[i] = array[i];

    for (int i = mid; i < size; i++)
        right[i - mid] = array[i];

    mergeSort(left, mid);
    mergeSort(right, size - mid);
    merge(array, left, mid, right, size - mid);

    free(left);
    free(right);
}
int singleNumber(int A[], int n) {
    int i, tmp;
    for (i = 0; i < n; ++i) {
        tmp = tmp ^ A[i];
    }
    return tmp;
}

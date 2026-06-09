#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <math.h>


void swap(double* a, double* b) {
    double tmp = *a;
    *a = *b;
    *b = tmp;
}


SEXP selection_sort_c(SEXP x) {
    int n = Rf_length(x);
    SEXP result = PROTECT(Rf_allocVector(REALSXP, n));

    double* x_in = REAL(x);
    double* res = REAL(result);

    for (int i = 0; i < n; i++)
        res[i] = x_in[i];
    
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (res[j] < res[min_idx])
                min_idx = j;

        }
        
        if (min_idx != i)
            swap(&res[min_idx], &res[i]);   
    }
    
    UNPROTECT(1);
    return result;
}

SEXP insertion_sort_c(SEXP x) {
    int n = Rf_length(x);
    SEXP result = PROTECT(Rf_allocVector(REALSXP, n));
    double* x_in = REAL(x);
    double* res = REAL(result);
    
    for (int i = 0; i < n; i++)
        res[i] = x_in[i];

    for (int i = 1; i < n; i++) {

        double key = res[i];
        int j = i - 1;
        
        while (j >= 0 && res[j] > key) {
            res[j + 1] = res[j];
            j--;
        }

        res[j + 1] = key;
    }
    
    UNPROTECT(1);

    return result;
}

SEXP bubble_sort_c(SEXP x) {
    int n = Rf_length(x);
    SEXP result = PROTECT(Rf_allocVector(REALSXP, n));
    double* x_in = REAL(x);
    double* res = REAL(result);
    
    for (int i = 0; i < n; i++)
        res[i] = x_in[i];
    
    int swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = 0;

        for (int j = 0; j < n - i - 1; j++) {
            if (res[j] > res[j + 1]) {
                swap(&res[j], &res[j + 1]);
                swapped = 1;
            }
        }
        if (!swapped) break; 

    }
    
    UNPROTECT(1);
    return result;
}

void quicksort_rec(double* x, int down, int up) {

    if (down < up) {
        double pivot = x[up];
        int i = (down - 1);

        for (int j = down; j <= up - 1; j++) {
            if (x[j] < pivot) {
                i++;
                swap(&x[i], &x[j]);
            }
        }
        swap(&x[i + 1], &x[up]);       
        quicksort_rec(x, down, i);
        quicksort_rec(x, i + 2, up);
    }
}

SEXP quicksort_c(SEXP x) {
    int n = Rf_length(x);
    SEXP result = PROTECT(Rf_allocVector(REALSXP, n));
    double *x_in = REAL(x);
    double *res = REAL(result);
    
    for (int i = 0; i < n; i++)
        res[i] = x_in[i];
    
    if (n > 1)
        quicksort_rec(res, 0, n - 1);
    
    UNPROTECT(1);
    return result;
}
SEXP selection_sort_CNA_c(SEXP x) {
    int x_n = Rf_length(x);
    double* x_in = REAL(x);
    int n = 0;
    for (int i = 0; i < x_n; i++) {
        if (!ISNA(x_in[i]) && !ISNAN(x_in[i]))
            n++;
    
    }
    SEXP result = PROTECT(Rf_allocVector(REALSXP, n));
    double* res = REAL(result);

    int idx = 0;
    for (int i = 0; i < x_n; i++) {
        if (!ISNA(x_in[i]) && !ISNAN(x_in[i]))
            res[idx++] = x_in[i];

    }
    

    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (res[j] < res[min_idx])
                min_idx = j;
        }
        
        if (min_idx != i)
            swap(&res[min_idx], &res[i]);

    }
    UNPROTECT(1);
    return result;
}

void merge(double* x, double* tmp, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (x[i] <= x[j]) {
            tmp[k++] = x[i++];
        } else {
            tmp[k++] = x[j++];
        }
    }

    while (i <= mid)
        tmp[k++] = x[i++];

    while (j <= right)
        tmp[k++] = x[j++];

    for (i = left; i <= right; i++)
        x[i] = tmp[i];
}

void mergesort_rec(double* x, double* tmp, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergesort_rec(x, tmp, left, mid);
        mergesort_rec(x, tmp, mid + 1, right);
        merge(x, tmp, left, mid, right);
    }
}

SEXP mergesort_c(SEXP x) {
    int n = Rf_length(x);
    SEXP result = PROTECT(Rf_allocVector(REALSXP, n));
    double* x_in = REAL(x);
    double* res = REAL(result);

    for (int i = 0; i < n; i++) 
        res[i] = x_in[i];

    if (n > 1) {
        double* tmp = (double *)R_alloc(n, sizeof(double));
        mergesort_rec(res, tmp, 0, n - 1);
    }

    UNPROTECT(1);
    return result;
}

SEXP countsort_c(SEXP x) {
    int n = Rf_length(x);
    
    double* x_in = REAL(x); 
    
    for (int i = 0; i < n; i++) {
        if (floor(x_in[i]) != x_in[i]) {
            Rf_error("ONLY INTEGERS");
        }
    }
    SEXP result = PROTECT(Rf_allocVector(INTSXP, n));
    int* res = INTEGER(result);

    if (n == 0) {
        UNPROTECT(1);
        return result;
    }
    
    int min_v = x_in[0];
    int max_v = x_in[0];
    for (int i = 1; i < n; i++) {
        if (x_in[i] < min_v) min_v = x_in[i];
        if (x_in[i] > max_v) max_v = x_in[i];
    }
    
    int range = max_v - min_v + 1;
    
    int* count = (int *)R_alloc(range, sizeof(int));
    for (int i = 0; i < range; i++) {
        count[i] = 0;
    }
    
    for (int i = 0; i < n; i++) {
        int current = (int)x_in[i];
        count[current - min_v]++;
    }
    
    int index = 0;
    for (int i = 0; i < range; i++) {
        while (count[i] > 0) {
            res[index++] = i + min_v;
            count[i]--;
        }
    }
    
    UNPROTECT(1);
    return result;
}

SEXP shellsort_c(SEXP x) {
    int n = Rf_length(x);
    SEXP result = PROTECT(Rf_allocVector(REALSXP, n));
    
    double* x_in = REAL(x);
    double* res = REAL(result);
    
    for (int i = 0; i < n; i++)
        res[i] = x_in[i];
    
    for (int space = n / 2; space > 0; space /= 2) {
        for (int i = space; i < n; i++) {
            double tmp = res[i];
            int j;
            
            for (j = i; j >= space && res[j - space] > tmp; j -= space) {
                res[j] = res[j - space];
            }
            res[j] = tmp;
        }
    }
    
    UNPROTECT(1);
    return result;
}
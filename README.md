# CsoRt

A lightweight R package providing high-performance sorting algorithms written entirely in C. 

Base R's `sort()` is great, but sometimes you need raw C performance, specific algorithmic complexity, or better memory management when handling missing values (`NA`) in large datasets. `CsoRt` bypasses R-level memory duplication by handling data cleaning and array allocations directly at the C pointer level via the `.Call()` interface.

## Algorithms Included

The package includes 7 classic algorithms:

* **O(n log n):** Quick Sort, Merge Sort
* **O(n):** Count Sort (strictly checks for integer inputs)
* **O(n^2) & Others:** Shell Sort, Insertion Sort, Selection Sort, Bubble Sort


#' @useDynLib CsoRt
NULL

#' Selection Sort
#'
#' Sorts a numeric vector using the Selection Sort algorithm 
#' @param x numeric vector
#' @return sorted vector
#' @export
selection_sort <- function(x) {
     if (!is.numeric(x)) {
    stop("vector must be numeric")
  }
  x <- x[!is.na(x)]
  
  .Call("selection_sort_c", as.numeric(x), PACKAGE = "CsoRt")
}

#' Selection Sort (but C removes NA (better))
#'
#' Sorts a numeric vector using the Selection Sort algorithm.
#' NA and NaN values are removed in C for lower memory usage
#' 
#'
#' @param x numeric vector 
#' @return sorted numeric vector 
#' @export
selection_sort_CNA <- function(x) {
   if (!is.numeric(x)) {
    stop("vector must be numeric")
  }
   
  
  .Call("selection_sort_CNA_c", as.numeric(x))
}

#' Insertion Sort
#'
#' Sorts a numeric vector using the Insertion Sort algorithm 
#' 
#'
#' @param x numeric vector
#' @return sorted numeric vector.
#' @export
insertion_sort <- function(x) {
   if (!is.numeric(x)) {
    stop("vector must be numeric")
  }
  
  x <- x[!is.na(x)]
  
  .Call("insertion_sort_c", as.numeric(x))
}

#' Bubble Sort
#'
#' Sorts a numeric vector using the Bubble Sort algorithm 
#' 
#'
#' @param x numeric vector
#' @return sorted numeric vector.
#' @export
bubble_sort <- function(x) {
   if (!is.numeric(x)) {
    stop("vector must be numeric")
  }
  x <- x[!is.na(x)]
  
  .Call("bubble_sort_c", as.numeric(x))
}
#' Quick Sort
#'
#' Sorts a numeric vector using the Quick Sort algorithm 
#' 
#'
#' @param x  numeric vector
#' @return sorted numeric vector
#' @export
quick_sort <- function(x) {
   if (!is.numeric(x)) {
    stop("vector must be numeric")
  }
  
  x <- x[!is.na(x)]
  
  .Call("quicksort_c", as.numeric(x))
}


#' Merge Sort
#'
#' Sorts numeric vector using the Mergesort algorithm 
#' 
#'
#' @param x  numeric vector 
#' @return  sorted numeric vector.
#' @export
merge_sort <- function(x) {
   if (!is.numeric(x)) {
    stop("vector must be numeric")
  }
  
  x <- x[!is.na(x)]
    
  .Call("mergesort_c", as.numeric(x))
}

#' Counting Sort (Unstable)
#'
#' Sorts integer vector using the Counting Sort algorithm.
#'
#'
#' @param x integer vector 
#' @return sorted integer vector.
#' @export
count_sort <- function(x) {
   if (!is.numeric(x)) {
    stop("vector must be numeric")
  }
  
  x <- x[!is.na(x)]
    
  .Call("countsort_c", x)
}

#' Shell Sort
#'
#' Sorts a numeric vector using the Shell Sort algorithm.
#' 
#'
#' @param x numeric vector 
#' @return sorted numeric vector.
#' @export
shell_sort <- function(x) {
  if (!is.numeric(x)) {
    stop("vector must be numeric")
  }
  
  x <- x[!is.na(x)]
  
  .Call("shellsort_c", as.numeric(x))
}
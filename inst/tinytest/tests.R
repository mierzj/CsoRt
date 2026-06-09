
library(CsoRt)

sort_functions <- list(
  selection = selection_sort,
  insertion = insertion_sort,
  bubble = bubble_sort,
  quick = quick_sort,
  merge = merge_sort,
  shell = shell_sort,
  selection_CNA = selection_sort_CNA,
  count = count_sort
)

v_basic <- c(10.5, 3.2, 7.8, 1.1, 5.0)
exp_basic <- c(1.1, 3.2, 5.0, 7.8, 10.5)

v_neg <- c(-5, 0, 100, -42, 3)
exp_neg <- c(-42, -5, 0, 3, 100)

v_dup <- c(5, 2, 9, 1, 5, 6, 2)
exp_dup <- c(1, 2, 2, 5, 5, 6, 9)

v_na <- c(4, NA, 1, NaN, 3)
exp_na <- c(1, 3, 4)

v_text <- c("a", "b", "c")


for (name in names(sort_functions)) {
  sort_func <- sort_functions[[name]]

  expect_error(sort_func(v_text))
  
  if (name == "count") {
    expect_error(sort_func(v_basic))
    expect_equal(sort_func(v_neg), exp_neg )
    expect_equal(sort_func(v_dup), exp_dup)
    
  } else {
   
    expect_equal(sort_func(v_basic), exp_basic)
    expect_equal(sort_func(v_neg), exp_neg)
    expect_equal(sort_func(v_dup), exp_dup)
  }
    expect_equal(sort_func(v_na), exp_na)

}
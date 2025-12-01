#ifndef  SORT_ALGORITHMS_H

#define  SORT_ALGORITHMS_H

#include  <vector>

#include  <string>

#include  <algorithm>

struct  Book  {

  std::string  title;

  double  rating;

};

void  selection_sort(std::vector<Book>& books)  {

  int  n = books.size();

  for  (int  i = 0; i  <  n  -  1; ++i)  {

  int  min_idx = i;

  for  (int  j = i  +  1; j  <  n; ++j)  {

  if  (books[j].rating  <  books[min_idx].rating)  {

  min_idx = j;

  }

  }

  std::swap(books[i], books[min_idx]);

  }

}

#endif  // SORT_ALGORITHMS_H
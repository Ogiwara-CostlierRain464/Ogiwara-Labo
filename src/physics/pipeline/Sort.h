#ifndef LABO_SORT_H
#define LABO_SORT_H

#define Key(a) ((a).key)

template <class SortData>
void mergeTwoBuffers(
  SortData* d1,
  unsigned int n1,
  SortData *d2,
  unsigned int n2,
  SortData *buff
  ){

  unsigned int i = 0, j = 0;

  while(i < n1 && j < n2){
    if(Key(d1[i]) < Key(d2[j])){
      buff[i+j] = d1[i++];
    }else{
      buff[i+j] = d2[j++];
    }
  }

  if(i<n1) {
    while(i<n1) {
      buff[i+j] = d1[i++];
    }
  }
  else if(j<n2) {
    while(j<n2) {
      buff[i+j] = d2[j++];
    }
  }

  for(unsigned int k=0;k<(n1+n2);k++) {
    d1[k] = buff[k];
  }

}

template <class SortData>
void mergeSort(SortData *d, SortData *buff, int n){




//  if(n <= 1){
//    return;
//  }

  int n1 = n>>1;
  int n2 = n - n1;

  if(n1 > 1) mergeSort(d, buff, n1);

  if(n2 > 1) mergeSort(d+n1, buff, n2);

  mergeTwoBuffers(d, n1, d+n1, n2, buff);

}

template <class SortData>
void merge(SortData arr[], int l, int m, int r)
{
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;
  SortData L[n1], R[n2];
// Copy data to temp array
  for (i = 0; i < n1; i++)
    L[i] = arr[l + i];
  for (j = 0; j < n2; j++)
    R[j] = arr[m + 1+ j];
// Merge the temp arrays
  i = 0;
  j = 0;
  k = l;
  while (i < n1 && j < n2)
  {
    if (Key(L[i]) <= Key(R[j]))
    {
      arr[k] = L[i];
      i++;
    }
    else
    {
      arr[k] = R[j];
      j++;
    }
    k++;
  }
// Copy the remaining elements of L[]
  while (i < n1)
  {
    arr[k] = L[i];
    i++;
    k++;
  }
// Copy the remaining elements of R[]
  while (j < n2)
  {
    arr[k] = R[j];
    j++;
    k++;
  }
}

template <class SortData>
void mSort(SortData arr[], int l, int r){
  if(l < r){
    int m = l+(r-l)/2;
    mSort(arr, l,m);
    mSort(arr, m+1, r);
    merge(arr, l, m, r);
  }
}



#endif //LABO_SORT_H

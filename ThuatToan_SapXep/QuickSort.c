//#include <stdio.h>
//#include <malloc.h>
//typedef int keytype;
//typedef float othertype;
//typedef struct {
//	keytype key;
//	othertype otherfields;
//}recordtype;
//
//void swap (recordtype *x, recordtype *y) {
//	recordtype temp;
//	temp = *x;
//	*x = *y;
//	*y = temp;
//}
//
//void ReadF (recordtype a[], int *n) {
//	FILE *f;
//	f = fopen ("data.txt", "r");
//	int i=0;
//	if(f != NULL)
//	while (!feof(f)) {
//		fscanf (f, "%d%f", &a[i].key, &a[i].otherfields);
//		i++;
//	}
//	else 
//		printf ("Loi mo file!!!");
//	fclose(f);
//	*n=i; //Bao nhiu dong i->se co bao nhiu phan tu n
//}
//
//void PrintF (recordtype a[], int n) {
//	int i;
//	for (i=0; i<n; i++) {
//		printf ("%5d%5.1f\n", a[i].key, a[i].otherfields);
//	}
//}
//
//int FindPivot (recordtype a[], int i, int j) {
//	keytype first_key;
//	int k=i+1;
//	first_key = a[i].key;
//	while ((k<=j) && (a[k].key==first_key))
//		k++;
//	if (k > j)
//		return -1;
//	if (a[k].key > first_key)
//		return k;
//	return i;
//}
////FindPivot bien the
////int FindPivot (recordtype a[], int i, int j) {
////	keytype first_key;
////	int k=i+1;
////	first_key = a[i].key;
////	while ((k<=j) && (a[k].key==first_key))
////		k++;
////	if (k > j)
////		return -1;
////	if (a[k].key < first_key)
////		return i;
////	return k;
////}
//
//int Partition (recordtype a[], int i, int j, keytype pivot) {
//	int L=i, R=j;
//	while (L < R) {
//		while (a[L].key < pivot)
//			L++;
//		while (a[R].key >= pivot)
//			R--;
//		if (L < R)
//			swap (&a[L], &a[R]);
//	}
//	return L;
//}
////Partition bien the
////int Partition (recordtype a[], int i, int j, keytype pivot) {
////	int L=i, R=j;
////	while (L < R) {
////		while (a[L].key <= pivot)
////			L++;
////		while (a[R].key > pivot)
////			R--;
////		if (L < R)
////			swap (&a[L], &a[R]);
////	}
////	return L;
////}
//
//void QuickSort (recordtype a[], int i, int j) {
//	int pivot_index, k;
//	pivot_index = FindPivot (a, i, j);
//	keytype pivot;
//	if (pivot_index != -1) {
//		pivot = a[pivot_index].key;
//		k = Partition (a, i, j, pivot);
//		QuickSort (a, i, k-1);
//		QuickSort (a, k, j);
//	}
//}
//int main () {
//	recordtype a[100];
//	int n;
//	ReadF (a, &n);
//	printf ("---Thuat toan QuickSort---\n");
//	printf ("Du lieu ban dau:\n");
//	PrintF (a,n);
//	QuickSort (a, 0, n-1);
//	printf("Du lieu sau khi sap xep:\n");
//	PrintF (a,n);
//	return 0;
//}


#include <stdio.h>

typedef int keytype;
typedef float othertype;

typedef struct {
	keytype key;
	othertype otherfields;
}recordtype;

void swap (recordtype *x, recordtype *y) {
	recordtype t=*x; *x=*y; *y=t;
}

void doc_F (recordtype a[], int *n) {
	FILE *f =fopen ("data.txt", "r");
	int i=0;
	if (f != NULL) {
		while (!feof(f)) {
			fscanf (f, "%d%f", &a[i].key, &a[i].otherfields);
			i++;
		}
	}
	else printf ("Loi");
	fclose (f);
	*n=i;
}

void in_F(recordtype a[], int n) {
	int i=0;
	for (; i<n; i++)
		printf ("%5d%5.1f\n", a[i].key, a[i].otherfields);
	printf ("--------------------------------------\n");
}

int timchot (recordtype a[], int i, int j) {
	int k = i+1;
	keytype fkey = a[i].key; 
	while ((j>=k) && (a[k].key == fkey))
		k++;
	if (j < k)
		return -1;
	if (a[k].key > fkey)
		return k;
	return i;
}

int phanhoach (recordtype a[], int i, int j, keytype v) {
	int L=i, R=j;
	while (L<R) {
		while (a[L].key < v) L++;
		while (a[R].key >= v) R--;
		if (L < R)
			swap (&a[L], &a[R]);
	}
	return L;
}

void sxnhanh (recordtype a[], int i, int j) {
	int cschot = timchot(a, i, j), k;
	keytype v;
	if (cschot != -1) {
		v = a[cschot].key;
		k = phanhoach (a, i, j, v);
		sxnhanh (a, i, k-1);
		sxnhanh(a, k, j);
	}
}

int main () {
	recordtype a[100];
	int n;
	doc_F(a, &n);
	in_F(a, n);
	sxnhanh(a, 0, n-1);
	in_F(a, n);
	return 0;
}

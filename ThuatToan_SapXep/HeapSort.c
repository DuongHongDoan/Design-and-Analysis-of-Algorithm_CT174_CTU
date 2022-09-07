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
//void PushDown (recordtype a[], int first, int last) {
//	int f = first;
//	while (f <= (last-1)/2)
//		if (last == 2*f+1) {
//			if (a[f].key > a[last].key)
//				swap (&a[f], &a[last]);
//				f = last;
//		}
//		else if ((a[f].key > a[2*f+1].key) && (a[2*f+1].key <= a[2*f+2].key)) {
//			swap (&a[f], &a[2*f+1]);
//			f = 2*f+1;
//		}
//		else if ((a[f].key > a[2*f+2].key) && (a[2*f+2].key < a[2*f+1].key)) {
//			swap (&a[f], &a[2*f+2]);
//			f = 2*f+2;
//		}
//		else 
//			f = last;
//}
//
//void HeapSort (recordtype a[], int n) {
//	int i;
//	for (i=(n-2)/2; i>=0; i--) {
//		PushDown (a, i, n-1);
//	}
//	for (i = n-1; i >= 2; i--) {
//		swap (&a[0], &a[i]);
//		PushDown (a, 0, i-1);
//	}
//	swap (&a[0], &a[1]);
//}
//int main () {
//	recordtype a[100];
//	int n;
//	ReadF (a, &n);
//	printf ("---Thuat toan HeapSort---\n");
//	printf ("Du lieu ban dau:\n");
//	PrintF (a,n);
//	HeapSort (a,n);
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
	recordtype t = *x;
	*x = *y;
	*y = t;
}

void readF (recordtype a[], int *n) {
	FILE *f = fopen ("data.txt", "r");
	int i=0; 
	if (f != NULL) 
		while (!feof(f)) {
			fscanf (f, "%d%f", &a[i].key, &a[i].otherfields);
			i++;
		}
	else 
		printf ("Loi mo file!");
	fclose (f);
	*n=i;
}

void printF (recordtype a[], int n) {
	int i; 
	for (i=n-1; i>=0; i--) 
		printf ("%5d%6.2f\n", a[i].key, a[i].otherfields);
}

void PushDown (recordtype a[], int first, int last) {
	int f = first;
	while (f <= (last-1)/2)
		if (last == 2*f+1) {
			if (a[f].key > a[last].key)
				swap (&a[f], &a[last]);
				f = last;
		}
		else if ((a[f].key > a[2*f+1].key) && (a[2*f+1].key <= a[2*f+2].key)) {
			swap (&a[f], &a[2*f+1]);
			f = 2*f+1;
		}
		else if ((a[f].key > a[2*f+2].key) && (a[2*f+2].key < a[2*f+1].key)) {
			swap (&a[f], &a[2*f+2]);
			f = 2*f+2;
		}
		else 
			f = last;
}


void HeapSort (recordtype a[], int n) {
	int i;
	for (i=(n-2)/2; i>=0; i--)
		PushDown (a, i, n-1);
	for (i=n-1; i>=2; i--) {
		swap (&a[0], &a[i]);
		PushDown (a, 0, i-1);
	}
	swap (&a[0], &a[1]);
}

int main () {
	recordtype a[100];
	int n;
	readF (a, &n);
	printF(a,n);
	printf ("-----------\n");
	HeapSort(a,n);
	printF(a,n);
	return 0;
}

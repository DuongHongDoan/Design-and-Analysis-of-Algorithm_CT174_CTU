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
//void BubbleSort (recordtype a[], int n) {
//	int i, j;
//	for (i=0; i<=n-2; i++) {
//		for (j=n-1; j>=i+1; j--) {
//			if (a[j].key < a[j-1].key)
//				swap (&a[j], &a[j-1]);
//		}
//	}
//}
//int main () {
//	recordtype a[100];
//	int n;
//	ReadF (a, &n);
//	printf ("---Thuat toan BubbleSort---\n");
//	printf ("Du lieu ban dau:\n");
//	PrintF (a,n);
//	BubbleSort (a,n);
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
	FILE *f = fopen ("data.txt", "r");
	int i=0;
	if (f != NULL) {
		while (!feof(f)) {
			fscanf (f, "%d%f", &a[i].key, &a[i].otherfields);
			i++;
		}
	}
	else printf ("loi");
	fclose (f);
	*n=i;
}

void in_F(recordtype a[], int n) {
	int i=0;
	for (; i<n; i++) {
		printf ("%5d%5.1f\n", a[i].key, a[i].otherfields);
	}
	printf ("-------------------------------------------------\n");
}

void sxnb (recordtype a[], int n) {
	int i, j;
	for (i=0; i<=n-2; i++) {
		for (j=n-1; j>=i+1; j--) {
			if (a[j].key < a[j-1].key)
				swap (&a[j], &a[j-1]);
		}
	}
}

int main () {
	recordtype a[100];
	int n;
	doc_F(a, &n);
	in_F(a, n);
	sxnb(a, n);
	in_F(a, n);
	return 0;
}

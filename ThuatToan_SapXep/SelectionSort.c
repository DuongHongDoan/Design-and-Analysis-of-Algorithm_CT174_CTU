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
//void SelectionSort (recordtype a[], int n) {
//	int i, j, lowindex;
//	keytype lowkey;
//	for (i=0; i<=n-2; i++) {
//		lowkey = a[i].key;
//		lowindex = i;
//		for (j=i+1; j<=n-1; j++) {
//			if (a[j].key < lowkey) {
//				lowkey = a[j].key;
//				lowindex = j;
//			}
//		}
//		swap (&a[i], &a[lowindex]);
//	}
//}
//int main () {
//	recordtype a[100];
//	int n;
//	ReadF (a, &n);
//	printf ("---Thuat toan SelectionSort---\n");
//	printf ("Du lieu ban dau:\n");
//	PrintF (a,n);
//	SelectionSort (a,n);
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
	else printf ("Loi");
	fclose (f);
	*n=i;
}

void in_F (recordtype a[], int n) {
	int i;
	for (i=0; i<n; i++) {
		printf ("%5d%5.1f\n", a[i].key, a[i].otherfields);
	}
	printf ("----------------------------------\n");
}

void sxchon (recordtype a[], int n) {
	int i, j, lowindex;
	keytype lowkey;
	for (i=0; i<=n-2; i++) {
		lowindex = i;
		lowkey = a[i].key;
		for (j=i+1; j<=n-1; j++) {
			if (a[j].key < lowkey) {
				lowindex = j;
				lowkey = a[j].key;
			}
		}
		swap (&a[i], &a[lowindex]);
	}
}

int main () {
	recordtype a[100];
	int n;
	doc_F (a, &n);
	in_F(a, n);
	sxchon(a, n);
	in_F (a, n);
	return 0;
}

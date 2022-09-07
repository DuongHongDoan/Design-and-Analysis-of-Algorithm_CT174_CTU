// Duong Hong Doan - B2013527
#include <stdio.h>

#define size 30
typedef struct {
	float do_dai;
	int dau, cuoi;
}canh;

void swap (canh *x, canh *y) {
	canh t = *x;
	*x = *y;
	*y = t;
}

void ReadF (canh a[], int *n) {
	int i, j, t;
	float temp;
	FILE *f;
	f = fopen("TSP.txt", "r");
	if (f==NULL) {
		printf ("Khong mo duoc file");
		return;
	}
	fscanf(f, "%d", n);
	int k=0;
	for (i=0; i<*n; i++) {
		for (j=i; j<*n; j++) {
			if (i==j) for (t=0; t<=j; t++) fscanf(f, "%f", &temp);
			else {
				fscanf (f, "%f", &a[k].do_dai);
				a[k].dau = i;
				a[k].cuoi = j;
				k++;
			}
		}
	}
	fclose(f);
}

void PrintCanh (canh a[], int m, int PA) {
	int i;
	float tong=0.0;
	for (i=0; i<m; i++) {
		printf ("%3d %c%c=%8.2f\n", i+1, a[i].dau+65, a[i].cuoi+65, a[i].do_dai);
		if(PA) 
			tong = tong + a[i].do_dai;
	}
	if (PA)
		printf ("Tong do dai cac canh la %.2f\n", tong);
}

void BubbleSort (canh a[], int m) {
	int i, j;
	for (i=0; i<m-1; i++) {
		for (j=m-1; j>i; j--) {
			if(a[j].do_dai < a[j-1].do_dai)
				swap(&a[j], &a[j-1]);
		}
	}
}

int dinh_cap3 (canh P_A[], int k, canh new) {
	int i=0, dem=1;
	while (i<k && dem<3) {
		if (new.dau == P_A[i].dau || new.dau == P_A[i].cuoi)
		dem++;
		i++;
	}
	if (dem==3)
		return 1;
	i=0;
	dem=1;
	while (i<k && dem<3) {
		if (new.cuoi == P_A[i].dau || new.cuoi == P_A[i].cuoi)
			dem++;
		i++;
	}
	return dem==3;
}

void init_forest (int parent[], int n) {
	int i;
	for (i=0; i<n; i++)
		parent[i] = i;
}

int find_root (int parent[], int u) {
	while (u != parent[u])
		u = parent[u];
	return u;
}

int chu_trinh (int r_dau, int r_cuoi) {
	return (r_dau == r_cuoi);
}

void update_forest (int parent[], int r1, int r2) {
	parent[r2] = r1;
}

void  Greedy (canh dscanh[], int n, canh P_A[]) {
	int i,j=0, parent[n], r_dau, r_cuoi; 
	init_forest(parent,n);
	for (i=0; i<n*(n-1)/2 && j<n-1; i++) {
		r_dau = find_root(parent, dscanh[i].dau);
		r_cuoi = find_root(parent, dscanh[i].cuoi);
		if (!dinh_cap3(P_A, j, dscanh[i]) && !chu_trinh(r_dau, r_cuoi)) {
			P_A[j]=dscanh[i];
			j++;
			update_forest(parent, r_dau, r_cuoi);
		}
	}
	
	for (; i<n*(n-1)/2; i++) {
		r_dau = find_root(parent, dscanh[i].dau);
		r_cuoi = find_root(parent, dscanh[i].cuoi);
		if (!dinh_cap3(P_A, n-1, dscanh[i])&& (chu_trinh(r_dau, r_cuoi))) {
			P_A[n-1]=dscanh[i];
			break;
		}
	}
}

int main () {
	canh dscanh[size];
	int n;
	ReadF(dscanh,&n);
	
	printf("Danh sach cac canh cua do thi\n");
	PrintCanh(dscanh,n*(n-1)/2, 0);
	
	BubbleSort(dscanh, n*(n-1)/2);
	printf("Danh sach do thi sau khi sap xep\n");
	PrintCanh(dscanh,n*(n-1)/2, 0);
	
	canh P_A[n];
	Greedy(dscanh, n, P_A);
	printf("Phuong an sau khi dung ki thuat tham an\n");
	PrintCanh(P_A,n,1);
	return 0;
}

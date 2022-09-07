//#include <stdio.h>
//#include <malloc.h>
//
//typedef struct {
//	char TenDV[20];
//	float TL, GT, DG;
//	int SL;
//}DoVat;
//
//void swap (DoVat *x, DoVat *y) {
//	DoVat t;
//	t = *x;
//	*x = *y;
//	*y = t;
//}
//
//DoVat *ReadF (float *W, int *n) {
//	FILE *f;
//	f = fopen("CaiBaLo1.txt", "r");
//	fscanf (f, "%f", W); //doc file f, so thuc vao bien W
//	DoVat *dsdv; // khai bao mang dong danh sach do vat (vi chua biet bao nhiu do vat)
//	dsdv = (DoVat*)malloc(sizeof(DoVat));
//	int i=0;
//	while (!feof(f)) {
//		fscanf(f, "%f%f%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].TenDV);
//		dsdv[i].DG = dsdv[i].GT/dsdv[i].TL;
//		dsdv[i].SL = 0;
//		i++;
//		dsdv = realloc(dsdv, sizeof(DoVat)*(i+1));
//	}
//	*n=i;
//	fclose(f);
//	return dsdv;
//}
//
//void PrintDV (DoVat *dsdv, int n, float W) {
//	int i;
//	float TongTL=0.0, TongGT=0.0;
//	printf ("Phuong an thu duoc sau khi dung ki thuat tham an: \n");
//	printf ("|STT|Ten Do Vat          |Trong Luong|Gia Tri|Don Gia|So Luong Do Vat Duoc Chon|\n");
//	for (i=0; i<n; i++) {
//		printf ("|%-3d|%-20s|%11.2f|%7.2f|%7.2f|%20d     |\n",
//		i+1, dsdv[i].TenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].DG, dsdv[i].SL);
//		TongTL = TongTL + dsdv[i].SL * dsdv[i].TL;
//		TongGT = TongGT + dsdv[i].SL * dsdv[i].GT;
//	}
//	printf ("\nTong trong luong la %-9.2f\nTong gia tri la %-9.2f\n", TongTL, TongGT);
//
//}
//
//void BubbleSort (DoVat *dsdv, int n) {
//	int i, j;
//	for (i=0; i<=n-2; i++) {
//		for (j=n-1; j>=i+1; j--) {
//			if(dsdv[j].DG > dsdv[j-1].DG)
//				swap(&dsdv[j], &dsdv[j-1]);
//		}
//	}
//}
//
//void  Greedy (DoVat *dsdv, int n, float W) {
//	int i; 
//	for (i=0; i<n; i++) {
//		dsdv[i].SL = (W/dsdv[i].TL);
//		W = W - dsdv[i].SL * dsdv[i].TL;
//	}
//}
//
//int main () {
//	int n;
//	float W;
//	DoVat *dsdv;
//	dsdv = ReadF(&W, &n);
//	BubbleSort (dsdv, n);
//	Greedy (dsdv, n, W);
//	PrintDV(dsdv, n, W);
//	free(dsdv);
//	return 0;
//}

#include <stdio.h>
#include <malloc.h>

typedef struct {
	char tendv[50];
	float tl, gt, dg;
	int sl;
}dv;

void swap (dv *x, dv *y) {
	dv t;
	t = *x;
	*x = *y;
	*y = t;
}

dv *doc_F (float *w, int *n) {
	FILE *f = fopen ("CaiBaLo3.txt", "r");
	fscanf (f, "%f", w);
	dv *ds = (dv*)malloc(sizeof(dv));
	int i=0;
	while (!feof(f)) {
		fscanf (f, "%f%f%[^\n]", &ds[i].tl, &ds[i].gt, &ds[i].tendv);
		ds[i].dg = ds[i].gt/ds[i].tl;
		ds[i].sl = 0;
		i++;
		ds = realloc(ds, sizeof(dv)*(i+1));
	}
	*n=i;
	fclose (f);
	return ds;
}

void in_ds (dv *ds, float w, int n) {
	int i;
	float ttl=0.0, tgt=0.0;
	printf ("Phuong an thu duoc sau khi dung ki thuat tham an: \n");
	printf ("|STT|Ten Do Vat          |Trong Luong|Gia Tri|Don Gia|So Luong Do Vat Duoc Chon|\n");
	for (i=0; i<n; i++) {
		printf ("|%-3d|%-20s|%11.2f|%7.2f|%7.2f|%20d     |\n", i+1, ds[i].tendv, ds[i].tl, ds[i].gt, ds[i].dg, ds[i].sl);
		ttl += ds[i].sl * ds[i].tl;
		tgt += ds[i].sl * ds[i].gt;
	}
	printf ("---------------------------------------------------------------------------------\n");
	printf ("Phuong an theo don gia giam = X(");
	for (i=0; i<n-1; i++) {
		printf ("%d, ", ds[i].sl);
	}
	printf ("%d)\n", ds[n-1].sl);
	printf ("TTL = %.2f\nTGT = %.2f",ttl, tgt);
}

void sxnb (dv *ds, int n) {
	int i=0, j;
	for (; i<=n-2; i++) {
		for (j=n-1; j>=i+1; j--) {
			if (ds[j].dg > ds[j-1].dg)
				swap (&ds[j], &ds[j-1]);
		}
	}
}

void ta (dv *ds, float w, int n) {
	int i;
	for (i=0; i<n; i++) {
		ds[i].sl = w / ds[i].tl;
		if (ds[i].sl > 1)
			ds[i].sl = 1;
		w -= ds[i].sl*ds[i].tl;
	}
}

int main () {
	int n;
	float w;
	dv *ds = doc_F (&w, &n);
	sxnb (ds, n);
	ta(ds, w, n);
	in_ds(ds, w, n);
	free(ds);
	return 0;
}

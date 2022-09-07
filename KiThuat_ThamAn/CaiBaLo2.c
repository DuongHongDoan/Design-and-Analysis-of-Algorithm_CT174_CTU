#include <stdio.h>
#include <malloc.h>

typedef struct {
	char TenDV[20];
	float TL, GT, DG;
	int SL, DV_Max;
}DoVat;

void swap (DoVat *x, DoVat *y) {
	DoVat t;
	t = *x;
	*x = *y;
	*y = t;
}

DoVat *ReadF (float *W, int *n) {
	FILE *f;
	f = fopen("CaiBaLo2.txt", "r");
	fscanf (f, "%f", W); //doc file f, so thuc vao bien W
	DoVat *dsdv; // khai bao mang dong danh sach do vat (vi chua biet bao nhiu do vat)
	dsdv = (DoVat*)malloc(sizeof(DoVat));
	int i=0;
	while (!feof(f)) {
		fscanf(f, "%f%f%d%[^\n]", &dsdv[i].TL, &dsdv[i].GT,&dsdv[i].DV_Max, &dsdv[i].TenDV);
		dsdv[i].DG = dsdv[i].GT/dsdv[i].TL;
		dsdv[i].SL = 0;
		i++;
		dsdv = realloc(dsdv, sizeof(DoVat)*(i+1));
	}
	*n=i;
	fclose(f);
	return dsdv;
}

void PrintDV (DoVat *dsdv, int n, float W) {
	int i;
	float TongTL=0.0, TongGT=0.0;
	printf ("Phuong an thu duoc sau khi dung ki thuat tham an: \n");
	printf ("|STT|Ten Do Vat          |Trong Luong|Gia Tri|So Luong Max|Don Gia|So Luong Do Vat Duoc Chon|\n");
	for (i=0; i<n; i++) {
		printf ("|%-3d|%-20s|%11.2f|%7.2f|%12d|%7.2f|%20d     |\n",
		i+1, dsdv[i].TenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].DV_Max, dsdv[i].DG, dsdv[i].SL);
		TongTL = TongTL + dsdv[i].SL * dsdv[i].TL;
		TongGT = TongGT + dsdv[i].SL * dsdv[i].GT;
	}
	printf ("\nTong trong luong la %-9.2f\nTong gia tri la %-9.2f\n", TongTL, TongGT);

}

void BubbleSort (DoVat *dsdv, int n) {
	int i, j;
	for (i=0; i<=n-2; i++) {
		for (j=n-1; j>=i+1; j--) {
			if(dsdv[j].DG > dsdv[j-1].DG)
				swap(&dsdv[j], &dsdv[j-1]);
		}
	}
}

void  Greedy (DoVat *dsdv, int n, float W) {
	int i; 
	for (i=0; i<n; i++) {
		dsdv[i].SL = (W/dsdv[i].TL);
		if (dsdv[i].SL > dsdv[i].DV_Max)
			dsdv[i].SL = dsdv[i].DV_Max;
			W = W - dsdv[i].SL * dsdv[i].TL;
	}
}

int main () {
	int n;
	float W;
	DoVat *dsdv;
	dsdv = ReadF(&W, &n);
	BubbleSort (dsdv, n);
	Greedy (dsdv, n, W);
	PrintDV(dsdv, n, W);
	free(dsdv);
	return 0;
}

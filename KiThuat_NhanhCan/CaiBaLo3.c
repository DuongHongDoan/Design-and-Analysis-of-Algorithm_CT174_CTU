#include <stdio.h>
#include <malloc.h>

typedef struct {
	char TenDV[20];
	float TL, GT, DG;
	int SL;
}DoVat;

void swap (DoVat *x, DoVat *y) {
	DoVat t;
	t = *x;
	*x = *y;
	*y = t;
}

DoVat *ReadF (float *W, int *n) {
	FILE *f;
	f = fopen("CaiBaLo3.txt", "r");
	fscanf (f, "%f", W); //doc file f, so thuc vao bien W
	DoVat *dsdv; // khai bao mang dong danh sach do vat (vi chua biet bao nhiu do vat)
	dsdv = (DoVat*)malloc(sizeof(DoVat));
	int i=0;
	while (!feof(f)) {
		fscanf(f, "%f%f%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].TenDV);
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
	printf ("|STT|Ten Do Vat          |Trong Luong|Gia Tri|Don Gia|So Luong Do Vat Duoc Chon|\n");
	for (i=0; i<n; i++) {
		printf ("|%-3d|%-20s|%11.2f|%7.2f|%7.2f|%20d     |\n",
		i+1, dsdv[i].TenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].DG, dsdv[i].SL);
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

void tao_nut_goc (float W, float *TL_conlai, float *CT, float *GLNTT, float *TGT, float DG_max) {
	*TL_conlai = W;
	*CT = *TL_conlai*DG_max;
	*GLNTT=0.0;
}

void cap_nhat_PA_best (float TGT, float *GLNTT, int x[], DoVat *dsdv, int n) {
	int i;
	if (*GLNTT<TGT) {
		*GLNTT=TGT; 
		for(i=0; i<n; i++) {
			dsdv[i].SL = x[i];
		}
	}
}

int min (int a, int b) {
	return a<b ? a : b;
}

void  nhanh_can (int i, float *TGT, float *CT, float *TL_conlai, float *GLNTT, int x[], DoVat *dsdv, int n) {
	int j; //so do vat dc chon
	int DV_choosed = min(1, *TL_conlai/dsdv[i].TL);
	for (j=DV_choosed; j>=0; j--) {
		*TGT = *TGT + j*dsdv[i].GT;
		*TL_conlai = *TL_conlai - j*dsdv[i].TL;
		*CT = *TGT + *TL_conlai*dsdv[i+1].DG;
		if (*CT > *GLNTT) {
			x[i]=j;
			if ((i==n-1) || (*TL_conlai==0.0))
				cap_nhat_PA_best(*TGT, GLNTT, x, dsdv, n);
			else 
				nhanh_can(i+1, TGT, CT, TL_conlai, GLNTT, x, dsdv, n);
		}
		x[i]=0;
		*TGT = *TGT - j*dsdv[i].GT;
		*TL_conlai = *TL_conlai + j*dsdv[i].TL;
	}
}

int main () {
	int n;
	float W;
	DoVat *dsdv;
	float CT, TGT, TL_conlai, GLNTT;
	dsdv = ReadF(&W, &n);
	int x[n]; //luu phuong an tot nhat tam thoi 
	BubbleSort (dsdv, n);
	tao_nut_goc(W, &TL_conlai, &CT, &GLNTT, &TGT, dsdv[0].DG);
	nhanh_can(0, &TGT, &CT, &TL_conlai, &GLNTT, x, dsdv,n);
	PrintDV(dsdv, n, W);
	free(dsdv);
	return 0;
}

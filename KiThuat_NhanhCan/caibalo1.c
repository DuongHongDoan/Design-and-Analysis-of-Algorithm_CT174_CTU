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
//void tao_nut_goc (float W, float *TL_conlai, float *CT, float *GLNTT, float *TGT, float DG_max) {
//	*TL_conlai = W;
//	*CT = *TL_conlai*DG_max;
//	*GLNTT=0.0;
//}
//
//void cap_nhat_PA_best (float TGT, float *GLNTT, int x[], DoVat *dsdv, int n) {
//	int i;
//	if (*GLNTT<TGT) {
//		*GLNTT=TGT; 
//		for(i=0; i<n; i++) {
//			dsdv[i].SL = x[i];
//		}
//	}
//}
//
////int min (int a, int b) {
////	return a<b ? a : b;
////}
//
//void  nhanh_can (int i, float *TGT, float *CT, float *TL_conlai, float *GLNTT, int x[], DoVat *dsdv, int n) {
//	int j; //so do vat dc chon
//	int DV_choosed = *TL_conlai/dsdv[i].TL;
//	for (j=DV_choosed; j>=0; j--) {
//		*TGT = *TGT + j*dsdv[i].GT;
//		*TL_conlai = *TL_conlai - j*dsdv[i].TL;
//		*CT = *TGT + *TL_conlai*dsdv[i+1].DG;
//		if (*CT > *GLNTT) {
//			x[i]=j;
//			if ((i==n-1) || (*TL_conlai==0.0))
//				cap_nhat_PA_best(*TGT, GLNTT, x, dsdv, n);
//			else 
//				nhanh_can(i+1, TGT, CT, TL_conlai, GLNTT, x, dsdv, n);
//		}
//		x[i]=0;
//		*TGT = *TGT - j*dsdv[i].GT;
//		*TL_conlai = *TL_conlai + j*dsdv[i].TL;
//	}
//}
//
//int main () {
//	int n;
//	float W;
//	DoVat *dsdv;
//	float CT, TGT, TL_conlai, GLNTT;
//	dsdv = ReadF(&W, &n);
//	int x[n]; //luu phuong an tot nhat tam thoi 
//	BubbleSort (dsdv, n);
//	tao_nut_goc(W, &TL_conlai, &CT, &GLNTT, &TGT, dsdv[0].DG);
//	nhanh_can(0, &TGT, &CT, &TL_conlai, &GLNTT, x, dsdv,n);
//	PrintDV(dsdv, n, W);
//	free(dsdv);
//	return 0;
//}

#include <stdio.h>
#include <malloc.h>

typedef struct {
	char tendv[50];
	int sl;
	float tl, gt, dg;
}dv;

void swap (dv *x, dv *y) {
	dv t;
	t = *x;
	*x = *y;
	*y = t;
}

dv *doc (float *w, int *n) {
	FILE *f = fopen ("CaiBaLo3.txt", "r");
	dv *ds = (dv*)malloc(sizeof(dv));
	fscanf (f, "%f", w);
	int i=0; 
	while (!feof(f)) {
		fscanf (f, "%f%f%[^\n]", &ds[i].tl, &ds[i].gt, &ds[i].tendv);
		ds[i].dg = ds[i].gt/ds[i].tl;
		ds[i].sl= 0;
		i++;
		ds = realloc(ds, sizeof(dv)*(i+1));
	}
	*n=i;
	fclose (f);
	return ds;
}

void in (dv *ds, int n, float w) {
	int i;
	float ttl=0.0;
	float tgt=0.0;
	printf ("------------------------------------------------------\n");
	printf ("|STT|Ten Do Vat          |Trong Luong|Gia Tri|Don Gia|So Luong Do Vat Duoc Chon|\n");
	for (i=0; i<n; i++) {
		printf ("|%-3d|%-20s|%11.2f|%7.2f|%7.2f|%20d     |\n", i+1, ds[i].tendv, ds[i].tl, ds[i].gt, ds[i].dg, ds[i].sl);
		ttl += ds[i].sl * ds[i].tl;
		tgt += ds[i].sl * ds[i].gt;
	}
	printf ("------------------------------------------------------\n");
	printf ("PA = X(");
	for (i=0; i<n-1; i++) {
		printf ("%d, ", ds[i].sl);
	}
	printf ("%d)\n", ds[n-1].sl);
	printf ("TTL = %.2f\nTGT = %.2f", ttl, tgt);
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

void taonutgoc (float w, float *tgt, float *ct, float *glntt, float *wconlai, float dgmax) {
	*wconlai = w;
	*ct = *wconlai * dgmax;
	*glntt = 0.0;
}
//void tao_nut_goc (float W, float *TL_conlai, float *CT, float *GLNTT, float *TGT, float DG_max) {
//	*TL_conlai = W;
//	*CT = *TL_conlai*DG_max;
//	*GLNTT=0.0;
//}

void capnhatpabest (float tgt, float *glntt, int x[], dv *ds, int n) {
	int i=0;
	if (*glntt < tgt) {
		*glntt = tgt;
		for (; i<n; i++) {
			ds[i].sl = x[i];
		}
	}
}
//
//void cap_nhat_PA_best (float TGT, float *GLNTT, int x[], DoVat *dsdv, int n) {
//	int i;
//	if (*GLNTT<TGT) {
//		*GLNTT=TGT; 
//		for(i=0; i<n; i++) {
//			dsdv[i].SL = x[i];
//		}
//	}
//}
//

int min (int a, int b) {
	return (a<b) ? a : b;
}
void nhanhcan (int i, float *tgt, float *ct, float *glntt, float *wconlai, dv *ds, int x[], int n) {
	int j;
	int dvchoosed = min(*wconlai / ds[i].tl, 1);
	for (j=dvchoosed; j>=0; j--) {
		*tgt += j*ds[i].gt;
		*wconlai -= j*ds[i].tl;
		*ct = *tgt + *wconlai * ds[i+1].dg;
		if (*ct > *glntt) {
			x[i]=j;
			if ((i==n-1) || (*wconlai==0.0))
				capnhatpabest(*tgt, glntt, x, ds, n);
			else nhanhcan (i+1, tgt, ct, glntt, wconlai, ds, x, n);
		}
		x[i]=0;
		*tgt -= j*ds[i].gt;
		*wconlai += j*ds[i].tl;
	}
}
//void  nhanh_can (int i, float *TGT, float *CT, float *TL_conlai, float *GLNTT, int x[], DoVat *dsdv, int n) {
//	int j; //so do vat dc chon
//	int DV_choosed = *TL_conlai/dsdv[i].TL;
//	for (j=DV_choosed; j>=0; j--) {
//		*TGT = *TGT + j*dsdv[i].GT;
//		*TL_conlai = *TL_conlai - j*dsdv[i].TL;
//		*CT = *TGT + *TL_conlai*dsdv[i+1].DG;
//		if (*CT > *GLNTT) {
//			x[i]=j;
//			if ((i==n-1) || (*TL_conlai==0.0))
//				cap_nhat_PA_best(*TGT, GLNTT, x, dsdv, n);
//			else 
//				nhanh_can(i+1, TGT, CT, TL_conlai, GLNTT, x, dsdv, n);
//		}
//		x[i]=0;
//		*TGT = *TGT - j*dsdv[i].GT;
//		*TL_conlai = *TL_conlai + j*dsdv[i].TL;
//	}
//}

int main () {
	float w, tgt, ct, glntt, wconlai;
	int n;
	dv *ds = doc(&w, &n);
	int x[n];
	sxnb(ds, n);
	taonutgoc(w, &tgt, &ct, &glntt, &wconlai, ds[0].dg);
	nhanhcan(0, &tgt, &ct, &glntt, &wconlai, ds, x, n);
	in(ds, n, w);
	free(ds);
	return 0;
}

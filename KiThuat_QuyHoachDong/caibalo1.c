////Duong Hong Doan - B2013527
//
//// Bai toan cai ba lo 1
//// Moi do vat co so luong khong han che
//// Du lieu cho trong file QHD_CaiBalo.INP
//// Giai bai toan bang thuat toan QUY HOACH DONG
//
//#include <stdio.h>
//#include <malloc.h>
//#include <string.h>
//
//typedef struct {
//	char TenDV[20];
//	int TL, GT, PA;
//} DoVat;
//
//typedef int bang[50][100];// Ba lo co trong luong toi da 99 va co toi da 50 do vat
//
//DoVat *ReadFromFile(int *W, int *n){
//     FILE *f;
//     f = fopen("caibalo1.txt", "r");
//     fscanf(f, "%d",W); // Xac dinh trong luong Ba lo
//	 DoVat *dsdv;
//	 dsdv=(DoVat*)malloc(sizeof(DoVat));
//	 int i=0;
// 	 while (!feof(f)){
//	   fscanf(f, "%d%d%[^\n]",&dsdv[i].TL,&dsdv[i].GT,&dsdv[i].TenDV);
//	   dsdv[i].PA=0;
//	   i++;
//	   dsdv=realloc(dsdv,sizeof(DoVat)*(i+1));  
//	 }
//	 *n=i;
//     fclose(f);
//     return dsdv;
//}
//
//void InDSDV(DoVat *dsdv ,int n, int W){
//	int i, TongTL=0, TongGT=0;
//	printf("\nPhuong an Cai Ba lo 1 dung thuat toan QUY HOACH DONG nhu sau:\n");
//		printf("|---|------------------|----------|---------|-----------|\n");
//		printf("|STT|     Ten Do Vat   | T Luong  | Gia Tri | Phuong an |\n");
//		printf("|---|------------------|----------|---------|-----------|\n");
//	for(i=0;i<n;i++){
//		printf("|%2d |%-18s|%5d     |%5d    |%6d     |\n",
//		i+1,dsdv[i].TenDV,dsdv[i].TL,dsdv[i].GT,dsdv[i].PA);
//		TongTL=TongTL+dsdv[i].PA * dsdv[i].TL;
//		TongGT=TongGT+dsdv[i].PA * dsdv[i].GT;
//	}	
//	printf("|---|------------------|----------|---------|-----------|\n");	
//	printf("Trong luong cua ba lo = %-9d\n",W);
//	printf("Tong trong luong = %-9d\n",TongTL);
//	printf("Tong gia tri = %-9d\n",TongGT);
//}
//
//void TaoBang(DoVat *dsdv,int n,int W, bang F,bang X){
// 	int xk, yk, k;
// 	int FMax, XMax, V;
//	
//	// Dien dong dau tien cua hai bang
// 	for(V= 0; V<=W; V++) {
// 		X[0][V] = V/dsdv[0].TL;
// 		F[0][V] = X[0][V] * dsdv[0].GT;
// 	}
//	
//	// ?ien c?c d?ng c?n lai
//	 for(k= 1; k<n; k++)
//		 for(V=0; V<=W; V++) {
//			 FMax = F[k-1][V] ;
//			 XMax = 0;
//			 yk = V/dsdv[k].TL;
//			 for(xk = 1; xk<=yk; xk++)
//			 	if(F[k-1][V-xk*dsdv[k].TL]+xk*dsdv[k].GT>FMax){
//			 		FMax=F[k-1][V-xk*dsdv[k].TL]+xk*dsdv[k].GT;
//			 		XMax= xk;
//			 		}
//			 F[k][V] = FMax;
//			 X[k][V] = XMax;
//	 	}
//}
//
//void InBang(int n, int W, bang F, bang X){
//	int V, k;
//	for(k=0; k<n; k++){
//		for(V=0; V<=W; V++)
//		 	printf("|%4d%2d",F[k][V], X[k][V]);
//		printf("\n");
//	}
//}
//
//void TraBang(DoVat *dsdv, int n, int W, bang X) {
//	int k, V;
//	V = W;
//	for(k= n-1; k>=0; k--) {
//	 	dsdv[k].PA = X[k][V];
//	 	V = V - X[k][V] * dsdv[k].TL;
//	}
//}
//
//int main(){
//	int n, W;
//	bang X,F;
//	DoVat *dsdv;
//	dsdv=ReadFromFile(&W, &n);
//	
//	TaoBang(dsdv,n,W,F,X);
//	InBang(n,W,F,X);
//	printf("\n");
//	TraBang(dsdv,n,W,X);
//	InDSDV(dsdv,n,W);
//	
//	free(dsdv);
//	return 0;
//}

#include <stdio.h>
#include <malloc.h>

typedef struct {
	char tendv[50];
	int dvmax, tl, gt, sl;
}dv;

typedef int bang[50][100];

dv *doc (int *n, int *w) {
	FILE *f = fopen ("caibalo2.txt", "r");
	dv *ds = (dv*)malloc(sizeof(dv));
	fscanf (f, "%d", w);
	int i=0;
	while (!feof(f)) {
		fscanf (f, "%d%d%d%[^\n]", &ds[i].tl, &ds[i].gt, &ds[i].dvmax, &ds[i].tendv);
		ds[i].sl = 0;
		i++;
		ds = realloc(ds, sizeof(dv)*(i+1));
	}
	*n=i;
	fclose(f);
	return ds;
}

void in (dv *ds, int n, int w) {
	int i, TongTL=0, TongGT=0;
	printf("\nPhuong an Cai Ba lo 1 dung thuat toan QUY HOACH DONG nhu sau:\n");
		printf("|---|------------------|----------|---------|-----------|\n");
		printf("|STT|     Ten Do Vat   | T Luong  | Gia Tri | dv max    | Phuong an |\n");
		printf("|---|------------------|----------|---------|-----------|-----------|\n");
	for(i=0;i<n;i++){
		printf("|%2d |%-18s|%5d     |%5d    |%6d     |%6d     |\n",
		i+1,ds[i].tendv,ds[i].tl,ds[i].gt, ds[i].dvmax, ds[i].sl);
		TongTL=TongTL+ds[i].sl * ds[i].tl;
		TongGT=TongGT+ds[i].sl * ds[i].gt;
	}	
	printf("|---|------------------|----------|---------|-----------|-----------|\n");	
	printf("Trong luong cua ba lo = %-9d\n",w);
	printf("Tong trong luong = %-9d\n",TongTL);
	printf("Tong gia tri = %-9d\n",TongGT);
}

void taobang (dv *ds, int n, int w, bang F, bang X) {
	int xk, yk, k, fmax, xmax, v;
	for (v=0; v<=w; v++) {
		X[0][v] = v/ds[0].tl;
		F[0][v] = X[0][v] * ds[0].gt;
	}
	
	for (k=1; k<n; k++) {
		for (v=0; v<=w; v++) {
			fmax = F[k-1][v];
			xmax = 0;
			yk = v/ds[k].tl;
			for (xk=1; xk<=yk; xk++) {
				if (F[k-1][v-xk*ds[k].tl]+xk*ds[k].gt > fmax) {
					fmax = F[k-1][v-xk*ds[k].tl]+xk*ds[k].gt;
					xmax = xk;
				}
			}
			F[k][v]=fmax;
			X[k][v]=xmax;
		}
	}
}

void inbang (int n, int w, bang F, bang X) {
	int v, k;
	for (k=0; k<n; k++) {
		for (v=0; v<=w; v++) {
			printf ("|%4d%2d", F[k][v], X[k][v]);
		}
		printf ("\n");
	}
}

int min (int a, int b) {
	return (a<b) ?a : b;
}

void trabang (dv *ds, int n, int w, bang X) {
	int k, v=w;
	for (k=n-1; k>=0; k--) {
		ds[k].sl = min(X[k][v], ds[k].dvmax);
		v -= ds[k].sl*ds[k].tl;
	}
}

int main () {
	int n, w;
	bang F, X;
	dv *ds = doc(&n, &w);
	taobang(ds, n, w, F, X);
	inbang(n, w, F, X);
	trabang(ds, n, w, X);
	in(ds, n, w);
	free(ds);
	return 0;
}

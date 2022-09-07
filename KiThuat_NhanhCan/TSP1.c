//#include <stdio.h>
//
//#define size 30
//typedef struct {
//	float do_dai;
//	int dau, cuoi, canh_da_dung;
//}canh;
//
//void ReadF (canh a[][size], int *n) {
//	int i, j;
//	FILE *f;
//	f = fopen("TSP1.txt" , "r");
//	fscanf(f, "%d", n);
//	if (f==NULL) {
//		printf ("Khong mo duoc file");
//		return;
//	}
//	for (i=0; i<*n; i++) {
//		for (j=0; j<*n; j++) {
//			fscanf(f, "%f", &a[i][j].do_dai);
//			a[i][j].dau = i;
//			a[i][j].cuoi = j;
//			a[i][j].canh_da_dung = 0;
//		}
//	}
//	fclose(f);
//}

#include <stdio.h>

#define size 30

typedef struct {
	float dodai;
	int dau, cuoi, canhused;
}canh;

void doc_F (canh a[][size], int *n) {
	int i, j;
	FILE *f = fopen ("TSP1.txt", "r");
	fscanf (f, "%d", n);
	if (f == NULL) {
		printf ("Loi");
		return;
	}
	for (i=0; i<*n; ii++) {
		for (j=0; j<*n; j++) {
			fscanf (f, "%f", &a[i][j].dodai);
			a[i][j].dau = i;
			a[i][j].cuoi = j;
			a[i][j].canhused = 0;
		}
	}
	fclose(f);
}

//void PrintCanh (canh a[][size], int n) {
//	int i,j;
//	printf ("Ma tran trong so cua do thi la \n");
//	for (i=0; i<n; i++) {
//		for (j=0; j<n; j++) {
//			printf ("  %c%c=%8.2f", a[i][j].dau+65, a[i][j].cuoi+65, a[i][j].do_dai);
//		}
//		printf ("\n");
//	}
//}

void in_dothi (canh a[][size], int n) {
	int i, j;
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			printf (" %c%c = %8.2f", a[i][j].dau+65, a[i][j].cuoi+65, a[i][j].dodai);
		}
		
		printf ("\n");
	}
}

//void in_PA (canh PA[], int n) {
//	int i;
//	float tong = 0.0;
//	printf ("Phuong an tim duoc:\n");
//	for (i=0; i<n; i++) {
//		tong = tong + PA[i].do_dai;
//		printf ("canh %c%c = %8.2f\n", PA[i].dau + 65, PA[i].cuoi + 65, PA[i].do_dai);
//	}
//	printf ("Tong do dai cac canh trong chu trinh la %.2f", tong);
//}

void inpa(canh pa[], int n) {
	int i;
	float sum = 0.0;
	printf ("Phuong an tim dc la: \n");
	for (i=0; i<n; i++) {
		printf ("canh %c%c = %8.2f\n", pa[i].dau+65, pa[i].cuoi+65, pa[i].dodai);
	}
	
	printf ("Tong do dai cac canh trong chu trinh = %.2f", sum);
}
float canh_min (canh a[][size], int n) {
	float Cmin = 3.40282e+38;
	int i, j;
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			if (i!=j && !a[i][j].canh_da_dung && a[i][j].do_dai < Cmin)
				Cmin = a[i][j].do_dai;
		}
	}
	return Cmin;
}

float can_duoi (canh a[][size], float TGT, int n, int i) {
	return TGT + (n-i)*canh_min(a,n);
}

void cap_nhat_PA_best (canh a[][size], int n, float TGT, float *GNNTT, canh x[], canh PA[]) {
	int i;
	x[n-1] = a[x[n-2].cuoi][x[0].dau]; //noi dinh cuoi cua x[n-2] voi dinh dau cua x[0] -> tao chu trinh
	TGT = TGT + x[n-1].do_dai;
	if (*GNNTT > TGT) {
		*GNNTT = TGT;
		for (i=0; i<n; i++)
			PA[i] = x[i];
	}
}

int co_chu_trinh (canh x[], int k, int canh_next) {
	int i=0, co_CT=0;
	while (i<k && !co_CT) {
		if (canh_next == x[i].dau)
			co_CT=1;
		else i++;
	}
	return co_CT;
}

void nhanh_can (canh a[][size], int n, int i, int dau, float *TGT, float *CD, float *GNNTT, canh x[], canh PA[]) {
	int j; //j la dinh ke tiep
	for (j=0; j<n; j++) {
		if (dau!=j && !a[dau][j].canh_da_dung && !co_chu_trinh(x, i, j)) {
			*TGT = *TGT + a[dau][j].do_dai;
			*CD = can_duoi(a, *TGT, n, i+1);
			if (*CD < *GNNTT) {
				x[i] = a[dau][j];
				a[dau][j].canh_da_dung = 1;
				a[j][dau].canh_da_dung = 1;
				if (i==n-2) {
					cap_nhat_PA_best (a,n,*TGT, GNNTT, x, PA);
				}
				else 
					nhanh_can (a,n,i+1,j,TGT,CD,GNNTT,x,PA);
			}
			*TGT =*TGT - a[dau][j].do_dai;
			a[dau][j].canh_da_dung = 0;
			a[j][dau].canh_da_dung = 0;
		}
	}
}

void reset (canh a[][size], int n) {
	int i, j;
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			a[i][j].canh_da_dung=0;
		}
	}
}

int main () {
	canh a[size][size];
	int n;
	ReadF (a, &n);
	canh PA[n];
	canh x[n];
	char tpxp, yn;
	while (1) {
		fflush(stdin);
		PrintCanh(a,n);
		float TGT=0.0, CD=0.0, GNNTT=3.40282e+38;
		printf ("\nXuat phat tu thanh pho nao? (1 trong cac thanh pho tu A den %c)", n-1+65);
		scanf ("%c", &tpxp);
		if (tpxp>=97)
			tpxp = tpxp - 32;
		nhanh_can (a,n,0,tpxp-65,&TGT, &CD, &GNNTT,x, PA);
		in_PA(PA,n);
		fflush(stdin);
		printf("\nTiep tuc Y/N?");
		scanf ("%c", &yn);
		if (yn == 'N' || yn == 'n')
			break;
		reset(a,n);
	}
	return 0;
}

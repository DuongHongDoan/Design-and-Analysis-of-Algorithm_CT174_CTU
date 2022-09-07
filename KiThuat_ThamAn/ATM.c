// Duong Hong Doan - B2013527
#include <stdio.h>
#include <malloc.h>

typedef struct {
	char TienChu[50];
	int SoToTien, TienSo;
}Tien;

void swap (Tien *x, Tien *y) {
	Tien t = *x;
	*x = *y;
	*y = t;
}

Tien *ReadF (int *t, int *n) {
	FILE *f;
	f = fopen("ATM.txt", "r");
	Tien *dstien; // khai bao mang dong danh sach tien (vi chua biet bao nhiu tien)
	dstien = (Tien*)malloc(sizeof(Tien));
	int i=0;
	while (!feof(f)) {
		fscanf(f, "%d%[^\n]", &dstien[i].TienSo, &dstien[i].TienChu);
		dstien[i].SoToTien = 0;
		i++;
		dstien = realloc(dstien, sizeof(Tien)*(i+1));
	}
	*n=i;
	fclose(f);
	return dstien;
}

void PrintT (Tien *dstien, int n, int t) {
	int i;
	int TongToTien=0, TongSoTien=0, TienDu;
	printf ("Phuong an thu duoc sau khi dung ki thuat tham an: \n");
	printf ("|STT|Tien bang chu       |Tien bang so|So To  |\n");
	for (i=0; i<n; i++) {
		if (dstien[i].SoToTien > 0) {
			printf ("|%-3d|%-20s|%-12d|%-7d|\n",
			i+1, dstien[i].TienChu, dstien[i].TienSo, dstien[i].SoToTien);
			TongToTien = TongToTien + dstien[i].SoToTien;
			TongSoTien = TongSoTien + dstien[i].SoToTien * dstien[i].TienSo;
			TienDu = t - TongSoTien;
		}
	}
	printf ("So to tien phai tra la %d to\n", TongToTien);
	printf ("So tien phai tra la %d\n", TongSoTien);
	printf ("So tien du khong the rut la %d", TienDu);
}

void BubbleSort (Tien *dstien, int n) {
	int i, j;
	for (i=0; i<=n-2; i++) {
		for (j=n-1; j>=i+1; j--) {
			if(dstien[j].TienSo > dstien[j-1].TienSo)
				swap(&dstien[j], &dstien[j-1]);
		}
	}
}

void  Greedy (Tien *dstien, int n, int t) {
	int i; 
	for (i=0; i<n; i++) {
		dstien[i].SoToTien = (t/dstien[i].TienSo);
		t = t - dstien[i].SoToTien * dstien[i].TienSo;
	}
}

int main () {
	int n, t;
	scanf("%d",&t);
	Tien *dstien;
	dstien = ReadF(&t, &n);
	BubbleSort (dstien, n);
	Greedy (dstien, n, t);
	PrintT(dstien, n, t);
	free(dstien);
	return 0;
}

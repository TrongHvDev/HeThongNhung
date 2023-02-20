// user nhap toa do 3 dinh tam giac, tinh dien tich va xuat gia tri ra man hinh
#include <stdio.h>
#include <math.h>
struct point{
    int x;
    int y;
};
struct triangle{
    float a;
    float b;
    float c;
    float s;
    float area;
};
struct triangle tr;
struct point pt1,pt2,pt3,pt4,pt5;
int main(void){
    printf("Nhap toa do dinh A: \n");
    scanf("%d %d",&pt1.x, &pt1.y);

    printf("Nhap toa do dinh B: \n");
    scanf("%d %d",&pt2.x, &pt2.y);

    printf("Nhap toa do dinh C: \n");
    scanf("%d %d",&pt3.x, &pt3.y);

    tr.a = sqrt(pow(pt1.x-pt2.x,2)+pow(pt1.y-pt2.y,2));
    tr.b = sqrt(pow(pt3.x-pt2.x,2)+pow(pt3.y-pt2.y,2));
    tr.a = sqrt(pow(pt1.x-pt3.x,2)+pow(pt1.y-pt3.y,2));
    tr.s = 0.5*(tr.a+tr.b+tr.c);
    tr.area = sqrt(tr.s*(tr.s-tr.a)*(tr.s-tr.b)*(tr.s-tr.c));

    printf("Dien tich cua tam giac la: %.2f \n",tr.area);

    return 0;
}

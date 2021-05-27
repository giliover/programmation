#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

typedef struct PointVector {
    float x, y, a;
} VPoint;

VPoint *initPointVector(int n) {
    VPoint* v = (VPoint *) malloc(n * sizeof(VPoint));

    if (v == NULL) {
        printf("Alocation eroor\n");
        exit(1);
    }
    return v;
}

void freePointVector(VPoint *polygon, VPoint *polCentr) {
    free(polygon);
    free(polCentr);
}

void initValues(int n, VPoint *v) {
    int i;
    srand(time(NULL));
    for (i = 0; i < n; i++) {
        v[i].x = 50 - (rand() % 100);
        v[i].y = 50 - (rand() % 100);
    }
}

void printVector(int n, VPoint *v) {
    int i;
    for (i = 0; i < n; i++) {
        printf("Point %d: (%.lf,%.lf)\n", i + 1, v[i].x, v[i].y);
    }

    printf("\n");
}

VPoint *centroidVector(int n, VPoint *v)
{
    VPoint *cent;
    int cx = 0, cy = 0, i;
    cent = (VPoint *) malloc(n * sizeof(VPoint));

    for (i = 0; i < n; i++) {
        cx += (v[i].x);
        cy += (v[i].y);
    }
    cx = round(cx / n);
    cy = round(cy / n);

    printf("(%d, %d)", cx, cy);

    for (i = 0; i < n; i++) {
        cent[i].x = (v[i].x - cx);
        cent[i].y = (v[i].y - cy);
    }

    return cent;
}

void calcAngle(int n, VPoint *v) {
    int i;
    float temp[] = { 0, 0 };

    for (i = 0; i < n; i++) {
        if (v[i].x > 0 && v[i].y > 0)
            v[i].a = (atan2(v[i].y, v[i].x)) * 180 / M_PI;
        else {
            if (v[i].x < 0 && v[i].y > 0) {
                temp[0] = -1 * v[i].x;
                v[i].a = ((atan2(v[i].y, temp[0])) * 180 / M_PI) + 90;
                //  printf("%f",v[i].a);
            }
            else {
                if (v[i].x < 0 && v[i].y < 0)
                {
                    temp[0] = -1 * v[i].x;
                    temp[1] = -1 * v[i].y;
                    v[i].a = ((atan2(temp[1], temp[0])) * 180 / M_PI) + 180;
                    // printf("%f eu to aqui\n",v[i].a);
                }
                else {
                    if (v[i].x > 0 && v[i].y < 0)
                    {
                        temp[1] = -1 * v[i].y;
                        v[i].a = ((atan2(temp[1], v[i].x)) * 180 / M_PI) + 270;
                        // printf("%f eu to aqui\n",v[i].a);
                    }
                    else {
                        if (v[i].x == 0 && v[i].y > 0)
                            v[i].a = 90;
                        else {
                            v[i].a = 270;
                            if ((v[i].x > 0 && v[i].y == 0) || (v[i].x == 0 && v[i].y == 0))
                                v[i].a = 0;
                            else v[i].a = 180;
                        }
                    }

                }
            }

        }

    }
    /*
        for(i=0;i<n;i++)
         printf("%d) %f\n",i+1,v[i].a);
    */
}

void orderAngle(int n, VPoint *v)
{
    int i, j;
    float temp;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - 1; j++)
        {
            if (v[j].a < v[j + 1].a)
            {
                temp = v[j].a;
                v[j].a =  v[j + 1].a;
                v[j + 1].a = temp;
                temp = v[j].x;
                v[j].x =  v[j + 1].x;
                v[j + 1].x = temp;
                temp = v[j].y;
                v[j].y =  v[j + 1].y;
                v[j + 1].y = temp;
            }
        }
    }
    v[n].x = v[0].x;
    v[n].y = v[0].y;

    /* for(i = 0;i<n;i++)
     {
       printf("%f\n",v[i].a);
     } */
}

void calcAreia(int n, VPoint *v)
{
    int i;
    float area = 0;
    for (i = 0; i < n; i++)
        area += ((v[i + 1].y + v[i].y) * (v[i + 1].x - v[i].x)) / 2;
    if (area < 0)
        area = -1 * area;

    printf("The area formed by polygon is: %f", area);
}

int main() {

    int n;
    VPoint *polygon, *polCentr;

    printf("Enter number of vertex of the polygon: ");
    scanf("%d", &n);

    polygon = initPointVector(n);
    initValues(n, polygon);

    printf("Vertex`s ordered pairs: \n");
    printVector(n, polygon);

    polCentr = initPointVector(n);
    polCentr = centroidVector(n, polygon);

    calcAngle(n, polCentr);
    orderAngle(n, polCentr);

    printf("Vertex organized by wide angle in relation to the x axis :\n");
    printVector(n, polCentr);

    calcAreia(n, polCentr);

    freePointVector(polCentr, polygon);
    return 0;
}
;
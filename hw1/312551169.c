#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct point;
double distance(struct point, struct point);
int cmpx(const void *, const void *);
int cmpy(const void *, const void *);

struct point {
	double x;
	double y;
};

// calculate distance between two points
double distance(struct point p1, struct point p2) {
	return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

// for qsort to compare x distance
int cmpx(const void *a, const void *b) {
	struct point *p1 = (struct point *) a;
	struct point *p2 = (struct point *) b;
	return (p1->x - p2->x);
}

// for qsort to compare y distance
int cmpy(const void *a, const void *b) {
	struct point *p1 = (struct point *) a;
	struct point *p2 = (struct point *) b;
	return (p1->y - p2->y);
}

// use recursive to find the smallest distance
double rec(struct point *p, int n) {
	if (n <= 3) {
		double min = 30000; // max = sqrt(20000^2 + 20000^2) < 30000
        	for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				double dist = distance(p[i], p[j]);
				if (dist < min) min = dist;
			}
		}
		return min;
	}
	int m = n / 2;
	struct point pmid = p[m];

	// Divide
	double l = rec(p, m);
	double r = rec(p+m, n-m);
	double d = l <= r ? l : r;

	struct point temp[n];
	int j = 0;
	for (int i=0;i<n;i++) {
		if (p[i].x - pmid.x < d) {
			temp[j] = p[i];
			j++;
		}	
	}

	qsort(temp, j, sizeof(struct point), cmpy);

	for (int i = 0; i < j; i++) {
		for (int k = i + 1; k < j && temp[k].y - temp[i].y < d; k++) {
			double dist = distance(temp[i], temp[k]);
			if (dist < d) d = dist;
		}
	}
	
	return d;
}

int main(void) {
	int t;
	scanf("%d", &t);
	
	while (t--) {
		int n;
		scanf("%d", &n);
		struct point *p = (struct point *) malloc(sizeof(struct point) * n);

		for (int i=0;i<n;i++) {
			scanf("%lf %lf", &(p[i].x), &(p[i].y));
		}

		qsort(p, n, sizeof(struct point), cmpx);

		double min = rec(p, n);

		printf("%lf\n", min);
	}

	return 0;
}

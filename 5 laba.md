#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct ListPoint
{
	int x;
	int y;
	struct ListPoint* next;
};
typedef ListPoint* lpListPoint;


//функция для определения направления тройки векторов;
// векторное произведение векторов (x2 - x1 , y2 - y1) , ( x3 - x1, y3 - y1) 
long Det(int x1, int y1, int x2, int y2, int x3, int y3)
{
	return  (long)(x2 - x1) * (y3 - y1) - (long)(y2 - y1) * (x3 - x1);
}

int isLeft_or_Right(lpListPoint List)
{
	lpListPoint ptr = List,
		prev = List,
		min = List,
		min_p = List;

	while (prev->next != List)
	{
		if (ptr->x < min->x) { min = ptr; min_p = prev; }
		prev = ptr;
		ptr = ptr->next;
	}
	if (min == List)
		while (min_p->next != min)
			min_p = min_p->next;

	if (Det(min->x, min->y, min_p->x, min_p->y,
		min->next->x, min->next->y) > 0) return 1;
	else return -1;
}
int main() {
	printf();
	return 0;
}

#include <stdio.h>
#include <stdlib.h>

/*합병 2
* 문제: 합병정렬 2에서 분할하여 정렬한 배열을 합병
* 입력: 인덱스 low, mid, high, 그리고 S의 부분배열(인덱스는 low부터 high까지)
*		low에서 mid까지 배열의 원소는 이미 정렬되어 있고, mid+1부터 high까지의 배열에 있는 원소도 마찬가지이다.
* 출력: 원소가 비내림차순으로 정렬되어 있는 S의 부분배열(인덱스는 low부터 high까지)
*/
void merge2(int S[],int low, int mid, int high) 
{
	int i = low;
	int j = mid + 1;
	//k는 정렬될 리스트에 대한 인덱스
	int k = low;
	
	//병합 한 결과를 담을 배열 U 동적 할당
	int* U = (int*)malloc(sizeof(int) * (high + 1));

	//병합 할 두영역의 데이터 비교후 정렬순서대로 U에 옮김
	while (i <= mid && j <= high) 
	{
		if (S[i] < S[j])
		{
			U[k] = S[i];
			i++;
		}
		else
		{
			U[k] = S[j];
			j++;
		}
		k++;
	}

	//배열의 앞부분을 U에 옮겼을때, 뒷부분 옮기기
	if (i > mid)
	{
		for (int index = j; index <= high; index++, k++)
			U[k] = S[index];
	}
	//배열의 뒷부분을 U에 옮겼을때, 앞부분 옮기기
	else 
	{
		for (int index = i; index <= mid; index++, k++)
			U[k] = S[index];
	}

	for (int index = low; index <= high; index++)
		S[index] = U[index];

	free(U);
}

/*합병정렬2
* 문제: n개 원소를 비내림차순으로 정렬
* 입력: 양의 정수 n, 배열 S(인덱스는 1부터 n까지)
* 출력: 원소를 비내림차순으로 정렬한 배열 S
*/
void mergesort2(int S[], int low, int high)
{
	//low<high는 더 나눌 수 있다는 것을 의미
	if (low < high)
	{
		int mid = (low + high) / 2;			//리스트의 균등 분할(중간지점 계산)
		mergesort2(S, low, mid);			//부분 리스트 정렬(low~mid)
		mergesort2(S, mid + 1, high);		//부분 리스트 정렬(mid+1~high)
		merge2(S, low, mid, high);			//정렬된 두 배열 병합
	}
}


int main(void) {

	int S[10] = { 10,3,8,2,4,9,1,7,6,5 };

	int len = sizeof(S) / sizeof(int);
	printf("합병정렬\n정렬 전 배열 상태: ");

	for (int i = 0; i < len; i++)
		printf("%d ", S[i]);
	
	mergesort2(S, 0, sizeof(S)/sizeof(int)-1);

	printf("\n정렬 후 배열 상태: ");

	for (int i = 0; i < len; i++)
		printf("%d ", S[i]);

	printf("\n");
	return 0;
}

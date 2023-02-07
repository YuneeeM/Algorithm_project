#include <stdio.h>

/* 분할
* 문제: 빠른정렬에서 쓸 수 있도록 배열 S를 분할
* 입력: 인덱스 low와 high, 배열 S에서 low부터 high까지의 부분배열
* 출력: low부터 high까지 인덱스로 된 S의 부분배열의 기준점, pivotpoint
*/
int partition(int S[], int low, int high)
{
	int temp;

	//pivotitem으로 첫 원소 선택(피벗 설정)
	int pivotitem = S[low]; 
	int j = low;
	
	//배열원소 하나씩 차례로 검사, 기준원소보다 작은 원소는 배열의 왼쪽으로 옮김
	for(int i=low+1; i<=high; i++)
		if (S[i] < pivotitem)
		{
			j++;
			temp = S[i];
			S[i] = S[j];
			S[j] = temp;
		}
	int pivotpoint = j;

	//pivotitem 값을 pivotpoint에 저장
	temp = S[low];	
	S[low] = S[pivotpoint];
	S[pivotpoint] = temp;
}

/* 빠른정렬
* 문제: 비내림차순으로 원소가 n개인 배열을 정렬
* 입력: 양의 정수 n, 배열 S(인덱스는 1부터 n까지)
* 출력: 비내림차순으로 정렬된 배열 S
*/
void quicksort(int S[], int low, int high)
{
	//정렬범위가 2개 이상인 경우
	if (low <= high)
	{
		int pivot = partition(S, low, high);	//둘로 나눠서
		quicksort(S, low, pivot - 1);			//왼쪽 영역을 정렬
		quicksort(S, pivot + 1, high);			//오른쪽 영역을 정렬
	}
}

int main(void) {

	int S[10] = { 9,3,10,2,4,8,1,7,6,5 };

	int len = sizeof(S) / sizeof(int);

	printf("퀵정렬\n정렬 전 배열 상태: ");
	for (int i = 0; i < len; i++)
		printf("%d ", S[i]);

	quicksort(S, 0, sizeof(S) / sizeof(int) - 1);

	printf("\n정렬 후 배열 상태: ");
	for (int i = 0; i < len; i++)
		printf("%d ", S[i]);

	printf("\n");
	return 0;

}

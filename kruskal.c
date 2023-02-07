// Kruskal Algorithm
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#define Max_vertex 5
#define Max_edge 7

FILE* f;

typedef struct Edge 
{
	int vertex[2]; // 시작점과 끝점
	int cost; // 가중치
}Edge; //간선을 나타내기 위해 구조체로 정의

int** make_matrix(int n); // 인접행렬 만들기
int read_matrix(int* G[], int n); // 파일에서 인접행렬값 읽기

void convert_matrix_edge(int* G[], Edge E[], int n); // 인접형렬을 간선으로 변환
void convert_edge_matrix(int* G[], Edge E[], int n); // 간선을 인접행렬으로 변환

void print_edge_cost(Edge E[], int n); // E 집합 출력

void kruskal(int n, int m, Edge E[], Edge F[]);

int find(int i, int U[]); //해당 정점이 어떤 집합에 속하는지 찾음
void sort(Edge E[], int m); //정렬
void merge(int p, int q, int U[]); // 집합(서로소)을 합침

//n x n 행렬 만들기
int** make_matrix(int n) 
{
	int** matrix;
	matrix = (int**)malloc(sizeof(int*) * n);
	for (int i = 0; i < n; i++)
		matrix[i] = (int*)malloc(sizeof(int) * n);

	return matrix;
}

//파일에서  행렬값을 읽어 행렬 G에 저장 및 출력
int read_matrix(int* G[], int n) 
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
		{
			fscanf(f, "%d", &G[i][j]);
			printf("%3d", G[i][j]);
		}
		puts(" ");
	}
}

//행렬 정보를 이음선 정보로 변환
void convert_matrix_edge(int* G[], Edge E[], int n)
{
	int num = 0;
	for (int i = 0; i < n; i++) // 행렬의 정보를 이음선 구조체에 삽입
		for (int j = i; j < n; j++) {
			if (G[i][j] != 0) {
				E[num].vertex[0] = i;
				E[num].vertex[1] = j;
				E[num].cost = G[i][j];
				num++;
			}
		}
}

//이음선 정보를 행렬 정보로 변환
void convert_edge_matrix(int* G[], Edge E[], int n)
{
	int num = 0;

	//행렬 G 초기화
	for (int i = 0; i <=n; i++)
	{
		for (int j = 0; j <= n; j++) {
			G[i][j] = 0;
		}
	}

	//행렬 G에 mst값 대입
	for (int i = 0; i < n; i++) {
		G[E[i].vertex[0]] [E[i].vertex[1]] = E[i].cost;
		G[E[i].vertex[1]][E[i].vertex[0]] = E[i].cost;	
	}

	//행렬 출력
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= n; j++) {
			printf("%3d", G[i][j]);
		}
		puts(" ");
	}
}

//i가 집합 U에서 어느 집합에 속해있는지 확인함
int find(int i, int U[]) 
{
	int j;
	j = i;

	while (U[j] != j)
		j = U[j];
	return j;
}

//집합의 합병
void merge(int p, int q, int U[]) 
{
	//set_pointer인 p,q값중 작은 것이 합병된 집합의 값이 된다.
	if (p < q)
		U[q] = p; // p<q임으로 합병집합의 값은 p
	else
		U[p] = q; //p>q임으로 합병집합의 값은 q
}

//E 이음선 집합 출력
void print_edge_cost(Edge E[], int n) 
{
	for (int i = 0; i < n; i++)
		if (E[i].cost != 0)
			printf("vertex%2d -> vertex%2d, 가중치= %2d\n", E[i].vertex[0]+1 , E[i].vertex[1]+1 , E[i].cost);
}

/*크루스칼 알고리즘
*문제: 최소비용 신장트리를 구하시오
* 입력: 정수 n(>=2), 양의 정수 m,n개의 마디와 m개의 이음선을 가진 연결된 가중치포함 비방향그래프, 이 그래프는 가중치와 함계 이음선이 포함된 집합 E로 표현함
* 출력: 최소비용 신장트리에서 이음선의 집합 F
*/
void kruskal(int n, int m, Edge E[], Edge F[]) 
{
	int i, j, k;
	int p, q; // 서로소 집합의 번호를 가르키는 변수(set_pointer)
	int num = 0;
	int* U = (int*)malloc(sizeof(int) * (n - 1)); // 서로소 집합 U
	Edge edge;

	printf("\n[[정렬 전, E집합 상태]]\n");
	print_edge_cost(E, m);
	sort(E, m); // E에 속한 m개 이음선을 가중치가 작은 것부터 차례로 정렬
	printf("\n[[정렬 후, E집합 상태]]\n");
	print_edge_cost(E, m);

	// makeset을 통한 initialize
	for (i = 0; i < n; i++) 
		U[i] = i;

	k = 0;
	while (num < n - 1) { // F의 이음선 n-1 작을때
		edge = E[k]; // 아직 고려하지 않은 이음선 중 가중치가 최소인 이음선
		i = E[k].vertex[0]; // i(시작), j(끝)이 e와 연결된 정점
		j = E[k].vertex[1];
		p = find(i, U); // p = i가 속하는 서로소 집합을 가리킴
		q = find(j, U);
		if (p != q) { // equal함수와 유사 p와 q가 다르다면
			merge(p, q, U); // p, q가 속한 집합을 합침
			F[num] = edge; // edge를 F에 추가
			num++;
		}
		k++;
	}
}

// E 집합의 가중치를 정렬하기 위한 함수
void sort(Edge E[], int m) 
{
	int case_sort = 0;
	Edge temp;
	// 정렬이 끝나지 않은경우
	while (!case_sort) { 
		case_sort = 1;
		for (int i = 1; i < m; i++) {
			if (E[i - 1].cost > E[i].cost) {
				temp = E[i - 1];
				E[i - 1] = E[i];
				E[i] = temp;
				case_sort = 0;
			}
		}
	}
}

int main()
{
	f = fopen("input.txt", "r");
	if (f == NULL) {
		perror("File open error");
		return 0;
	}

	int n = Max_vertex; //초기 정점의 개수
	int m = Max_edge; //초기 이음선의 개수

	int** G;
	G = make_matrix(n); 

	printf("\n[[파일에서 읽은 인접행렬]]\n\n");
	read_matrix(G, n); 

	Edge* E = (Edge*)malloc(sizeof(Edge) * m); //이음선
	Edge* F = (Edge*)malloc(sizeof(Edge) * m); //최소비용 신장트리
	
	convert_matrix_edge(G, E, n); 

	//크루스칼을 실행한 최소 비용 신장 트리를 F집합에 삽입
	kruskal(n, m, E, F);

	printf("\n[[최소 비용 신장 트리 F의 결과]]\n");
	print_edge_cost(F, n - 1);

	printf("\n\n[[Adjacent Matrix로 표현된 MST]]\n\n");
	convert_edge_matrix(G, F, n-1);

	fclose(f);
	return 0;
}

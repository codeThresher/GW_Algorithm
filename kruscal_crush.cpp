#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

stack<int> st;

//집합의 초기화 과정, 정점 하나하나를 집합으로 만듬
void init_set(int *arr, int n){
	for(int i=0; i<n; i++) arr[i] = -1;
}

//루트 노드확인 재귀함수
int find(int n, int *arr){  
	if(arr[n] < 0){//루트 노드는 음수 일때이므로,
		while(!st.empty()){
			arr[st.top()] = n; // 부모가 남아 push했던 아이를 n 
			st.pop();
		}
		return n; // 이미 루트 노드를 찾은 상태이므로 그대로 리턴
	}
	else{ // 값이 양수일때는 arr[n]이 가리키는 것이 루트 노드가 아니므로 
		st.push(n); // n값을 스택에 넣어서 전달 
		return n = find(arr[n], arr); // 재귀함수, 루트 노드 찾을 때까지만(음수 일때 까지)  계속 호출 하도록 만들어 줌 
	}
}

//두 집합을 합치고 부모노드를 가리키는 정점을 바꿔주는 함수
void unionP(int a, int b, int arr[], int &sum, int amount){ // sum 참조 매개변수로 받음 
	if(arr[a] <= arr[b]){ // a의 깊이가 더 클때 음수이므로 , a집합으로 합쳐줌, 깊이가 같을때는 인식 어려움 
		arr[a] += arr[b]; // arr[a]에 음수 값 arr[b] 넣어줌 
		arr[b] = a; //합치고 난 후 부모 노드 값 parent에 넣어줌
		sum += amount;

	}
	else{
		arr[b] += arr[a];
		arr[a] = b; // 반대일 경우는 반대로 넣어줌
		sum += amount;	
	}
}

//stack<int> &stack
// 간선 클래스 선언 
class Line{
public:
	int node[2];
	int lineValue;
	// 생성자 선언 
	Line(int a, int b, int lineValue){ 
		this->node[0] = a; //시작 정점
		this->node[1] = b; // 도착 정점
		this->lineValue = lineValue; // 간선의 가중치; 
	}
	// 연산자 오버로딩 
	bool operator < (Line &line){
		return this->lineValue < line.lineValue;
		//가중치가 작은 순으로 출력되게 만들어줌 
	}
};

int main(void){
	
	int n=9;
	//붕괴 크러스컬에 사용 스택 
	vector<Line> v;// 간선 클래스의 벡터 변수 선언 
	//트리 집합 데이터 y축 세로방향 첫번째 노드, x축 두번째노드, 인덱스 노드간 가중치 
	int treeData[n][n] = {{0,4,0,0,0,0,0,8,0},  
					{4,0,8,0,0,0,0,11,0},  
					{0,8,0,7,0,4,0,0,2},
					{0,0,7,0,9,14,0,0,0}, //3
					{0,0,0,9,0,10,0,0,0},
					{0,0,4,14,10,0,2,0,0},
					{0,0,0,0,0,2,0,1,6},  //6
					{8,11,0,0,0,0,1,0,7},
					{0,0,2,0,0,0,6,7,0}};
					
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(i == j || treeData[i][j] == 0)
				continue;
			
			v.push_back(Line(i, j, treeData[i][j])); //14
			treeData[i][j] = 0;
			treeData[j][i] = 0;
		}
	}
	//간선의 가중치를 기준으로 오름차순 정렬 
	sort(v.begin(), v.end()); // algorithm 헤더의 sort 퀵정렬 이용 
	// 클래스 선언부에서, 이미 가중치 낮은순으로 연산자 오버로딩 하였기 때문에, compare함수 구현 안해줘도됨.  
	 
	int parent[n]; // 부모노드를 알려주는 배열 선언 
	
	init_set(parent, n); // 부모 노드와 깊이를 알기 위해, 음수값 -1로 초기화 
	
	int sum= 0; //가중치의 합
	for(int i=0; i<v.size(); i++){ //벡터 컨테이너에 저장되어 있는만큼 반복 
		int aParent = find(v[i].node[0], parent); // 비교할 첫번째 정점, 루트노드, 트리의 깊이 확인 
		int bParent = find(v[i].node[1], parent); // 비교할 두번째 정점, 음수면 다음단계 
		int amount = v[i].lineValue;
		
		
		if(aParent != bParent) // 타당성 조사, 두 집합이 다른 집합일때, 
			unionP(aParent, bParent, parent , sum, amount); // 두 집합을 합쳐주고, 부모 노드를 가르키게함.	
		}
	
	for(int i=0; i<st.size(); i++)
		cout << st.top() << endl;

	for(int i=0; i<n; i++) cout << i << "  ";
		cout << "정점 번호\n";
	for(int i=0; i<n; i++) cout << parent[i] << "  ";
		cout << "정점 값\n";
	cout << "이 트리에서 요구되는 최소 비용은 "<< sum << " 입니다.\n";
}

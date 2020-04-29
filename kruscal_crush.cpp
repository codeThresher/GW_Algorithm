#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

stack<int> st;

//������ �ʱ�ȭ ����, ���� �ϳ��ϳ��� �������� ����
void init_set(int *arr, int n){
	for(int i=0; i<n; i++) arr[i] = -1;
}

//��Ʈ ���Ȯ�� ����Լ�
int find(int n, int *arr){  
	if(arr[n] < 0){//��Ʈ ���� ���� �϶��̹Ƿ�,
		while(!st.empty()){
			arr[st.top()] = n; // �θ� ���� push�ߴ� ���̸� n 
			st.pop();
		}
		return n; // �̹� ��Ʈ ��带 ã�� �����̹Ƿ� �״�� ����
	}
	else{ // ���� ����϶��� arr[n]�� ����Ű�� ���� ��Ʈ ��尡 �ƴϹǷ� 
		st.push(n); // n���� ���ÿ� �־ ���� 
		return n = find(arr[n], arr); // ����Լ�, ��Ʈ ��� ã�� ��������(���� �϶� ����)  ��� ȣ�� �ϵ��� ����� �� 
	}
}

//�� ������ ��ġ�� �θ��带 ����Ű�� ������ �ٲ��ִ� �Լ�
void unionP(int a, int b, int arr[], int &sum, int amount){ // sum ���� �Ű������� ���� 
	if(arr[a] <= arr[b]){ // a�� ���̰� �� Ŭ�� �����̹Ƿ� , a�������� ������, ���̰� �������� �ν� ����� 
		arr[a] += arr[b]; // arr[a]�� ���� �� arr[b] �־��� 
		arr[b] = a; //��ġ�� �� �� �θ� ��� �� parent�� �־���
		sum += amount;

	}
	else{
		arr[b] += arr[a];
		arr[a] = b; // �ݴ��� ���� �ݴ�� �־���
		sum += amount;	
	}
}

//stack<int> &stack
// ���� Ŭ���� ���� 
class Line{
public:
	int node[2];
	int lineValue;
	// ������ ���� 
	Line(int a, int b, int lineValue){ 
		this->node[0] = a; //���� ����
		this->node[1] = b; // ���� ����
		this->lineValue = lineValue; // ������ ����ġ; 
	}
	// ������ �����ε� 
	bool operator < (Line &line){
		return this->lineValue < line.lineValue;
		//����ġ�� ���� ������ ��µǰ� ������� 
	}
};

int main(void){
	
	int n=9;
	//�ر� ũ�����ÿ� ��� ���� 
	vector<Line> v;// ���� Ŭ������ ���� ���� ���� 
	//Ʈ�� ���� ������ y�� ���ι��� ù��° ���, x�� �ι�°���, �ε��� ��尣 ����ġ 
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
	//������ ����ġ�� �������� �������� ���� 
	sort(v.begin(), v.end()); // algorithm ����� sort ������ �̿� 
	// Ŭ���� ����ο���, �̹� ����ġ ���������� ������ �����ε� �Ͽ��� ������, compare�Լ� ���� �����൵��.  
	 
	int parent[n]; // �θ��带 �˷��ִ� �迭 ���� 
	
	init_set(parent, n); // �θ� ���� ���̸� �˱� ����, ������ -1�� �ʱ�ȭ 
	
	int sum= 0; //����ġ�� ��
	for(int i=0; i<v.size(); i++){ //���� �����̳ʿ� ����Ǿ� �ִ¸�ŭ �ݺ� 
		int aParent = find(v[i].node[0], parent); // ���� ù��° ����, ��Ʈ���, Ʈ���� ���� Ȯ�� 
		int bParent = find(v[i].node[1], parent); // ���� �ι�° ����, ������ �����ܰ� 
		int amount = v[i].lineValue;
		
		
		if(aParent != bParent) // Ÿ�缺 ����, �� ������ �ٸ� �����϶�, 
			unionP(aParent, bParent, parent , sum, amount); // �� ������ �����ְ�, �θ� ��带 ����Ű����.	
		}
	
	for(int i=0; i<st.size(); i++)
		cout << st.top() << endl;

	for(int i=0; i<n; i++) cout << i << "  ";
		cout << "���� ��ȣ\n";
	for(int i=0; i<n; i++) cout << parent[i] << "  ";
		cout << "���� ��\n";
	cout << "�� Ʈ������ �䱸�Ǵ� �ּ� ����� "<< sum << " �Դϴ�.\n";
}

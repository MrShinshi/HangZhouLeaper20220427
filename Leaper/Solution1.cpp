//#define DEBUG
#ifdef DEBUG

#include <iostream>
#include <vector>

using std::vector;

int Solution(vector<vector<int>>& mat, int nStartRow, int nStartCol);

int main()
{

	vector<vector<int>> mat1 = {
		{ 0, 1, 1, 0, 0 },
		{ 1, 1, 1, 1, 0 },
		{ 0, 1, 0, 0, 0 },
		{ 0, 0, 1, 1, 1 }
	};
	int res1 = Solution(mat1, 1, 2);
	std::cout << "Result1 is " << res1 << std::endl;

	vector<vector<int>> mat2 = {
		{ 0, 1, 1, 0, 0, 1, 1 },
		{ 1, 1, 1, 1, 1, 0, 1 },
		{ 0, 1, 1, 0, 1, 0, 0 },
		{ 0, 1, 0, 1, 1, 1, 0 },
		{ 0, 1, 0, 0, 0, 0, 1 },
		{ 0, 0, 1, 1, 1, 0, 0 }
	};
	int res2 = Solution(mat2, 5, 2);
	std::cout << "Result2 is " << res2 << std::endl;

}

/*
	��������: ����Ŀ��Ԫ��������ֵΪ 1 ����ͨ�����С.
	��������:	1.ԭ���ݻᱻ�ƻ�
				2.��Ȼ��������������Ч���,�����������ɿ���Ϊ��
				3.ÿ�εݹ鶼�����¼�������,�˷���Դ
				4.�ݹ�ÿ����ִ֧��ǰ�������ж��Ѿ��������±�Խ��,��˲����ٽ�����Ϊ���ڽ����ж�
	�Ż���ʽ:	1. �ڱ��ݺ�������Ͻ��м���		�����ھ����Сʱ
				2. ��¼Ⱦɫ������				�����ھ���ϴ�����ͨ�����Сʱ(����ͨ�������ʱ�������ݿռ�ռ�û�Զ��������)
*/
#define OptionX

#ifdef Option1 //����һ

int DFS(vector<vector<int>>& mat, int nStartRow, int nStartCol) {

	if (mat[nStartRow][nStartCol] == 0) {
		return 0;
	}

	int res{ 1 };
	mat[nStartRow][nStartCol] = 0;

	if (nStartRow > 0) {
		res += Solution(mat, nStartRow - 1, nStartCol);
	}
	if (nStartRow < mat.size() - 1) {
		res += Solution(mat, nStartRow + 1, nStartCol);
	}
	if (nStartCol > 0) {
		res += Solution(mat, nStartRow, nStartCol - 1);
	}
	if (nStartCol < mat[0].size() - 1) {
		res += Solution(mat, nStartRow, nStartCol + 1);
	}
	mat[nStartRow][nStartCol] = 1;

	return res;
}

int Solution(vector<vector<int>>& mat, int nStartRow, int nStartCol)
{
	if (mat.size() <= 0 || mat[0].size() <= 0) {
		return 0;
	}

	vector<vector<int>>_mat(mat);

	return DFS(_mat, nStartRow, nStartCol);
}

#endif // Option1

#ifdef Option2 //������

int DFS(vector<vector<int>>& mat, int nStartRow, int nStartCol, vector<std::pair<int, int>>& record) {

	if (mat[nStartRow][nStartCol] == 0) {
		return 0;
	}

	int res{ 1 };
	mat[nStartRow][nStartCol] = 0;
	record.push_back({ nStartRow, nStartCol });

	if (nStartRow > 0) {
		res += Solution(mat, nStartRow - 1, nStartCol);
	}
	if (nStartRow < mat.size() - 1) {
		res += Solution(mat, nStartRow + 1, nStartCol);
	}
	if (nStartCol > 0) {
		res += Solution(mat, nStartRow, nStartCol - 1);
	}
	if (nStartCol < mat[0].size() - 1) {
		res += Solution(mat, nStartRow, nStartCol + 1);
	}

	return res;
}

int Solution(vector<vector<int>>& mat, int nStartRow, int nStartCol)
{
	if (mat.size() <= 0 || mat[0].size() <= 0) {
		return 0;
	}

	vector<std::pair<int, int>> record;

	vector<vector<int>> _mat(mat);

	int res{ DFS(_mat, nStartRow, nStartCol, record) };

	for(auto& pair:record)
		mat[pair.first][pair.second] = 1;

	return res;
}

#endif // Option2

#endif
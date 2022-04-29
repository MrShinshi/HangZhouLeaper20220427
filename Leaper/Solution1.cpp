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
	函数功能: 返回目标元素所属数值为 1 的连通区域大小.
	存在问题:	1.原数据会被破坏
				2.虽然对行数进行了有效检查,但是列数依旧可能为空
				3.每次递归都会重新检查矩阵规格,浪费资源
				4.递归每个分支执行前的条件判断已经限制了下标越界,因此不必再将其作为出口进行判断
	优化方式:	1. 在备份后的数据上进行检索		适用于矩阵较小时
				2. 记录染色的坐标				适用于矩阵较大且连通区域较小时(当连通区域过大时坐标数据空间占用会远超矩阵本身)
*/
#define OptionX

#ifdef Option1 //方案一

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

#ifdef Option2 //方案二

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
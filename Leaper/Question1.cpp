#ifdef DEBUG

/*! 感谢您参与利珀科技笔试，题目说明如下：
* [Q1]
* 假定mat中的每一个子 vector 都拥有相同的 size，请回答以下问题：
* 1. Solution() 函数实现了什么功能
* 2. 此函数的实现方式有什么问题
* 3. 如何对此函数进行优化，完成相关编码
*/

#include <iostream>
#include <vector>

using std::vector;

int Solution(vector<vector<int>>& mat, int nStartRow, int nStartCol);

int main()
{
	std::cout << "Hello World!\n";

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
	std::cout << "Result2 is " << res1 << std::endl;
}

/*! Solution 函数
* @param mat
* @param nStartRow
* @param nStartCol
* @retval
*/
int Solution(vector<vector<int>>& mat, int nStartRow, int nStartCol)
{
	/**!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!**/
	/* 请阅读此函数，并回答文件开头出提出的 3 个问题。*/
	/**!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!**/

	if (mat.size() <= 0) {
		return 0;
	}
	if (mat.size() <= nStartRow || mat[0].size() <= nStartCol) {
		return 0;
	}
	if (mat[nStartRow][nStartCol] == 0) {
		return 0;
	}

	int res = 1;
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

	return res;
}

#endif
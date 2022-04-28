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
		{ 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1 }
	};
	int res2 = Solution(mat2, 5, 2);
	std::cout << "Result2 is " << res2 << std::endl;
}

/*函数功能:
	删除目标元素所属数值为 1 的连通区域, 并返回其大小.
*/
int Solution(vector<vector<int>>& mat, int nStartRow, int nStartCol)
{
	if (mat.size() <= 0) {
		return 0;
	}
	if (mat.size() <= nStartRow || mat[0].size() <= nStartCol) {
		return 0;
	}
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

	return res;
}

#endif
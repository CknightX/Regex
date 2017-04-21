#include "state_list.h"
void Matrix::construct(int n)
{
	matrix = new int*[n];
	for (int i = 0; i < n; ++i)
		matrix[i] = new int[MAX_CHAR];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < MAX_CHAR; ++j)
			matrix[i][j] = 0;
}
void Matrix::destruct()
{
	for (int i = 0; i < N; ++i)
		delete[]matrix[i];
	delete[]matrix;
}


State_List::State_List(DFA& dfa)
	:matrix(dfa.AllStatus.size())
{
	auto find_status = [&](DFA_Status* status){
		auto iter = find(dfa.AllStatus.begin(), dfa.AllStatus.end(), status);
		if (iter == dfa.AllStatus.end()) return -1;
		return iter - dfa.AllStatus.begin();
	};

	int status_no = -1;
	for (auto status : dfa.AllStatus)
	{
		++status_no;
		if (status->IsFinal)
		{
			for (int i = 0; i < 256; ++i)
				matrix.set(-1,status_no,i);
		}

		for (auto edge : dfa.AllEdges)
		{
			int pos = find_status(edge->End);
			for (int i = edge->MatchContent.left; i <= edge->MatchContent.right; ++i)
			{
				matrix.set(pos, status_no, i);
			}
		}
	}

}
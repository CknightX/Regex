#include "re.h"
string Re::match_all(const string& source)
{
	string result = "";
	while (curr_index < source.size())
	{
		result += match(source);
		result += " ";
	}
	return result;
}
string Re::match(const string& source)
{ 
	curr_index=0;
	unsigned i=curr_index,i_bak=i-1; //source �α�
	int start_pos = state_list.get_start();
	int curr_status = start_pos;
	if (curr_status == -1)
		throw;
	string result="";
	while (true)
	{
		if (curr_status == start_pos) //λ�ڿ�ʼ״̬���α�ָ���ԭ����+1
		{
			result = "";
			i = ++i_bak;
		}
		if (i >= source.size()) //�α��ƶ�����β
			break;
		curr_status = state_list.get_status(curr_status, source[i]);
		if (curr_status == -1) //����ĩβ״̬��������һ������ʹ��ת�Ƶ��ַ�
			break;
		result += source[i];
		++i;
	}
	if (state_list.is_in_end_pos(curr_status) || curr_status == -1) //���ڽ���״̬(���������*+ƥ�䵽���һ���ַ������) || ĩβδת��
	{
		curr_index = i_bak+result.size();
		return result;
	}
	else //ֱ����β��û��ƥ�䵽
	{
		curr_index = source.size();
	}
	return "";
}
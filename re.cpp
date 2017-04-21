#include "re.h"
string Re::match(const string& source)
{
	int i=0,i_bak=i-1; //source ÓÎ±ê
	int curr_status = 0;
	string result="";
	while (true)
	{
		if (curr_status == 0)
		{
			result = "";
			i = ++i_bak;
		}
		if (i >= source.size())
			break;
		curr_status = state_list.get_status(curr_status, source[i]);
		if (curr_status == -1)
			break;
		result += source[i];
		++i;
	}
	if (curr_status != -1)
		return "";
	return result;
}
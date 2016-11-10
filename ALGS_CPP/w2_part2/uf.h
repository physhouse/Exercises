#ifndef _UF_H_
#define _UF_H_

#include <vector>

class UF
{
public:
	UF(int num);
	void union_path(int i, int j);
	int  find(int i);
	int	 getCount();
	bool connected(int i, int j);

private:
	std::vector<int>	parent;
	std::vector<int>	rank;
	int					count;
};

#endif

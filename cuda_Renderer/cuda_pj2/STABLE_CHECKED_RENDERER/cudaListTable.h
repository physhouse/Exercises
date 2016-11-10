#ifndef __LISTTABLE_H_
#define __LISTTABLE_H_

#include <cstdlib>

struct ListTable
{
  size_t count;
  int    elements;
  int*   size;
  int*   index;
  int*   entry;
};

void initializeTable(ListTable&, int);
void freeTable(ListTable&);
void generateScan(ListTable&);
void copyTable2Host(const ListTable&, ListTable&);
void deleteHost(ListTable& host);

#endif

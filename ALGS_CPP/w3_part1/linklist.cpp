#include <cstdlib>
#include <cstdio>

struct Edge
{
	int end_A;
	int end_B;
};

class EdgeNode
{
	friend class EdgeList;
private:
	Edge e;
	EdgeNode* next;
	EdgeNode* prev;
public:
	EdgeNode()
	{
		next = NULL;
		prev = NULL;
	}
};

class EdgeList
{
private:
	int	size;
	EdgeNode* head;
public:
	EdgeList();
	void insert(struct Edge);
	void kick(EdgeNode*);
	int getSize();
};

EdgeList::EdgeList()
{
	size = 0;
	head = new EdgeNode();
}

int EdgeList::getSize()
{
	return size;
}

void EdgeList::insert(Edge edge)
{
	EdgeNode* p = head;

	while (p->next)
	{
		p = p->next;
	}

	EdgeNode* newNode = new EdgeNode();
	newNode->e = edge;
	newNode->next = p->next;
	p->next = newNode;
	newNode->prev = p;
	size++;
}

void EdgeList::kick(EdgeNode* p)
{
	if (p->prev != NULL)
	{
		(p->prev)->next = p->next;
	}
	p->next = NULL;
	delete(p);
	size--;
}

int main()
{
	Edge e1 = { .end_A = 1, .end_B = 3 };
	Edge e2 = { .end_A = 1, .end_B = 4 };
	Edge e3 = { .end_A = 1, .end_B = 2 };
	Edge e4 = { .end_A = 1, .end_B = 7 };
	Edge e5 = { .end_A = 1, .end_B = 5 };

	EdgeList pp;
	printf("here\n");
	pp.insert(e1);
	pp.insert(e2);
	pp.insert(e3);
	pp.insert(e4);
	pp.insert(e5);

	printf("size = %d\n", pp.getSize());
	
}

#!/usr/bin/env python
from collections import deque

class Node(object):
  def __init__(self,data,left=None,right=None):
     self.data = data
     self.left = left
     self.right = right

class Btree(object):
  def __init__(self, root=None):
     self.root = root

  def preOrderTraverse(self, Node):
     if Node is None:
	return
     else:
	print Node.data
	self.preOrderTraverse(Node.left)
	self.preOrderTraverse(Node.right)

  def preOrderNonRecursive(self):
     Stack=[]
     Stack.append(self.root)

     while len(Stack)>0:
	temp = Stack.pop()
	print(temp.data)
	if temp.right is not None:
	   Stack.append(temp.right)
	if temp.left is not None:
	   Stack.append(temp.left)

  def inOrderNonRecursive(self):
     Stack=[]
     tempnode=root

     while len(Stack)>0 or (tempnode is not None):
        if tempnode is not None:
	   Stack.append(tempnode)
	   tempnode = tempnode.left
	else:
           tempnode = Stack[-1]
	   print(tempnode.data)
	   rr = Stack.pop()
	   tempnode=tempnode.right 

  def levelOrderTraverse(self):
     queue = deque(root)
     whi

if __name__=="__main__":
   n1 = Node(data=1)
   n2 = Node(2,n1,None)
   n3 = Node(3)
   n4 = Node(4)
   n5 = Node(5,n3,n4)
   n6 = Node(6,n2,n5)
   n7 = Node(7,n6,None)
   n8 = Node(8)
   root = Node('root',n7,n8)

   bt = Btree(root)
   bt.preOrderTraverse(bt.root)
   print("NonRecursive")
   bt.preOrderNonRecursive()
   bt.inOrderNonRecursive()
     

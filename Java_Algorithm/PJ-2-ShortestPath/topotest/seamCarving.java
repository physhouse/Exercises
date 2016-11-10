import java.awt.Color;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.StdOut;

//Calculating seamCarving using topological shortest path algorithm for DAGs

public class seamCarving {

   private int height;
   private int width;

   public seamCarving(int w, int h)
   {
	 height = h;
	 width  = w;

   }

   public Iterable<Integer> topoOrder(int y)
   {
      Stack<Integer> p = new Stack<Integer>();
	  Queue<Integer> postorder = new Queue<Integer>();
	  boolean[][] marked = new boolean[width][height];
	  for (int i=0; i<height; i++)
	    for (int j=0; j<height; j++)
		  marked[i][j] = false;

	  int root = xyToIndex(0,y);
	  p.push(root);
	  while(!p.isEmpty())
	  {
		int top = p.peek();
		int topx = indexToX(top);
		int topy = indexToY(top);
		//marked[topx][topy] = true;

		if (topx == width - 1)
		{
		   int out = p.pop();
		   postorder.enqueue(out);
		   continue;
		}

		boolean popflag = true;
		for (int offset = -1; offset <= 1; offset++)
		{
		  int py = topy + offset;
		  int px = topx + 1;
		  if (py < 0) continue;
		  else if (py > height - 1) continue;
		  else
		  {
		     if (!marked[px][py])
			 {
			   popflag = false;
		       int id = xyToIndex(px, py);
		       p.push(id);
			   marked[px][py] = true;
			 }
		  }
		}
	
	    if (popflag) 
		{
			int out = p.pop();
			postorder.enqueue(out);
		}
	  }

	  Stack<Integer> reverseOrder = new Stack<Integer>();
	  for (int v : postorder)
	  {
	    reverseOrder.push(v);
	  }
	  return reverseOrder;
   }
   

   public int xyToIndex(int x, int y)
   {
      return x * height + y;
   }

   public int indexToX(int index)
   {
      int x = index / height;
	  return x;
   }
   
   public int indexToY(int index)
   {
	  return index % height;
   }

   public static void main(String[] args)
   {
     seamCarving sc = new seamCarving(768,364);
	 Iterable<Integer> order = sc.topoOrder(100);
	 for (int v : order)
	 {
	   StdOut.printf("%d %d\n", sc.indexToX(v), sc.indexToY(v));
	 }
	 //StdOut.print(order);
   }
}  

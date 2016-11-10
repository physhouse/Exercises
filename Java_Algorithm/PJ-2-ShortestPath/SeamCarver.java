import java.awt.Color;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.Picture;
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.StdOut;

//Calculating seamCarving using topological shortest path algorithm for DAGs

public class SeamCarver {

   private Picture pic_current;
   private double[][] energy;
   private int height;
   private int width;

   public SeamCarver(Picture picture)
   {
     pic_current = new Picture(picture);
	 height = pic_current.height();
	 width  = pic_current.width();

	 energy = new double[width][height];
	 for (int i=0; i<width; i++)
	 {
	   for (int j=0; j<height; j++)
	     {
		   energy[i][j] = energy(i,j);
		 }
     }

   }

   public Picture picture()
   {
     return pic_current;
   }

   public int width()
   {
     return this.width;
   }

   public int height()
   {
     return this.height;
   }

   public double energy(int x, int y)
   {
     if (x < 0 || x >= width || y < 0 || y >= height)
	    throw new java.lang.IndexOutOfBoundsException("Out of Bounds");
     if (x == 0 || y == 0 || x == width - 1 || y == height -1)
	 	return 1000.0;
	 else
	 {
       Color color_plus = pic_current.get(x+1,y);
       Color color_minus = pic_current.get(x-1,y);
	   double rx = (color_plus.getRed() - color_minus.getRed());
	   double gx = (color_plus.getGreen() - color_minus.getGreen());
	   double bx = (color_plus.getBlue() - color_minus.getBlue());

       color_plus = pic_current.get(x,y+1);
       color_minus = pic_current.get(x,y-1);

	   double ry = (color_plus.getRed() - color_minus.getRed());
	   double gy = (color_plus.getGreen() - color_minus.getGreen());
	   double by = (color_plus.getBlue() - color_minus.getBlue());

	   return Math.sqrt(rx*rx + gx*gx + bx*bx + ry*ry + gy*gy + by*by); 
	 }
   }

   private Iterable<Integer> topoOrder(int width, int height)
   {
      Stack<Integer> p = new Stack<Integer>();
	  Queue<Integer> postorder = new Queue<Integer>();
	  boolean[][] marked = new boolean[width][height];
	  for (int i=0; i<width; i++)
	    for (int j=0; j<height; j++)
		  marked[i][j] = false;

	  for (int i=0; i<height; i++)
	  {
	    int root = xyToIndex(0,i, height);
	    p.push(root);
	    marked[0][i] = true;

	    while(!p.isEmpty())
	    {
	   	  int top = p.peek();
	   	  int topx = indexToX(top, height);
	   	  int topy = indexToY(top, height);

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
	   	        int id = xyToIndex(px, py, height);
	   		    marked[px][py] = true;
	   	        p.push(id);
	   		  } 
	   	    }
	   	  }
	   
	      if (popflag) 
	   	  {  
	   		int out = p.pop();
	   		postorder.enqueue(out);
	   	  }
	    }
      }

	  Stack<Integer> reverseOrder = new Stack<Integer>();
	  for (int v : postorder)
	  {
	    reverseOrder.push(v);
	  }
	  return reverseOrder;
   }
   
   private void relax(int x, int y, double[][] disTo, int[][] edgeTo, int width, int height, double[][] energy)
   {
      if (x == width - 1) return;
      for (int offset=-1; offset <= 1; offset++)
	  {
	     int py = y + offset;
		 int px = x + 1;
	     if (py < 0) continue;
		 else if (py > height - 1) continue;
		 else
		 {
		   if (disTo[px][py] > disTo[x][y] + energy[px][py])
		   {
		      disTo[px][py] = disTo[x][y] + energy[px][py];
			  edgeTo[px][py] = xyToIndex(x, y, height);
		   }
		 }
	  }
   }

   private double topoMinPath(int[] path, int width, int height, double[][] energy)
   {
      Iterable<Integer> topo = topoOrder(width, height);
      double[][] disTo  = new double[width][height];
      int[][] edgeTo = new int[width][height];
	  for (int i=0; i<width; i++)
	    for (int j=0; j<height; j++)
		{
		  if (i == 0) disTo[i][j] = 0.0;
		  else 	      disTo[i][j] = Double.POSITIVE_INFINITY;
		  edgeTo[i][j] = -1;
		}

	  for (int v : topo)
	  {
	  	 int vx = indexToX(v, height);
		 int vy = indexToY(v, height);
		 relax(vx, vy, disTo, edgeTo, width, height, energy);
	  }

	  double length = Double.POSITIVE_INFINITY;
	  int end = -1;
	  for (int i=0; i<height; i++)
      {
	    if (disTo[width-1][i] < length)
		{
		  length = disTo[width-1][i];
          end = i;
		}
	  }

	  // find the path
	  path[width-1] = end; //indexToY(end, height);
	  int level = width-1;
	  while (level >= 1)
	  {
	    int k = edgeTo[level][path[level]];
		level--;
		path[level] = indexToY(k, height);
	  }

	  return length;
   }

   private int xyToIndex(int x, int y, int height)
   {
      return x * height + y;  
   }

   private int indexToX(int index, int height)
   {
      int x = index / height;
	  return x;
   }
   
   private int indexToY(int index, int height)
   {
	  return index % height;
   }

   public int[] findHorizontalSeam()
   {
     int[] minPath = new int[width];
	 double length = -1.0;

     length = topoMinPath(minPath, width, height, energy);
   
	 return minPath;
   }

   public int[] findVerticalSeam()
   {
     int[] minPath = new int[height];
	 double length = -1.0;
     double[][] t_energy = transpose(energy, width, height);
	 length = topoMinPath(minPath, height, width, t_energy);
     return minPath;
   }

   private double[][] transpose(double[][] energy, int width, int height)
   {
     double[][] t_energy = new double[height][width];
	 for (int i=0; i<width; i++)
	   for (int j=0; j<height; j++)
	     t_energy[j][i] = energy[i][j];
	 return t_energy;
   }

   public void removeHorizontalSeam(int[] seam)
   {
     if (height <= 1)
	   throw new java.lang.IllegalArgumentException("height<=1");
	 if (seam.length != width)
	   throw new java.lang.IllegalArgumentException("Wrong Input for removeHotizontal");
	   
     Picture updated = new Picture(width, height-1);
	 double[][] updatedEnergy = new double[width][height-1];

     for (int col=0; col < width; col++)
	 {
	   if ( col == 0 && !(seam[col] >= 0 && seam[col] < height))
	     throw new java.lang.IllegalArgumentException("Wrong Input for removeHotizontal");

	   if ( col >= 1)
	   {
	     if (!(seam[col] >= 0 && seam[col] < height))
	       throw new java.lang.IllegalArgumentException("Wrong Input for removeHotizontal");
	     int distance = seam[col]-seam[col - 1];
		 if (distance > 1 || distance < -1)
	       throw new java.lang.IllegalArgumentException("Not Adjacent paths");
	   }

	   for (int row = 0; row < seam[col]; row++)
	   {
	     updated.set(col, row, pic_current.get(col, row));
		 updatedEnergy[col][row] = energy[col][row];
	   }
	   for (int row = seam[col]+1; row < height; row++)
	   {
	     updated.set(col, row-1, pic_current.get(col, row));
		 updatedEnergy[col][row-1] = energy[col][row];
	   }
	 }

	 height = height - 1;
	 pic_current = updated;
	 energy = updatedEnergy;

	 for (int i=0; i<width; i++)
	 {
	   int position = seam[i];
	   for (int j=position-2; j <= position +1; j++)
	   {
	     if (j >=0 && j<= height -1)
	       energy[i][j] = energy(i,j);
	   }
     }
   }

   public void removeVerticalSeam(int[] seam)
   {
     if (width <= 1)
	   throw new java.lang.IllegalArgumentException("width<=1");
	 if (seam.length != height)
	   throw new java.lang.IllegalArgumentException("Wrong Input for removeVertical");
	   
     Picture updated = new Picture(width-1, height);
	 double[][] updatedEnergy = new double[width-1][height];

     for (int row=0; row < height; row++)
	 {
	   if (row == 0 && !(seam[row] >= 0 && seam[row] < width))
	     throw new java.lang.IllegalArgumentException("Wrong Input for removeHotizontal");

	   if (row >= 1)
	   {
	     if (!(seam[row] >= 0 && seam[row] < width))
	       throw new java.lang.IllegalArgumentException("Wrong Input for removeHotizontal");

	     int distance = seam[row]-seam[row - 1];
		 if (distance > 1 || distance < -1)
	       throw new java.lang.IllegalArgumentException("Not Adjacent paths");
	   }

	   for (int col = 0; col < seam[row]; col++)
	   {
	     updated.set(col, row, pic_current.get(col, row));
		 updatedEnergy[col][row] = energy[col][row];
	   }
	   for (int col = seam[row]+1; col < width; col++)
	   {
	     updated.set(col-1, row, pic_current.get(col, row));
		 updatedEnergy[col-1][row] = energy[col][row];
	   }
	 }

	 width = width - 1;
	 pic_current = updated;
	 energy = updatedEnergy;

	 for (int i=0; i<height; i++)
	 {
	   int position = seam[i];
	   for (int j=position-2; j <= position +1; j++)
	   {
	     if (j >=0 && j<= width-1)
	       energy[j][i] = energy(j,i);
	   }
     }
   }

   /*public static void main(String[] args)
   {
     Picture pic = new Picture(args[0]);
     SeamCarver sc = new SeamCarver(pic);
	 Iterable<Integer> order = sc.topoOrder();
	 for (int v : order)
	 {
	   StdOut.printf("%d %d\n", sc.indexToX(v), sc.indexToY(v));
	 }
   }*/
}  

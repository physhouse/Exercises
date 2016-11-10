import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdDraw;
import java.util.List;
import java.util.LinkedList;

public class KdTree
{

   private static class Node
   {
     private Point2D data;
	 private RectHV  rect;
	 private Node    lb;
	 private Node	 rt;

	 public Node(Point2D p)
	 {
	   lb = null;
	   rt = null;
	   data = p;
	 }

	 public void SetRect(RectHV r)
	 {
	   rect = r;
	 }

	 public RectHV getRect()
	 {
	   return this.rect;
	 }

   }
   
   private  Node root;
   private  int  size;

   public   KdTree()                                 // construct an empty set of points 
   {
     root = null;
	 size = 0;
   }

   public   boolean isEmpty()                        // is the set empty? 
   {
     return size == 0;
   }

   public   int size()                               // number of points in the set 
   {
     return size;
   }

   public   void insert(Point2D p)                   // add the point to the set (if it is not already in the set)
   {
     if (root == null)
	 {
	   root = new Node(p);
	   size = 1;
	   root.SetRect(new RectHV(0, 0, 1, 1));
	 }
     root = insert(root, p, 0, root.getRect());
   }

   private  Node insert(Node x, Point2D p, int level, RectHV rectangle)  //helper functions like BST insert
   {
     if (x == null) 
	 { 
	   size++;
	   Node member = new Node(p);
	   member.SetRect(rectangle);
	   return member;
	 }

	 if (x.data.compareTo(p) == 0) return x;
     
	 int nextlevel = 1 - level;
	 if (level == 0)
	 {
	   if (x.data.x() > p.x()) 
	   {
	     rectangle = new RectHV(rectangle.xmin(), rectangle.ymin(), x.data.x(), rectangle.ymax());
	     x.lb = insert(x.lb, p, nextlevel, rectangle);
	   }
	   else 
	   {
	     rectangle = new RectHV(x.data.x(), rectangle.ymin(), rectangle.xmax(), rectangle.ymax());
	     x.rt = insert(x.rt, p, nextlevel, rectangle);
	   }
	 }
	 else
	 {
	   if (x.data.y() > p.y()) 
	   {
	     rectangle = new RectHV(rectangle.xmin(), rectangle.ymin(), rectangle.xmax(), x.data.y());
	     x.lb = insert(x.lb, p, nextlevel, rectangle);
	   }
	   else 
	   {
	     rectangle = new RectHV(rectangle.xmin(), x.data.y(), rectangle.xmax(), rectangle.ymax());
	     x.rt = insert(x.rt, p, nextlevel, rectangle);
	   }
	 }
	 return x;
   }

   public   boolean contains(Point2D p)              // does the set contain point p? 
   {
     return find(root, p, 0);
   }

   private  boolean find(Node x, Point2D p, int level)
   {
     if (x == null) return false;

     int nextlevel = 1 - level;
     if (x.data.compareTo(p) == 0) return true;

	 if (level == 0)
	 {
	   if (x.data.x() > p.x()) return find(x.lb, p, nextlevel);
	   else return find(x.rt, p, nextlevel);
	 }
	 else
	 {
	   if (x.data.y() > p.y()) return find(x.lb, p, nextlevel);
	   else return find(x.rt, p, nextlevel);
	 }
   }

   public   void draw()                              // draw all points to standard draw 
   {
     if (root != null) draw(root, 0);
   }

   private  void draw(Node x, int level)
   {
     StdDraw.setPenColor(StdDraw.BLACK);
	 StdDraw.setPenRadius(.01);
     x.data.draw();
	 StdDraw.setPenRadius(.001);

	 int nextlevel = 1 - level;

     if (level == 0)
	 {
	   StdDraw.setPenColor(StdDraw.RED);
	   StdDraw.line(x.data.x(), x.getRect().ymin(), x.data.x(), x.getRect().ymax());
	 }

	 else
	 {
	   StdDraw.setPenColor(StdDraw.BLUE);
	   StdDraw.line(x.getRect().xmin(), x.data.y(), x.getRect().xmax(), x.data.y());
	 }

	 if (x.lb != null) draw(x.lb, nextlevel);
	 if (x.rt != null) draw(x.rt, nextlevel);
   }

   public   Iterable<Point2D> range(RectHV rect)     // all points that are inside the rectangle 
   {
     List<Point2D> q = new LinkedList<Point2D>();
	 range(root, rect, q);
	 return q;
   }

   private  void range(Node x, RectHV rect, List<Point2D> q)
   {
     //pruning the BST
	 if (x == null)
	    return;

     if (!rect.intersects(x.getRect()))
	    return;

	 if (rect.contains(x.data)) q.add(x.data);

	 range(x.lb, rect, q);
	 range(x.rt, rect, q);
   }

   public   Point2D nearest(Point2D p)               // a nearest neighbor in the set to point p; null if the set is empty 
   {
     if (isEmpty())
	   return null;

     Point2D champion = root.data;
	 double  minDist = Double.POSITIVE_INFINITY;
	 return nearestNeighbor(root, p, 0, champion, minDist);
   }

   private  Point2D nearestNeighbor(Node x, Point2D p, int level, Point2D champion, double minDist)
   {
     if (x == null)
	   return champion;

     double currDist = x.data.distanceSquaredTo(p);
	 double minpossibleDist = x.getRect().distanceSquaredTo(p);

	 if (minpossibleDist > minDist)
	   return champion;
     else
	 {
	   if (currDist < minDist)
	   {
	     minDist = currDist;
	     champion = x.data;
	   }

	   if (level == 0)
	   {
	     int nextlevel = 1;
		 if (p.x() < x.data.x())
		 {
	       champion = nearestNeighbor(x.lb, p, nextlevel, champion, minDist);
		   minDist = champion.distanceSquaredTo(p);
	       champion = nearestNeighbor(x.rt, p, nextlevel, champion, minDist);
		 }
		 else
		 {
	       champion = nearestNeighbor(x.rt, p, nextlevel, champion, minDist);
		   minDist = champion.distanceSquaredTo(p);
	       champion = nearestNeighbor(x.lb, p, nextlevel, champion, minDist);
		 }
	   }
       else
	   {
	     int nextlevel = 0;
		 if (p.y() < x.data.y())
		 {
	       champion = nearestNeighbor(x.lb, p, nextlevel, champion, minDist);
		   minDist = champion.distanceSquaredTo(p);
	       champion = nearestNeighbor(x.rt, p, nextlevel, champion, minDist);
		 }
		 else
		 {
	       champion = nearestNeighbor(x.rt, p, nextlevel, champion, minDist);
		   minDist = champion.distanceSquaredTo(p);
	       champion = nearestNeighbor(x.lb, p, nextlevel, champion, minDist);
		 }
	   }

	 }

	 return champion;
   }


   public static void main(String[] args)            // unit testing of the methods (optional) 
   {
     KdTree kd = new KdTree();
	 kd.insert(new Point2D(0.4, 0.2));
	 kd.insert(new Point2D(0.1, 0.8));
	 kd.insert(new Point2D(0.3, 0.6));
	 kd.insert(new Point2D(0.9, 0.2));
	 kd.insert(new Point2D(0.5, 0.2));
     StdOut.println("Find existing point: " + kd.contains(new Point2D(0.9, 0.2)));
   	 StdOut.println("Find non-existant p: " + kd.contains(new Point2D(0.2, 0.6)));
	 StdOut.println("Count of nodes = 5 : " + kd.size());
	 kd.insert(new Point2D(0.5, 0.2));
	 StdOut.println("Should not increase : " + kd.size());
	 kd.draw();
   }
}

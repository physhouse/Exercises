import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.SET;
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.StdDraw;
import java.util.List;
import java.util.LinkedList;

public class PointSET 
{
   private  SET<Point2D> pSet;  // In java STl, the set was implemented as Red Black Tree
   
   public   PointSET()                               // construct an empty set of points 
   {
      pSet = new SET<Point2D>();
   }

   public   boolean isEmpty()                        // is the set empty? 
   {
      return size() == 0;
   }

   public   int size()                               // number of points in the set 
   {
      return pSet.size();
   }

   public   void insert(Point2D p)                   // add the point to the set (if it is not already in the set)
   {
      pSet.add(p); 
   }

   public   boolean contains(Point2D p)              // does the set contain point p? a
   {
	  return pSet.contains(p);
   }

   public   void draw()                              // draw all points to standard draw 
   {
      StdDraw.setPenColor(StdDraw.BLACK);
	  StdDraw.setPenRadius(.01);

      for (Point2D tmp : pSet)
	  {
	    tmp.draw();
	  }
	  StdDraw.show(0);
   }

   public   Iterable<Point2D> range(RectHV rect)     // all points that are inside the rectangle 
   {
      List<Point2D> q = new LinkedList<Point2D>();
      for (Point2D tmp : pSet)
	  {
	  	if (rect.contains(tmp))
		  q.add(tmp);
	  }
	  return q;
   }

   public   Point2D nearest(Point2D p)               // a nearest neighbor in the set to point p; null if the set is empty 
   {
      Point2D nn = new Point2D(1,1);
	  double  min = Double.POSITIVE_INFINITY;
      for (Point2D tmp : pSet)
	  {
	    double dist = tmp.distanceTo(p);
	  	if (dist < min)
		{
		  nn = tmp;
		  min = dist;
		}
      }
	  return nn;
   }
}

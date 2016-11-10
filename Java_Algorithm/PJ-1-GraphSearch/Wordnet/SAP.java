import edu.princeton.cs.algs4.Digraph;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.Queue;
import java.util.ArrayList;


public class SAP {
   private int[] edgetov;
   private int[] edgetow;
   private int[] distov;
   private int[] distow;
   private boolean[] markedv;
   private boolean[] markedw;
   private Digraph DG;

   public SAP(Digraph G) {
     DG = new Digraph(G);
     markedv = new boolean[G.V()];
     markedw = new boolean[G.V()];
     edgetov = new int[G.V()];
     edgetow = new int[G.V()];
     distov = new int[G.V()];
     distow = new int[G.V()];
     
   }

   public int length(int v, int w) {
     if (v==w)
	    return 0;
	
     for (int p=0; p<DG.V(); p++) {
    	distov[p]=-10000;
	    distow[p]=-10000;
        markedv[p]=false;
        markedw[p]=false;
     }
  
     int best_length = 1000000;

     Queue<Integer> qv = new Queue<Integer>();
     Queue<Integer> qw = new Queue<Integer>();
     markedv[v]=true;
     markedw[w]=true;
     qv.enqueue(v);
     qw.enqueue(w);
     distov[v]=0;
     distow[w]=0;
     //concurrently BFS
     while (!qv.isEmpty() || !qw.isEmpty())
     {
	   if(!qv.isEmpty())
	   {
	     int vr = qv.dequeue();
		 if (markedw[vr])
		 {
		    int dist_now = distov[vr]+distow[vr];
			if (dist_now < best_length)
			{
			   best_length = dist_now;
			}
		 }

	     for (int v_n : DG.adj(vr))
	     {
	       if(!markedv[v_n])
	       {
		     edgetov[v_n] = vr;
		     markedv[v_n] = true;
	   	     distov[v_n]  = distov[vr]+1;

			 if (distov[v_n] > best_length)
			 	return best_length;

		     if (markedw[v_n])
		     {
		       int dist_now = distov[v_n]+distow[v_n];
			   if (dist_now < best_length)
			   {
			      best_length = dist_now;
			   }
		     }
		     qv.enqueue(v_n);
	       }
	     }	 
       }
   
       //System.out.println(markedv[4]);
	   if(!qw.isEmpty())
	   {
	     int wr = qw.dequeue();
		 if (markedv[wr])
		 {
		    int dist_now = distov[wr]+distow[wr];
			if (dist_now < best_length)
			{
			   best_length = dist_now;
			}
		 }
	     for (int w_n : DG.adj(wr))
	     {
	       if(!markedw[w_n])
	       {
		     edgetow[w_n] = wr;
		     markedw[w_n] = true;
	   	     distow[w_n]  = distow[wr]+1;

			 if (distow[w_n] > best_length)
			 	return best_length;

		     if (markedv[w_n])
		     {
		       int dist_now = distov[w_n]+distow[w_n];
			   if (dist_now < best_length)
			   {
			      best_length = dist_now;
			   }
		     }
		     qw.enqueue(w_n);
	       }
	     }
	   }
     }

	 if (best_length > 100000) return -1;
	 else
       return best_length;
   }

   public int ancestor(int v, int w)
   {
     if (v==w)
	    return v;

     for (int p=0; p<DG.V(); p++) {
    	distov[p]=-10000;
	    distow[p]=-10000;
        markedv[p]=false;
        markedw[p]=false;
     }
	
	 int best_length = 1000000;
	 int ancestor = -1;
     Queue<Integer> qv = new Queue<Integer>();
     Queue<Integer> qw = new Queue<Integer>();
     markedv[v]=true;
     markedw[w]=true;
     qv.enqueue(v);
     qw.enqueue(w);
     distov[v]=0;
     distow[w]=0;
     //concurrently BFS
     while (!qv.isEmpty() || !qw.isEmpty())
     {
	   if(!qv.isEmpty())
	   {
	     int vr = qv.dequeue();
		 if (markedw[vr])
		 {
		    int dist_now = distov[vr]+distow[vr];
			if (dist_now < best_length)
			{
			   best_length = dist_now;
			   ancestor = vr;
			}
		 }
	     for (int v_n : DG.adj(vr))
	     {
	       if(!markedv[v_n])
	       {
		     edgetov[v_n] = vr;
		     markedv[v_n] = true;
	   	     distov[v_n]  = distov[vr]+1;

			 if (distov[v_n] > best_length)
			 	return ancestor;

		     if (markedw[v_n])
		     {
		       int dist_now = distov[v_n]+distow[v_n];
			   if (dist_now < best_length)
			   {
			      best_length = dist_now;
				  ancestor = v_n;
			   }
		     }
		     qv.enqueue(v_n);
	       }
	     }	 
       }
   
       //System.out.println(markedv[4]);
	   if(!qw.isEmpty())
	   {
	     int wr = qw.dequeue();
		 if (markedv[wr])
		 {
		    int dist_now = distov[wr]+distow[wr];
			if (dist_now < best_length)
			{
			   best_length = dist_now;
			   ancestor = wr;
			}
		 }
	     for (int w_n : DG.adj(wr))
	     {
	       if(!markedw[w_n])
	       {
		     edgetow[w_n] = wr;
		     markedw[w_n] = true;
	   	     distow[w_n]  = distow[wr]+1;

			 if (distow[w_n] > best_length)
			 	return ancestor;

		     if (markedv[w_n])
		     {
		       int dist_now = distov[w_n]+distow[w_n];
			   if (dist_now < best_length)
			   {
			      best_length = dist_now;
				  ancestor = w_n;
			   }
		     }
		     qw.enqueue(w_n);
	       }
	     }
	   }
     }
     return ancestor;
   }

   public int length(Iterable<Integer> v, Iterable<Integer> w)
   {
     for (int p=0; p<DG.V(); p++) {
    	distov[p]=-10000;
	    distow[p]=-10000;
        markedv[p]=false;
        markedw[p]=false;
     }

     int best_length = 1000000;
     Queue<Integer> qv = new Queue<Integer>();
     Queue<Integer> qw = new Queue<Integer>();
     for (int sv : v)
     {
       markedv[sv]=true;
       qv.enqueue(sv);
       distov[sv]=0;
     }
     for (int sw: w)
     {
       markedw[sw]=true;
	   if (markedv[sw])
	      return 0;
       qw.enqueue(sw);
       distow[sw]=0;
     }
	 
     //concurrently BFS
     while (!qv.isEmpty() || !qw.isEmpty())
     {
	   if(!qv.isEmpty())
	   {
	     int vr = qv.dequeue();
		 if (markedw[vr])
		 {
		    int dist_now = distov[vr]+distow[vr];
			if (dist_now < best_length)
			{
			   best_length = dist_now;
			}
		 }
	     for (int v_n : DG.adj(vr))
	     {
	       if(!markedv[v_n])
	       {
		     edgetov[v_n] = vr;
		     markedv[v_n] = true;
	   	     distov[v_n]  = distov[vr]+1;

			 if (distov[v_n] > best_length)
			 	return best_length;

		     if (markedw[v_n])
		     {
		       int dist_now = distov[v_n]+distow[v_n];
			   if (dist_now < best_length)
			      best_length = dist_now;
		     }
		     qv.enqueue(v_n);
	       }
	     }	 
       }
   
       //System.out.println(markedv[4]);
	   if(!qw.isEmpty())
	   {
	     int wr = qw.dequeue();
		 if (markedv[wr])
		 {
		    int dist_now = distov[wr]+distow[wr];
			if (dist_now < best_length)
			{
			   best_length = dist_now;
			}
		 }
	     for (int w_n : DG.adj(wr))
	     {
	       if(!markedw[w_n])
	       {
		     edgetow[w_n] = wr;
		     markedw[w_n] = true;
	   	     distow[w_n]  = distow[wr]+1;

			 if (distow[w_n] > best_length)
			 	return best_length;

		     if (markedv[w_n])
		     {
		       int dist_now = distov[w_n]+distow[w_n];
			   if (dist_now < best_length)
			      best_length = dist_now;
		     }
		     qw.enqueue(w_n);
	       }
	     }
	   }
     }

	 if (best_length > 100000) return -1;
	 else
       return best_length;
   }

   public int ancestor(Iterable<Integer> v, Iterable<Integer> w)
   {
     for (int p=0; p<DG.V(); p++) {
    	distov[p]=-10000;
	    distow[p]=-10000;
        markedv[p]=false;
        markedw[p]=false;
     }
    
	 int best_length = 1000000;
	 int ancestor = -1;
     Queue<Integer> qv = new Queue<Integer>();
     Queue<Integer> qw = new Queue<Integer>();
     for (int sv : v)
     {
       markedv[sv]=true;
       qv.enqueue(sv);
       distov[sv]=0;
     }
     for (int sw: w)
     {
       markedw[sw]=true;
	   if (markedv[sw])
	     return sw;
       qw.enqueue(sw);
       distow[sw]=0;
     }
     //concurrently BFS
     while (!qv.isEmpty() || !qw.isEmpty())
     {
	   if(!qv.isEmpty())
	   {
	     int vr = qv.dequeue();
		 if (markedw[vr])
		 {
		    int dist_now = distov[vr]+distow[vr];
			if (dist_now < best_length)
			{
			   best_length = dist_now;
			   ancestor = vr;
			}
		 }
	     for (int v_n : DG.adj(vr))
	     {
	       if(!markedv[v_n])
	       {
		     edgetov[v_n] = vr;
		     markedv[v_n] = true;
	   	     distov[v_n]  = distov[vr]+1;

			 if (distov[v_n] > best_length)
			 	return ancestor;

		     if (markedw[v_n])
		     {
		       int dist_now = distov[v_n]+distow[v_n];
			   if (dist_now < best_length)
			   {
			      best_length = dist_now;
				  ancestor = v_n;
			   }
		     }
		     qv.enqueue(v_n);
	       }
	     }	 
       }
   
       //System.out.println(markedv[4]);
	   if(!qw.isEmpty())
	   {
	     int wr = qw.dequeue();
		 if (markedv[wr])
		 {
		    int dist_now = distov[wr]+distow[wr];
			if (dist_now < best_length)
			{
			   best_length = dist_now;
			   ancestor = wr;
			}
		 }
	     for (int w_n : DG.adj(wr))
	     {
	       if(!markedw[w_n])
	       {
		     edgetow[w_n] = wr;
		     markedw[w_n] = true;
	   	     distow[w_n]  = distow[wr]+1;

			 if (distow[w_n] > best_length)
			 	return ancestor;

		     if (markedv[w_n])
		     {
		       int dist_now = distov[w_n]+distow[w_n];
			   if (dist_now < best_length)
			   {
			      best_length = dist_now;
				  ancestor = w_n;
			   }
		     }
		     qw.enqueue(w_n);
	       }
	     }
	   }
     }
     return ancestor;
   }

   public static void main (String[] args) {
	In in = new In(args[0]);
	Digraph G = new Digraph(in);	
	//int v = Integer.parseInt(args[1]);
	//int w = Integer.parseInt(args[2]);
    //ArrayList<Integer> s = new ArrayList<Integer>();
	//s.add(10);
	//s.add(1);

    //ArrayList<Integer> sp = new ArrayList<Integer>();
	//sp.add(5);
	//sp.add(0);
    int s = 14;
	int sp = 21;
	SAP example = new SAP(G);
	int result = example.length(s,sp);
	int ances = example.ancestor(s,sp);
	StdOut.printf("dist = %d\n", result);
	StdOut.printf("ancestor = %d\n", ances);
	//StdOut.printf("distance between %d and %d = %d\n", v, w, result);
	//StdOut.printf("ancestor between %d and %d = %d\n", v, w, ances);
   }
}

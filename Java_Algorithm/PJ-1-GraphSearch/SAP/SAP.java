import edu.princeton.cs.algs4.Digraph;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.Queue;


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
     for (int v=0; v<G.V(); v++) {
	distov[v]=-10000;
	distow[v]=-10000;
     }
     
   }

   public int length(int v, int w) {
     Queue<Integer> qv = new Queue<Integer>();
     Queue<Integer> qw = new Queue<Integer>();
     markedv[v]=true;
     markedw[w]=true;
     qv.enqueue(v);
     qw.enqueue(w);
     distov[v]=0;
     distow[w]=0;
     //concurrently BFS
     while (!qv.isEmpty() && !qw.isEmpty())
     {
	int vr = qv.dequeue();
	int wr = qw.dequeue();

	for (int v_n : DG.adj(vr))
	{
	   if(!markedv[v_n])
	   {
		edgetov[v_n] = vr;
		markedv[v_n] = true;
	   	distov[v_n]  = distov[vr]+1;
		if (markedw[v_n])
		{
		   return distov[v_n]+distow[v_n];
		}
		qv.enqueue(v_n);
	   }
	}

	for (int w_n : DG.adj(wr))
	{
	   if(!markedw[w_n])
	   {
		edgetow[w_n] = wr;
		markedw[w_n] = true;
	   	distow[w_n]  = distow[wr]+1;
		if (markedv[w_n])
		{
		   return distov[w_n]+distow[w_n];
		}
		qw.enqueue(w_n);
	   }
	}
	
     }
     return -1;
   }

   public int ancestor(int v, int w)
   {
     Queue<Integer> qv = new Queue<Integer>();
     Queue<Integer> qw = new Queue<Integer>();
     markedv[v]=true;
     markedw[w]=true;
     qv.enqueue(v);
     qw.enqueue(w);
     distov[v]=0;
     distow[w]=0;
     //concurrently BFS
     while (!qv.isEmpty() && !qw.isEmpty())
     {
	int vr = qv.dequeue();
	int wr = qw.dequeue();

	for (int v_n : DG.adj(vr))
	{
	   if(!markedv[v_n])
	   {
		edgetov[v_n] = vr;
		markedv[v_n] = true;
	   	distov[v_n]  = distov[vr]+1;
		if (markedw[v_n])
		{
		   return v_n;
		}
		qv.enqueue(v_n);
	   }
	}

	for (int w_n : DG.adj(wr))
	{
	   if(!markedw[w_n])
	   {
		edgetow[w_n] = wr;
		markedw[w_n] = true;
	   	distow[w_n]  = distow[wr]+1;
		if (markedv[w_n])
		{
		   return w_n;
		}
		qw.enqueue(w_n);
	   }
	}
	
     }
     return -1;
   }

   public int length(Iterable<Integer> v, Iterable<Integer> w)
   {
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
       qw.enqueue(sw);
       distow[sw]=0;
     }
     //concurrently BFS
     while (!qv.isEmpty() && !qw.isEmpty())
     {
	int vr = qv.dequeue();
	int wr = qw.dequeue();

	for (int v_n : DG.adj(vr))
	{
	   if(!markedv[v_n])
	   {
		edgetov[v_n] = vr;
		markedv[v_n] = true;
	   	distov[v_n]  = distov[vr]+1;
		if (markedw[v_n])
		{
		   return distov[v_n]+distow[v_n];
		}
		qv.enqueue(v_n);
	   }
	}

	for (int w_n : DG.adj(wr))
	{
	   if(!markedw[w_n])
	   {
		edgetow[w_n] = wr;
		markedw[w_n] = true;
	   	distow[w_n]  = distow[wr]+1;
		if (markedv[w_n])
		{
		   return distov[w_n]+distow[w_n];
		}
		qw.enqueue(w_n);
	   }
	}
	
     }
     return -1;
   }

   public int ancestor(Iterable<Integer> v, Iterable<Integer> w)
   {
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
       qw.enqueue(sw);
       distow[sw]=0;
     }
     //concurrently BFS
     while (!qv.isEmpty() && !qw.isEmpty())
     {
	int vr = qv.dequeue();
	int wr = qw.dequeue();

	for (int v_n : DG.adj(vr))
	{
	   if(!markedv[v_n])
	   {
		edgetov[v_n] = vr;
		markedv[v_n] = true;
	   	distov[v_n]  = distov[vr]+1;
		if (markedw[v_n])
		{
		   return v_n;
		}
		qv.enqueue(v_n);
	   }
	}

	for (int w_n : DG.adj(wr))
	{
	   if(!markedw[w_n])
	   {
		edgetow[w_n] = wr;
		markedw[w_n] = true;
	   	distow[w_n]  = distow[wr]+1;
		if (markedv[w_n])
		{
		   return w_n;
		}
		qw.enqueue(w_n);
	   }
	}
	
     }
     return -1;
   }

   public static void main (String[] args) {
	In in = new In(args[0]);
	Digraph G = new Digraph(in);	
	int v = Integer.parseInt(args[1]);
	int w = Integer.parseInt(args[2]);

	SAP example = new SAP(G);
	int result = example.length(v,w);
	StdOut.printf("distance between %d and %d = %d\n", v, w, result);
   }
}

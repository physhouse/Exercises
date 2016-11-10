import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Digraph;
import edu.princeton.cs.algs4.DepthFirstOrder;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.KosarajuSharirSCC;

public class test{
	public static void main(String[] args)
	{
		In in = new In(args[0]);
		Digraph G = new Digraph(in);
	
		KosarajuSharirSCC scc = new KosarajuSharirSCC(G);
		int m = scc.count();
		StdOut.println(m + " components");


	}
}

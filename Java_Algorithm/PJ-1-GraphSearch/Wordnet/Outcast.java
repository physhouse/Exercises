import java.util.ArrayList;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;

public class Outcast
{
    private WordNet net;

	public Outcast(WordNet wordnet)
	{
	   this.net = wordnet;
	}
	
	public String outcast(String[] nouns)
	{
	   int size = nouns.length;

	   int[] distance;
	   distance = new int[size];
	   for (int i=0; i<size; i++) distance[i] = 0;

	   for (int i=0; i<size; i++)
	   {
	      for (int j=i+1; j<size; j++)
		  {
		  	  int dij = net.distance(nouns[i], nouns[j]);
		  	  distance[i] += dij;
		  	  distance[j] += dij;
		  }
	   }

	   int max = 0;
	   int dmax = 0;
	   for (int i=0; i<size; i++)
	   {
	      //System.out.println(i+" = "+distance[i]);
	      if(distance[i] > dmax) 
		  {
		  	max = i;
			dmax = distance[i];
		  }
	   }
	
	   return nouns[max];
	}

	public static void main(String[] args)
	{
	   WordNet wordnet = new WordNet(args[0], args[1]);
	   Outcast outcast = new Outcast(wordnet);
	   for (int t = 2; t < args.length; t++) {
		  In in = new In(args[t]);
          String[] nouns = in.readAllStrings();
	      StdOut.println(args[t] + ": " + outcast.outcast(nouns));
	   }
	}
}

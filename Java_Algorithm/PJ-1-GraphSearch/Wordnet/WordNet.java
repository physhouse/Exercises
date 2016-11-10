import java.util.HashMap;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.Iterator;
import java.util.HashSet;
import java.util.Set;
import edu.princeton.cs.algs4.Digraph;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.Queue;


public class WordNet {
   private  class synline
   {
     private int id;
	 private String synset;
	 synline(int index, String input)
	 {
	 	this.id = index;
		this.synset = input;
	 }
   }
   private  HashMap<String, HashSet<Integer>> word2ids;
   private  ArrayList<synline> linemap;
   private  Digraph DG;
   private  SAP sap;

   public WordNet(String synsets, String hypernyms) {
	//check arguments
	if ((synsets == null) || (hypernyms==null))
	   throw new IllegalArgumentException("Check your input files");

	int setcount = 0;
	int nouncount = 0;
	int edgecount = 0;
	In input_set = new In(synsets);
	String line = input_set.readLine();
	word2ids = new HashMap<String, HashSet<Integer>>();
	linemap = new ArrayList<synline>();

	while(line!= null)
	{
	  String[] fields = line.split(",");
	  int id = Integer.parseInt(fields[0]);
	  synline thisline = new synline(id, fields[1]);
	  linemap.add(thisline);
	  String[] nouns = fields[1].split(" ");
	  for (String n : nouns)
	  {
	     //System.out.println(n);
	     if (!word2ids.containsKey(n))
	     {
	  	    nouncount++;
	     	word2ids.put(n, new HashSet<Integer>());
	     }
	     word2ids.get(n).add(id);
	  }
	  setcount++;
	  line = input_set.readLine();
	}

	/*Set set = word2ids.entrySet();
	Iterator iterator = set.iterator();	
	while (iterator.hasNext()) {
	  Map.Entry mentry = (Map.Entry)iterator.next();
	  System.out.print("key is "+mentry.getKey()+" value is ");
	  System.out.println(mentry.getValue());
	}
	System.out.println("Initialization finished");*/ //These are testing code

	DG = new Digraph(setcount);
	In input_hyper = new In(hypernyms);
	line = input_hyper.readLine();
	while(line != null)
	{
	  String[] fields = line.split(",");
	  int id = Integer.parseInt(fields[0]);
	  //System.out.println(id);
	  for (int i=1; i<fields.length; i++)
	  {
	     int v = Integer.parseInt(fields[i]);
	     DG.addEdge(id, v);
		 edgecount++;
	  }
	  line = input_hyper.readLine();
	}
	
	sap = new SAP(DG);	
	//System.out.println(nouncount);
	//System.out.println(edgecount);
	//System.out.println("Passed phase 2");

   }

   public Iterable<String> nouns()
   {
       return word2ids.keySet();
   }

   public boolean isNoun(String word)
   {
       if (word == null)
	   {
	   	  throw new NullPointerException("Cannot accept null pointer");
	   }
       return word2ids.containsKey(word);
   }

   public int distance(String nounA, String nounB)
   {    
       if (nounA == null || nounB == null)
	   {
	   	  throw new NullPointerException("Cannot accept null pointer");
	   }

       HashSet<Integer> setA = word2ids.get(nounA);
       HashSet<Integer> setB = word2ids.get(nounB);

	   if (setA.isEmpty() || setB.isEmpty())
	   {
	      throw new IllegalArgumentException("Not defined words");
	   }
	   return sap.length(setA, setB);
   }

   public String sap(String nounA, String nounB)
   {
       if (nounA == null || nounB == null)
	   {
	   	  throw new NullPointerException("Cannot accept null pointer");
	   }
       HashSet<Integer> setA = word2ids.get(nounA);
       HashSet<Integer> setB = word2ids.get(nounB);

	   if (setA.isEmpty() || setB.isEmpty())
	   {
	      throw new IllegalArgumentException("Not defined words");
	   }

	   int ancestor =  sap.ancestor(setA, setB);
	   //System.out.println(ancestor);
	   if (ancestor == -1)
	   	  return "None";
	   else
	      return linemap.get(ancestor).synset;
   }
   
   public static void main(String []args)
   {
	   WordNet wn = new WordNet(args[0], args[1]);
	   System.out.println("initiliazation");
	   //System.out.println(wn.sap("worm","bird"));
	   System.out.println(wn.distance("Black_Plague","black_marlin"));
	   System.out.println(wn.distance("American_water_spaniel","histology"));
	   System.out.println(wn.distance("worm","bird"));
	   System.out.println(wn.distance("individual","edible_fruit"));
	   System.out.println(wn.distance("municipality","region"));
	   System.out.println(wn.distance("white_marlin","mileage"));
	   //System.out.println(wn.sap("Brown_Swiss","barrel_roll"));
   }
}

import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.In;
import java.util.List;
import java.util.LinkedList;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Collections;

public class BoggleSolver
{
  private TST<Integer> dictionary;

  public BoggleSolver(String[] dictionary)
  {
    this.dictionary = new TST<Integer>();
    for (String s: dictionary)
	  this.dictionary.put(s, 1108);
  }

  public Iterable<String> getAllValidWords(BoggleBoard board)
  {
    List<String> results = new LinkedList<String>();
    int rows = board.rows();
	int cols = board.cols();

	for (int i=0; i<rows; i++)
	  for (int j=0; j<cols; j++)
	    results.addAll(validWords(i, j, board));
	
    List<String> sortedResults = new ArrayList<String>(new HashSet<String>(results));
	Collections.sort(sortedResults);
	return sortedResults;
  }

  private LinkedList<String> validWords(int i, int j, BoggleBoard board)
  {
     int rows = board.rows();
	 int cols = board.cols();
	 int marked[][] = new int[rows][cols];

	 for (int m=0; m<rows; m++)
	   for (int n=0; n<cols; n++)
	     marked[m][n] = 0;
	
	 String prefix = "";
	 LinkedList<String> result = new LinkedList<String>();
	 getValidWords(i, j, board, marked, rows, cols, prefix, result); 

     return result;
  }

  private void getValidWords(int i, int j, BoggleBoard board, int[][] marked, int rows, int cols, String prefix, LinkedList<String> result)
  {
    marked[i][j] = 1;
	char letter = board.getLetter(i,j);

	if (letter == 'Q')
	{
	  prefix += "QU";
	}
	else
	  prefix += letter;

    if (!dictionary.hasPrefix(prefix))
	{
	  marked[i][j] = 0;
      prefix = prefix.substring(0, prefix.length()-1);	
	  return;
	}

    if (prefix.length() > 2 && dictionary.contains(prefix))
	  result.add(prefix);

	for (int m=-1; m<2; m++)
	  for (int n=-1; n<2; n++)
	  {
	    if (m == 0 && n == 0) continue;

		if (i+m<rows && i+m >= 0 && j+n < cols && j+n >=0)
		{
		  if (marked[i+m][j+n] == 0)
		  {
		    getValidWords(i+m, j+n, board, marked, rows, cols, prefix, result);
		  }
		}
	  }

	marked[i][j] = 0;
    prefix = prefix.substring(0, prefix.length()-1);	
  }

  public int scoreOf(String word)
  {        
    if (dictionary.contains(word)) 
	{
      switch (word.length()) 
	  {
		case 0:
		case 1:
		case 2:
		  return 0;
		case 3:
		case 4:
		  return 1;
		case 5:
		  return 2;
	    case 6:
	      return 3;
		case 7:
		  return 5;
		default:
		  return 11;
	   }
	 }
	 else return 0;
  }

  public static void main(String[] args)
  {
    In in = new In(args[0]);
	String[] dictionary = in.readAllStrings();
	BoggleSolver solver = new BoggleSolver(dictionary);
	BoggleBoard  board  = new BoggleBoard(args[1]);
	int score = 0;
	for (String word : solver.getAllValidWords(board))
	{
	  StdOut.println(word);
	  score += solver.scoreOf(word);
	}
	StdOut.println("Score = " + score);
  }
}

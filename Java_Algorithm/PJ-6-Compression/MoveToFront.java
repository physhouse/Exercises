import java.util.LinkedList;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.BinaryStdIn;
import edu.princeton.cs.algs4.BinaryStdOut;

public class MoveToFront
{
  public static void encode()
  {
    LinkedList<Character> list = new LinkedList<Character>();
	for (int i=0; i<256; i++) list.add((char)i);

	while (BinaryStdIn.isEmpty() == false)
	{
	  char c = BinaryStdIn.readChar();
	  int index = list.indexOf(c);
	  BinaryStdOut.write((char)index);
	  list.remove(index);
	  list.addFirst(c);
	}
	  BinaryStdOut.flush();
	  BinaryStdOut.close();
  }

  public static void decode()
  {
    LinkedList<Character> list = new LinkedList<Character>();
	for (int i=0; i<256; i++) list.add((char)i);

	while (BinaryStdIn.isEmpty() == false)
	{
	  char index = BinaryStdIn.readChar();
	  char c = list.get(index);
	  BinaryStdOut.write(c);
	  list.remove(index);
	  list.addFirst(c);
	}
	  BinaryStdOut.flush();
	  BinaryStdOut.close();
  }

  public static void main(String[] args)
  {      
    if (args.length != 1)
       throw new IllegalArgumentException("Expected + or -\n");
    else if (args[0].equals("+"))
       decode();
	else if (args[0].equals("-"))
	   encode();
	else {
	   String msg = "Unknown argument: " + args[0] + "\n";
	   throw new IllegalArgumentException(msg);
    }
  }
}

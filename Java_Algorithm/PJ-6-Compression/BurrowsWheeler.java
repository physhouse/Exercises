import edu.princeton.cs.algs4.BinaryStdIn;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.BinaryStdOut;

public class BurrowsWheeler
{

   public static void encode()
   {
     String s = BinaryStdIn.readString();
	 CircularSuffixArray csa = new CircularSuffixArray(s);
	 int len = csa.length();
	 int first = 0;
	 for (int i=0; i<len; i++)
	 {
	   if (csa.index(i) == 0)
	   {
	     first = i;
		 break;
	   }
	 }

     BinaryStdOut.write(first);
	 for (int i=0; i<len; i++)
	 {
	   BinaryStdOut.write(s.charAt((csa.index(i) + len - 1) % len));
	 }
	 BinaryStdOut.close();
   }

   public static void decode()
   {
     int R = 256; //ASCII Code
     int first = BinaryStdIn.readInt();
	 String t  = BinaryStdIn.readString();
	 int len = t.length();
	 int[] next = new int[len];
	 int[] count = new int[R+1];
     char[] front = new char[len];

     //This also can be done with linked queue
	 for (int i=0; i<len; i++)
	 {
	   count[t.charAt(i) + 1]++;
	 }

     int j=0;
     for (int i=1; i<R+1; i++)
	 {
	   int num = count[i];
	   if (num == 0) continue;

	   char c_i = (char)(i-1);
	   for (int k=0; k<num; k++) {
	     front[j++] = c_i;
	   }
	 }

	 for (int i=1; i<R+1; i++)
	 {
	   count[i] += count[i-1];
	 }

	 for (int i=0; i<len; i++)
	 {
	   next[count[t.charAt(i)]++] = i;
	 }

	 for (int i=first, c=0; c<len; i = next[i], c++)
	 {
	   BinaryStdOut.write(front[i]);
	 }
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

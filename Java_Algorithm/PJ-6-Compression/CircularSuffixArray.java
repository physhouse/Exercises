import edu.princeton.cs.algs4.StdOut;

public class CircularSuffixArray
{
   private int[] index;
   private int len;
   private int CUTOFF;  //cutoff to insertion

   public CircularSuffixArray(String s)
   {
     len = s.length();
	 index = new int[len];
	 for (int i=0; i<len; i++)
	   index[i] = i;
	 sort(s, 0, len-1, 0);
   }

   private void sort(String s, int lo, int hi, int d)  //3-Way QuickSort, complexity N * logR(N) N->length of String
   { 
     if (lo >= hi)
	   return;

     /*if (hi <= lo + CUTOFF)
	 {
	   insertion(s, lo, hi, d);
	   return;
	 }*/

     int lt = lo;
	 int gt = hi;
	 int pind = (index[lo] + d) % len; //index of pivot
     int pivot = s.charAt(pind);
	 int i = lt + 1;
	 while (i <= gt)
	 {
	   int tind = (index[i] + d) % len;
	   int t = s.charAt(tind);

	   if (t < pivot) exchange(lt++, i++);
	   else if (t > pivot) exchange(i, gt--);
	   else	i++;
	 }

	 sort(s, lo, lt-1, d);
	 if (pivot >= 0) sort(s, lt, gt, d+1);
	 sort(s, gt+1, hi, d);
   }

   /*private void insertion(String s, int lo, int hi, int d)
   {
     for (int i=lo; i<=hi; i++)
	 {
	   for (int j=i; j>lo && less(s, j, j-1, d); j--)
	     exchange(j, j-1);
	 }
   }

   private boolean less(String s, int i, int j, int d)
   {
     int index_i = (index[i] + d) % len;
	 int index_j = (index[j] + d) % len;
	 return s.charAt(index_i) < 
   }*/

   private void exchange(int i, int j)
   {
      int tmp = index[i];
	  index[i] = index[j];
	  index[j] = tmp;
   }

   public int length()
   {
      return len;
   }

   public int index(int i)
   {
      if (i < 0 || i >= len)
	    throw new java.lang.IndexOutOfBoundsException("Index out of bounds!");
      return index[i];
   }

   public static void main(String[] args) //Unit Test
   {
     String s = "ABRACADABRA!";
	 CircularSuffixArray csa = new CircularSuffixArray(s);
	 for (int i=0; i<s.length(); i++)
	   StdOut.println(csa.index(i));
   }
}

public class fib2 {


public static int FIB=5;

public static int g0,ans,g1;


public static int fib(int n)
{
  System.out.print("fib: ");
  System.out.println(n);
  switch(n) {
    case 0: return 1;
    case 1: return 1;
    default: return fib(n-1)+fib(n-2);
  }
}

public static void  main(String args[])
{
  ans=fib(FIB);
  g0=0xfeedface;
  g1=0xdeadbeaf;
  System.out.println(g0);
  System.out.println(ans);
  System.out.println(g1);
}

}

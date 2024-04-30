public class test2 {


public static void foo(String s)
{
  int t,i;
  for(t=0;t<=26;t++) {
    for(i=0;i<t;i++) System.out.print(s.charAt(i));
    System.out.println();
  }
}


public static void main(String args[])
{
  int q;
  String ss="abcdefghijklmnopqrstuvxwyz";
  for(q=0;q<10;q++) foo(ss);
}

}

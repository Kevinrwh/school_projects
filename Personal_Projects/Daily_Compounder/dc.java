import java.util.*;

/* daily compounder*/

public class dc {
  public static void main(String[] args)
  {
    float initialAmount;

    Scanner sc = new Scanner(System.in);
    initialAmount = sc.nextFloat();

    System.out.println("Test: " + initialAmount*1.05);

    float totalAfterCompounding = initialAmount;

    for(int i = 0; i < 265; i++){
      totalAfterCompounding*=1.05;
    }

    System.out.println("Total amount = " + totalAfterCompounding);
  }
}

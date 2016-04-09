import java.util.*; 

public class Solution {
    public static void main(String []args) {
        int[] nums = {10, 9, 2, 5, 3, 7, 101, 18};
        int len;
        len = lengthOfLIS(nums);
    }
    
    public static int lengthOfLIS(int[] nums) {            
        int[] dp = new int[nums.length];
        int len = 0;

        for(int x : nums) {
            int i = Arrays.binarySearch(dp, 0, len, x);
            System.out.print("x = " + x);
            System.out.print(" len = " + len);
            System.out.print(" i_0 = " + i);
            if(i < 0) i = -(i + 1);
            System.out.println(" i = " + i);
            dp[i] = x;
            if(i == len) len++;
            System.out.println("len = " + len);
            System.out.println(Arrays.toString(dp));
        }

        return len;
    }
}

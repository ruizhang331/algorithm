//https://leetcode.com/problems/sum-of-square-numbers/#/description
/*
Given a non-negative integer c, your task is to decide whether there're two integers a and b such that a2 + b2 = c.

Example 1:
Input: 5
Output: True
Explanation: 1 * 1 + 2 * 2 = 5
Example 2:
Input: 3
Output: False
*/

bool judgeSquareSum(int c) {
    if (c < 0) {
        return false;
    }
    int left = 0, right = sqrt(c);
    while (left <= right) {
        int cur = left * left + right * right;
        if (cur < c) {
            left++;
        } else if (cur > c) {
            right--;
        } else {
            return true;
        }
    }
    return false;
}

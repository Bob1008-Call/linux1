#!usr/bin/python
#coding=utf-8

class Solution(object):
    def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        start = -1
        max = 0
        dic = {}
        # dic 里面存放的就是当前字符最迟出现的位置，start记录的是可以作为新的max字符串的起点，最后i遍历到结尾，i-start就是最长字符串的长度
        for i in range(len(s)):
            if s[i] in dic and start < dic[s[i]]:
                start = dic[s[i]]
                dic[s[i]] = i
            else:
                dic[s[i]] = i
                if i - start > max:
                    max = i - start
        return max

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
       int size = nums.size();
       vector<int> result;
       unordered_map<int, int> m;
       for (int i = 0; i < size; ++i) {
	       if (m.find(target-nums[i]) != m.end()) {
#ifdef TEST
		       cout << nums[i] << " " << target - nums[i] << "; " << i << " " << m[i] << endl;
#endif
		       result.push_back(m[target -nums[i]]+1);
		       result.push_back(i+1);
		       break;
	       } else {
		       m[nums[i]] = i;
	       }
       }

       return result;
    }
};

int main()
{
	vector<int> nums{0, 4, 3, 0};
	vector<int> result;
	Solution s;
	result = s.twoSum(nums, 0);
	cout << result[0] << " " << result[1] << endl;


	return 0;
}

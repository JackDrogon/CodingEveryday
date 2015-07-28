#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
       int size = nums.size();
       bool flag = true;
       vector<int> result;
       for (int i = 0; i < size && flag; ++i) {
	       for (int j = i+1; j < size; ++j) {
		       if (nums[i] + nums[j] == target) {
			       result.push_back(i+1);
			       result.push_back(j+1);
			       flag = false;
			       break;
		       }
	       }
       }

       return result;
    }
};

int main()
{
	vector<int> nums{2, 7, 11, 15};
	vector<int> result;
	Solution s;
	result = s.twoSum(nums, 9);
	cout << result[0] << " " << result[1] << endl;


	return 0;
}

#include <iostream>                                                                                               
using namespace std;                                                                                              
#include <vector>
#if 0                                                                                                            
class Base                                                                                                        
{                                                                                                                 
public:                                                                                                           
	virtual void Func1()                                                                                            
	{                                                                                                               
		cout<<"Func1()"<<endl;                                                                                        
	}
	virtual void Func2()
	{
		cout << "Func2()" << endl;
	}
private:                                                                                                          
	int _b;                                                                                                         
};                                

class  Derived : public Base
{
public:
	virtual void Func1()
	{
		cout << "Func1()" << endl;
	}
	virtual void Func3()
	{
		cout << "Func3()" << endl;
	}
	virtual void Func4()
	{
		cout << "Func4()" << endl; 
	}
private:
	int _d;
};

typedef void(*VFPTR) ();

void PrintTable(VFPTR vtable[])
{
	for (int i = 0; vtable[i] != nullptr; ++i)
	{
		printf("%d : 0X%x\n", i, vtable[i]);
		VFPTR f = vtable[i];
		f();
	}
}


int main()                                                                                                        
{   
	Base b;
	Derived d;
	VFPTR* vtableb = (VFPTR*)(*(int*)&b);
	PrintTable(vtableb);

	VFPTR* vtabled = (VFPTR*)(*(int*)&d);
	PrintTable(vtabled);
	return 0;                                                                                                       
}                      
#endif
class Solution {
public:
	// int singleNumber(vector<int>& nums) {
	//     if(nums.size() == 1)
	//     {
	//         return nums[0];
	//     }
	//     map<int,int> m;
	//     for(int i = 0;i<nums.size();++i)
	//     {
	//         m[nums[i]]++;
	//     }
	//     for(int i = 0;i<nums.size();++i)
	//     {
	//         if(m[nums[i]] == 1)
	//         {
	//             return nums[i];
	//         }
	//     }
	//     return nums[0];
	// }
	int singleNumber(vector<int>& nums) {
		int a = 0, b = 0;
		for (auto x : nums) {
			b = (b ^ x) & ~a;
			a = (a ^ x) & ~b;
		}
		return b;
	}
};

int main()
{
	vector<int> v{ 2, 2,3,2};
	Solution s;
	s.singleNumber(v);
	return 0;
}

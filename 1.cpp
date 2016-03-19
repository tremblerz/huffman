#include<string>
#include<iostream>
using namespace std;
int main(){
	string s="mallu";
	cout<<s<<endl;
	s.erase(s.size()-1);
	cout<<s<<endl;
	return 0;
}

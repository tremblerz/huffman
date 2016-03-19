#include<iostream>
#include<string>
#include<bitset>
#include<queue>
#include<fstream>
#include<cstring>
using namespace std;
struct node{
	string s;
	int freq;
	node *left,*right;
};
class compare{
	public:
    	bool operator() (node *a, node *b)
    	{
       		return a->freq>b->freq;
    	}
};
class huffman{
	string s,x[100],o,en;
	int freq[95];
	node *head;
	node *n;
	priority_queue<node*,vector<node *>,compare> h;
	public:
		int len;
		void makeFreq();
		void makeHuff();
		void makeHeap();
		void compress();
		string getBinary(node *,char);
		void write(char *);
		void printNewBinary();
		int getfreq(char * );
		huffman(){
			for(int i=0;i<95;i++)
				freq[i]=-1;
//			freq[94]=0;
			s="";
		}
		~huffman(){
		}
};
void huffman::makeHeap(){
	for(int i=0;i<95;i++){
		if(freq[i]!=-1){
			n = new node();
			n->freq = freq[i];
			n->left=NULL;
			n->right=NULL;
			n->s = char(i);
			h.push(n);
//			cout<<n->freq<<endl;
		}
	}
}
void huffman::makeHuff(){
	node *head,*left,*right;//= new node();
	while(h.size()>1){
		head = new node();
		left = h.top();
//		cout<<left->s<<" ";
		h.pop();
		right = h.top();
//		cout<<right->s<<endl;
		h.pop();
		head->s = left->s + right->s;
		head->freq = left->freq + right->freq;
		head->left = left;
		head->right = right;
		h.push(head);
	}
	this->head = head;
}
void huffman::compress(){
	int j=0;
	for(int i=0;i<len;i++){
		if(freq[i]!=-1){
			x[j] = getBinary(head,char(i));
			j++;
		}
	}
}
string huffman::getBinary(node *e,char x){	
	if(e!=NULL){
		if(e->s.size()==1){
			return "";
		}
		else if(e->left!=NULL&&e->left->s.find(x)!=-1){
			return "1" + getBinary(e->left,x);
		}
		else{
			return "0" + getBinary(e->right,x);
		}
	}
}
int huffman::getfreq(char *file){
	ifstream i;
	int j=0;
//	char c;
	i.open(file);
	while(i>>freq[j]){
		cout<<freq[j]<<" ";
		j++;
	}
	cout<<endl;
//	cout<<endl<<j<<endl;
	return j;
}
void huffman::write(char *file){
	ofstream o;
	o.open(file);
	for(int i=0;i<len;i++)
		o<<x[i]<<" ";
}
int main(int argc, char *argv[]){
	huffman h;
	h.len = h.getfreq(argv[1]);
	h.makeHeap();
	h.makeHuff();
	h.compress();
	h.write(argv[2]);
return 0;
}

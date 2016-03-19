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
	string s,x,o,en;
	int freq[95];
	node *head;
	node *n;
	priority_queue<node*,vector<node *>,compare> h;
	public:
		void makeFreq();
		void makeHuff();
		void makeHeap();
		void makeString(string);
		void traverse(node *n,string s);
		void printOriginalBinary();
		void compress();
		void printNewBinary();
		void decompress();
		void encodeString();
		void writeToFile(char * );
		string getBinary(node *,char x);
		void generateFile(char * );
		void getfreq(char * );
		void getenc(char * );
		huffman(){
			for(int i=0;i<95;i++)
				freq[i]=-1;
			freq[94]=0;
			s="";
			x="";
		}
		~huffman(){
		}
};
void huffman::printOriginalBinary(){
	for(size_t i=0;i!=s.size();i++)
		cout<<bitset<8>(s[i]);
	cout<<endl;
}
void huffman::traverse(node *e,string st){
	if(e!=NULL){
		if(e->s.size()==1)
			cout<<e->s<<"  "<<st<<endl;
		if(e->left!=NULL){
			st+="0";
			traverse(e->left,st);
			st.erase(st.size()-1);
		}
		if(e->right!=NULL){
			st+="1";
			traverse(e->right,st);
			st=st.erase(st.size()-1);
		}
	}
}
void huffman::makeFreq(){
	for(string::iterator i=s.begin();i!=s.end();i++)
		if(freq[int(*i)-30]==-1)
			freq[int(*i)-30]=1;
		else
			freq[int(*i)-30]++;
}
void huffman::makeString(string y){
	s=y;
}
void huffman::makeHeap(){
	for(int i=0;i<95;i++){
		if(freq[i]!=-1){
			n = new node();
			n->freq = freq[i];
			n->s = (char)(i+30);
			n->left=NULL;
			n->right=NULL;
			h.push(n);
		}
	}
}
void huffman::makeHuff(){
	node *head,*left,*right;//= new node();
	while(h.size()>1){
		head = new node();
		left = h.top();
		h.pop();
		right = h.top();
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
	for(string::iterator i=s.begin();i!=s.end();i++){
		x.append(getBinary(head,*i));
		cout<<*i<<" = "<<getBinary(head,*i)<<endl;
	}
	x.append(getBinary(head,'{'));
	cout<<"{ = "<<getBinary(head,'{')<<endl;
}
string huffman::getBinary(node *e,char x){	
	if(e!=NULL){
		if(e->s.size()==1){
			return "";
		}
		else if(e->left!=NULL&&e->left->s.find(x)!=-1){
			return "0" + getBinary(e->left,x);// + "0";
		}
		else{
			return "1" + getBinary(e->right,x);// + "1";
		}
	}
}
void huffman::printNewBinary(){
	x.erase(x.size()-1);
	while(((x.size()-1)%8)!=0)		
		x.erase(x.size()-1);
	cout<<x<<endl;
}
void huffman::decompress(){
	string a;
	node *h;
	bool flag=false;
	for(string::iterator i=x.begin();i!=x.end();i++){
		h = head;
		while(h->s.size()!=1){
			if((*i)=='0'){
				h = h->left;
				i++;
				if(i==x.end()){
					flag = true;
					break;
				}
			}
			else{
				h = h->right;
				i++;
				if(i==x.end()){
					flag = true;
					break;
				}
			}
		}
		i--;
		if(!flag)
		o.append(h->s);
	}
	cout<<o<<endl;
}
void huffman::encodeString(){
	for(int i=0;i<x.size();i+=8){
		string part(x,i,i+8);
		bitset<8> b(part);
		en += string(1,char(b.to_ulong()));
	}
}
void huffman::writeToFile(char * file){
	ofstream o;
	o.open(file);
	o<<en;
}
void huffman::generateFile(char * file){
	ofstream o;
	o.open(file);
	for(int i=0;i<27;i++)
		o<<freq[i]<<endl;
}
void huffman::getfreq(char *file){
	ifstream i;
	int j=0;
	i.open(file);
	while(i>>freq[j])
		j++;
}
void huffman::getenc(char *file){
	char ch;
	x = "";
	ifstream i;
	i.open(file);
	while(i>>noskipws>>ch)
		x += bitset<8>(char(ch)).to_string();
	while((x.size()-1)%8!=0)
		x.erase(x.size()-1);
	cout<<endl<<x<<endl;
}
int main(){
	huffman h;
	int choice;
	ifstream k;
	char file[100],temp1[100];
	string s,temp;
	while(true){
		cout << "\033[2J\033[1;1H";
		cout<<"\t\t\t\t\t\t\t\tWelcome\n1.  Encode\n2.  Decode\n0.  Exit\n\n>";
		cin>>choice;
		if(choice == 1){
			cout<<"Enter name of the file\n>";
			cin>>file;
			k.open(file);
			while(getline(k,temp)){
				s+=temp;
			}
			h.makeString(s);
			h.makeFreq();
			h.makeHeap();
			h.makeHuff();
			h.compress();
			h.encodeString();
			strcat(file,".huff");
			h.writeToFile(file);
			strcat(file,".data");
			h.generateFile(file);
		}
		else if(choice == 2){
			cout<<"Enter name of the file\n>";
			cin>>file;
			strcat(file,".huff");
			h.getenc(file);
			strcat(file,".data");
			h.getfreq(file);
			h.makeHeap();
			h.makeHuff();
			h.decompress();
		}
		else if(choice == 0){
			return 0;
		}
		else{
			cout<<"Invalid Choice\n";
		}
	}
return 0;
}

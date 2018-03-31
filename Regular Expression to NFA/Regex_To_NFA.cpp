#include<bits/stdc++.h>
using namespace std;


//Globals
string new_reg_exp;
string reg_exp;
int i=0;

int priority(char ch)
{
	switch(ch){
        case '*': return 3;
        case '.': return 2;
        case '+': return 1;
        default: return 0;
    }
}
string convert_to_postfix(string expr)
{
	string postfix;
	postfix.clear();
	char ch;
	stack <char> temp;
	for(int i=0;i<expr.length();i++)
	{
		ch=expr[i];
		if((ch >= 65 && ch <= 91) || (ch >=97 && ch <= 122))
		{
			postfix=postfix+ch;
		}
		else if(ch=='(')
		{
			temp.push(ch);
		}
		else if(ch==')')
		{
			 while(temp.top()!='(')
			 {
                    postfix+=temp.top();
                    temp.pop();
                }
                temp.pop();
		}
		else if (ch=='*'||ch=='+'||ch=='.')
		{
			while(!temp.empty()&&priority(temp.top())>priority(ch))
			{
				postfix+=temp.top();
				temp.pop();
			}
			temp.push(ch);
		}
		else
		{
			cout<<"invalid input.";
			//exit(0);
		}
	}
	while(!temp.empty())
	{
			postfix+=temp.top();
				temp.pop();
	}
	return postfix;
}

struct edges
{
	int src;
	int dst;
	char ip;
};
class nfa
{
	public:
	int initial;
	int final;
	int no_of_edges;
	vector <edges> e;

	void single_char(char ch)
	{
		initial=i++;
		final=i++;
		no_of_edges=1;
		e.push_back({initial,final,ch});
		//e.dst.push_back(1);
		//e.ip.push_back(ch);
	//	cout<<initial<<"------"<<e[0].ip<<"----"<<final<<endl;
	
}

};
vector <nfa> st;
nfa Union(nfa n1,nfa n2)
{
  	nfa n;
  	n.no_of_edges=n1.no_of_edges+n2.no_of_edges+4;
  	n.initial=i++;
  	n.final=i++;
  	
  	for(int j=0;j<n1.no_of_edges;j++)
  	{
  		n.e.push_back({n1.e[j].src,n1.e[j].dst,n1.e[j].ip});
	}
	  	for(int j=0;j<n2.no_of_edges;j++)
  	{
  		n.e.push_back({n2.e[j].src,n2.e[j].dst,n2.e[j].ip});
	}
	n.e.push_back({n.initial,n1.initial,'E'});
  	n.e.push_back({n.initial,n2.initial,'E'});
  	n.e.push_back({n1.final,n.final,'E'});
  	n.e.push_back({n2.final,n.final,'E'});
  	
	 return n;
}

nfa Concat(nfa n1,nfa n2)
{
	nfa n;
  	n.no_of_edges=n1.no_of_edges+n2.no_of_edges+1;
  	n.initial=n1.initial;
  	n.final=n2.final;
  	
  	for(int j=0;j<n1.no_of_edges;j++)
  	{
  		n.e.push_back({n1.e[j].src,n1.e[j].dst,n1.e[j].ip});
	}

  	for(int j=0;j<n2.no_of_edges;j++)
  	{
  		n.e.push_back({n2.e[j].src,n2.e[j].dst,n2.e[j].ip});
	}
	  
	n.e.push_back({n1.final,n2.initial,'E'});
	return n; 
}

nfa Star(nfa n1)
{
	nfa n;
	n.no_of_edges=n1.no_of_edges+4;
	n.initial=i++;
  	n.final=i++;
  	
  	for(int j=0;j<n1.no_of_edges;j++)
  	{
  		n.e.push_back({n1.e[j].src,n1.e[j].dst,n1.e[j].ip});
	}
	  
	n.e.push_back({n.initial,n1.initial,'E'});
	n.e.push_back({n1.final,n.final,'E'});
  	n.e.push_back({n.initial,n.final,'E'});
  	n.e.push_back({n1.final,n1.initial,'E'}); 	
return n;		
}

int main()
{
	st.clear();
	cout<<"Enter regular expression:";
	cin>>reg_exp;
	new_reg_exp=convert_to_postfix(reg_exp);
	cout<<"Postfix Expression: "<<new_reg_exp<<endl;
	for(int i =0;i<new_reg_exp.length();i++)
	{
		if((new_reg_exp[i] >= 65 && new_reg_exp[i] <= 91) || (new_reg_exp[i] >= 97 && new_reg_exp[i] <=122))
		{
			nfa n;
			n.single_char(new_reg_exp[i]);
			st.push_back(n);
		}
		else if(new_reg_exp[i] == '+')
		{
			nfa op1,op2,op3;
        	op2=st.back();
    		st.pop_back();
        	op1=st.back();
    		st.pop_back();
    	    op3=Union(op1,op2);
    	    st.push_back(op3);
		}
		else if(new_reg_exp[i] == '.')
		{
			nfa op1,op2,op3;
        	op2=st.back();
    		st.pop_back();
        	op1=st.back();
    		st.pop_back();
    	    op3=Concat(op1,op2);
    	    st.push_back(op3);
		}
		else if(new_reg_exp[i] == '*')
		{
			nfa op1,op2;
        	op1=st.back();
    		st.pop_back();
       	    op2=Star(op1);
    	    st.push_back(op2);
		}
	}

	cout<<"\t"<<setfill('-')<<setw(50)<<"Non Deterministic Finite Automata"<<setfill('-')<<setw(14)<<"";
	cout<<"\n\tInitial state:"<<st[0].initial;
	cout<<"\t\tFinal state:"<<st[0].final;
	cout<<"\t\tNo of edges:"<<st[0].no_of_edges<<endl;

	cout<<"\n\t"<<std::setfill(' ')<<setw(10)<<"From"<<setw(20)<<"To"<<setw(30)<<"Symbol";

	for(int j=0;j<i;j++)
	{
		for(int x=0;x<st[0].no_of_edges;x++)
		{
			if(st[0].e[x].src==j)
			{
				cout<<"\n\t"<<std::setfill(' ')<<setw(8)<<st[0].e[x].src<<setw(22)<<st[0].e[x].dst<<setw(28)<<st[0].e[x].ip;
			}
		}

	} 
	cout<<endl;
	return 0;
} 
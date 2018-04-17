#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<set>
#include<map>
using namespace std;
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
		if(ch=='a'||ch=='b')
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
	n.e.push_back({n.initial,n1.initial,'e'});
  	n.e.push_back({n.initial,n2.initial,'e'});
  	n.e.push_back({n1.final,n.final,'e'});
  	n.e.push_back({n2.final,n.final,'e'});
  	
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
	  
	n.e.push_back({n1.final,n2.initial,'e'});
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
	  
	n.e.push_back({n.initial,n1.initial,'e'});
	n.e.push_back({n1.final,n.final,'e'});
  	n.e.push_back({n.initial,n.final,'e'});
  	n.e.push_back({n1.final,n1.initial,'e'}); 	
return n;		
}




//-----------------------------------------------------------nfa to dfa----------------------------------------------------------

int m=0;
set <int> ep_cl[50];
map <set <int>,int> mp;

void epsilon(int a,set <int> &b)
{
	set<int>::iterator it;
for(int x=0;x<st[0].no_of_edges;x++)
{
if((st[0].e[x].src==a)&&(st[0].e[x].ip=='e'))
    {
    	it=b.find(st[0].e[x].dst);
    	if( it==b.end())
         {
	
		    	b.insert(st[0].e[x].dst);
    	        epsilon(st[0].e[x].dst,b);
	
 	}	
}
}
}

class dfa
{
	public:
		int i_state;
	    vector <int> f_state;
		int no_of_states;
		int n_edge;
		vector <edges> ed;
};



void nfa_to_dfa(set <int> state,dfa &d)
{
	set <int> temp;
	set <int> new_state;
	set<int>::iterator iter;
	set<int>::iterator it;
	map<set <int> ,int>::iterator mp_it;
//-----------------------input a-----------------------------------------------
for(iter=state.begin(); iter!=state.end();++iter)
{
    for(int x=0;x<st[0].no_of_edges;x++)
      {
           if((st[0].e[x].src==*iter)&&(st[0].e[x].ip=='a'))
            {
    	        temp.insert(st[0].e[x].dst);
			}
	
      }
}
    for(it=temp.begin(); it!=temp.end();++it)
      {
	  	new_state.insert(ep_cl[*it].begin(),ep_cl[*it].end());
	  }
	  
	  if(!new_state.empty())
	  {
	  mp_it=mp.find(new_state);
	
	  if(mp_it==mp.end())
	  {
	  	mp[new_state]=m++;
	  	d.no_of_states++;
	  	nfa_to_dfa(new_state,d);
	  }
	   d.ed.push_back({mp.find(state)->second,mp.find(new_state)->second,'a'});
	   d.n_edge++;
	   cout<<"No. of edges :"<<d.n_edge<<endl;
	   cout<<"Edge pushed :"<<endl;
	   cout<<mp.find(state)->second<<"____________"<<mp.find(new_state)->second<<"___________________'a'"<<endl;
}
	  temp.clear();
	  new_state.clear();
//-------------------------------------input b--------------------------------
	  
for(iter=state.begin(); iter!=state.end();++iter)
{
    for(int x=0;x<st[0].no_of_edges;x++)
      {
           if((st[0].e[x].src==*iter)&&(st[0].e[x].ip=='b'))
            {
    	        temp.insert(st[0].e[x].dst);
    	        
			}
	
      }
}
      for(it=temp.begin(); it!=temp.end();++it)
      {
	  	new_state.insert(ep_cl[*it].begin(),ep_cl[*it].end());
	  }
	  
	  if(!new_state.empty())
	  {
	  
	  mp_it=mp.find(new_state);
	
	  if(mp_it==mp.end())
	  {
	  	mp[new_state]=m++;
	  	d.no_of_states++;
	  	nfa_to_dfa(new_state,d);
	  }
	   d.ed.push_back({mp.find(state)->second,mp.find(new_state)->second,'b'});
	   d.n_edge++;
	   cout<<"No. of edges :"<<d.n_edge<<endl;
	   cout<<"Edge pushed :"<<endl;
	   cout<<mp.find(state)->second<<"____________"<<mp.find(new_state)->second<<"___________________'b'"<<endl;
}
	  


}
	  
	  
    




int main()
{
	st.clear();
	cout<<"Enter regular expression:";
	cin>>reg_exp;
	new_reg_exp=convert_to_postfix(reg_exp);
	cout<<new_reg_exp<<endl;
	for(int i =0;i<new_reg_exp.length();i++)
	{
	switch(new_reg_exp[i])
	{
		
	case 'a':
		{
		    nfa n;
			n.single_char(new_reg_exp[i]);
			st.push_back(n);
			break;
		}
	case 'b':
	   {
	       
	       nfa n;
			n.single_char(new_reg_exp[i]);
			st.push_back(n);
			break;
		
	    }
    case '+':
    	{
    		nfa op1,op2,op3;
        	op2=st.back();
    		st.pop_back();
        	op1=st.back();
    		st.pop_back();
    		
    	   op3=Union(op1,op2);
    	   st.push_back(op3);
    	   break;
    		
				
		}
	case '.':
    	{
    		nfa op1,op2,op3;
        	op2=st.back();
    		st.pop_back();
        	op1=st.back();
    		st.pop_back();
    	
    		
    	   op3=Concat(op1,op2);
    	   
    	   st.push_back(op3);
    	   
    	   break;
				
		}
		case '*':
    	{
    		nfa op1,op2;
        	op1=st.back();
    		st.pop_back();
    	
    		
    	   op2=Star(op1);
    	   
    	   st.push_back(op2);
    	   
    	   break;
				
		}
	}
}


cout<<"\nFinal nfa is:\n";

cout<<"Initial state:"<<st[0].initial<<endl;
cout<<"Final state:"<<st[0].final<<endl;
cout<<"No of edges:"<<st[0].no_of_edges<<endl;
cout<<"------edges-------"<<endl;
for(int j=0;j<i;j++)
{
	for(int x=0;x<st[0].no_of_edges;x++)
	{
		if(st[0].e[x].src==j)
		{
				cout<<st[0].e[x].src;
	cout<<"-----"<<st[0].e[x].ip<<"----";
	cout<<st[0].e[x].dst<<endl;
		}
	}

} 


//----------------------------------------------nfa to dfa-------------------------------------------
//creating epsilon of initial state

for(int j=0;j<i;j++)
{
	ep_cl[j].insert(j);
	
}
for(int j=0;j<i;j++)
{
	epsilon(j,ep_cl[j]);
	
}
/*set<int>::iterator iter;

for(iter=ep_cl[st[0].initial].begin(); iter!=ep_cl[st[0].initial].end();++iter)
{
    cout<<*iter<<endl;

}
*/
dfa d;
d.n_edge=0;
mp[ep_cl[st[0].initial]]=m++;
d.no_of_states=1;
d.i_state=mp.find(ep_cl[st[0].initial])->second;
nfa_to_dfa(ep_cl[st[0].initial],d);


cout<<"\nFinal dfa is:\n";

cout<<"Initial state:"<<d.i_state<<endl;
//cout<<"Final state:"<<d.final<<endl;
cout<<"No of states:"<<d.no_of_states<<endl;
cout<<"No of edges:"<<d.n_edge<<endl;
cout<<"------edges-------"<<endl;
for(int j=0;j<d.n_edge;j++)
{
	cout<<d.ed[j].src;
	cout<<"-----"<<d.ed[j].ip<<"----";
	cout<<d.ed[j].dst<<endl;
		}
	

} 





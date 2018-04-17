#include<bits/stdc++.h>
using namespace std;

map< char,map<char,char> > table;

void generateTable()
{
	// map< char,map<char,char> > table;
	map<char,char> row;
	row['a'] = '-';
	row['+'] = '>';
	row['*'] = '>';
	row['$'] = '>';
	table['a'] = row;

	row['a'] = '<';
	row['+'] = '>';
	row['*'] = '<';
	row['$'] = '>';
	table['+'] = row;

	row['a'] = '<';
	row['+'] = '>';
	row['*'] = '>';
	row['$'] = '>';
	table['*'] = row;

	row['a'] = '<';
	row['+'] = '<';
	row['*'] = '<';
	row['$'] = '-';
	table['$'] = row;

	// cout<<(table['a'])['+'];
}

int main()
{
	string inputData;
	stack<char> stk;
	generateTable(); 
	// cout<<"\n\tTable Generated";
	cout<<"\n\tEnter the input string: ";
	getline(cin,inputData);
	cout<<"\n\tData Entered";
	stk.push('$');
	for(int counter=0;counter<inputData.length();)
	{
		// cout<<"\n\tCurrent Pointer: "<<inputData[counter];
		// cout<<"\n\tTop of Stack: "<<stk.top();
		// cout<<"\n\tRelational Symbol: table["<<inputData[counter]<<"]["<<stk.top()<<"]"<<(table[inputData[counter]])[stk.top()];
		if((table[inputData[counter]])[stk.top()] == '>')
		{
			cout<<"\n\tPushed "<<inputData[counter];
			stk.push(inputData[counter]);
			counter++;
		}
		else if((table[inputData[counter]])[stk.top()] == '<')
		{
			if(stk.top() == '*' || stk.top() == '+')
				cout<<"\n\tReduced E"<<stk.top()<<"E";
			else
				cout<<"\n\tReduced "<<stk.top()<<" to E";
			stk.pop();
		}
		if(counter == inputData.length())
		{
			cout<<"\n\tReduced "<<stk.top()<<" to E";
			stk.pop();
			while(stk.top() != '$')
			{
				cout<<"\n\tReduced E"<<stk.top()<<"E";
				stk.pop();
			}
		}
	}
	cout<<"\n\tString Parsed!"<<endl;
	return 0;
}
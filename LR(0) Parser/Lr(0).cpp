#include<bits/stdc++.h>
using namespace std;

map<char, map<char,string> > table;
map<char,vector<string> > mapping;	//Stores Productions as a Map

void createTable()
{
	map<char,string> columnMap;

	columnMap['a'] = "S3";
	columnMap['A'] = "2";
	columnMap['S'] = "1";
	table['0'] = columnMap;

	columnMap.clear();
	columnMap['$'] = "accept";
	table['1'] = columnMap;

	columnMap.clear();
	columnMap['a'] = "S3";
	columnMap['b'] = "S4";
	columnMap['A'] = "5";
	table['2'] = columnMap;

	columnMap.clear();
	columnMap['a'] = "S3";
	columnMap['b'] = "S4";
	columnMap['A'] = "6";
	table['3'] = columnMap;

	columnMap.clear();
	columnMap['a'] = "R3";
	columnMap['b'] = "R3";
	columnMap['$'] = "R3";
	table['4'] = columnMap;

	columnMap.clear();
	columnMap['a'] = "R1";
	columnMap['b'] = "R1";
	columnMap['$'] = "R1";
	table['5'] = columnMap;

	columnMap.clear();
	columnMap['a'] = "R2";
	columnMap['b'] = "R2";
	columnMap['$'] = "R2";
	table['6'] = columnMap;
}

int main()
{
	string production;
	vector<string> words;

	int flag = 1;
	cout<<"\n\t------------------------Instructions------------------------";
	cout<<"\n\t1.Enter 1 to Continue Entering Productions\n\t2.Use \'#\' to Enter Epsilon\n\t3. Use \'S\' as Start Symbol";
	
	createTable();
	while(flag == 1)
	{
		string word;
		cout<<"\n\tEnter the production: ";
		cin>>production;
		int counter = 3;
		for(;production[counter] != '\0';counter++)
		{
			if(production[counter] != '/')
			{
				word += production[counter];
			}
			else
			{
				words.push_back(word);
				word.clear();
			}
		}
		words.push_back(word);		//For pushing the last production sequence
		mapping[production[0]] = words;
		words.erase(words.begin(),words.end());
		word.clear();
		cout<<"\n\t";
		cin>>flag;
	}

	// for(auto it = mapping.begin();it != mapping.end();it++)
	// {
	// 	cout<<it->first<<"->";
	// 	for(auto l = (it->second).begin(); l != (it->second).end();l++)
	// 	{
	// 		cout<<*l<<"/";
	// 	}
	// }
	return 0;
}
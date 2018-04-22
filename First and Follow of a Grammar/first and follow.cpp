#include<bits/stdc++.h>
using namespace std;

map< char,vector<string> > mapping;
//Used to Store Productions in form: {S : [aA,b] , A: [cbE,f] , E: [e] }

vector<char> nonTerminals;
set<char> terminals;


set<char> calculateFirst(vector<string> production)
{
	set<char> first;
	bool epsilonFlag = false;
	for(auto counter = production.begin();counter != production.end();counter++)
	{
		string word = *counter;
		for(int offset = 0;offset<word.length();offset++)
		{
			if(word[offset] >= 97 && word[offset] <=122)
			{
				first.insert(word[offset]);
				break;
			}
			else if(word[offset] >= 65 && word[offset] <= 90)
			{
				set<char> tempFirst = calculateFirst(mapping[word[offset]]);
				for(auto i= tempFirst.begin();i != tempFirst.end();i++)
				{
					if((*i) != '#')		//Also check here for duplication
						first.insert(*i);
					else
						epsilonFlag = true;
				}
			}
			else if(word[offset] == '#')
			{
				first.insert('#');
				break;
			}

			if(!epsilonFlag)
				break;

			if(epsilonFlag && word[offset + 1] == '\0')
				first.insert('#');
			epsilonFlag = false;
		}
	}
	return first;
}

bool checkNonTerminal(char character)
{
	for(int i=0;i<nonTerminals.size();i++)
	{
		if(character == nonTerminals[i])
			return true;
	}
	return false;
}

set<char> calculateFollow(char followChar)
{
	set<char> followSymbols;		//Vector For storing follow of Non-Terminals
	if(followChar == 'S')
		followSymbols.insert('$');
	for(auto it = mapping.begin();it != mapping.end();it++)	//Checking follow of current NonTerminal in each production
	{
		for(int j = 0;j<(it->second).size();j++)	//Every Element Will be a string
		{
			//Check if current Non-Terminal exists in Current Production or not
			string currentProduction = (it->second)[j];
			for(int k=0;k<currentProduction.length();k++)
			{
				if(followChar == currentProduction[k])
				{
					k++;	//Incrementing value of k

					//Check if the next char is a terminal,non-terminal or /0
					if(checkNonTerminal(currentProduction[k]))
					{
						/*Calculate the first of this Non-terminal
						Eg: We are calculating the follow of A in production having left side as aABc.
						So Follow of A will be First of B.	*/

						reCalculate:		//Label
						set<char> firsts = calculateFirst(mapping[currentProduction[k]]);
						bool flag = false;

						/*Now insert all firsts into the set of follow of current Non-Terminal Symbol whose follow
						  is being calculated */
						for(auto l = firsts.begin();l != firsts.end();l++)
						{
							if(*l != '#')
								followSymbols.insert(*l);
							else
								flag = true;
						}

						/*Suppose Production is S->ACB/CbB/Ba, and we are calculating follow of A.
						If first of C contains epsilon,then we need to consider Follow of B as well and so on. */
						if(flag == true && currentProduction[k+1] != '\0')
						{
							k++;
							if(checkNonTerminal(currentProduction[k]))
								goto reCalculate;
							else
								followSymbols.insert(currentProduction[k]);
							/* For Production like S->aABb and first of B contains epsilon. We do not need to calculate
							first because next symbol is Terminal.*/
						}
						else if(flag == true && currentProduction[k+1] == '\0')
						{
							/*When A->aBA,where B->#,A->#. Then it will try to find Follow of A Recursively
							therefore giving segmentation fault */
							if(currentProduction[k-1] == it->first)	
							{
								cout<<"\n\tAvoided Recursive Call";
								return followSymbols;
							}
							set<char> followReturned = calculateFollow(it->first);
							for(auto l = followReturned.begin();l != followReturned.end();l++)
								followSymbols.insert(*l);	
						}


					}
					else if(currentProduction[k] == '\0')
					{
						
						/*When A->aBA,where B->#,A->#. Then it will try to find Follow of A Recursively
						therefore giving segmentation fault */
						if(currentProduction[k-1] == it->first)	
						{
							cout<<"\n\tAvoided Recursive Call";
							return followSymbols;
						}

						/*If the production is of the form B->abA,and we are calculating the follow of A,then 
						Follow of A will contain First of B. */
						set<char> followReturned = calculateFollow(it->first);

						/*Now insert all Follow Symbols into the set of follow of current Non-Terminal Symbol whose follow
						is being calculated */
						for(auto l = followReturned.begin();l != followReturned.end();l++)
							followSymbols.insert(*l);	
					}
					else 	//It will be a terminal,so insert it into followSymbols
					{
						followSymbols.insert(currentProduction[k]);
					}
				}
			}
		}
	}
	return followSymbols;
}


int main()
{
	string production;
	vector<string> words;
	map<char, set<char> > firstMap;
	int flag = 1;
	cout<<"\n\t------------------------Instructions------------------------";
	cout<<"\n\t1.Enter 1 to Continue Entering Productions\n\t2.Use \'#\' to Enter Epsilon\n\t3. Use \'S\' as Start Symbol";
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
				if(production[counter] >= 97 && production[counter] <= 122)
					terminals.insert(production[counter]);
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
		nonTerminals.push_back(production[0]);
		words.erase(words.begin(),words.end());
		word.clear();
		cout<<"\n\t";
		cin>>flag;
	}


	//Calculate First Of All Symbols
	for(auto counter = mapping.begin();counter != mapping.end();counter++)
	{
		set<char> first = calculateFirst(counter->second);
		firstMap[counter->first] = first;
		cout<<"\n\tFirst of "<<counter->first<<" are: ";
		for(auto offset = first.begin(); offset!=first.end();offset++)
			cout<<*offset<< " ";
	}
	cout<<"\n\t";

	map<char,set<char> > followMap;

	//Calculating Follow of all the symbols
	for(int i = 0; i<nonTerminals.size();i++)
	{
		set<char> follow = calculateFollow(nonTerminals[i]);
		followMap[nonTerminals[i]] = follow;
	}

	for(auto it = followMap.begin();it != followMap.end();it++)
	{
		cout<<"\n\tFollow of "<<it->first<<" : ";
		for(auto l = (it->second).begin();l != (it->second).end();l++)
		{
			cout<<*l<<" ";
		}
	}
	cout<<"\n\t";


	//Creating an LL(1) Table

	/*For each production create a map such that, that production should be placed under the given 
	Terminal Symbol.
	Eg: {S : { a: [S->aBC] } }
	If any vector has more than two productions in it,then grammar cannot be parsed. i.e. Grammar is ambigious.
	*/

	map<char, map<char,vector<string> > > table;
	/* 1st char represents row, 2nd char represents column and vector represents its values */

	for(auto it = mapping.begin();it != mapping.end();it++)
	{
		map<char,vector<string> > columnMap;
		for(int counter = 0;counter< (it->second).size();counter++)
		{
			string currentProduction = (it->second)[counter];
			vector<string> production;
			production.push_back(currentProduction);	//Because calculateFirst() takes vector<string> as an argument'
			if(currentProduction != string(1,'#'))	//This means that current production will be placed at firsts of the production
			{
				set<char> firsts = calculateFirst(production);
				for(auto l = firsts.begin();l != firsts.end();l++)
				{
					//Check if *l already exist in map
					if(columnMap.find(*l) != columnMap.end())
						columnMap[*l].push_back(string(1,it->first) + "->" + currentProduction);
					else
					{
						vector<string> values;
						values.push_back(string(1,it->first) + "->" + currentProduction);
						columnMap[*l] = values;
					}
				}
			}
			else	// A->epsilon is a production,it will be placed under follow of A.
			{
				set<char> follow = followMap[it->first];
				for(auto l = follow.begin();l != follow.end();l++)
				{
					//Check if *l already exist in map
					if(columnMap.find(*l) != columnMap.end())
						columnMap[*l].push_back(string(1,it->first) + "->" + currentProduction);
					else
					{
						vector<string> values;
						values.push_back(string(1,it->first) + "->" + currentProduction);
						columnMap[*l] = values;
					}
				}
			}
		}
		table[it->first] = columnMap;
	}

	//Printing the table
	bool ambiguity = false;
	for(auto it = table.begin();it != table.end();it++)
	{
		cout<<"\n\t";
		cout<<"\n\tRow: "<< it->first;
		for(auto l = (it->second).begin();l != (it->second).end();l++)
		{
			cout<<"\n\tColumn: "<<l->first;
			cout<<"\n\tValues: ";
			if((l->second).size() > 1)
				ambiguity = true;
			for(int counter = 0;counter< (l->second).size();counter++)
				cout<<(l->second)[counter]<<" ";
		}
	}
	cout<<"\n\t";
	if(ambiguity)
		cout<<"\n\tGrammar is Ambigious. Parser Cannot Parse The Grammar";
	else
		cout<<"\n\tGrammar is Unambigious. Parser Will Parse The Grammar";

	return 0;
}
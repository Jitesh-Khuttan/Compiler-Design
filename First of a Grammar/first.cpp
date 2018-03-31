#include<bits/stdc++.h>
using namespace std;

map< char,vector<string> > mapping;


vector<char> calculateFirst(vector<string> production)
{
	vector<char> first;
	bool epsilonFlag = false;
	for(auto counter = production.begin();counter != production.end();counter++)
	{
		string word = *counter;
		for(int offset = 0;offset<word.length();offset++)
		{
			if(word[offset] >= 97 && word[offset] <=122)
			{
				first.push_back(word[offset]);
				break;
			}
			else if(word[offset] >= 65 && word[offset] <= 90)
			{
				vector<char> tempFirst = calculateFirst(mapping[word[offset]]);
				for(int i=0;i<tempFirst.size();i++)
				{
					if(tempFirst[i] != '#')		//Also check here for duplication
						first.push_back(tempFirst[i]);
					else
						epsilonFlag = true;
				}
			}
			else if(word[offset] == '#')
			{
				first.push_back('#');
				break;
			}

			if(!epsilonFlag)
				break;

			if(epsilonFlag && word[offset + 1] == '\0')
				first.push_back('#');
			epsilonFlag = false;
		}
	}
	return first;
}

int main()
{
	string production;
	vector<string> words;
	int flag = 1;
	cout<<"\n\t------------------------Instructions------------------------";
	cout<<"\n\t1.Enter 1 to Continue Entering Productions\n\t2.Use \'#\' to Enter Epsilon";
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

	for(auto counter = mapping.begin();counter != mapping.end();counter++)
	{
		vector<char> first = calculateFirst(counter->second);
		cout<<"\n\tFirst of "<<counter->first<<" are: ";
		for(int offset = 0; offset<first.size();offset++)
			cout<<first[offset]<< " ";
	}
	cout<<"\n\t";
	return 0;
}
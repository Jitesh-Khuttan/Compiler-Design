#include<bits/stdc++.h>
using namespace std;

int main()
{
	string production;
	vector<string> words;
	int flag = 1;
	cout<<"\n\tEnter 1 to Continue Entering Productions";
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
		word.clear();

		//Just for three Productions
		string str1 = words[0];
		string str2 = words[1];
		string commonPart;
		int commonLength=0;
		for(int i=0;i<min(str1.length(),str2.length());i++)
		{
			if(str1[i] == str2[i])
			{
				commonPart += str1[i];
				commonLength += 1;
			}
			else
				break;
		}
		cout<<"\n\t"<<production[0]<<"->"<<commonPart<<"X'/"<<words[2];
		cout<<"\n\t"<<"X'->"<<str1.substr(commonLength,str1.length()-commonLength + 1)<<"/"<<str2.substr(commonLength,str2.length()-commonLength+1)<<"\n\t";
		cin>>flag;
	}
	return 0;
}
#include<bits/stdc++.h>
using namespace std;

int main(){
	string productions;
	cout<<"\n\tEnter 1 to continue entering productions";
	int flag = 1;
	while(flag == 1)
	{
		cout<<"\n\tEnter production: ";
		cin>>productions;
		//cout<<productions[0]<<"=="<<productions[3];
		if(productions[0] == productions[3])
		{
			//cout<<"Matched!";
			string alpha;
			int counter = 4;
			while(productions[counter] != '/')
			{
				//cout<<"slash Matched";
				alpha += productions[counter++];
			}
			counter++;
			string beta;
			while(productions[counter] != '\0')
			{
				beta += productions[counter++];
			}

			string newProduction1;
			newProduction1 = productions.substr(0,3);
			newProduction1 += beta;
			newProduction1 += "A'";
			string newProduction2 = "A' -> ";
			newProduction2 += alpha;
			newProduction2 += "A'/epsilon";
			cout<<"\n\t"<<newProduction1;
			cout<<"\n\t"<<newProduction2;
		}
		else
		{
			cout<<"\n\t"<<productions;
		}
		cout<<"\n\t";
		cin>>flag;
		productions.clear();
	}
	return 0;
}
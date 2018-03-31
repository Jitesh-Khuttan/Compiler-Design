#include<bits/stdc++.h>
using namespace std;

/*Recursive Descent Parser For Following Grammar
			E -> iT
			T-> +iT / -iT / *iT / /iT / ^iT / epsilon
*/

string inputString;
int counter;

bool match(char t){
	if(inputString[counter] == t)
	{
		counter += 1;
		return true;
	}
	else
	{
		counter += 1;
		return false;
	}
}

bool T(){
	bool result1,result2;
	if(inputString[counter] == '+'){
		result1 = match('+');
		result2 = match('i');
		if(result1 == true && result2 == true)
			T();
		else
			return false;
	}
	else if(inputString[counter] == '-'){
		result1 = match('-');
		result2 = match('i');
		if(result1 == true && result2 == true)
			T();
		else
			return false;
	}
	else if(inputString[counter] == '*')
	{
		result1 = match('*');
		result2 = match('i');
		if(result1 == true && result2 == true)
			T();
		else
			return false;
	}
	else if(inputString[counter] == '/')
	{
		result1 = match('/');
		result2 = match('i');
		if(result1 == true && result2 == true)
			T();
		else
			return false;
	}
	else if(inputString[counter] == '^')
	{
		result1 = match('^');
		result2 = match('i');
		if(result1 == true && result2 == true)
			T();
		else
			return false;
	}
	else if(inputString[counter] == '$')
		return true;
}

bool E(){
	bool result;
	if(inputString[counter] == 'i'){
		result = match('i');
		if(result == true)
			result = T();
		else
			return false;
	}
	return result;
}



int main(){
    counter = 0;
	cout<<"\n\tEnter a String: ";
	cin>> inputString;
	bool result = E();
	if(result == true)
		cout<<"\n\tString Accepted\n";
	else
		cout<<"\n\tString Rejected\n";
	return 0;
}

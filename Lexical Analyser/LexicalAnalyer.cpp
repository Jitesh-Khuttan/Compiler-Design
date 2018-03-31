#include<bits/stdc++.h>
#define OPSIZE 6
#define KEYSIZE 32
using namespace std;

class Compiler
{
private:
    string keywords[KEYSIZE] = {"auto","break","case","char","const","continue","default",
                            	"do","double","else","enum","extern","float","for","goto",
                            	"if","int","long","register","return","short","signed",
                            	"sizeof","static","struct","switch","typedef","union",
                            	"unsigned","void","volatile","while"};  //Valid in C++14 gcc compiler
                            	
    string operators[OPSIZE] = {"+","-","*","/","=",","};
    int keywordCount;
    int operatorCount;
    int identifierCount;
public:
    Compiler();
    void LexicalAnalyser(string program);
    void getData();
};

Compiler :: Compiler()
{
    keywordCount = 0;
    operatorCount = 0;
    identifierCount = 0;
}

void Compiler :: LexicalAnalyser(string program)
{
    bool isKeyword = false;
    bool operatorFound =false;
    int counter = 0;
    int flag_backslash_check = 1;
    string currentword;
    while(program[counter] != '\0')
    {
        //cout<<"\n\tCurrent String: "<<currentword;
        if(program[counter] == '/' && counter < (program.length() - 1) && program[counter + 1] == '/')  //For Ignoring Comments
        {
            break;
        }
        else if(program[counter] == ' ')
        {
            //cout<<"\n\tSpace Encountered";
            //If space is encountered then check whether the string read till now is an operator or keyword
            for(int i = 0 ;i < KEYSIZE;i++)
            {
                if(currentword.compare(keywords[i]) == 0)
                {
                    //cout<<"\n\tKeyWord Match Found";
                    cout<<"\n\t"<<currentword<<"\t\tKeyword";
                    keywordCount++;
                    isKeyword = true;
                    currentword.clear();
                    break;
                }
            }
            if(!isKeyword && currentword.length() != 0) //currenword.length() to prevent from considering space as an identifier.
            {
                //cout<<"\n\tIdentifier Found!";
                cout<<"\n\t"<<currentword<<"\t\tIdentifier";
                identifierCount++;
                //cout<<"\n\tIdentifier Count Incremented!";
                currentword.clear();
            }
        }
        else
        {
            for(int i = 0;i< OPSIZE; i++)
            {
                //Check if the current character is operator
                string character = string(1,program[counter]); //Creating a string from a character of length 1
                //cout<<"\n\tComapring "<<character<<" with "<<operators[i];
                if(character.compare(operators[i]) == 0)
                {
                    operatorFound = true;
                    cout<<"\n\t"<<character<<"\t\tOperator";
                    //cout<<"\n\tOperator Found";
                    operatorCount++;
                    //cout<<"\n\tOperator Count Incremented";

                    //If operator was encountered then check the current string is identifier or a keyword
                    for(int j=0;j<KEYSIZE;j++)
                    {
                        if(currentword.compare(keywords[i]) == 0)
                        {
                            //cout<<"\n\tKeyWord Match Found";
                            cout<<"\n\t"<<currentword<<"\t\tKeyword";
                            keywordCount++;
                            //cout<<"\n\tKeyWord Count Incremented";
                            isKeyword = true;
                            currentword.clear();
                            break;
                        }
                    }
                }
            }
            if(operatorFound && !isKeyword && currentword.length() != 0)    //Check here for the last word
            {
                //cout<<"\n\tIdentifier Found!";
                //cout<<"\n\tIdentifer Count Incremented!";
                cout<<"\n\t"<<currentword<<"\t\tIdentifier";
                identifierCount++;
                currentword.clear();
            }
            if(!operatorFound)      //When operator was not found and even space was not found
                currentword += program[counter];
        }
        counter++;

        if(program[counter] == '\0')    //Check for the last word,since no check will be performed in next loop
        {
            //The last word could either be a keyword or it could be an identifier.
            //No need to check for operator,coz that is done by previous condition.
            for(int i = 0 ;i < KEYSIZE;i++)
            {
                if(currentword.compare(keywords[i]) == 0)
                {
                    //cout<<"\n\tLast Word is a Keyword!";
                    cout<<"\n\t"<<currentword<<"\t\tKeyword";
                    keywordCount++;
                    isKeyword = true;
                    currentword.clear();
                    break;
                }
            }
            if(!isKeyword)
            {
                //cout<<"\n\tLast Word is an Identifier!";
                cout<<"\n\t"<<currentword<<"\t\tIdentifier";
                identifierCount++;
                currentword.clear();
            }

        }
        isKeyword = false;
        operatorFound = false;
    }
}

void Compiler :: getData()
{
    cout<<"\n\n\tNumber of Identifier: "<<identifierCount;
    cout<<"\n\tNumber of Operators: "<<operatorCount;
    cout<<"\n\tNumber of Keywords: "<<keywordCount;
}



int main()
{
    Compiler lexical;
//    string program = "inta float char a = c + b * -/ e+d  ,   int  -+ f char";
	string program;
	cout<<"\n\tEnter Your Program\n\t";
	getline(cin,program);
    lexical.LexicalAnalyser(program);
    lexical.getData();
    cout<<endl;

    return 0;
}

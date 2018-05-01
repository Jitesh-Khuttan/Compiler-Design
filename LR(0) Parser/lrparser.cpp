#include<iostream>
#include<stack>
#include<map>
using namespace std;
main()
{
    string arr[7][5]={
        {"s3","","","2","1" },
        {"","","accept","",""},
        {"s3","s4","","5",""},
        {"s3","s4","","6",""},
        {"r3","r3","r3","",""},
        {"r1","r1","r1","",""},
        {"r2","r2","r2","",""}
     };
     map<char,int> m;
     m['a']=0;
     m['b']=1;
     m['$']=2;
     m['A']=3;
     m['S']=4;
     cout<<"Enter Input String: ";
     string str;
     cin>>str;
     str.push_back('$');
     int i=0;
     stack<char> st;
     st.push('0');
     int flag=1;
     while(i<str.length())
     {
       int index=st.top()-48;
       if(st.top()>='0' && st.top()<='9'  && arr[ (int)(st.top()-48 ) ][m[ str[i] ] ]=="accept" )
       {
           flag=0;
           cout<<"String accepted\n";
           break;
       }
       else if(arr[index][m[  str[i] ]]=="")
       {
           break;
       }

       if( arr[index][m[  str[i] ]][0]=='s' )
       {
           st.push(str[i]);
           st.push( arr[index][m[ str[i] ]][1] );
           i++;
       }
       else if( arr[index][m[ str[i] ]][0]=='r' )
       {
          int temp= arr[index][m[str[i]]][1]-48;
          if(temp<3)
          {
              for(int j=0;j<4;j++)
              st.pop();
             if(temp==1)
             {
                 int p=st.top()-48;
              char ch=arr[p][m['S']][0];
              st.push('S');
              st.push(ch);
             }
             else if(temp==2)
             {
                  int p=st.top()-48;
              char ch=arr[p][m['A']][0];
              st.push('A');
              st.push(ch);
             }

          }
          else{
               for(int j=0;j<2;j++)
              st.pop();
              int p=st.top()-48;
              char ch=arr[p][m['A']][0];
              st.push('A');
              st.push(ch);

          }
       }
     }
     if(flag)
     cout<<endl<<"String rejected\n";
}


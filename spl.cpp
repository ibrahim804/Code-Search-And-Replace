#include <bits/stdc++.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <set>

using namespace std;

char *fileName;

ifstream iFile;
ofstream oFile;

vector <string> dataType_list, methods_list, variables_list;


map <string, vector <string> > methodsAndTheirVariables;
map <string, vector <string> > :: iterator finalMapIT;

map <string,int> variablesHolder,methodsHolder;
map <string,int> :: iterator it;

map <int,string> reverseMethods;
map <int,string> :: iterator rev;

map <string,int> methodAndLine,variableAndLine;
//map <string,int> :: iterator nameLineIT;

string keywords_list[]={
	"auto","break","case","char","const","continue","default","do",
		"double","else","enum","extern","float","for","goto","if","int","long","register",
		"return","short","signed","sizeof","static","struct","switch","typedef","union",
		"unsigned","void","volatile","while"
	};

void line_Number_And_Char_Count(int &total_lines, int &total_chars);
void clearEverything();
void Words_Keys_And_Loop_Count(int &total_words, int &total_keywords, int &total_loops);
void Methods_VAriebles_Count(int &total_variebles, int &total_methods);
void Clear_Method_and_Variables_Name();
void printing_line_char_word_keyword(int total_lines, int total_chars, int total_words, int total_keywords);
void printing_loop(int total_loops);
void Show_Changed_Source_Code();
void Variable_Name_Search();
void Method_Name_Search();
void Taking_User_Input_For_Changing_A_Name();
bool Check_A_Valid_Name_Request(string replaceBy, vector <string> locaal);
bool Global_Struct_Union_Variable_Identify(string word);
void Check_For_False_Method_And_Variable(string &word);
void Make_Relationship_Variable_and_Method();
void Show_Methods_And_Their_Children_Variables();
void change_method_name(string methodName, string replaceBy);
bool checkVariableInRelationshipTree();
void Change_Variable_Name(string methodName, string varName, string replaceBy);




void line_Number_And_Char_Count(int &total_lines, int &total_chars)
{

	iFile.open(fileName);

	char ch;

	while(iFile.get(ch))
	{
		total_chars++;
		if(ch=='\n') total_lines++;
	}

	iFile.close();
}

void Show_Changed_Source_Code()
{
	iFile.open(fileName);
	oFile.open("source_temp.txt");
	char ch;

	while(iFile.get(ch))
	{
		oFile << ch;
	}

	oFile.close();
	iFile.close();
}

void Words_Keys_And_Loop_Count(int &total_words, int &total_keywords, int &total_loops)
{

	oFile.open("source_temp.txt");
	iFile.open(fileName);

	char ch;
	string word;

	while(iFile.get(ch))
	{
		if((ch>=65 and ch<=90) or (ch>=97 and ch<=122) or (ch>=48 and ch<=57))
		{
			oFile << ch;
		}

		else if(ch=='\n') oFile << endl;
		else oFile << " ";
	}

	iFile.close();
	oFile.close();


	dataType_list.push_back("void");
	dataType_list.push_back("int");
	dataType_list.push_back("char");
	dataType_list.push_back("float");
	dataType_list.push_back("double");
	dataType_list.push_back("short");
	dataType_list.push_back("long");
	dataType_list.push_back("signed");
	dataType_list.push_back("unsigned");

	int forLoop=0, doLoop=0, whileLoop=0;

	bool flag=false,yes1=false,yes2=false;

	string false_dataType;

	iFile.open("source_temp.txt");

	bool loopFound_NowVariableHasToFind=false;

	while(iFile >> word)
	{

		total_words++;

		if(loopFound_NowVariableHasToFind)
		{
			if(!(word[0]>='0' and word[0]<='9'))
			{
				//loop_variables.insert(word);
				loopFound_NowVariableHasToFind=false;
			}
		}

		for(int i=0; i<32; i++)
		{
			if(word==keywords_list[i])
			{
				total_keywords++;

				if(word=="while")
				{
					whileLoop++;
					loopFound_NowVariableHasToFind=true;
				}

				else if(word=="for")
				{ 
					forLoop++;
					loopFound_NowVariableHasToFind=true;
				}

				else if(word=="do")
				{
					doLoop++;
				}

				break;
			}
		}

		if(flag)
		{

			bool temp=true; 

			for(int i=0; i<dataType_list.size(); i++)
			{
				if(word==dataType_list[i])
				{
					temp=false;
					break;
				}
			}

			if(temp)
			{
				dataType_list.push_back(word);
				flag=false;
			}
		}

		if(word=="typedef" or word=="struct" or word=="union")
		{
			flag=true;
		}


	} 

	iFile.close(); 

	total_loops=forLoop+doLoop+(whileLoop-doLoop);

}

void Check_For_False_Method_And_Variable(string &word)
{
	int pos1=-1,pos2=-1;

	for(int i=0; i<word.length(); i++)
	{
		if(word[i]=='"')
		{
			pos1=i;

			for(int k=pos1+1; k<word.length(); k++)
			{
				if(word[k]=='"')
				{
					pos2=k;
					break;
				}
			}

			if(pos2==-1) return ;

			//cout << pos1 << " " << pos2 << endl;
			word.erase(word.begin()+pos1+1,word.end()-(word.length()-pos2));
			//cout << word << endl;
			return;
		} 
	}
}

bool Global_Struct_Union_Variable_Identify(string word, int number)
{

	//cout << "yeah bro \n";
	for(int i=0; i<word.length(); i++)
	{
		if(word[i]==' ') continue;

		if(word[i]!='}') return false;
		else break;
	}

	for(int i=0; i<word.length(); i++)
	{
		if(!((word[i]>='A' and word[i]<='Z') or  (word[i]>='a' and word[i]<='z') or (word[i]>=48 and word[i]<=57)))
		{
			word[i]=' ';
		}
	}

	istringstream iss(word);

	string temp;

	while(iss >> temp)
	{
		if(temp[0]>=48 and temp[0]<=57) continue;
		variables_list.push_back(temp);
		variableAndLine[temp]=number;
	}

	return true;

}

void Methods_VAriebles_Count(int &total_variebles, int &total_methods)
{
	iFile.open(fileName);

	string word;

	bool breakLine=false;

	bool flagForStructAndUnion=false;

	int lineNumberHere=0;

	while(getline(iFile,word))
	{			
		lineNumberHere++;

		Check_For_False_Method_And_Variable(word);				

		if(flagForStructAndUnion)
		{
			if(Global_Struct_Union_Variable_Identify(word,lineNumberHere))
			{
				flagForStructAndUnion=false;
				
			}

			continue;
		}

		if(breakLine) breakLine=false;

		string word2=word, first_Word;

		istringstream iss(word2);

		iss >> first_Word;

		if(first_Word=="typedef")
		{
		    continue;
		}

		if(first_Word=="struct" or first_Word=="union")
		{
			flagForStructAndUnion=true;

		}

		for(int i=0; i<dataType_list.size(); i++)
		{	

			if(breakLine) break;

			string dataType=dataType_list[i]+" ";		

			bool flag=false;
			int pos=0;
			
			for(int k=0; k<word.length(); k++)
			{											
		
				if(breakLine) break;

				if(word.length()<dataType.length()+2) break;

				//if

				if(!flag)
				{
					string temp=word.substr(k,dataType.length());

					if(temp==dataType)   // parameter check and false variable/method check
					{
						bool ifAlreadyMethodExistsInThisLine=false;
						
						for(int p=k; p>=0; p--)
						{
							if(word[p]=='(' or word[p]=='"')
							{
								ifAlreadyMethodExistsInThisLine=true;
								break;
							}

						}

						if(!ifAlreadyMethodExistsInThisLine)
						{
							flag=true;
							k+=dataType.length();
							pos=k;
							k++;
						}

					}
				}

				if(flag)
				{

					if(word[k]=='(')
					{

						total_methods++;
						flag=false;
						methods_list.push_back(word.substr(pos,k-pos));
						methodAndLine[word.substr(pos,k-pos)]=lineNumberHere;
						pos=0; 
						breakLine=true;
						break;
					}

					else if(word[k]==';' or word[k]==',')
					{

						total_variebles++;
						
						string dblVar= word.substr(pos,k-pos);

						while(true){

							bool yeah=false;

							for(int z=0; z<variables_list.size(); z++)
							{
								if(dblVar==variables_list[z])
								{
									dblVar+=".";
									yeah=true;
									break;
								}

							}

							if(yeah==false) break;

						}

						variables_list.push_back(dblVar);
						//if(dblVar) variables_list[variables_list.size()-1]=lastVal+".";

						variableAndLine[variables_list[variables_list.size()-1]]=lineNumberHere;
						pos=k+1;

						if(word[k]==';') flag=false;
					}

				}

			}

			if(breakLine) break;
		}

	}

	iFile.close();

}

void Clear_Method_and_Variables_Name()
{

	for(int i=0; i<variables_list.size(); i++)
	{											

		int pos1=0,pos2=0;

		int line1=variableAndLine[variables_list[i]];
		//cout << variables_list[i] << " " << line1 << endl ;

		for(int k=0; k<variables_list[i].size(); k++)
		{
			char ch=variables_list[i][k];
			if((ch>=65 and ch<=90) or (ch>=97 and ch<=122) or ch=='_')
			{
				pos1=k;
				break;
			}

		}

		for(int k=pos1; k<variables_list[i].size(); k++)
		{
			char ch=variables_list[i][k];
			if(!((ch>=65 and ch<=90) or ch=='.' or (ch>=97 and ch<=122) or ch=='_' or (ch>=48 and ch<=57)))
			{
				pos2=k;
				break;
			}
		}

		if(pos2==0)
		{
			variables_list[i]=variables_list[i].substr(pos1,variables_list[i].length()-pos1);
		}

		else
		{
			variables_list[i]=variables_list[i].substr(pos1,pos2-pos1);
		}
		
		bool quotemark=false;

		for(int z=0; z<variables_list[i].size(); z++)
		{
			if(variables_list[i][z]=='"' or variables_list[i][z]==39)
			{
				quotemark=true;
				break;
			}
		}

		if(quotemark) continue;

		variablesHolder[variables_list[i]]=line1;

		for(int k=0; k<dataType_list.size(); k++)
		{
			if(variables_list[i]==dataType_list[k])
			{
				variables_list.erase(variables_list.begin()+i,variables_list.end()-(variables_list.size()-1-i));
				i--;
			}
		} 

		for(int k=0; k<dataType_list.size(); k++)
		{
			for(it=variablesHolder.begin(); it!=variablesHolder.end(); it++)
			{
				if(dataType_list[k]==it->first)
				{
					variablesHolder.erase(it);
					break;
				}
			}
		}

	} 
	
	for(int i=0; i<methods_list.size(); i++)
	{	

		int pos=0, line2=methodAndLine[methods_list[i]];
		//cout << methods_list[i] << " " << line << endl ;

		for(int k=0; k<methods_list[i].size(); k++)
		{
			char ch=methods_list[i][k];
			if((ch>=65 and ch<=90) or (ch>=97 and ch<=122) or ch=='_')
			{
				pos=k; 
				break;
			}

		}

		methods_list[i]=methods_list[i].substr(pos,methods_list[i].length()-pos);
		methodsHolder[methods_list[i]]=line2;
		
	} 

}

void Make_Relationship_Variable_and_Method()
{


	map <string,bool> visibility;
	map <string,bool> :: iterator vis;

	for(it=variablesHolder.begin(); it!=variablesHolder.end(); it++)
	{
		visibility[it->first]=false;
	}

	for(it=methodsHolder.begin(); it!=methodsHolder.end(); it++)
	{
		reverseMethods[it->second]=it->first;
	}

	rev=reverseMethods.begin();
	int start=rev->first;

	vector <string> tempVec;

	for(it=variablesHolder.begin(); it!=variablesHolder.end(); it++)
	{
		if(it->second<start)
		{
			string itFirst=it->first;
			int dotCount=0;

			for(int z=itFirst.length()-1; z>=0; z--)
			{
				if(itFirst[z]=='.') dotCount++;
				else break;
			}

			itFirst=itFirst.substr(0,itFirst.length()-dotCount);

			tempVec.push_back(itFirst);
			visibility[it->first]=true;
		}
	}

	methodsAndTheirVariables["Global"]=tempVec;
	tempVec.clear();

	for(rev=reverseMethods.begin(); rev!=reverseMethods.end(); rev++)
	{

		//if(rev->second=="main") break;e
		rev++;
		if(rev==reverseMethods.end()) break;
		rev--;

		start=rev->first;
		rev++;
		int last=rev->first;
		rev--;

		tempVec.clear();

		for(it=variablesHolder.begin(); it!=variablesHolder.end(); it++)
		{

			if(it->second>start and it->second<last)
			{

				string itFirst=it->first;
				int dotCount=0;

				for(int z=itFirst.length()-1; z>=0; z--)
				{
					if(itFirst[z]=='.') dotCount++;
					else break;
				}

				itFirst=itFirst.substr(0,itFirst.length()-dotCount);

				tempVec.push_back(itFirst);
				visibility[it->first]=true;
			}
		}

		methodsAndTheirVariables[rev->second]=tempVec;
	}

	tempVec.clear();

	for(vis=visibility.begin(); vis!=visibility.end(); vis++)
	{
		if(vis->second==false)
		{
			string itFirst=vis->first;
			int dotCount=0;

			for(int z=itFirst.length()-1; z>=0; z--)
			{
				if(itFirst[z]=='.') dotCount++;
				else break;
			}

			itFirst=itFirst.substr(0,itFirst.length()-dotCount);

			tempVec.push_back(itFirst);
			visibility[vis->first]=true;
		}
	}

	rev=reverseMethods.end();
	rev--;
	methodsAndTheirVariables[rev->second]=tempVec;


}

void printing_line_char_word_keyword(int total_lines, int total_chars, int total_words, int total_keywords)
{
	oFile.open("output.txt");

	oFile << "total line numbers=" << total_lines << endl;
	oFile << "total words numbers=" << total_words << endl;
	oFile << "total char numbers=" << total_chars << endl;
	oFile << "total keywords numbers=" << total_keywords << endl;

}

void printing_loop(int total_loops)
{
	oFile << "total loop number=" << total_loops;

	oFile << endl << endl << endl;

	oFile.close();
}

bool Check_A_Valid_Name_Request(string replaceBy, vector <string> locaal)
{
	for(int i=0; i<locaal.size(); i++)
	{
		if(locaal[i]==replaceBy)
		{
			return true;
		}
	}

	return false;
}

void Show_Methods_And_Their_Children_Variables()
{
	int cnt=1;

	for(finalMapIT=methodsAndTheirVariables.begin(); finalMapIT!=methodsAndTheirVariables.end(); finalMapIT++)
	{
		cout << cnt << ": " << finalMapIT->first << endl;
		int cnt2=1;

		for(int k=0; k<(finalMapIT->second).size(); k++)
		{
			cout << "\t" << cnt << "." << cnt2 << " " << (finalMapIT->second)[k] << endl;
			cnt2++;
		}

		cout << endl;
		cnt++;
	}

}

bool checkVariableInRelationshipTree(string name)
{
	for(finalMapIT=methodsAndTheirVariables.begin(); finalMapIT!=methodsAndTheirVariables.end(); finalMapIT++)
	{
		
		for(int k=0; k<(finalMapIT->second).size(); k++)
		{
			if((finalMapIT->second)[k]==name)
			{
				return true;
			}
		}

	}

	return false;
}

void change_method_name(string methodName, string replaceBy)
{


	ofstream oFileHere;
	iFile.open(fileName);
	oFileHere.open("sudo.c");

	string word;

	while(getline(iFile,word))
	{						
		for(int i=0; i<=word.length()-methodName.length(); i++)
		{
			if(word.length()<methodName.length()+3) break;

			string match=word.substr(i,methodName.length());
			match;
			if(match==methodName)
			{
				//cout << match << endl;
				//cout << "yesssssssssssssssssssss";
				string one,two,three;
				one=two=three="";
				one=word.substr(0,i);
				two=replaceBy;
				three=word.substr(i+methodName.length(),word.length()-(i+methodName.length()));
				word=one+two+three;
				break;
			}

		}

		oFileHere << word << endl;
	}

	iFile.close();
	oFileHere.close();

	iFile.open("sudo.c");
	oFileHere.open(fileName);

	char ch;

	while(iFile.get(ch))
	{
		oFileHere << ch;
	}

	iFile.close();
	oFileHere.close();
}

void Change_Variable_Name(string methodName, string varName, string replaceBy)
{
	/*
	int first,last;

	for(rev=reverseMethods.begin(); rev!=reverseMethods.end(); rev++)
	{
		cout << rev->first << " " << rev->second << endl;
	}
	*/

	vector <int> vec;

	for(rev=reverseMethods.begin(); rev!=reverseMethods.end(); rev++)
	{
		vec.push_back(rev->first);
	}

	vec.push_back(0);
	vec.push_back(12345678);

	sort(vec.begin(),vec.end());

	int first,last;

	for(it=methodsHolder.begin(); it!=methodsHolder.end(); it++)
	{
		if(it->first==methodName)
		{
			first=it->second;
			break;
		}
	}

	for(int k=0; k<vec.size(); k++)
	{
		if(vec[k]==first)
		{
			last=vec[k+1];
			break;
		}
	}

	//cout << first << " " << last << endl;

	ofstream oFileHere;
	iFile.open(fileName);
	oFileHere.open("sudo.c");

	string word;
	int c=0;

	while(getline(iFile,word))
	{
		c++;

		if(c<first or c>last)
		{
			oFileHere << word << endl;
			continue;
		}

		for(int i=0; i<word.length(); i++)
		{
			if(word.length()<=varName.length()) break;

			string temp=word.substr(i,varName.length());
			
			if(temp==varName)
			{

				//cout <<  "cc: "<< c << endl;
				int len=varName.length();

				if((word[i-1]>= 97 and word[i-1]<= 122 )or(word[i-1]>= 65 and word[i-1]<= 90)or(word[i-1]>=48 and word[i-1]<=57)or word[i-1]=='_')
				{
					continue;
				}

				else if((word[i+len]>= 97 and word[i+len]<= 122 )or(word[i+len]>= 65 and word[i+len]<= 90)or(word[i+len]>=48 and word[i+len]<=57)or word[i+len]=='_')
				{
					continue;
				}

				string one=word.substr(0,i);
				string two=replaceBy;
				string three=word.substr(i+varName.length(),word.length()-(i+varName.length()));
				word=one+two+three;
				i=-1;
			}
		}

		oFileHere << word << endl;
	}

	iFile.close();
	oFileHere.close();

	iFile.open("sudo.c");
	oFileHere.open(fileName);

	while(getline(iFile,word))
	{
		oFileHere << word << endl;
	}

	iFile.close();
	oFileHere.close();
}

void Variable_Name_Search()
{

	while(true)
	{

		string nameM,nameV;

		bool flag=false;
	
		cout << "Enter first method Name to identify it's scope(type Global for global scope) : ";

		cin >> nameM;

		cout << "Enter variable name : ";

		cin >> nameV;

		for(finalMapIT=methodsAndTheirVariables.begin(); finalMapIT!=methodsAndTheirVariables.end(); finalMapIT++)
		{
			if(nameM==finalMapIT->first)
			{
				for(int k=0; k<(finalMapIT->second).size(); k++)
				{
					if((finalMapIT->second)[k]==nameV)
					{
						flag=true;
					}
				}

			}
		}

		if(flag==false)
		{
			cout << "Method and variable name doesn't exit, try again\n";
			continue;
		}

		cout <<"Enter a new name to replace your variable name : ";
		
		string replaceBy;

		while(true)
		{
			cin >> replaceBy;

			flag=true;

			if(!(replaceBy[0]=='_' or (replaceBy[0]>='a' and replaceBy[0]<='z') or (replaceBy[0]>='A' and replaceBy[0]<='Z')))
			{
				cout <<"You entered a wrong variable name.\n";
				cout <<"Enter a valid name to replace your variable name : ";
				continue;
			}

			for(int i=0; i<replaceBy.length(); i++)
			{
				if((replaceBy[i]=='_' or (replaceBy[i]>='a' and replaceBy[i]<='z') or (replaceBy[i]>='A' and replaceBy[i]<='Z')))
				{
					continue;
				} 

				else if(replaceBy[i]>=48 and replaceBy[i]<=57)
				{
					continue;
				}

				else 
				{
					cout <<"You entered a wrong variable name.\n";
					cout <<"Enter a valid name to replace your variable name : ";
					flag=false;
					break;
				} 
			}

			if(flag==false) continue;
			bool k=false;
			
			for(finalMapIT=methodsAndTheirVariables.begin(); finalMapIT!=methodsAndTheirVariables.end(); finalMapIT++)
			{
				if(finalMapIT->first==nameM)
				{
					bool kk=false;
					for(int y=0; y<(finalMapIT->second).size(); y++)
					{
						if(replaceBy==(finalMapIT->second)[y])
						{
							cout << "This variable name is already exist in this scope\n";
							cout << "Try with another \n";
							kk=true;
							break;
						}
					}

					if(kk) break;
					k=false;
					break;
				}
			}

			//if(kk) continue;
			if(k) continue;

			if(Check_A_Valid_Name_Request(replaceBy,methods_list))
			{
				cout << "This named method aleady exist, try with another\n";
				continue;
			}

			if(Check_A_Valid_Name_Request(replaceBy,dataType_list))
			{
				cout << "This named datatype aleady exist, try with another\n";
				continue;
			}

			for(int i=0; i<32; i++)
			{
				if(keywords_list[i]==replaceBy)
				{
					cout << "This named keyword aleady exist, try with another\n";
					flag=false;
					break;
				}
			}

			if(flag==false) continue;

			break;

		}


		cout << "variable name accepted\n";

		Change_Variable_Name(nameM,nameV,replaceBy);

		break;

    }

	

}



void Method_Name_Search()
{

	while(true)
	{

		string name;
		bool flag=false;
	
		cout << "Enter your method name : ";

		cin >> name;

		if(name=="main")
		{
			cout << "You can't change main methode name, try another methode to change\n";
			continue;
		}

		flag=Check_A_Valid_Name_Request(name,methods_list);

		if(!flag)
		{
			cout <<"Your entered method is not exist.\n";
			continue;
		}

		flag=checkVariableInRelationshipTree(name);
		if(flag)
		{
			cout << "This is already a variable name \n, Try with another\n";
			continue;
		}

		cout <<"Enter a new name to replace your method name : ";
		
		string replaceBy;


		while(true)
		{

			cin >> replaceBy;

			flag=true;

			if(!(replaceBy[0]=='_' or (replaceBy[0]>='a' and replaceBy[0]<='z') or (replaceBy[0]>='A' and replaceBy[0]<='Z')))
			{
				cout <<"You entered a wrong method name.\n";
				cout <<"Enter a valid name to replace your method name : ";
				continue;
			}

			for(int i=0; i<replaceBy.length(); i++)
			{
				if((replaceBy[i]=='_' or (replaceBy[i]>='a' and replaceBy[i]<='z') or (replaceBy[i]>='A' and replaceBy[i]<='Z')))
				{
					continue;
				} 

				else if(replaceBy[i]>=48 and replaceBy[i]<=57)
				{
					continue;
				}

				else 
				{
					cout <<"You entered a wrong methods_list name.\n";
					cout <<"Enter a valid name to replace your methods name : ";
					flag=false;
					break;
				} 
			}

			if(flag==false) continue;

			if(Check_A_Valid_Name_Request(replaceBy,methods_list))
			{
				cout << "This named method aleady exist, try with another\n";
				continue;
			}

			if(Check_A_Valid_Name_Request(replaceBy,dataType_list))
			{
				cout << "This named datatype aleady exist, try with another\n";
				continue;
			}

			if(checkVariableInRelationshipTree(replaceBy))
			{
				cout <<"This variable name is already exist\n, Try with another:";
				continue;
			}

			for(int i=0; i<32; i++)
			{
				if(keywords_list[i]==replaceBy)
				{
					cout << "This named keyword aleady exist, try with another\n";
					flag=false;
					break;
				}
			}

			if(flag==false) continue;

			break;

		}

		cout <<"method name accepted.\n";

		change_method_name(name,replaceBy);

		break;

    }

 	
}

void clearEverything()
{

	variables_list.clear();
	methods_list.clear();
	dataType_list.clear();
	methodsAndTheirVariables.clear();
	variablesHolder.clear();
	methodsHolder.clear();
	reverseMethods.clear();
	methodAndLine.clear();
	variableAndLine.clear();
}

void Taking_User_Input_For_Changing_A_Name()
{

		Show_Methods_And_Their_Children_Variables();

		cout << "Enter 1 to change Variable name\nor 2 to change Method name\n";

		int choice;
		cin >> choice;

		if(choice==1)
		{
			Variable_Name_Search();
		}

		else if(choice==2)
		{	
			Method_Name_Search();
		}

		else return;
}

int main(int argc , char *argv[])
{												

	fileName=argv[1];

	iFile.open(fileName);

	if(!iFile.is_open())
	{
		oFile << "c File is not exist !!\n";
		return 0;
	}

	iFile.close();

	int total_methods, total_variebles, total_keywords;
	int total_lines,  total_chars,  total_words,  total_loops;

	total_words=0;
	total_chars=0;
	total_lines=0;
	total_variebles=0;
	total_loops=0;
	total_methods=0;
	total_keywords=0;

	
	line_Number_And_Char_Count(total_lines,total_chars);
	Words_Keys_And_Loop_Count(total_words,total_keywords,total_loops);

	Methods_VAriebles_Count(total_variebles,total_methods);
	Clear_Method_and_Variables_Name();
	printing_line_char_word_keyword(total_lines,total_chars,total_words,total_keywords);
	printing_loop(total_loops);
	Make_Relationship_Variable_and_Method();

	for(int i=0; i<dataType_list.size(); i++)
	{
		cout << dataType_list[i] << endl;
	}

	Taking_User_Input_For_Changing_A_Name();

	return 0;
}


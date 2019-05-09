#include <string>
#include <string.h>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <fstream>
#include <queue>
#include <sstream>
#include <bits/stdc++.h>

using namespace std;

#define checkBit(n,p) (bool)(n&(1<<p))
/*
###############################################################################
					Rishitha & Abhinand
						IIT Tirupati
					   course: cs2610
###############################################################################
*/

unordered_map<string,string> parse(string path);

string decToBin(int num,int length);


int main()
{
    
    int val;
    string ins,op,r1,r2,r3,cmnt;
    unordered_map<string,string> R_TYPE,I_TYPE,J_TYPE,RegisterValue;
    //Obtaining static values from storage
    R_TYPE = parse("C:/Users/hp/Desktop/assembler/CS2610Project/File/R_TYPE.txt");
    I_TYPE = parse("C:/Users/hp/Desktop/assembler/CS2610Project/File/I_TYPE.txt");
    J_TYPE = parse("C:/Users/hp/Desktop/assembler/CS2610Project/File/J_TYPE.txt");
    RegisterValue = parse("C:/Users/hp/Desktop/assembler/CS2610Project/File/RegisterValue.txt");
    //ifstream inputFile("C:/Users/hp/Desktop/assembler/CS2610Project/File/input.txt");
    ifstream inputFile("C:/Users/hp/Desktop/assembler/CS2610Project/File/validtestcases.txt");
    //ifstream inputFile("File/invalidtestcases.txt");
    ofstream outputFile1("C:/Users/hp/Desktop/assembler/CSE332Project/File/output2.txt");
    while(getline(inputFile,ins))
    {
        stringstream ss;
        //cout << ins << endl;
        //Checking if instruction is empty or not
        if(ins.size()==0)
        {
            cout << "Invalid: Instruction is empty" << endl;
            outputFile1 << "Invalid: Instruction is empty" << endl;
            continue;
        }
        ss << ins;
        ss >> op;
        //If operation code is J Type then the program will go in here
        if(J_TYPE.find(op)!=J_TYPE.end())
        {
            val = -1;
            ss >> val;
            if(val<0)
            {
                val -= 10;
            }
            val = ceil(val/4.0);
            //Checking instruction validities
            if(val<0)
            {
            	cout<<"error!!! "<<endl;
                cout << "suggestion: value can not be neg" << endl;
                outputFile1 << "invalid: value can not be neg" << endl;
            }
            else if(val>67108869)
            {
            	cout<<"error!!! "<<endl;
                cout << "suggestion: value is too large" << endl;
                outputFile1 << "invalid: value is too large" << endl;
            }
            else if(ss>>cmnt&&(cmnt[0]!='/'||cmnt[1]!='/'))
            {
            	cout<<"error!!! "<<endl;
            	cout << "suggestion: comment structure not maintained" << endl;
            	outputFile1 << "Invalid: comment structure not maintained" << endl;
            }
            //Printing machine code
            else
            {
                //cout << J_TYPE[op] << " " << decToBin(val,26) << endl;
                outputFile1 << J_TYPE[op] << " " << decToBin(val,26) << endl;
            }
            continue;
        }
        ss >> r1;
        if(op!="jr")
        {
            if(r1[0]!='$')
            {
            	cout<<"error!!! "<<endl;
                cout << "suggestion: '$' sign is missing before rd" << endl;
                outputFile1 << "Invalid: '$' sign is missing before rd" << endl;
                continue;
            }
            else if(r1[r1.size()-1]!=',')
            {
            	cout<<"error!!! "<<endl;
                cout << "suggestion: ',' is missing after rd" << endl;
                outputFile1 << "Invalid: ',' is missing after rd" << endl;
                continue;
            }
            r1.erase(r1.end()-1);
        }
        //If operation code is R Type then the program will go in here
        if(R_TYPE.find(op)!=R_TYPE.end())
        {
            val = 0;
            if(op=="jr")
            {
                r2 = r3 = "$zero";
                goto print;
            }
            if(op=="sll"||op=="srl")
            {
                r2 = "$zero";
            }
            else
            {
                ss >> r2;
                if(r2[0]!='$')
                {
                	cout<<"error!!! "<<endl;
                    cout << "suggestion: '$' sign is missing before rs" << endl;
                    outputFile1 << "Invalid: '$' sign is missing before rs" << endl;
                    continue;
                }
                else if(r2[r2.size()-1]!=',')
                {
                	cout<<"error!!! "<<endl;
                    cout << "suggestion: ',' is missing after rs" << endl;
                    outputFile1 << "Invalid: ',' is missing after rs" << endl;
                    continue;
                }
                r2.erase(r2.end()-1);
            }
            ss >> r3;
            if(r3[0]!='$')
            {
            	cout<<"error!!! "<<endl;
                cout << "suggestion: '$' sign is missing before rt" << endl;
                outputFile1 << "Invalid: '$' sign is missing before rt" << endl;
                continue;
            }
            if(op=="sll"||op=="srl")
            {
                if(r3[r3.size()-1]!=',')
                {
                	cout<<"error!!! "<<endl;
                    cout << "suggestion: ',' is missing after rt" << endl;
                    outputFile1 << "Invalid: ',' is missing after rt" << endl;
                    continue;
                }
                r3.erase(r3.end()-1);
                val = -1;
                ss >> val;
            }
            //Checking instruction validities
            print:
            if(r1=="$zero")
            {
            	cout<<"error!!! "<<endl;
                cout << "suggestion: $zero can not be used" << endl;
                outputFile1 << "Invalid: $zero can not be used" << endl;
            }
            else if(RegisterValue.find(r1)==RegisterValue.end())
            {
            	cout<<"error!!! "<<endl;
                cout << "suggestion: rd not found" << endl;
                outputFile1 << "Invalid: rd not found" << endl;
            }
            else if(RegisterValue.find(r2)==RegisterValue.end())
            {
            	cout<<"error!!! "<<endl;
                cout << "suggestion: rs not found" << endl;
                outputFile1 << "Invalid: rs not found" << endl;
            }
            else if(RegisterValue.find(r3)==RegisterValue.end())
            {
            	cout<<"error!!! "<<endl;
                cout << "suggestion: rt not found" << endl;
                outputFile1 << "Invalid: rt not found" << endl;
            }
            else if(val<0)
            {
            	cout<<"error!!! "<<endl;
                cout << "suggestion: value can not be neg" << endl;
                outputFile1 << "Invalid: value can not be neg" << endl;
            }
            else if(val>31)
            {
            	cout<<"error!!! "<<endl;
                cout << "suggestion: value is too large" << endl;
                outputFile1 << "Invalid: value is too large" << endl;
            }
            else if(ss>>cmnt&&(cmnt[0]!='/'||cmnt[1]!='/'))
            {
            	cout<<"error!!! "<<endl;
            	cout << "suggestion: comment structure not maintained" << endl;
            	outputFile1 << "Invalid: comment structure not maintained" << endl;
            }
            //Printing machine code if instruction is valid
            else
            {
                //cout << "000000" << " " << RegisterValue[r2] << " " << RegisterValue[r3] << " " << RegisterValue[r1] << " " << decToBin(val,5) << " " << R_TYPE[op] << endl;
                outputFile1 << "000000" << " " << RegisterValue[r2] << " " << RegisterValue[r3] << " " << RegisterValue[r1] << " " << decToBin(val,5) << " " << R_TYPE[op] << endl;
            }
        }
        //If operation code is I Type then the program will go in here
        else if(I_TYPE.find(op)!=I_TYPE.end())
        {
        	val = -1;
        	if(op=="lw"||op=="sw")
        	{
        		ss >> val >> r2;
        		if(r2[0]!='(')
                {
                	cout<<"error!!! "<<endl;
                    cout << "suggestion: '(' is missing before rs" << endl;
                    outputFile1 << "Invalid: '(' is missing before rs" << endl;
                    continue;
                }
                else if(r2[r2.size()-1]!=')')
                {
                	cout<<"error!!! "<<endl;
                    cout << "suggestion: ')' is missing after rs" << endl;
                    outputFile1 << "Invalid: ')' is missing after rs" << endl;
                    continue;
                }
                else if(r2[1]!='$')
                {
                	cout<<"error!!! "<<endl;
                    cout << "suggestion: '$' sign is missing before rs" << endl;
                    outputFile1 << "Invalid: '$' sign is missing before rs" << endl;
                    continue;
                }
        		r2.erase(r2.begin());
        		r2.erase(r2.end()-1);
        		swap(r1,r2);
        		if(r1=="$zero")
                {
                    r1 = "";
                    cout<<"error!!! "<<endl;
                    cout << "suggestion: $zero can to be used" << endl;
                    outputFile1 << "Invalid: $zero can to be used" << endl;
                    continue;
                }
                else if(r2=="$zero")
                {
                	cout<<"error!!! "<<endl;
                    r2 = "";
                    cout << "suggestion: $zero can to be used" << endl;
                    outputFile1 << "Invalid: $zero can to be used" << endl;
                    continue;
                }
        	}
        	else
        	{
        		ss >> r2 >> val;
        		if(r2[0]!='$')
                {
                	cout<<"error!!! "<<endl;
                    cout << "suggestion: '$' sign is missing before rs" << endl;
                    outputFile1 << "Invalid: '$' sign is missing before rs" << endl;
                    continue;
                }
                else if(r2[r2.size()-1]!=',')
                {
                	cout<<"error!!! "<<endl;
                    cout << "suggestion: ',' is missing after rs" << endl;
                    outputFile1 << "Invalid: ',' is missing after rs" << endl;
                    continue;
                }
        		r2.erase(r2.end()-1);
        		if(op=="addi"||op=="andi"||op=="ori")
        		{
        		    swap(r1,r2);
        		    if(r1=="$zero")
                    {
                        r1 = "";
                        cout<<"error!!! "<<endl;
                        cout << "suggestion: $zero can to be used" << endl;
                        outputFile1 << "Invalid: $zero can to be used" << endl;
                        continue;
                    }
        		}
        		else
        		{
        		    if(val<0)
                    {
                        val -= 10;
                    }
        			val = ceil(val/4.0);
        		}
        	}
        	//Checking instruction validities
            if(RegisterValue.find(r1)==RegisterValue.end())
            {
            	cout<<"error!!! "<<endl;
                cout << "suggestion: rd not found" << endl;
                outputFile1 << "Invalid: rd not found" << endl;
            }
            else if(RegisterValue.find(r2)==RegisterValue.end())
            {
            	cout<<"error!!! "<<endl;
                cout << "suggestion: rs not found" << endl;
                outputFile1 << "Invalid: rs not found" << endl;
            }
            else if(op!="addi"&&op!="andi"&&op!="ori"&&val<0)
            {
            	cout<<"error!!! "<<endl;
                cout << "suggestion: value can not be neg" << endl;
                outputFile1 << "Invalid: value can not be neg" << endl;
            }
            else if(val>32767)
            {
            	cout<<"error!!! "<<endl;
                cout << "suggestion: value is too large" << endl;
                outputFile1 << "Invalid: value is too large" << endl;
            }
            else if(val<-32768)
            {
            	cout<<"error!!! "<<endl;
                cout << "suggestion: value is too small" << endl;
                outputFile1 << "Invalid: value is too small" << endl;
            }
            else if(ss>>cmnt&&(cmnt[0]!='/'||cmnt[1]!='/'))
            {
            	cout<<"error!!! "<<endl;
            	cout << "suggestion: comment structure not maintained" << endl;
            	outputFile1 << "Invalid: comment structure not maintained" << endl;
            }
            //Printing machine code if instruction is valid
            else
            {
            	//cout << I_TYPE[op] << " " << RegisterValue[r1] << " " << RegisterValue[r2] << " " << decToBin(val,16) << endl;
            	outputFile1 << I_TYPE[op] << " " << RegisterValue[r1] << " " << RegisterValue[r2] << " " << decToBin(val,16) << endl;
            }
        }
        else
        {
        	cout<<"error!!! "<<endl;
        	cout << "suggestion: Op code not found" << endl;
        	outputFile1 << "Invalid: Op code not found" << endl;
        }
    }
    inputFile.close();
}

unordered_map<string,string> parse(string path)
{
	string s = path;
    string word,value;
    unordered_map<string,string> m;
    ifstream file(s.c_str());
    while(file>>word>>value)
    {
        m[word] = value;
    }
    file.close();
    return m;
}

string decToBin(int num,int length)
{
    string result = "";
    for(int i=0;i<length;i++)
    {
        if(checkBit(num,i))
        {
            result = "1" + result;
        }
        else
        {
            result = "0" + result;
        }
    }
    return result;
}



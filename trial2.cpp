#include <stdio.h>
#include<iostream>
#include<string>
#include<unordered_set>
#include<fstream>
using namespace std;
/*
Unordered_set storing keywords
*/
unordered_set<string> mp;
unordered_set<string> keywords;
void insertion(){
  keywords.insert("int");
  keywords.insert("float");
  keywords.insert("void");
  keywords.insert("return");
}

std::string converttostring(std::string filename = "/Users/sayash/Desktop/Similarity/file1.txt")	//default local file
{
    std::ifstream file;
    file.open (filename);
    if (!file.is_open()) return "invalid filename";

    string ans;
    string word;
    int flag=0;
    while (file >> word)
    {
      if(flag==1)
      {
        if(mp.find(word)!=mp.end())
        {
          word="";
        }
        else
        {
          mp.insert(word);
        }
        flag=0;
        continue;
      }
      if(keywords.find(word)!=keywords.end())
      {
        flag=1;
      }
      ans+=word;
    }
    return ans;

}

int levenshtein(std::string a, std::string b){
  int len_a = a.length();
  int len_b = b.length();
  int d[len_a + 1][len_b+1];

  for(int i = 0; i < len_a + 1; i++)
    d[i][0] = i;

  for(int j = 0; j < len_b + 1; j++)
    d[0][j] = j;

  for(int i = 1; i < len_a + 1; i++){
    for(int j = 1; j < len_b + 1; j++){
      if(a[i - 1] == b[j - 1]){
        d[i][j] = d[i - 1][j - 1];
      }
      else{
        d[i][j] = 1 + min(min(d[i][j-1],d[i-1][j]),d[i-1][j-1]);
      }
    }
  }

  int answer = d[len_a][len_b];

  return answer;
}


int main()
{
    insertion();

    std::string filename1="/Users/sayash/Desktop/Similarity/file1.txt";
    std::string filename2="/Users/sayash/Desktop/Similarity/file2.txt";
    std::cout<<"enter filename 1 ";
    std::cin>>filename1;
    std::cout<<"enter filename 2 ";
    std::cin>>filename2;
    cout<<"\n";

    // std::string s1=converttostring(filename1);
    // std::string s2=converttostring(filename2);

    std::string s1=converttostring("/Users/sayash/Desktop/Similarity/file1.txt");   //file1 to be compared
    std::string s2=converttostring("/Users/sayash/Desktop/Similarity/file2.txt");   //file2 to be compared

    std::cout<<s1<<std::endl;
    std::cout<<s2<<std::endl;

    if(s1=="invalid filename\n" || s2=="invalid filename\n")    //error in filename
    {
      std::cout<<"Invalid filename\n";
    }

    std::cout<<levenshtein(s1,s2);    //final output

    return 0;
}

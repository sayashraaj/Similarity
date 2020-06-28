//time
#include<chrono>

#include <stdio.h>
#include<iostream>
#include<string>
#include<unordered_set>
#include<fstream>
using namespace std;
//time
using namespace std::chrono;
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

//FILE TO STRING AND FILTER
std::string converttostring(std::string filename = "/Users/sayash/Desktop/Similarity/file1.txt")	//default local file
{
  std::string s,temp_word;    //string to return
  FILE *in_file;    //open stream
  char ch,flag=0;

  in_file = fopen(filename.c_str(), "r");   //open file as character string

  if (in_file == NULL)                      //filename error handled
    std::cout<<"invalid filename\n";
  else
  {
      while ((ch = fgetc(in_file)) != EOF)  //fgetc gets character and points to next character
      {
          if (ch == ' ' || ch == '\n' || ch == '\t') continue;  //de-formatting the code
          /*
          C++ ignores spaces between statements, tabs, and newline characters
          in order to reduce file size by a significant amount, the characters can be deleted and ignored
          from edit distance in levenshtein
          */

          else if((ch>='A' && ch<='Z') || (ch<='z' && ch>='a')){

            if(flag){
              while(((ch>='A' && ch<='Z') || (ch<='z' && ch>='a') ||(ch<='9' && ch>='0') )&& ch!=EOF){
                //skipping this word
                temp_word.push_back(ch);
                ch=fgetc(in_file);
              }
              mp.insert(temp_word);
              temp_word="";
              if (!(ch == ' ' || ch == '\n' || ch == '\t')) s.push_back(ch);
            flag=0;continue;}

            while(((ch>='A' && ch<='Z') || (ch<='z' && ch>='a') ||(ch<='9' && ch>='0') )&& ch!=EOF){
              temp_word.push_back(ch);
              // s+=temp_word;
              ch=fgetc(in_file);

              // if(keywords.find(temp_word)!=keywords.end()) flag++;
            }
            if (!(ch == ' ' || ch == '\n' || ch == '\t')) s.push_back(ch);
            if(mp.find(temp_word)==mp.end()) s+=temp_word;
            // cout<<temp_word<<endl;
            if(keywords.find(temp_word)!=keywords.end()) {flag++;}//cout<<1<<endl; inside {}
            temp_word="";
          }
          else{
            s.push_back(ch);
          }
      }
  }
  fclose(in_file);      //closing the stream is very important
  return s;
}

//LEVENSHTEIN
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

//MAIN
int main(){
  insertion();

//starting clock
auto start = high_resolution_clock::now();

std::string s1 = converttostring("/Users/sayash/Desktop/Similarity/file1.txt");
std::string s2 = converttostring("/Users/sayash/Desktop/Similarity/file3.txt");
cout<<s1<<endl;
cout<<s2<<endl;

//levenshtein comparison
std::cout<<levenshtein(s1,s2);    //final output

//stopping clock
auto stop = high_resolution_clock::now();
auto duration = duration_cast<microseconds>(stop - start);
cout << "Time taken: "<< duration.count() << " microseconds" << endl;
}

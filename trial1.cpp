#include <stdio.h>
#include<iostream>
#include<string>
using namespace std;
std::string converttostring(std::string filename = "/Users/sayash/Desktop/Similarity/file1.txt")	//default local file
{
  std::string s;
  char in_name[80];
  FILE *in_file;
  int ch, character = 0, line = 0, space = 0, tab = 0;

  printf("Enter file name:\n");
  scanf("%s", in_name);

  in_file = fopen(filename.c_str(), "r");

  if (in_file == NULL)
    s="invalid filename";
  else
  {
      while ((ch = fgetc(in_file)) != EOF)
      {
          if (ch == ' ' || ch == '\n' || ch == '\t') continue;
          else
          {
            character++;
            s.push_back(ch);
          }
      }
  }
  fclose(in_file);
  return s;
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
    std::string s1=converttostring();   //file1 to be compared
    std::string s2=converttostring();   //file2 to be compared
    std::cout<<levenshtein(s1,s2);

    return 0;
}

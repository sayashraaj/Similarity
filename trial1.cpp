#include <stdio.h>
#include<iostream>
#include<string>

std::string converttostring(std::string filename = "/Users/sayash/Desktop/Similarity/file.txt")	//default local file
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

int levenshtein(std::string s1, std::string s2)
{
  int count=0;

  return count;
}

int main()
{
    std::string s1=converttostring();   //file1 to be compared
		std::cout<<s1; //testing
    //std::string s2=converttostring();   //file2 to be compared

    // int similarity = levenshtein(s1,s2);
    // std::cout<<similarity<<std::endl;
    return 0;
}

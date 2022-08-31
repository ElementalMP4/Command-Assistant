#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <list>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

string exec(string command) {
   char buffer[128];
   string result = "";

   FILE* pipe = popen(command.c_str(), "r");
   if (!pipe) {
      return "popen failed!";
   }

   while (!feof(pipe)) {
      if (fgets(buffer, 128, pipe) != NULL)
         result += buffer;
   }

   pclose(pipe);
   return result;
}

unsigned int distance(const string& s1, const string& s2)
{
	const size_t len1 = s1.size(), len2 = s2.size();
	vector<vector<unsigned int>> d(len1 + 1, vector<unsigned int>(len2 + 1));

	d[0][0] = 0;
	for(unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
	for(unsigned int i = 1; i <= len2; ++i) d[0][i] = i;

	for(unsigned int i = 1; i <= len1; ++i)
		for(unsigned int j = 1; j <= len2; ++j)
            d[i][j] = min({ d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1) });
	return d[len1][len2];
}

int main(int argc, char *argv[]) {
   string command_list = exec("exec bash -c 'compgen -c | egrep -v \".dll|.exe|.NLS|.bat|.cmd|.ps1|.sql|.DLL|.EXE|.nlp|.log|.txt|.pdf|.html|.TXT|.xml|.mof|.png|.nls\"'");
   list<string> commands;

   stringstream ss(command_list);
   string command;

   while(getline(ss, command, '\n')){
      commands.push_front(command);
   }

   if (argc < 3) return 0;
   string command_to_find = argv[2];

   list<string> possible_commands;
   copy_if(commands.begin(), commands.end(), std::back_inserter(possible_commands),
      [&](string command_name){return distance(command_name, command_to_find) <= 1;} );

   cout << "Command '" << command_to_find << "' could not be found." << endl;

   if (possible_commands.size() > 0) {
      cout << "Did you mean one of these: ";
      list<string>::iterator it;
      for (it = possible_commands.begin(); it != possible_commands.end(); it++) {
         cout << "'" << it -> c_str() << "' ";
      }
      cout << endl;
   }
   
   return 0;
}
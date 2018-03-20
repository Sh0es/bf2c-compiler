#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

static ifstream bfFile;
static ofstream cFile;

string ext(string fn)
{
	string x = string();
	for(int i = fn.find('.'); i < fn.size(); i++)
	{
		x.push_back(fn[i]);
	}
	return fn;
}

int main()
{
	string ifname;
	char curr_char;
	unsigned int loop;

	cout << "Enter Filename" << endl;
	cin >> ifname;

	if(ext(ifname) != "bf")
	{
		cerr << "ERROR: That isn't a `bf` file." << endl;
		return -1;
	}

	string ofname = string();
	for(int i = 0; i < ifname.find('.'); i++)
	{
		ofname.push_back(ifname[i]);
	}
	ofname += ".c";

	bfFile.open(ifname);
	if(bfFile.fail())
	{
		cerr << "ERROR: File Failed to Open" << endl;
		return -1;
	}

	cFile.open(ofname);

	cFile << "#include <stdlib.h>" << endl
	      << "#include <stdio.h>" << endl
	      << endl
	      << "unsigned char tape[30000] = {0};" << endl
	      << "unsigned char* ptr = tape" << endl
          << "int main() {" << endl
          << "	size_t loop;" << endl
          << "\t" << endl;

	while(!bfFile.eof())
	{
		bfFile >> curr_char;

		if (curr_char == '>')
		{
			cFile << "	++ptr;" << endl;
		}
		else if (curr_char == '<')
		{
			cFile << "	--ptr;" << endl;
		}
		else if (curr_char == '+')
		{
			cFile << "	++*ptr;" << endl;
		}
		else if (curr_char == '-')
		{
			cFile << "	--*ptr;" << endl;
		}
		else if (curr_char == '.')
		{
			cFile << "	putchar(*ptr);" << endl;
		}
		else if (curr_char == ',')
		{
			cFile << "	*ptr = getchar();" << endl;
		}
		else if (curr_char == '[')
		{
			cFile << "	continue;" << endl;
		}
		else if (curr_char == ']')
		{
			cFile << "	loop = 1;" << endl
			      << "	while (loop > 0) {" << endl
			      << "		curr_char = input[--i];" << endl
			      << "		if (curr_char == '[') {" << endl
			      << "			loop--;" << endl
			      << "		} else if (curr_char == ']') {" << endl
			      << "			loop++;" << endl
			      << "		}" << endl
			      << "	}" << endl;
		}
		cout << "\t" << endl;
	}

	cout << "File `" << ofname << "` successfully created!" << endl;

	bfFile.close();
	cFile.close();
	return 0;
}

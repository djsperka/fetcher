/*
 * main.cpp
 *
 *  Created on: Nov 6, 2018
 *      Author: dan
 */

#include "fetcher.h"
#include <string>
#include <iostream>

#include <boost/algorithm/string.hpp>
using boost::algorithm::to_lower_copy;
using boost::algorithm::to_lower;

using namespace std;
using boost::filesystem::path;


// using function pointer - cannot store state, so e.g. changing extension type requires hardcoding it into function,
// saving it as global, etc.
//bool my_match(const path& p, string& key)
//{
//	bool b = false;
//	//cerr << p.string() << endl;
//	if (to_lower_copy(p.extension().string()) == string(".bmp"))
//	{
//		b = true;
//		key = p.stem().string();
//	}
//	return b;
//}

class MyPathMatcher: public PathMatcher<string>
{
	string m_extension;
public:
	MyPathMatcher(const string& ext): m_extension(ext) { to_lower(m_extension); };
	bool operator()(const path& p, string& key)
	{
		bool b = false;
		//cerr << p.string() << endl;
		if (to_lower_copy(p.extension().string()) == m_extension)
		{
			b = true;
			key = p.stem().string();
		}
		return b;
	}
};



int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    cout << "Usage: fetcher path\n";
    return 1;
  }
  cerr << "path is " << argv[1] << endl;
//  FetcherWithFuncPointer<string> myfiles(string(argv[1]), my_match);
//  cerr << "With func pointer result" << endl;
//  for (map<string, path>::iterator it = myfiles.begin(); it != myfiles.end(); it++)
//	  cout << it->second.string() << endl;

  MyPathMatcher mpm(".bmp");
  FetcherWithFunctor<string> withFunctor(string(argv[1]), mpm);
  cerr << "With functor result" << endl;
  for (map<string, path>::iterator it = withFunctor.begin(); it != withFunctor.end(); it++)
	  cerr << it->second.string() << endl;

  return 0;
}

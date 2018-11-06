//============================================================================
// Name        : fetcher.cpp
// Author      : Daniel J Sperka
// Version     :
// Copyright   : Copyright 2018
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/filesystem.hpp>
using namespace std;
using namespace boost::filesystem;


//template(class K) {
//	class Fetcher: public map<K, path>
//	{
//		Fetcher(const string& folder, bool (*match)(const path& p, K& key))
//		{
//}


int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    cout << "Usage: tut4 path\n";
    return 1;
  }

  path p (argv[1]);

  try
  {
    if (exists(p))
    {
      if (is_regular_file(p))
        cout << p << " size is " << file_size(p) << '\n';

      else if (is_directory(p))
      {
        cout << p << " is a directory containing:\n";

        std::vector<path> v;

        for (auto&& x : directory_iterator(p))
          v.push_back(x.path());

        std::sort(v.begin(), v.end());

        for (auto&& x : v)
          cout << "    " << x.filename() << '\n';
      }
      else
        cout << p << " exists, but is not a regular file or directory\n";
    }
    else
      cout << p << " does not exist\n";
  }

  catch (const filesystem_error& ex)
  {
    cout << ex.what() << '\n';
  }

  return 0;
}

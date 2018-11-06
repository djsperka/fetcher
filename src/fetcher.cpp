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
#include <map>
#include <boost/filesystem.hpp>
using namespace std;
using namespace boost::filesystem;


bool my_match(const path& p, string& key)
{
	bool b = false;
	if (to_lower(p.extension()) == string(".bmp"))
	{
		b = true;
		key = p.stem();
	}
	return b;
}



template<class K>
	class Fetcher: public map<K, path>
	{
	private:
		bool (*match)(const path& p, K& key);
		void scan_path(const path& p)
		{
			K key;
			if (is_regular_file(p) && m_match(p, key))
				this->insert(make_pair(key, p));
			else if (is_directory(p))
			{
				for (auto&& x : directory_iterator(p))
					scan_path(x.path());
			}
		};

	public:
		Fetcher(const string& folder, bool (*match)(const path& p, K& key))
		{
			path p(folder);
			scan_path(p);
		};
	};


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

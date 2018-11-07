# fetcher
utility for fetching/using set of files from a folder
Header-only utility for a situation where you want to access one of a 
set of files. 

The files can be in a single folder (which may contain a 
hierarchy). 

You provide a class that implements operator() and which 
answers this question for each file encountered in a crawl of the 
base folder: *Should this file be included in the map, and if so, what
should the identifying key be?*

The key type can be anything that satisfies the requirements for a map key, 
namely they be *copyable*, *assignable*. 

A *comparator* can be provided
in the map constructor, which can define the ordering of the keys, 
but I haven't done that here. The default is to use less<K>, same as operator<
in typical cases. 

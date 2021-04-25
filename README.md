# nanaprint
A library for printing from nana gui applications.

[nana](https://nanapro.org) is a modern C++ cross-platform library for developing GUI applications.
It is a library, not a framework.
Therefore, much functionality is not included in nana, such as printing capabilities. nanaprint
is a library that
is intended to provide that missing functionality, thereby allowing printing in nana applications. 
Initially, it supports printing using
CUPS and Win32 APIs. Support for other printing libraries may be added at a later time.

After six months of work on this project, I have decided to shelve it, at least for the time being.

## Problem Areas

### CUPS
There are a number of CUPS APIs: cups, ipp, ppd, and maybe others. Here are some of the problems that I found:
* The cups and ipp apis can be used to return information from the printer driver, such as the media sizes (paper
sizes). But the ipp API returns the default paper size from the printer driver based on locale. This is typically
either A4 or Letter. If the user changes the default paper size, the information is stored in the printer driver's
PPD file, so to get the user specified default, you must use the ppd api.
* The PPD API is deprecated.
* Not all printer drivers come with PPD files.

### WIN32
nana uses UTF8 for input and output strings. The WIN32 APIs use either ASCII or UTF16.
* There are some conversion techniques provided in the C++ STL for converting between the two, but they are
deprecated because ill-formed UTF can be used as an attack vector. There are currently no safe alternatives provided
in the STL.
* An alternative may be to use WideCharToMultibyte and MultibytToWideChar in the WIN32 API, but they suffer from
the same problem.

It may be possible to kludge something together. If fact, I have found a couple of attempts on the internet, although
I do not know how safe they are. I can think of a technique that might work, but then it may suffer from the same problem
that the techniques in the STL suffer from.

So, for now, I am going to work on another project until either new functionality is added to the STL (C++23/C++26 anyone?) or
I feel inspired to got look at the problem some more.

# strglob TODO list

* better input validation inside `open_bracket`, permitted syntax:
  - `[`-|]` 
  - `[x-}]`
  - `[+1-+2]`
  - `[+1-2]`

* Create UNIX manual page with `nroff`

* Write PDF guide with LaTeX

* Make a Ruby C extension gem

* give the command line tester --usage and --version flags via `getopt_long()`

* [doxygen](http://stack.nl/~dimitri/doxygen/ "Generate documentation from source code")

* Include a function for disjunctive syllogism of a set?

* Zero pad first part of range if ending part of range is padded, i.e. `[0-02]`

* Make new syntaxes:

<pre>
[1000-2000%10] => 1000 1010 1020 1030 1040 .. 1980 1990 2000

{aa-zz} => aa ab ac .. ba bb bc .. zx zy zz

{a-zzz} => a b .. aa ab ac .. ba bb bc .. ca cb cc .. aaa aab aac .. baa bab bac .. bbb bca bcb .. caa cab cac .. zzz

[-10--1] => -10 -9 -8 -7 -6 -5 -4 -3 -2 -1

[-1-0] => -1 0

[-1-1] => -1 0 1

[-1-+1] => -1 0 +1

[1.0-1.9,0.1] => 1.0 1.1 1.2 1.3 1.4 1.5 1.6 1.7 1.8 1.9 # comma sinigifes increment/decrement

[2-5_x/2] => 1 .5 2 2.5 # underscore signifies formula

{:wdays:} => mon, tue, wed, thu, fri, sat, sun # character class vs string class

{:Wdays:} => Mon, Tue, Wed, Thu, Fri, Sat, Sun

{:WDAYS:} => MON, TUE, WED, THU, FRI, SAT, SUN

{:weekdays:} => monday, tuesday, wednesday, thursday, friday, saturday, sunday 

([1-2][1-3]) => 1 2 1 2 3

([1-3]{a,b,c}) => 1 2 3 a b c

{.//file/test.txt} => testline1, testline2 # realpath //file/test.txt => /file/test.txt

{"a","b","c"} => a b c # start these with quotes to distinguish other syntax?

unicode/wchar.h ?!?
</pre>

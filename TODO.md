# strglob TODO list

* generate random string from expression

* create screencast for README 
  - https://imdjh.github.io/howto/2015/10/09/howto-ffmpeg-capture-screen-as-gif.html

* use `assert.sh` for testing

* BUG: `a[00-01]b`

* `{1..10..2}`
  - 1 through 10 with 2 as increment

* `{-1..-10..-2}`
  - -1 through -10 with -2 as increment

* `{-1.2..-2.4..1.2}`
  - -1.2 through -2.4 with 1.2 as increment -2.4/1.2 is evenly divisble

* `{a..z..10}`
  - this works too

* combining/negating character classes
  - `[[:print:][^[:alnum:]]]`

* inside of parens is IP address expansion for:
  - 192.168.0.0/16
  - 192.168.*.*
  - 192.168.0-255.0-255
  - 192.168.0.0/255.255.0.0

* restrict file input according to one or more of:
  - only allow CWD
  - allow allow HOME
  - pathname must match realpath
  - pathname cannot be relative
  - pathname cannot contain "CDUP" `..`

* interpolate environment variabes
  - `{$HOME}` one string
  - `{:${ANARRAY[@]}:}` multiple strings

* implement cmake and/or autotools

* better input validation inside `open_bracket`, permitted syntax:
  - `[`-|]` 
  - `[x-}]`

* Create UNIX manual page with `nroff`

* Write PDF guide with LaTeX

* Make a Ruby C extension gem

* give the command line tester --usage and --version flags via `getopt_long()`

* [doxygen](http://stack.nl/~dimitri/doxygen/ "Generate documentation from source code")

* Make new syntaxes:

<pre>
{aa-zz} => aa ab ac .. ba bb bc .. zx zy zz

{a-zzz} => a b .. aa ab ac .. ba bb bc .. ca cb cc .. aaa aab aac .. baa bab bac .. bbb bca bcb .. caa cab cac .. zzz

[1.0-1.9,0.1] => 1.0 1.1 1.2 1.3 1.4 1.5 1.6 1.7 1.8 1.9 # comma sinigifes increment/decrement

[2-5_x/2] => 1 .5 2 2.5 # underscore signifies formula

{:wdays:} => mon, tue, wed, thu, fri, sat, sun # character class vs string class

{:Wdays:} => Mon, Tue, Wed, Thu, Fri, Sat, Sun

{:WDAYS:} => MON, TUE, WED, THU, FRI, SAT, SUN

{:weekdays:} => monday, tuesday, wednesday, thursday, friday, saturday, sunday 

[01abc] => 0 1 a b c
</pre>

https://msdn.microsoft.com/en-us/library/system.char.issymbol(v=vs.110).aspx
https://msdn.microsoft.com/en-us/library/system.char.ispunctuation(v=vs.110).aspx
https://msdn.microsoft.com/en-us/library/system.globalization.unicodecategory(v=vs.110).aspx
http://www.unicode.org/reports/tr44/
http://doctoc.herokuapp.com/
c



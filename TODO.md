# strglob TODO list

* generate random string from expression <randcrap> (???) 

* decide on good delimiter for increment 
  - period already used for decimal in float/double numbers
  - dash used for delimiter in range
  - etc.

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

* expand environment variables

* command execution with $(pwd)

* restrict file input according to one or more of:
  - only allow CWD
  - allow allow HOME
  - pathname must match realpath
  - pathname cannot be relative
  - pathname cannot contain "CDUP" `..`

* implement cmake and/or autotools

* better input validation inside `open_bracket`, permitted syntax:
  - `[`-|]` 
  - `[x-}]`

* Create UNIX manual page with `nroff`

* Write PDF guide with LaTeX

* Make Ruby and Go extensions

* give the command line tester --usage and --version flags via `getopt_long()`

* [doxygen](http://stack.nl/~dimitri/doxygen/ "Generate documentation from source code")

* Make new syntaxes:

<pre>
{aa-zz} => aa ab ac .. ba bb bc .. zx zy zz

{a-zzz} => a b .. aa ab ac .. ba bb bc .. ca cb cc .. aaa aab aac .. baa bab bac .. bbb bca bcb .. caa cab cac .. zzz

{2..5..x/2} => 1 .5 2 2.5 # 'x' signifies formula

{:wdays:} => mon, tue, wed, thu, fri, sat, sun # character class vs string class

{:Wdays:} => Mon, Tue, Wed, Thu, Fri, Sat, Sun

{:WDAYS:} => MON, TUE, WED, THU, FRI, SAT, SUN

{:weekdays:} => monday, tuesday, wednesday, thursday, friday, saturday, sunday 

[01abc] => 0 1 a b c
</pre>

* weekdays, months, states, countries (abbrevs/capital/upper/etc. of all these)

# strglob by Derek Callaway [derek {D0T} callaway (AT) ioactive {D0T} com]

`strglob` is a shared and/or static library implementation designed to expand supplied globbing syntax pattern into multiple strings.
Its purpose is to provide a compact specification for software security test cases. 
In particular, the enumeration of input data strings for use against the attack surfaces of web-based technologies.

This is similar to the ranges used by [curl](https://curl.haxx.se "cURL") on a shell command line:

- `curl 'https://host.dom/[a-c]/'`
  * `https://a`
  * `https://b`
  * `https://c`

- `curl 'https://host.dom/[0-2]/'`
  * `https://0`
  * `https://1`
  * `https://2`

`strglob` supports a wide variety of syntax for ranges, classes and sets, including:
  * numeric ranges
    - [0-4] => 0 1 2 3 4
    - [10-14] => 10 11 12 13 14
  * alphabetic ranges
    - [e-i] => e f g h i
    - [A-C] => A B C
  * zero-prepended numeric ranges
    - [01-03] => 01 02 03
  * character classes
    - [:digit:] => 0 1 2 3 4 5 6 7 8 9 0
  * string sets
    - {"a","b","c"} => a b c
  * string classes
    - {:wdays:} => sun mon tue wed thu fri sat sun
    - {:Mons:} => Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec

See the `TODO.md` file for planned syntaxes..

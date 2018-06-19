# strglob :speech_balloon:   

## Description :page_facing_up:

1. `strglob` is a C development library designed to enumerate characters/numbers/strings by expanding "globbing" pattern syntax
2. Its purpose is to provide a compact specification for test case input string generation.
<!-- 3. For example, the `fjorge` tool that links against `libstrglob` uses it to automatically craft successive HTTP requests. -->


## strglob Features :bar_chart:

`strglob` supports a wide variety of syntax types for both character and string generation including: 
  1. ranges :game_die: 
    * alphabetic ranges
      - `[e-i]` => `e f g h i` (lowercase)
      - `[A-C]` => `A B C` (uppercase)
    * numeric ranges
      - `[0-4]` => `0 1 2 3 4` (zero inclusive natural numbers)
      - `[10-14]` => `10 11 12 13 14` (multiple digits)
    * negative numeric ranges
      - `[-2-2]` => `-2 -1 0 1 2` (real numbers and whole numbers)
      - `[-4--2]` => `-4 -3 -2` (real numbers only)
    * zero-prepended numeric ranges
      - `[01-03]` => `01 02 03` (both limits)
      - `[01-4]` => `01 02 03 04` (first only)
      - `[0-02]` => `0 1 2` (last only)
    * reverse ranges
      - `[c-a]` => `c b a` (alphabetic characters)
      - `[3-1]` => `3 2 1` (numeric digits)
      - `[-1--3]` => `-1 -2 -3` (negative integers)
      - `[2--1]` => `2 0 1 -1` (real numbers)
    * sequence expression ranges
      - `{d..b}` => `d c b` (reverse range of alphabetic characters)
      - `{a..f..2}` => `a c e` (alphabetic range with increment value)
      - `{1..3}` => `1 2 3` (numeric range)
      - `{-2..2}` => `-2 -1 0 1 2` (negative numeric range)
      - `{0..6..2}` => `0 2 4 6` (numeric range with increment value)
  2. classes :wind_chime:
    * [character classes](https://github.com/decal/strglob/wiki/Character-Classes)
      - `[:digit:]` => `0 1 2 3 4 5 6 7 8 9 0` [numeric digits](
      - `[:reserved:]` => `! # $ & ' ( ) * + , / : ; = ? @ [ ]` [percent-encoding reserved characters](https://wikipedia.org/wiki/Percent-encoding#Percent-encoding_reserved_characters)
    * [string classes](https://github.com/decal/strglob/wiki/String-Classes)
      - `{:wdays:}` => `sun mon tue wed thu fri sat sun` (lowercase weekdays)
      - `{:Wdays:}` => `Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec` (capital weekdays)
      - `{:WDAYS:}` => `JAN FEB MAR APR MAY JUN JUL AUG SEP OCT NOV DEC` (uppercase weekdays)
  3. sets :round_pushpin:
    * [string sets](https://github.com/decal/strglob/wiki/String-Sets)
      - `{a,b,c}` => `a b c` (logical and)
  4. shell features :ticket:
    * [environment expansion](https://github.com/decal/strglob/wiki/Environment-Expansion)
      - `{$LOGNAME}` => `decal` (login name variable)
    * [file includes](https://github.com/decal/strglob/wiki/File-Includes)
      - `{/etc/issue.net}` => `Ubuntu 16.04.4 LTS` (identification file for telnet sessions)
    
### Note that.. :memo:

> Numeric and character ranges are denoted by square brackets 

> Strings are signified with curly braces

> Range limits are delimited by dashes which are also for signing negative integers

> String sets are separated by commas

> Both character and string class names are surrounded by colons

> Character class identifiers are taken from the standard C library's `ctype.h` header file

> Bash-style sequence expressions are specified with curly braces and take an optional numeric increment value


## Related Documentation :books:

  * See the `TODO.md` file for planned syntax techniques..
  * [strglob wiki](https://github.com/decal/strglob/wiki)
  * [Globbing](http://tldp.org/LDP/abs/html/globbingref.html "Advanced Bash-Scripting Guide")
  * [glob (programming)](https://wikipedia.org/wiki/Glob_%28programming%29)
  * [String generation](https://wikipedia.org/wiki/String_generation)


## cURL Influence :curly_loop:

`strglob` behaves similar to the lists and ranges implemented by [curl](https://curl.haxx.se "cURL") on the command line:

- `curl 'https://host.dom/{foo,bar,baz}/'`
  * `https://foo`
  * `https://bar`
  * `https://baz`

- `curl 'https://host.dom/[0-2]/'`
  * `https://0`
  * `https://1`
  * `https://2`

- Refer to the *URL globbing* section in [_Everything curl_](https://ec.haxx.se/cmdline-globbing.html) for more information.

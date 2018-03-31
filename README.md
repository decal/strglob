# strglob :speech_balloon:   

## Description :page_facing_up:

1. `strglob` is a C development library designed to enumerate strings by expanding "globbing" pattern syntax
2. Its purpose is to provide a compact specification for test case input string generation.
3. For example, the `fjorge` tool that links against `libstrglob` uses it to automatically craft successive HTTP requests.


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


## strglob Features :bar_chart:

`strglob` supports a wide variety of syntax types for both character and string generation including: 
  1. ranges  
    * alphabetic ranges
      - [e-i] => e f g h i
      - [A-C] => A B C
    * numeric ranges
      - [0-4] => 0 1 2 3 4
      - [10-14] => 10 11 12 13 14
    * zero-prepended numeric ranges
      - [01-03] => 01 02 03
      - [0-02] => 0 1 2
  2. classes  
    * character classes
      - [:digit:] => 0 1 2 3 4 5 6 7 8 9 0
    * string classes
      - {:wdays:} => sun mon tue wed thu fri sat sun
      - {:Mons:} => Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
  3. sets  
    * string sets
      - {"a","b","c"} => a b c


## Related Documentation :books:

  * See the `TODO.md` file for planned syntax techniques..
  * [Globbing](http://tldp.org/LDP/abs/html/globbingref.html "Advanced Bash-Scripting Guide")
  * [glob (programming)](https://en.wikipedia.org/wiki/Glob_%28programming%29)
  * [String generation](https://en.wikipedia.org/wiki/String_generation)

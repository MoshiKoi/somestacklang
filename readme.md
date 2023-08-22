# somestacklang

Originally made for [mkukiro](https://github.com/mkukiro)'s esolang contest, has since been revised slightly and with added documentation.

# Overview

There are four types of values in somestacklang:

|Type|Execution behavior|
|:-|:-|
|Number|Print the number to stdout|
|String|Print the string to stdout|
|List|Push the values to the stack|
|Operation|Execute the operation|

## Operations

|Operation|Stack|Notes|
|:-|:-|:-|
|`add`|`[...] 'a:Number 'b:Number add → [('a + 'b) ...]`||
|`sub`|`[...] 'a:Number 'b:Number sub → [('a - 'b) ...]`||
|`mul`|`[...] 'a:Number 'b:Number mul → [('a * 'b) ...]`||
|`div`|`[...] 'a:Number 'b:Number div → [('a / 'b) ...]`||
|`dup`|`'a dup → 'a 'a`||
|`commute`|`[[...]*] 'a commute → [['a ...]*]`||
|`read`|`[...] read →  [String ...]`|Reads a string from standard input|
|`readnum`|`[...] readnum →  [Number ...]`|Reads a number from standard input|
|`cond`|`[...] 'a 'b 'c if → [('a or 'b) ...]`|If `'c` is truthy selects `'b`, otherwise selects `'a`|

A program represents the initial stack, going from bottom to top. A program is executed by repeatedly popping the top of the stack and executing the popped value. The program ends when the stack is empty.

# Examples

## Truth Machine

```
[] 0 [[dup 1] dup] [if] readnum
```

 - `[] 0 [[dup 1] dup] [if] readnum` - Reads a number `'x`
 - `[] 0 [[dup 1] dup] ['x if]` - Unwraps
 - `[] 0 [[dup 1] dup] 'x if`
 - If `'x` is truthy (non-zero)
    - `[[[dup 1] dup]]` Unwrap
    - `[[dup 1] dup]` Unwrap
    - `[dup 1] dup` Duplicate
    - `[dup 1] [dup 1]` Unwrap
    - `[dup 1] dup 1` Print 1
    - `[dup 1] dup` Stack repeats
 - Otherwise
    - `[0]` Unwrap
    - `0` Print `0`
    - End
# ccwc: a `wc` clone for learning purposes

This endeavor is proposed by John Crickett in his [Coding Challenges](https://codingchallenges.fyi/challenges/challenge-wc/).

It has been an amazing opportunity to learn lots of things:
- implementing discrete math algorithms by hand
- understanding the (mess) rich variety of `wc` implementations for formatting output*
- using FSMs for modelling state transitions
- ([once again](https://github.com/OmarMesqq/unicode_converter)) doing low-level bit processing of UTF-8 chars
- file and standard input byte reading 


## Usage
You can use this software in 3 distinct forms:
1. `ccwc -X <file>`
2. `ccwc <file>`
3. `ccwc -X` (for `stdin` processing)

where `X` is one of the supported flags of OG `wc`:
- `-c`: byte count
- `-l`: line count
- `-w`: word count
- `-m`: character count

*this project is compliant to the BSD version of `wc`, found on macOS.
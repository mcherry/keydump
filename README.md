# keydump

A simple keylogger for OSX written in C. The keylogger is designed to execute for two minutes and prints the log to standard output suitable for redirecting in a shell script. Key strings are also 'encoded' to hide them inside the binary. The binary can also be compressed with UPX and embedded in a shell script using uuencode.

Based on code from the following project:

https://github.com/caseyscarborough/keylogger

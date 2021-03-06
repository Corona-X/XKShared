/**=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=**/
/* CLUnicode.h - Basic Unicode String Handling for C               */
/**=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=**/
/* beeselmane - 8.8.2017   - 5:00 PM EST                           */
/**=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=**/

#ifndef __KERNEL_C_CLUNICODE__
#define __KERNEL_C_CLUNICODE__ 1

#include <Corona-X.h>
#include <System/OSTypes.h>
#include <System/OSCompilerMacros.h>

#define kCLUTF32Error               0xFFFFFFFF
#define kCLUTF16Error               0xFFFF
#define kCLUTF8Error                0xFF

#define kCLSurrogateHighBegin       0xD800
#define kCLSurrogateHighFinish      0xDBFF
#define kCLSurrogateLowBegin        0xDC00
#define kCLSurrogateLowFinish       0xDFFF

/**
 * This function converts a unicode codepoint into a string of UTF-8 bytes.
 *   It is NOT guarenteed to work for characters greater than U+10FFFF, as this
 *   is the highest possible codepoint for standard UTF-8.
 *
 * @argument point:
 *   The codepoint to be converted to UTF-8
 *
 * @argument output:
 *   The buffer in which to place the resulting UTF-8. The 'size' field in this
 *   buffer specifies how many characters may be placed into it. If more bytes
 *   are needed, this function will fail.
 *
 * @return:
 *   This function returns the number of characters placed into the buffer,
 *   or 0 in the case of an error. The possible errors are that the codepoint
 *   given cannot be encoded in the UTF-8 format or that the buffer is too small
 *   to hold all the required bytes. If the buffer is not large enough, no bytes
 *   will be written to it on return.
 */
OSShared OSCount CLUTF8FromCodePoint(OSUnicodePoint point, OSUTF8Char *output, OSSize outputSize);

/**
 * This function converts a string of UTF-8 characters into a single code point.
 *   This method will work on 1-6 characters to produce a codepoint, although the
 *   resulting value is not guarenteed to be a valid Unicode point.
 *
 * @argument input:
 *   The buffer from which to read the input bytes. The 'size' field in this buffer
 *   specifies how many characters are in the input buffer. If a full codepoint
 *   cannot be extracted from this buffer, this function will fail.
 *
 * @argument used:
 *   This is a pointer used to communicate how many bytes from the input buffer were
 *   used to create the output codepoint. This pointer must not be null. It will be
 *   set to the number of bytes used when the function returns. If the function
 *   fails, it will be set to the size of the input buffer.
 *
 * @return:
 *   This function returns either a codepoint which was constructed from the first
 *   bytes in the buffer or a value of 'kXKUTF32Error' if an error occurred. This
 *   function will error if there are not enough bytes in the input buffer, the used
 *   pointer is null, or if the input buffer contains malformed UTF-8.
 */
OSShared OSUnicodePoint CLUTF8ToCodePoint(const OSUTF8Char *input, OSSize inputSize, OSCount *used);

/**
 * This function converts a unicode codepoint into a string of UTF-16 words.
 *   It is NOT guarenteed to work for characters greater than U+10FFFF, as this
 *   is the highest possible codepoint for standard UTF-16.
 *
 * @argument point:
 *   The codepoint to be converted to UTF-16
 *
 * @argument output:
 *   The buffer in which to place the resulting UTF-16. The 'size' field in this
 *   buffer specifies how many characters may be placed into it. If more space
 *   is needed, this function will fail.
 *
 * @return:
 *   This function returns the number of characters placed into the buffer,
 *   or 0 in the case of an error. The possible errors are that the codepoint
 *   given cannot be encoded in the UTF-16 format or that the buffer is too
 *   small to hold all the required bytes. If the buffer is not large enough,
 *   no bytes will be written to it on return.
 */
OSShared OSCount CLUTF16FromCodePoint(OSUnicodePoint point, OSUTF16Char *output, OSSize outputSize);

/**
 * This function converts a string of UTF-16 characters into a single code point.
 *   This method will work on 1-6 characters to produce a codepoint, although the
 *   resulting value is not guarenteed to be a valid Unicode point.
 *
 * @argument input:
 *   The buffer from which to read the input characters. The 'size' field in this
 *   buffer specifies how many characters are in the input buffer. If a full
 *   codepoint cannot be extracted from this buffer, this function will fail.
 *
 * @argument used:
 *   This is a pointer used to communicate how many characters from the input buffer
 *   were used to create the output codepoint. This pointer must not be null. It wil
 *   be set to the number of bytes used when the function returns. If the function
 *   fails, it will be set to the size of the input buffer.
 *
 * @return:
 *   This function returns either a codepoint which was constructed from the first
 *   characters in the buffer or a value of 'kXKUTF32Error' if an error occurred.
 *   This function will error if there are not enough characters in the input buffer,
 *   the used pointer is null, or if the input buffer contains malformed UTF-8.
 */
OSShared OSUnicodePoint CLUTF16ToCodePoint(const OSUTF16Char *input, OSSize inputSize, OSCount *used);

/**
 * This function gets the number of characters required to encode a UTF-16 encoded
 *   string in UTF-8.
 *
 * @argument string:
 *   The UTF-16 encoded string.
 *
 * @return:
 *   The number of bytes required to re-encode the string on success, or every bit
 *     set in the result for error.
 */
OSShared OSLength CLUTF16LengthInUTF8(const OSUTF16Char *string);

/**
 * This function gets the number of characters required to encode a UTF-8 encoded
 *   string in UTF-16.
 *
 * @argument string:
 *   The UTF-8 encoded string.
 *
 * @return:
 *   The number of bytes required to re-encode the string on success, or every bit
 *     set in the result for error.
 */
OSShared OSLength CLUTF8LengthInUTF16(const OSUTF8Char *string);

/**
 * This function converts a provided UTF-16 encoded string into
 *   an equivalent string encoded in UTF-8. The returned string
 *   must be free'd with the proper function (whatever the
 *   current definition of XKFree is in XKSharedTarget.h)
 *
 * @argument string:
 *   The UTF-16 encoded string to convert.
 *
 * @return:
 *   On failure, a null pointer.
 *   On successs, a string allocated with XKAllocate encoded with
 *   the UTF-8 encoding. Must be freed with XKFree (note:
 *   XKAllocate and XKFree are macros define in XKSharedTarget.h)
 */
OSShared OSUTF8Char *CLUTF16ToUTF8(const OSUTF16Char *string);

/**
 * This function converts a provided UTF-8 encoded string into
 *   an equivalent string encoded in UTF-16. The returned string
 *   must be free'd with the proper function (whatever the
 *   current definition of XKFree is in XKSharedTarget.h)
 *
 * @argument string:
 *   The UTF-8 encoded string to convert.
 *
 * @return:
 *   On failure, a null pointer.
 *   On successs, a string allocated with XKAllocate encoded with
 *   the UTF-16 encoding. Must be freed with XKFree (note:
 *   XKAllocate and XKFree are macros define in XKSharedTarget.h)
 */
OSShared OSUTF16Char *CLUTF8ToUTF16(const OSUTF8Char *string);

/**
 * This function gets the number of characters in the given
 *   UTF-32 encoded string.
 *
 * @argument string:
 *   The UTF-32 encoded string.
 *
 * @return:
 *   The number of characters in the string.
 */
OSShared OSLength CLUTF32Length(const OSUTF32Char *string);

/**
 * This function gets the number of characters in the given
 *   UTF-16 encoded string.
 *
 * @argument string:
 *   The UTF-16 encoded string.
 *
 * @return:
 *   The number of characters in the string.
 */
OSShared OSLength CLUTF16Length(const OSUTF16Char *string);

/**
 * This function gets the number of characters in the given
 *   UTF-8 encoded string.
 *
 * @argument string:
 *   The UTF-8 encoded string.
 *
 * @return:
 *   The number of characters in the string.
 */
OSShared OSLength CLUTF8Length(const OSUTF8Char *string);

#endif /* !defined(__KERNEL_C_CLUNICODE__) */

/* Automatically generated by
	VMPluginCodeGenerator VMMaker.oscog-eem.2445 uuid: ecf80f10-9e24-4ff5-8a41-d65cb2690c94
   from
	FileAttributesPlugin FileAttributesPlugin.oscog-AlistairGrant.38 uuid: f0fcdb0f-e642-4f87-8a9f-d35ffa0d05ff
 */
static char __buildInfo[] = "FileAttributesPlugin FileAttributesPlugin.oscog-AlistairGrant.38 uuid: f0fcdb0f-e642-4f87-8a9f-d35ffa0d05ff " __DATE__ ;



#include "config.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <limits.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#if _WIN32 || _WIN64
# include <windows.h>
# include <winbase.h>
# define FAIL() { return -1; }
# include "sqWin32File.h"
# if !defined(PATH_MAX) /* work around bug in 64-bit cygwin; sigh :-( */
#	define PATH_MAX 4096
# endif
# define HAVE_CHMOD 0
# define HAVE_CHOWN 0
#else
#define HAVE_CHMOD 1
#define HAVE_CHOWN 1
#endif
#include <sys/stat.h>
#if !defined(HAVE_LSTAT) && !defined(_WIN32) && !defined(_WIN64)
# define HAVE_LSTAT 1
#endif
#include <unistd.h>
/* AKG 2018 - FileAttributesPlugin.c translated from class FileAttributesPlugin */

/* Default EXPORT macro that does nothing (see comment in sq.h): */
#define EXPORT(returnType) returnType

/* Do not include the entire sq.h file but just those parts needed. */
#include "sqConfig.h"			/* Configuration options */
#include "sqVirtualMachine.h"	/*  The virtual machine proxy definition */
#include "sqPlatformSpecific.h"	/* Platform specific definitions */

#define true 1
#define false 0
#define null 0  /* using 'null' because nil is predefined in Think C */
#ifdef SQUEAK_BUILTIN_PLUGIN
# undef EXPORT
# define EXPORT(returnType) static returnType
#endif

#include "faCommon.h"
#include "sqMemoryAccess.h"


/*** Constants ***/
#define PrimErrBadArgument 3
#define PrimErrNoMemory 9


/*** Function Prototypes ***/
static sqInt addressObjectFor(void *aMachineAddress);
static sqInt canOpenDirectoryStreamForlength(char *aPathCString, sqInt length);
static sqInt canStatFilePathlength(char *aPathCString, sqInt length);
#if _WIN32
static sqLong convertWinToSqueakTime(SYSTEMTIME st);
#endif /* _WIN32 */
static int fileToAttributeArraymaskarray(fapath *faPath, sqInt attributeMask, sqInt *attributeArray);
EXPORT(const char*) getModuleName(void);
EXPORT(sqInt) initialiseModule(void);
static int pathOoptoBuffermaxLen(sqInt pathNameOop, char *cPathName, sqInt maxLen);
static void * pointerFrom(sqInt directoryPointerBytes);
static sqInt posixFileTimesFromto(faStatStruct *statBufPointer, sqInt attributeArray);
EXPORT(sqInt) primitiveChangeMode(void);
EXPORT(sqInt) primitiveChangeOwner(void);
EXPORT(sqInt) primitiveClosedir(void);
EXPORT(sqInt) primitiveFileAttribute(void);
EXPORT(sqInt) primitiveFileAttributes(void);
EXPORT(sqInt) primitiveFileExists(void);
EXPORT(sqInt) primitiveFileMasks(void);
EXPORT(sqInt) primitiveLogicalDrives(void);
EXPORT(sqInt) primitiveOpendir(void);
EXPORT(sqInt) primitivePathMax(void);
EXPORT(sqInt) primitivePlatToStPath(void);
EXPORT(sqInt) primitiveReaddir(void);
EXPORT(sqInt) primitiveRewinddir(void);
EXPORT(sqInt) primitiveStToPlatPath(void);
EXPORT(sqInt) primitiveSymlinkChangeOwner(void);
EXPORT(sqInt) primitiveVersionString(void);
static sqInt processDirectory(fapath *faPath);
static sqInt readLinkintomaxLength(char *cPathName, char *cLinkPtr, size_t maxLength);
EXPORT(sqInt) setInterpreter(struct VirtualMachine*anInterpreter);
static sqInt squeakPathtoPlatformmaxLen(sqInt pathOop, char *cPathString, sqInt maxLength);
static sqInt statArrayFortoArrayfromfileName(fapath *faPath, sqInt attributeArray, faStatStruct *statBufPointer, sqInt fileNameOop);
static sqInt stringFromCString(const char *aCString);
#if _WIN32
static sqInt winFileCreationTimeForto(WIN32_FILE_ATTRIBUTE_DATA *winAttrs, sqLong *creationDate);
#endif /* _WIN32 */
#if _WIN32
static sqInt winFileLastAccessTimeForto(WIN32_FILE_ATTRIBUTE_DATA *winAttrs, sqLong *accessDate);
#endif /* _WIN32 */
#if _WIN32
static sqInt winFileLastWriteTimeForto(WIN32_FILE_ATTRIBUTE_DATA *winAttrs, sqLong *writeDate);
#endif /* _WIN32 */
#if _WIN32
static sqInt winFileTimesForto(fapath *faPath, sqInt attributeArray);
#endif /* _WIN32 */


/*** Variables ***/
static int hasSecurityPlugin = 1;

#if !defined(SQUEAK_BUILTIN_PLUGIN)
static void * (*arrayValueOf)(sqInt oop);
static sqInt (*classArray)(void);
static sqInt (*classByteArray)(void);
static sqInt (*classString)(void);
static sqInt (*failed)(void);
static sqInt (*instantiateClassindexableSize)(sqInt classPointer, sqInt size);
static sqInt (*integerObjectOf)(sqInt value);
static void * (*ioLoadFunctionFrom)(char *functionName, char *moduleName);
static sqInt (*isKindOf)(sqInt oop, char *aString);
static sqInt (*isBytes)(sqInt oop);
static sqInt (*methodReturnValue)(sqInt oop);
static sqInt (*nilObject)(void);
static sqInt (*popthenPush)(sqInt nItems, sqInt oop);
static sqInt (*popRemappableOop)(void);
static sqInt (*positive32BitIntegerFor)(unsigned int integerValue);
static sqInt (*positive64BitIntegerFor)(usqLong integerValue);
static sqInt (*primitiveFail)(void);
static sqInt (*primitiveFailFor)(sqInt reasonCode);
static sqInt (*primitiveFailForOSError)(sqLong osError);
static sqInt (*primitiveFailureCode)(void);
static sqInt (*pushRemappableOop)(sqInt oop);
static sqInt (*signed64BitIntegerFor)(sqLong integerValue);
static sqInt (*stSizeOf)(sqInt oop);
static sqInt (*stackIntegerValue)(sqInt offset);
static sqInt (*stackObjectValue)(sqInt offset);
static sqInt (*stackValue)(sqInt offset);
static sqInt (*storePointerofObjectwithValue)(sqInt index, sqInt oop, sqInt valuePointer);
#else /* !defined(SQUEAK_BUILTIN_PLUGIN) */
extern void * arrayValueOf(sqInt oop);
extern sqInt classArray(void);
extern sqInt classByteArray(void);
extern sqInt classString(void);
extern sqInt failed(void);
extern sqInt instantiateClassindexableSize(sqInt classPointer, sqInt size);
extern sqInt integerObjectOf(sqInt value);
extern void * ioLoadFunctionFrom(char *functionName, char *moduleName);
extern sqInt isKindOf(sqInt oop, char *aString);
extern sqInt isBytes(sqInt oop);
extern sqInt methodReturnValue(sqInt oop);
extern sqInt nilObject(void);
extern sqInt popthenPush(sqInt nItems, sqInt oop);
extern sqInt popRemappableOop(void);
extern sqInt positive32BitIntegerFor(unsigned int integerValue);
extern sqInt positive64BitIntegerFor(usqLong integerValue);
extern sqInt primitiveFail(void);
extern sqInt primitiveFailFor(sqInt reasonCode);
extern sqInt primitiveFailForOSError(sqLong osError);
extern sqInt primitiveFailureCode(void);
extern sqInt pushRemappableOop(sqInt oop);
extern sqInt signed64BitIntegerFor(sqLong integerValue);
extern sqInt stSizeOf(sqInt oop);
extern sqInt stackIntegerValue(sqInt offset);
extern sqInt stackObjectValue(sqInt offset);
extern sqInt stackValue(sqInt offset);
extern sqInt storePointerofObjectwithValue(sqInt index, sqInt oop, sqInt valuePointer);
extern
#endif
struct VirtualMachine* interpreterProxy;
static const char *moduleName =
#ifdef SQUEAK_BUILTIN_PLUGIN
	"FileAttributesPlugin FileAttributesPlugin.oscog-AlistairGrant.38 (i)"
#else
	"FileAttributesPlugin FileAttributesPlugin.oscog-AlistairGrant.38 (e)"
#endif
;
static void * sCLPfn;
static void * sCOFfn;



/*	Answer an ExternalAddress object which represents aMachineAddress */

	/* FileAttributesPlugin>>#addressObjectFor: */
static sqInt
addressObjectFor(void *aMachineAddress)
{
    sqInt addressOop;
    unsigned char *addressOopArrayPointer;
    union {void *address; unsigned char bytes[sizeof(void *)];} addressUnion;
    sqInt idx;

	addressOop = instantiateClassindexableSize(classByteArray(), sizeof(void *));
	if (!(addressOop)) {
		return primitiveFailFor(PrimErrNoMemory);
	}
	addressOopArrayPointer = arrayValueOf(addressOop);
	addressUnion.address = aMachineAddress;
	idx = 0;
	while (idx < (sizeof(void *))) {
		addressOopArrayPointer[idx] = addressUnion.bytes[idx];
		idx += 1;
	}
	return addressOop;
}


/*	Answer non-zero if security permits the directory to be listed. */
/*	FIXME: This function has not been tested. -dtl */
/*	If the security plugin can be loaded, use it to check . 
	If not, assume it's ok */
/*	The hasSecurityPlugin flag is set to 1 by default */

	/* FileAttributesPlugin>>#canOpenDirectoryStreamFor:length: */
static sqInt
canOpenDirectoryStreamForlength(char *aPathCString, sqInt length)
{
	if (hasSecurityPlugin == 0) {
		return 1;
	}
	if (sCLPfn != 0) {
		return  ((int (*) (char *, int)) sCLPfn)(aPathCString, length);
	}
	else {

		/* Reset the flag so we do not try again next time */
		hasSecurityPlugin = 0;
		return 1;
	}
}


/*	Answer non-zero if security permits the a stat() call on the file path.
	Allow a
	stat() call only on files which we are permitted to open.
 */
/*	FIXME: This function has not been tested. -dtl */
/*	If the security plugin can be loaded, use it to check . 
	If not, assume it's ok */
/*	The hasSecurityPlugin flag is set to 1 by default */

	/* FileAttributesPlugin>>#canStatFilePath:length: */
static sqInt
canStatFilePathlength(char *aPathCString, sqInt length)
{
	if (hasSecurityPlugin == 0) {
		return 1;
	}
	if (sCOFfn != 0) {
		return  ((int (*) (char *, int, int)) sCOFfn)(aPathCString, length, 0);
	}
	else {

		/* Reset the flag so we do not try again next time */
		hasSecurityPlugin = 0;
		return 1;
	}
}


/*	Convert the supplied Windows SYSTEMTIME to Squeak time */

	/* FileAttributesPlugin>>#convertWinToSqueakTime: */
#if _WIN32
static sqLong
convertWinToSqueakTime(SYSTEMTIME st)
{
    sqLong dy;
    static sqLong nDaysPerMonth[14] = { 
		0,  0,  31,  59,  90, 120, 151,
		181, 212, 243, 273, 304, 334, 365 };
    sqLong secs;

	dy = (st.wYear) - 1901;

	/* base seconds */
	/* seconds of leap years */
	/* check if month > 2 and current year is a leap year */
	secs = ((((dy * 365) * 24) * 60) * 60) + ((((((usqInt) dy >> 2)) * 24) * 60) * 60);
	if (((st.wMonth) > 2)
	 && ((dy & 3) == 3)) {

		/* add one day */
		secs += (24 * 60) * 60;
	}

	/* add the hours, minutes, and seconds */
	secs += (nDaysPerMonth[st.wMonth] + st.wDay - 1) * 24 * 60 * 60;
	secs += st.wSecond + 60*(st.wMinute + 60*st.wHour);
	return secs;
}
#endif /* _WIN32 */


/*	Answer a file attribute array from pathNameOop. */

	/* FileAttributesPlugin>>#fileToAttributeArray:mask:array: */
static int
fileToAttributeArraymaskarray(fapath *faPath, sqInt attributeMask, sqInt *attributeArray)
{
    sqInt accessArray;
    sqInt combinedArray;
    sqInt fileNameOop;
    int getAccess;
    int getStats;
    sqInt statArray;
    faStatStruct statBuf;
    sqInt status;
    int useLstat;


	/* Determine which attributes to retrieve */
	accessArray = 0;
	fileNameOop = 0;
	statArray = 0;
	getStats = attributeMask & 1;
	getAccess = attributeMask & 2;
	if (!(getStats
		 || (getAccess))) {

		/* No information has been requested, which doesn't make sense */
		return -6 /* invalidArguments */;
	}
	if (getStats) {
		useLstat = attributeMask & 4;
		statArray = instantiateClassindexableSize(classArray(), 12);
		if (!(statArray)) {
			return primitiveFailFor(PrimErrNoMemory);
		}
		status = (useLstat
			? faLinkStat(faPath, (&statBuf), (&fileNameOop))
			: faStat(faPath, (&statBuf), (&fileNameOop)));
		if (status != 0) {
			return status;
		}
		status = statArrayFortoArrayfromfileName(faPath, statArray, (&statBuf), fileNameOop);
		if (status != 0) {
			return status;
		}
		attributeArray[0] = statArray;
	}
	if (getAccess) {
		accessArray = instantiateClassindexableSize(classArray(), 3);
		if (!(accessArray)) {
			return primitiveFailFor(PrimErrNoMemory);
		}
		faAccessAttributes(faPath, accessArray, 0);
		attributeArray[0] = accessArray;
	}
	if (getStats
	 && (getAccess)) {
		combinedArray = instantiateClassindexableSize(classArray(), 2);
		if (!(combinedArray)) {
			return primitiveFailFor(PrimErrNoMemory);
		}
		attributeArray[0] = combinedArray;
		storePointerofObjectwithValue(0, combinedArray, statArray);
		storePointerofObjectwithValue(1, combinedArray, accessArray);
	}
	return 0;
}


/*	Note: This is hardcoded so it can be run from Squeak.
	The module name is used for validating a module *after*
	it is loaded to check if it does really contain the module
	we're thinking it contains. This is important! */

	/* InterpreterPlugin>>#getModuleName */
EXPORT(const char*)
getModuleName(void)
{
	return moduleName;
}

	/* FileAttributesPlugin>>#initialiseModule */
EXPORT(sqInt)
initialiseModule(void)
{
	sCOFfn = ioLoadFunctionFrom("secCanOpenFileOfSizeWritable", "SecurityPlugin");
	sCLPfn = ioLoadFunctionFrom("secCanListPathOfSize", "SecurityPlugin");
	return 1;
}


/*	Copy the supplied path name string object to the supplied c string buffer */

	/* FileAttributesPlugin>>#pathOop:toBuffer:maxLen: */
static int
pathOoptoBuffermaxLen(sqInt pathNameOop, char *cPathName, sqInt maxLen)
{
    sqInt len;
    char *sPtr;

	len = stSizeOf(pathNameOop);
	if (len >= maxLen) {
		return -1 /* stringTooLong */;
	}
	sPtr = arrayValueOf(pathNameOop);
	if ((canStatFilePathlength(sPtr, len)) == 0) {
		/* begin cantStatPath */
		return ((sqInt) -3);
	}
	memcpy(cPathName, sPtr, len);
	cPathName[len] = 0;
	return 0;
}


/*	Answer the machine address contained in anExternalAddressOop. */

	/* FileAttributesPlugin>>#pointerFrom: */
static void *
pointerFrom(sqInt directoryPointerBytes)
{
    union {void *address; unsigned char bytes[sizeof(void *)];} addressUnion;
    sqInt idx;
    unsigned char *ptr;

	if (!((isKindOf(directoryPointerBytes, "ByteArray"))
		 && ((stSizeOf(directoryPointerBytes)) == (sizeof(void *))))) {
		return null;
	}
	ptr = arrayValueOf(directoryPointerBytes);
	idx = 0;
	while (idx < (sizeof(void *))) {
		addressUnion.bytes[idx] = ptr[idx];
		idx += 1;
	}
	return addressUnion.address;
}


/*	Populate attributeArray with the file times from statBufPointer */

	/* FileAttributesPlugin>>#posixFileTimesFrom:to: */
static sqInt
posixFileTimesFromto(faStatStruct *statBufPointer, sqInt attributeArray)
{
    sqLong attributeDate;

	
#  if defined(_WIN32)
#  else /* defined(_WIN32) */
	attributeDate = faConvertUnixToLongSqueakTime(statBufPointer->st_atime);
	storePointerofObjectwithValue(8, attributeArray, signed64BitIntegerFor(attributeDate));
	attributeDate = faConvertUnixToLongSqueakTime(statBufPointer->st_mtime);
	storePointerofObjectwithValue(9, attributeArray, signed64BitIntegerFor(attributeDate));
	attributeDate = faConvertUnixToLongSqueakTime(statBufPointer->st_ctime);
	storePointerofObjectwithValue(10, attributeArray, signed64BitIntegerFor(attributeDate));
	storePointerofObjectwithValue(11, attributeArray, nilObject());
#  endif /* defined(_WIN32) */
	return 0;
}


/*	Set the mode of the supplied file using chmod(). */

	/* FileAttributesPlugin>>#primitiveChangeMode */
EXPORT(sqInt)
primitiveChangeMode(void)
{
    char cString[PATH_MAX+1];
    sqInt fileNameOop;
    sqInt newMode;
    sqInt status;

	fileNameOop = stackObjectValue(1);
	newMode = stackIntegerValue(0);
	if ((failed())
	 || (!(isBytes(fileNameOop)))) {
		return primitiveFailFor(PrimErrBadArgument);
	}
	
#  if HAVE_CHMOD
	squeakPathtoPlatformmaxLen(fileNameOop, cString, PATH_MAX);
	if (failed()) {
		return primitiveFailForOSError(primitiveFailureCode());
	}
	status = chmod(cString, newMode);
	if (status != 0) {
		return primitiveFailForOSError(errno);
	}
	return methodReturnValue(nilObject());
#  endif /* HAVE_CHMOD */
	return primitiveFailForOSError(-13 /* unsupportedOperation */);
}


/*	Set the owner of the supplied file using chown(). */

	/* FileAttributesPlugin>>#primitiveChangeOwner */
EXPORT(sqInt)
primitiveChangeOwner(void)
{
    char cString[FA_PATH_MAX];
    sqInt fileNameOop;
    sqInt groupId;
    sqInt ownerId;
    sqInt status;

	fileNameOop = stackObjectValue(2);
	ownerId = stackIntegerValue(1);
	groupId = stackIntegerValue(0);
	if ((failed())
	 || (!(isBytes(fileNameOop)))) {
		return primitiveFailFor(PrimErrBadArgument);
	}
	
#  if HAVE_CHOWN
	squeakPathtoPlatformmaxLen(fileNameOop, cString, FA_PATH_MAX);
	if (failed()) {
		return primitiveFailForOSError(primitiveFailureCode());
	}
	status = chown(cString, ownerId, groupId);
	if (status != 0) {
		return primitiveFailForOSError(errno);
	}
	return methodReturnValue(nilObject());
#  endif /* HAVE_CHOWN */
	return primitiveFailForOSError(-13 /* unsupportedOperation */);
}


/*	Close the directory stream for dirPointerOop. Answer dirPointerOop on
	success. Raise PrimErrBadArgument if the parameter is not a ByteArray
	length size(void *).
	If closedir() returns an error raise PrimitiveOSError.
 */

	/* FileAttributesPlugin>>#primitiveClosedir */
EXPORT(sqInt)
primitiveClosedir(void)
{
    sqInt dirPointerOop;
    void * faPath;
    sqInt result;

	dirPointerOop = stackValue(0);
	faPath = pointerFrom(dirPointerOop);
	if (!(faPath)) {
		return primitiveFailFor(PrimErrBadArgument);
	}
	result = faCloseDirectory(faPath);
	if (!(result == 0)) {
		return primitiveFailForOSError(result);
	}
	free(faPath);
	popthenPush(2, dirPointerOop);
	return 0;
}


/*	Answer a single file attribute.
	primFileAttributes: aString attributeNumber: attributeNumber
	aString is the path to the file
	attributeNumber identifies which attribute to return:
	1 - 12: stat(): name, mode, ino, dev, nlink, uid, gid, size, accessDate,
	modifiedDate, changeDate, creationDate
	13 - 15: access(): R_OK, W_OK, X_OK
	16: isSymlink
	On error, answer a single element array containing the appropriate error
	code. 
 */

	/* FileAttributesPlugin>>#primitiveFileAttribute */
EXPORT(sqInt)
primitiveFileAttribute(void)
{
    sqInt attributeNumber;
    fapath *faPath;
    sqInt fileName;
    sqInt resultOop;

	fileName = stackObjectValue(1);
	attributeNumber = stackIntegerValue(0);
	if ((failed())
	 || ((!(((attributeNumber >= 1) && (attributeNumber <= 16))))
	 || (!(isBytes(fileName))))) {
		return primitiveFailFor(PrimErrBadArgument);
	}
	faPath = (fapath *) calloc(1, sizeof(fapath));
	if (faPath == null) {
		return primitiveFailForOSError(-10 /* cantAllocateMemory */);
	}
	faSetStPathOop(faPath, fileName);
	if (failed()) {
		return primitiveFailureCode();
	}
	resultOop = faFileAttribute(faPath, attributeNumber);
	if (failed()) {
		return primitiveFailureCode();
	}
	if (resultOop == 0) {

		/* It shouldn't be possible to get here */
		primitiveFailForOSError(-14 /* unexpectedError */);
	}
	else {
		popthenPush(3, resultOop);
	}
	return 0;
}


/*	Answer an array of file attributes.
	primFileAttributes: aString mask: attributeMask
	aString is the path to the file
	attributeMask indicates which attributes to retrieve:
	bit 0 - get stat() attributes
	bit 1 - get access() attributes
	bit 2 - use lstat() instead of stat()
	On error answer the appropriate error code (Integer) */

	/* FileAttributesPlugin>>#primitiveFileAttributes */
EXPORT(sqInt)
primitiveFileAttributes(void)
{
    sqInt attributeArray;
    sqInt attributeMask;
    fapath *faPath;
    sqInt fileName;
    int status;
    sqInt val;

	attributeArray = 0;
	val = 0;
	fileName = stackObjectValue(1);
	attributeMask = stackIntegerValue(0);
	if ((failed())
	 || (!(isBytes(fileName)))) {
		return primitiveFailFor(PrimErrBadArgument);
	}
	faPath = (fapath *) calloc(1, sizeof(fapath));
	if (faPath == null) {
		return primitiveFailForOSError(-10 /* cantAllocateMemory */);
	}
	faSetStPathOop(faPath, fileName);
	if (failed()) {
		return primitiveFailureCode();
	}
	status = fileToAttributeArraymaskarray(faPath, attributeMask, (&attributeArray));
	if (status != 0) {
		primitiveFailForOSError(status);
	}
	else {
		popthenPush(3, attributeArray);
	}
	return 0;
}


/*	Check for existence of a file with a call to access(). */

	/* FileAttributesPlugin>>#primitiveFileExists */
EXPORT(sqInt)
primitiveFileExists(void)
{
    fapath *faPath;
    sqInt fileNameOop;

	fileNameOop = stackObjectValue(0);
	if (!(isBytes(fileNameOop))) {
		return primitiveFailFor(PrimErrBadArgument);
	}
	faPath = (fapath *) calloc(1, sizeof(fapath));
	if (faPath == null) {
		return primitiveFailForOSError(-10 /* cantAllocateMemory */);
	}
	faSetStPathOop(faPath, fileNameOop);
	if (failed()) {
		return primitiveFailureCode();
	}
	return methodReturnValue(faExists(faPath));
}


/*	Answer an array of well known file masks */

	/* FileAttributesPlugin>>#primitiveFileMasks */
EXPORT(sqInt)
primitiveFileMasks(void)
{
    sqInt masks;

	masks = instantiateClassindexableSize(classArray(), 8);
	if (!(masks)) {
		return primitiveFailFor(PrimErrNoMemory);
	}
	storePointerofObjectwithValue(0, masks, (BytesPerWord == 8
		? positive64BitIntegerFor(S_IFMT)
		: positive32BitIntegerFor(S_IFMT)));
	
#  if !(defined(_WIN32))
	storePointerofObjectwithValue(1, masks, (BytesPerWord == 8
		? positive64BitIntegerFor(S_IFSOCK)
		: positive32BitIntegerFor(S_IFSOCK)));
	storePointerofObjectwithValue(2, masks, (BytesPerWord == 8
		? positive64BitIntegerFor(S_IFLNK)
		: positive32BitIntegerFor(S_IFLNK)));
#  endif /* !(defined(_WIN32)) */
	storePointerofObjectwithValue(3, masks, (BytesPerWord == 8
		? positive64BitIntegerFor(S_IFREG)
		: positive32BitIntegerFor(S_IFREG)));
	storePointerofObjectwithValue(4, masks, (BytesPerWord == 8
		? positive64BitIntegerFor(S_IFBLK)
		: positive32BitIntegerFor(S_IFBLK)));
	storePointerofObjectwithValue(5, masks, (BytesPerWord == 8
		? positive64BitIntegerFor(S_IFDIR)
		: positive32BitIntegerFor(S_IFDIR)));
	storePointerofObjectwithValue(6, masks, (BytesPerWord == 8
		? positive64BitIntegerFor(S_IFCHR)
		: positive32BitIntegerFor(S_IFCHR)));
	storePointerofObjectwithValue(7, masks, (BytesPerWord == 8
		? positive64BitIntegerFor(S_IFIFO)
		: positive32BitIntegerFor(S_IFIFO)));
	popthenPush(1, masks);
	return 0;
}


/*	Answer the logical drive mask on windows */

	/* FileAttributesPlugin>>#primitiveLogicalDrives */
EXPORT(sqInt)
primitiveLogicalDrives(void)
{
    unsigned int mask;

	
#  if defined(_WIN32)
	mask = GetLogicalDrives();
	if (mask != 0) {
		return popthenPush(1, positive32BitIntegerFor(mask));
	}
#  endif /* defined(_WIN32) */
	primitiveFail();
	return 0;
}


/*	self primOpendir: '/etc' */

	/* FileAttributesPlugin>>#primitiveOpendir */
EXPORT(sqInt)
primitiveOpendir(void)
{
    sqInt dirName;
    sqInt dirOop;
    fapath *faPath;
    sqInt resultOop;
    sqInt status;

	dirName = stackObjectValue(0);
	if (!(isBytes(dirName))) {
		return primitiveFailFor(PrimErrBadArgument);
	}
	faPath = (fapath *) calloc(1, sizeof(fapath));
	if (faPath == null) {
		return primitiveFailForOSError(-10 /* cantAllocateMemory */);
	}
	faSetStDirOop(faPath, dirName);
	if (!(canOpenDirectoryStreamForlength(faGetStPath(faPath), faGetStPathLen(faPath)))) {
		free(faPath);
		return primitiveFailForOSError(-9 /* cantOpenDir */);
	}
	status = faOpenDirectory(faPath);
	if (status == 1 /* noMoreData */) {
		return popthenPush(2, nilObject());
	}
	if (status < 0) {
		free(faPath);
		return primitiveFailForOSError(status);
	}
	resultOop = processDirectory(faPath);
	if (failed()) {
		free(faPath);
		return primitiveFailureCode();
	}
	
#if SPURVM
	dirOop = addressObjectFor(faPath);

#else /* SPURVM */
	pushRemappableOop(resultOop);
	dirOop = addressObjectFor(faPath);
	resultOop = popRemappableOop()
#endif /* SPURVM */
;
	return (storePointerofObjectwithValue(2, resultOop, dirOop),
		popthenPush(2, resultOop));
}


/*	Answer the value of PATH_MAX for the current VM */

	/* FileAttributesPlugin>>#primitivePathMax */
EXPORT(sqInt)
primitivePathMax(void)
{
	return popthenPush(1, integerObjectOf(FA_PATH_MAX));
}


/*	Convert the supplied file name (platform encoded) to the St UTF8 encoded
	byte array
 */

	/* FileAttributesPlugin>>#primitivePlatToStPath */
EXPORT(sqInt)
primitivePlatToStPath(void)
{
    unsigned char *byteArrayPtr;
    fapath *faPath;
    sqInt fileName;
    sqInt resultOop;

	fileName = stackObjectValue(0);
	if ((failed())
	 || (!(isBytes(fileName)))) {
		return primitiveFailFor(PrimErrBadArgument);
	}
	faPath = (fapath *) calloc(1, sizeof(fapath));
	if (faPath == null) {
		return primitiveFailForOSError(-10 /* cantAllocateMemory */);
	}
	faSetPlatPathOop(faPath, fileName);
	if (failed()) {
		return primitiveFailureCode();
	}
	resultOop = instantiateClassindexableSize(classByteArray(), faGetStPathLen(faPath));
	if (!(resultOop)) {
		return primitiveFailFor(PrimErrNoMemory);
	}
	byteArrayPtr = arrayValueOf(resultOop);
	memcpy(byteArrayPtr, faGetStPath(faPath), faGetStPathLen(faPath));
	return methodReturnValue(resultOop);
}


/*	Get the next entry in the directory stream. Answer the name of the entry,
	or nil for the end of the directory stream.
	Arguments:
	- directoryPointer (ByteArray) */

	/* FileAttributesPlugin>>#primitiveReaddir */
EXPORT(sqInt)
primitiveReaddir(void)
{
    sqInt dirPointerOop;
    fapath *faPath;
    sqInt resultArray;
    sqInt status;

	dirPointerOop = stackValue(0);
	faPath = pointerFrom(dirPointerOop);
	if (!(faPath)) {
		return primitiveFailFor(PrimErrBadArgument);
	}
	status = faReadDirectory(faPath);
	if (status == 1 /* noMoreData */) {
		return popthenPush(2, nilObject());
	}
	if (status < 0) {
		return primitiveFailForOSError(status);
	}
	resultArray = processDirectory(faPath);
	if (failed()) {
		return primitiveFailureCode();
	}
	popthenPush(2, resultArray);
	return 0;
}


/*	Set directoryStream to first entry. Answer dirPointerOop. */

	/* FileAttributesPlugin>>#primitiveRewinddir */
EXPORT(sqInt)
primitiveRewinddir(void)
{
    sqInt dirPointerOop;
    fapath *faPath;

	dirPointerOop = stackValue(0);
	faPath = pointerFrom(dirPointerOop);
	if (!(faPath)) {
		return primitiveFailFor(PrimErrBadArgument);
	}
	return primitiveFailForOSError(-14 /* unexpectedError */);
}


/*	Convert the supplied file name (UTF8 encoded) to the platform encoded byte
	array 
 */

	/* FileAttributesPlugin>>#primitiveStToPlatPath */
EXPORT(sqInt)
primitiveStToPlatPath(void)
{
    unsigned char *byteArrayPtr;
    fapath *faPath;
    sqInt fileName;
    sqInt resultOop;

	fileName = stackObjectValue(0);
	if ((failed())
	 || (!(isBytes(fileName)))) {
		return primitiveFailFor(PrimErrBadArgument);
	}
	faPath = (fapath *) calloc(1, sizeof(fapath));
	if (faPath == null) {
		return primitiveFailForOSError(-10 /* cantAllocateMemory */);
	}
	faSetStPathOop(faPath, fileName);
	if (failed()) {
		return primitiveFailureCode();
	}
	resultOop = instantiateClassindexableSize(classByteArray(), faGetPlatPathByteCount(faPath));
	if (!(resultOop)) {
		return primitiveFailFor(PrimErrNoMemory);
	}
	byteArrayPtr = arrayValueOf(resultOop);
	memcpy(byteArrayPtr, faGetPlatPath(faPath), faGetPlatPathByteCount(faPath));
	return methodReturnValue(resultOop);
}


/*	Set the owner of the supplied file using chown(). */

	/* FileAttributesPlugin>>#primitiveSymlinkChangeOwner */
EXPORT(sqInt)
primitiveSymlinkChangeOwner(void)
{
    char cString[PATH_MAX+1];
    sqInt fileNameOop;
    sqInt groupId;
    sqInt ownerId;
    sqInt status;

	fileNameOop = stackObjectValue(2);
	ownerId = stackIntegerValue(1);
	groupId = stackIntegerValue(0);
	if ((failed())
	 || (!(isBytes(fileNameOop)))) {
		return primitiveFailFor(PrimErrBadArgument);
	}
	squeakPathtoPlatformmaxLen(fileNameOop, cString, PATH_MAX);
	if (failed()) {
		return primitiveFailForOSError(primitiveFailureCode());
	}
	
#  if HAVE_CHOWN
	status = lchown(cString, ownerId, groupId);
	if (status != 0) {
		return primitiveFailForOSError(errno);
	}
	return methodReturnValue(nilObject());
#  endif /* HAVE_CHOWN */
	return primitiveFailForOSError(-13 /* unsupportedOperation */);
}


/*	Answer a string containing the version string for this plugin. */

	/* FileAttributesPlugin>>#primitiveVersionString */
EXPORT(sqInt)
primitiveVersionString(void)
{
	popthenPush(1, stringFromCString("2.0.0"));
	return 0;
}

	/* FileAttributesPlugin>>#processDirectory: */
static sqInt
processDirectory(fapath *faPath)
{
    sqInt attributeArray;
    sqInt entryName;
    sqInt resultArray;
    sqInt status;
    sqInt val;

	attributeArray = 0;
	entryName = 0;
	val = 0;
	status = faCharToByteArray(faGetStFile(faPath), (&entryName));
	if (status != 0) {
		return primitiveFailForOSError(status);
	}

	/* If the stat() fails, still return the filename, just no attributes */
	status = fileToAttributeArraymaskarray(faPath, 1, (&attributeArray));
	if (status != 0) {
		attributeArray = nilObject();
	}
	
#if SPURVM
	resultArray = instantiateClassindexableSize(classArray(), 3);

#else /* SPURVM */
	pushRemappableOop(entryName);
	pushRemappableOop(attributeArray);
	resultArray = instantiateClassindexableSize(classArray(), 3);
	attributeArray = popRemappableOop();
	entryName = popRemappableOop()
#endif /* SPURVM */
;
	if (!(resultArray)) {
		return primitiveFailFor(PrimErrNoMemory);
	}
	storePointerofObjectwithValue(0, resultArray, entryName);
	storePointerofObjectwithValue(1, resultArray, attributeArray);
	return resultArray;
}


/*	Get the target filename of the supplied symbolic link. */

	/* FileAttributesPlugin>>#readLink:into:maxLength: */
static sqInt
readLinkintomaxLength(char *cPathName, char *cLinkPtr, size_t maxLength)
{
    sqInt len;


	/* len must be signed so that -1 can be communicated as an error. */
	len = 
#  if defined(_WIN32)
		-1
#  else /* defined(_WIN32) */
		readlink(cPathName, cLinkPtr, maxLength)
#  endif /* defined(_WIN32) */
		;
	if (len < 0) {
		
#    if defined(INDEBUG)
		fprintf(stderr, "FileAttributesPlugin: unable to readlink(): %d, errno=%d\n", len, errno);
#    endif /* defined(INDEBUG) */
		/* begin cantReadlink */
		return -8;
	}
	cLinkPtr[len] = 0;
	return len;
}


/*	Note: This is coded so that it can be run in Squeak. */

	/* InterpreterPlugin>>#setInterpreter: */
EXPORT(sqInt)
setInterpreter(struct VirtualMachine*anInterpreter)
{
    sqInt ok;

	interpreterProxy = anInterpreter;
	ok = ((interpreterProxy->majorVersion()) == (VM_PROXY_MAJOR))
	 && ((interpreterProxy->minorVersion()) >= (VM_PROXY_MINOR));
	if (ok) {
		
#if !defined(SQUEAK_BUILTIN_PLUGIN)
		arrayValueOf = interpreterProxy->arrayValueOf;
		classArray = interpreterProxy->classArray;
		classByteArray = interpreterProxy->classByteArray;
		classString = interpreterProxy->classString;
		failed = interpreterProxy->failed;
		instantiateClassindexableSize = interpreterProxy->instantiateClassindexableSize;
		integerObjectOf = interpreterProxy->integerObjectOf;
		ioLoadFunctionFrom = interpreterProxy->ioLoadFunctionFrom;
		isKindOf = interpreterProxy->isKindOf;
		isBytes = interpreterProxy->isBytes;
		methodReturnValue = interpreterProxy->methodReturnValue;
		nilObject = interpreterProxy->nilObject;
		popthenPush = interpreterProxy->popthenPush;
		popRemappableOop = interpreterProxy->popRemappableOop;
		positive32BitIntegerFor = interpreterProxy->positive32BitIntegerFor;
		positive64BitIntegerFor = interpreterProxy->positive64BitIntegerFor;
		primitiveFail = interpreterProxy->primitiveFail;
		primitiveFailFor = interpreterProxy->primitiveFailFor;
		primitiveFailForOSError = interpreterProxy->primitiveFailForOSError;
		primitiveFailureCode = interpreterProxy->primitiveFailureCode;
		pushRemappableOop = interpreterProxy->pushRemappableOop;
		signed64BitIntegerFor = interpreterProxy->signed64BitIntegerFor;
		stSizeOf = interpreterProxy->stSizeOf;
		stackIntegerValue = interpreterProxy->stackIntegerValue;
		stackObjectValue = interpreterProxy->stackObjectValue;
		stackValue = interpreterProxy->stackValue;
		storePointerofObjectwithValue = interpreterProxy->storePointerofObjectwithValue;
#endif /* !defined(SQUEAK_BUILTIN_PLUGIN) */
	}
	return ok;
}


/*	Convert the supplied path string oop to a unix c path string.
	Parameter checking is done in the main primitive, so pathOop is assumed to
	be valid.
	pathOop is supplied as a precomposed UTF8 string.
	cPathString must be encoded using the host OS conventions, e.g. decomposed
	UTF8 on MacOS.
	Signal primitive failure on error.
 */

	/* FileAttributesPlugin>>#squeakPath:toPlatform:maxLen: */
static sqInt
squeakPathtoPlatformmaxLen(sqInt pathOop, char *cPathString, sqInt maxLength)
{
    int status;
    char uxName[FA_PATH_MAX];

	if (maxLength >= (FA_PATH_MAX)) {
		return primitiveFailForOSError(-6 /* invalidArguments */);
	}
	
#  if _WIN32
	status = pathOoptoBuffermaxLen(pathOop, cPathString, maxLength);
	if (status != 0) {
		return primitiveFailForOSError(status);
	}
#  else /* _WIN32 */
	status = pathOoptoBuffermaxLen(pathOop, uxName, PATH_MAX);
	if (status != 0) {
		return primitiveFailForOSError(status);
	}
	status = sq2uxPath(uxName, strlen(uxName), cPathString, maxLength, 1);
	if (status == 0) {
		return primitiveFailForOSError(-6 /* invalidArguments */);
	}
#  endif /* _WIN32 */
	return 0;
}


/*	Answer a file entry array from the supplied statBufPointer */

	/* FileAttributesPlugin>>#statArrayFor:toArray:from:fileName: */
static sqInt
statArrayFortoArrayfromfileName(fapath *faPath, sqInt attributeArray, faStatStruct *statBufPointer, sqInt fileNameOop)
{
    sqInt sizeIfFile;
    sqInt status;

	sizeIfFile = ((S_ISDIR(statBufPointer->st_mode)) == 0
		? statBufPointer->st_size
		: 0);
	storePointerofObjectwithValue(0, attributeArray, fileNameOop);
	storePointerofObjectwithValue(1, attributeArray, positive64BitIntegerFor(statBufPointer->st_mode));
	storePointerofObjectwithValue(2, attributeArray, positive64BitIntegerFor(statBufPointer->st_ino));
	storePointerofObjectwithValue(3, attributeArray, positive64BitIntegerFor(statBufPointer->st_dev));
	storePointerofObjectwithValue(4, attributeArray, positive64BitIntegerFor(statBufPointer->st_nlink));
	storePointerofObjectwithValue(5, attributeArray, positive64BitIntegerFor(statBufPointer->st_uid));
	storePointerofObjectwithValue(6, attributeArray, positive64BitIntegerFor(statBufPointer->st_gid));
	storePointerofObjectwithValue(7, attributeArray, positive64BitIntegerFor(sizeIfFile));
	
#  if defined(_WIN32)
	status = winFileTimesForto(faPath, attributeArray);
#  else /* defined(_WIN32) */
	status = posixFileTimesFromto(statBufPointer, attributeArray);
#  endif /* defined(_WIN32) */
	return status;
}


/*	Answer a new String copied from a null-terminated C string.
	Caution: This may invoke the garbage collector. */

	/* FileAttributesPlugin>>#stringFromCString: */
static sqInt
stringFromCString(const char *aCString)
{
    sqInt len;
    sqInt newString;

	len = strlen(aCString);
	newString = instantiateClassindexableSize(classString(), len);
	if (!(newString)) {
		return primitiveFailFor(PrimErrNoMemory);
	}
	strncpy(arrayValueOf(newString), aCString, len);
	return newString;
}


/*	Set the file creation time from the supplied attributes. */

	/* FileAttributesPlugin>>#winFileCreationTimeFor:to: */
#if _WIN32
static sqInt
winFileCreationTimeForto(WIN32_FILE_ATTRIBUTE_DATA *winAttrs, sqLong *creationDate)
{
    FILETIME fileTime;
    SYSTEMTIME sysTime;

	if ((FileTimeToLocalFileTime(&winAttrs->ftCreationTime, &fileTime)) == 0) {
		/* begin timeConversionFailed */
		return -5;
	}
	if ((FileTimeToSystemTime(&fileTime, &sysTime)) == 0) {
		/* begin timeConversionFailed */
		return -5;
	}
	*creationDate = convertWinToSqueakTime(sysTime);
	return 0;
}
#endif /* _WIN32 */


/*	Set the file creation time from the supplied attributes. */

	/* FileAttributesPlugin>>#winFileLastAccessTimeFor:to: */
#if _WIN32
static sqInt
winFileLastAccessTimeForto(WIN32_FILE_ATTRIBUTE_DATA *winAttrs, sqLong *accessDate)
{
    FILETIME fileTime;
    SYSTEMTIME sysTime;

	if ((FileTimeToLocalFileTime(&winAttrs->ftLastAccessTime, &fileTime)) == 0) {
		/* begin timeConversionFailed */
		return -5;
	}
	if ((FileTimeToSystemTime(&fileTime, &sysTime)) == 0) {
		/* begin timeConversionFailed */
		return -5;
	}
	*accessDate = convertWinToSqueakTime(sysTime);
	return 0;
}
#endif /* _WIN32 */


/*	Set the file write time from the supplied attributes. */

	/* FileAttributesPlugin>>#winFileLastWriteTimeFor:to: */
#if _WIN32
static sqInt
winFileLastWriteTimeForto(WIN32_FILE_ATTRIBUTE_DATA *winAttrs, sqLong *writeDate)
{
    FILETIME fileTime;
    SYSTEMTIME sysTime;

	if ((FileTimeToLocalFileTime(&winAttrs->ftLastWriteTime, &fileTime)) == 0) {
		/* begin timeConversionFailed */
		return -5;
	}
	if ((FileTimeToSystemTime(&fileTime, &sysTime)) == 0) {
		/* begin timeConversionFailed */
		return -5;
	}
	*writeDate = convertWinToSqueakTime(sysTime);
	return 0;
}
#endif /* _WIN32 */

	/* FileAttributesPlugin>>#winFileTimesFor:to: */
#if _WIN32
static sqInt
winFileTimesForto(fapath *faPath, sqInt attributeArray)
{
    sqLong attributeDate;
    sqInt status;
    WIN32_FILE_ATTRIBUTE_DATA winAttrs;


	/* Get the file attributes */
	attributeDate = 0;
	status = GetFileAttributesExW(faGetPlatPath2(faPath), GetFileExInfoStandard, &winAttrs);
	if (status == 0) {
		/* begin getAttributesFailed */
		return -4;
	}
	status = winFileLastAccessTimeForto((&winAttrs), (&attributeDate));
	if (!(status == 0)) {
		return status;
	}
	storePointerofObjectwithValue(8, attributeArray, signed64BitIntegerFor(attributeDate));
	status = winFileLastWriteTimeForto((&winAttrs), (&attributeDate));
	if (!(status == 0)) {
		return status;
	}
	storePointerofObjectwithValue(9, attributeArray, signed64BitIntegerFor(attributeDate));
	storePointerofObjectwithValue(10, attributeArray, nilObject());
	status = winFileCreationTimeForto((&winAttrs), (&attributeDate));
	if (!(status == 0)) {
		return status;
	}
	storePointerofObjectwithValue(11, attributeArray, signed64BitIntegerFor(attributeDate));
	return 0;
}
#endif /* _WIN32 */


#ifdef SQUEAK_BUILTIN_PLUGIN

static char _m[] = "FileAttributesPlugin";
void* FileAttributesPlugin_exports[][3] = {
	{(void*)_m, "getModuleName", (void*)getModuleName},
	{(void*)_m, "initialiseModule", (void*)initialiseModule},
	{(void*)_m, "primitiveChangeMode\000\001", (void*)primitiveChangeMode},
	{(void*)_m, "primitiveChangeOwner\000\001", (void*)primitiveChangeOwner},
	{(void*)_m, "primitiveClosedir\000\001", (void*)primitiveClosedir},
	{(void*)_m, "primitiveFileAttribute\000\000", (void*)primitiveFileAttribute},
	{(void*)_m, "primitiveFileAttributes\000\001", (void*)primitiveFileAttributes},
	{(void*)_m, "primitiveFileExists\000\000", (void*)primitiveFileExists},
	{(void*)_m, "primitiveFileMasks\000\377", (void*)primitiveFileMasks},
	{(void*)_m, "primitiveLogicalDrives\000\377", (void*)primitiveLogicalDrives},
	{(void*)_m, "primitiveOpendir\000\000", (void*)primitiveOpendir},
	{(void*)_m, "primitivePathMax\000\377", (void*)primitivePathMax},
	{(void*)_m, "primitivePlatToStPath\000\000", (void*)primitivePlatToStPath},
	{(void*)_m, "primitiveReaddir\000\002", (void*)primitiveReaddir},
	{(void*)_m, "primitiveRewinddir\000\001", (void*)primitiveRewinddir},
	{(void*)_m, "primitiveStToPlatPath\000\000", (void*)primitiveStToPlatPath},
	{(void*)_m, "primitiveSymlinkChangeOwner\000\001", (void*)primitiveSymlinkChangeOwner},
	{(void*)_m, "primitiveVersionString\000\377", (void*)primitiveVersionString},
	{(void*)_m, "setInterpreter", (void*)setInterpreter},
	{NULL, NULL, NULL}
};

#else /* ifdef SQ_BUILTIN_PLUGIN */

signed char primitiveChangeModeAccessorDepth = 1;
signed char primitiveChangeOwnerAccessorDepth = 1;
signed char primitiveClosedirAccessorDepth = 1;
signed char primitiveFileAttributeAccessorDepth = 0;
signed char primitiveFileAttributesAccessorDepth = 1;
signed char primitiveFileExistsAccessorDepth = 0;
signed char primitiveOpendirAccessorDepth = 0;
signed char primitivePlatToStPathAccessorDepth = 0;
signed char primitiveReaddirAccessorDepth = 2;
signed char primitiveRewinddirAccessorDepth = 1;
signed char primitiveStToPlatPathAccessorDepth = 0;
signed char primitiveSymlinkChangeOwnerAccessorDepth = 1;

#endif /* ifdef SQ_BUILTIN_PLUGIN */

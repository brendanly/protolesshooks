﻿#include <stdio.h>
#include "protolesshooks.h"

//..............................................................................

// target function

int foo()
{
	printf("foo\n");
	return 123;
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

// enter & leave hooks

void
fooHookEnter(
	void* targetFunc,
	void* callbackParam,
	size_t frameBase
	)
{
	printf(
		"fooHookEnter(func: %p, param: %p, frame: %p)\n",
		targetFunc,
		callbackParam,
		(void*)frameBase
		);
}

void
fooHookLeave(
	void* targetFunc,
	void* callbackParam,
	size_t frameBase,
	size_t returnValue
	)
{
	printf(
		"fooHookLeave(func: %p, param: %p, frame: %p, retval: %zd/0x%zx)\n",
		targetFunc,
		callbackParam,
		(void*)frameBase,
		returnValue,
		returnValue
		);
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

int
main()
{
	typedef int FooFunc();

	plh::Hook* fooHook = plh::allocateHook((void*)foo, (void*)0xabcdef, fooHookEnter, fooHookLeave);
	((FooFunc*)fooHook)();
	plh::freeHook(fooHook);
	return 0;
}

//..............................................................................

/****************************************************************************************/
/*  stack.h                                                                             */
/*                                                                                      */
/*  Author:       Jim Mischel, Ken Baird, Jeff Lomax                                    */
/*  Description:  Genesis world editor header file                                      */
/*                                                                                      */
/*  The contents of this file are subject to the Genesis3D Public License               */
/*  Version 1.01 (the "License"); you may not use this file except in                   */
/*  compliance with the License. You may obtain a copy of the License at                */
/*  http://www.genesis3d.com                                                            */
/*                                                                                      */
/*  Software distributed under the License is distributed on an "AS IS"                 */
/*  basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See                */
/*  the License for the specific language governing rights and limitations              */
/*  under the License.                                                                  */
/*                                                                                      */
/*  The Original Code is Genesis3D, released March 25, 1999.                            */
/*  Copyright (C) 1996-1999 Eclipse Entertainment, L.L.C. All Rights Reserved           */
/*                                                                                      */
/****************************************************************************************/
#ifndef STACK_H
#define STACK_H

#include "list.h"

#ifdef __cplusplus
	extern "C" {
#endif

typedef struct tag_Stack Stack;
typedef List_DestroyCallback Stack_DestroyCallback;

// Create a stack that is initially empty.
// On success, returns a pointer to the stack.
// Returns NULL on error.
Stack *Stack_Create (void);

// Destroy a stack.
void Stack_Destroy (Stack **ppStack, Stack_DestroyCallback DestroyCallback);

// Push an item onto the stack.
//Returns GE_TRUE if the item was pushed successfully.
geBoolean Stack_Push (Stack *pStack, void *Data);

// Pop an item from the stack.
// It is an error to try to
// pop when there's nothing on the stack.
void *Stack_Pop (Stack *pStack);

// returns GE_TRUE if the stack is empty (has no items)
geBoolean Stack_IsEmpty (const Stack *pStack);


#ifdef __cplusplus
	}
#endif



#endif

/*
 * Copyright (c) 2007 Hypertriton, Inc. <http://www.hypertriton.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <agar/core.h>
#include <agar/gui.h>

#include <stdarg.h>
#include <string.h>

#include "cadtools.h"

const AG_ObjectOps camProgramOps = {
	"CAM_Program",
	sizeof(CAM_Program),
	{ 0,0 },
	CAM_ProgramInit,
	NULL,			/* reinit */
	CAM_ProgramDestroy,
	CAM_ProgramLoad,
	CAM_ProgramSave,
	CAM_ProgramEdit
};

CAM_Program *
CAM_ProgramNew(void *parent, const char *name)
{
	CAM_Program *prog;

	prog = Malloc(sizeof(CAM_Program), M_OBJECT);
	CAM_ProgramInit(prog, name);
	AG_ObjectAttach(parent, prog);
	return (prog);
}

void
CAM_ProgramInit(void *obj, const char *name)
{
	CAM_Program *prog = obj;

	AG_ObjectInit(prog, name, &camProgramOps);
	prog->flags = 0;
}

void
CAM_ProgramDestroy(void *obj)
{
}

int
CAM_ProgramLoad(void *obj, AG_Netbuf *buf)
{
	CAM_Program *prog = obj;

	if (AG_ReadObjectVersion(buf, prog, NULL) != 0) {
		return (-1);
	}
	prog->flags = (Uint)AG_ReadUint32(buf);
	return (0);
}

int
CAM_ProgramSave(void *obj, AG_Netbuf *buf)
{
	CAM_Program *prog = obj;

	AG_WriteObjectVersion(buf, prog);
	AG_WriteUint32(buf, (Uint32)prog->flags);
	return (0);
}

void *
CAM_ProgramEdit(void *obj)
{
	CAM_Program *prog = obj;
	AG_Window *win;
	AG_Console *cons;

	win = AG_WindowNew(0);
	AG_WindowSetCaption(win, _("Program: %s"), AGOBJECT(prog)->name);

	/* XXX use AG_Textview */
	cons = AG_ConsoleNew(win, AG_CONSOLE_EXPAND);

	return (win);
}

/*	Public domain	*/

#ifndef _CADTOOLS_PROGRAM_H_
#define _CADTOOLS_PROGRAM_H_

#include "begin_code.h"

enum cam_program_type {
	CAM_MILLING3,		/* Mill: Linear X/Y/Z */
	CAM_MILLING4,		/* Mill: Linear X/Y/Z, rotary A */
	CAM_MILLING5,		/* Mill: Linear X/Y/Z, rotary A/B */
	CAM_MILLING6,		/* Mill: Linear X/Y/Z, rotary A/B/C */
	CAM_LATHE2,		/* Lathe: Linear X/Z */
	CAM_LASER3,		/* Laser: Linear X/Y, with Z=current */
	CAM_PICKPLACE3,		/* Pickplace: Linear X/Y, with Z=pickup */
};

typedef struct cam_program {
	struct ag_object obj;
	enum cam_program_type type;
	Uint flags;
} CAM_Program;

__BEGIN_DECLS
extern const AG_ObjectOps camProgramOps;

CAM_Program	*CAM_ProgramNew(void *, const char *);
void	 	 CAM_ProgramInit(void *, const char *);
void		 CAM_ProgramReinit(void *);
void		*CAM_ProgramEdit(void *);
int		 CAM_ProgramLoad(void *, AG_DataSource *);
int		 CAM_ProgramSave(void *, AG_DataSource *);
__END_DECLS

#include "close_code.h"
#endif	/* _CADTOOLS_PROGRAM_H_ */

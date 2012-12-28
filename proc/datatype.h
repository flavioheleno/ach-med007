#ifndef __DATATYPE_H__
#define __DATATYPE_H__

#include <stdint.h>

//STATE MACHINE STAGES
typedef enum {
	FETCH,
	DECODE,
	EXECUTE,
	RESET,
	HALT
} enStage;


#endif

#ifndef _DGUI_H_
#define _DGUI_H_

#define _DGUI_INCLUDED_
#define DGUI_INCLUDED

#include "dincludes.h"
namespace dgui_ns{
	#include "ddef.h"
	#include "dds.h"
	#include "dmath.h"
	#include "dstring.h"
	#include "devent.h"
	#include "dweb.h"
	#include "dcon.h"
	#include "dbasic.h"
	#include "dscript.h" 
	#include "duser.h"
	#include "dmenu.h"
	#include "dimg.h"
	#include "dmusic.h" 
	#include "deffect.h"
	#include "dcontrol.h"
	#include "dobj.h"
	#include "dver.h" 
}

#ifdef _DGUI_NOUSINGNS_
#define _DGUI_NOUSINGNAMESPACE_
#endif
#ifdef DGUI_NOUSINGNAMESPACE
#define _DGUI_NOUSINGNAMESPACE_
#endif
#ifdef DGUI_NOUSINGNS
#define _DGUI_NOUSINGNAMESPACE_
#endif

#ifndef _DGUI_NOUSINGNAMESPACE_
using namespace dgui_ns;
#endif

#endif

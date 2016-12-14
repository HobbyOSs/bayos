#if !defined(_BAYOS_H_INCLUDED_)
#define _BAYOS_H_INCLUDED_

#define BAYOS_VERSION "BayOS $LastChangedDate: 2007-03-02 01:29:19 +0900 (Fri, 02 Mar 2007) $"
#define BAYOS_COPYING "Copyright (C) 2004-2006, bayside."

/* ヘッダファイル一覧 */

#include "apilib.h"
#include "system/arraylist.h"
#include "system/message.h"
#include "system/descriptor.h"
#include "system/ihandler.h"
#include "driver/pic.h"
#include "driver/dtk5s.h"
#include "driver/file.h"
#include "driver/pci.h"
#include "driver/fat12.h"
#include "driver/ide.h"
#include "driver/iso9660.h"
#include "system/memory.h"
#include "system/scheduler.h"
#include "system/sheet.h"
#include "system/console.h"
#include "system/jpegls.h"
#include "driver/beep.h"
#include "driver/clock.h"
#include "driver/keyboard.h"
#include "driver/mouse.h"
#include "driver/timer.h"
#include <string.h>

using namespace system;
using namespace driver;

#endif

/**
    COPYRIGHT AND PERMISSION NOTICE

    Copyright (c) 2006 bayside

    All rights reserved.

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to
    deal in the Software without restriction, including without limitation the
    rights to use, copy, modify, merge, publish, distribute, and/or sell copies
    of the Software, and to permit persons to whom the Software is furnished to
    do so, provided that the above copyright notice(s) and this permission
    notice appear in all copies of the Software and that both the above
    copyright notice(s) and this permission notice appear in supporting
    documentation.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
    IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS INCLUDED IN THIS NOTICE BE
    LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR
    ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
    IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
    OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

    Except as contained in this notice, the name of a copyright holder shall not
    be used in advertising or otherwise to promote the sale, use or other
    dealings in this Software without prior written authorization of the
    copyright holder.
*/

#if !defined(_BAYGUI_H_INCLUDED_)
#define _BAYGUI_H_INCLUDED_

enum
{
    baygui_lang_Object,
    baygui_lang_Integer,
    baygui_lang_Math,
    baygui_lang_String,
    baygui_util_ArrayList,
    baygui_awt_AWTEvent,
    baygui_awt_Button,
    baygui_awt_Checkbox,
    baygui_awt_CheckboxGroup,
    baygui_awt_Component,
    baygui_awt_Container,
    baygui_awt_Frame,
    baygui_awt_Graphics,
    baygui_awt_Label,
    baygui_awt_Listbox,
    baygui_awt_Scrollbar,
    baygui_awt_TextArea,
    baygui_awt_TextField,
    baygui_awt_Rectangle,
    baygui_awt_event_ActionEvent,
    baygui_awt_event_ActionListener,
    baygui_awt_event_KeyEvent,
    baygui_awt_event_KeyListener,
    baygui_awt_event_MouseEvent,
    baygui_awt_event_MouseListener,
    baygui_awt_event_MouseMotionListener,
};

#define BAYOS    1
#define HARIBOTE 1

#ifdef HARIBOTE
#ifndef NULL
#define NULL 0
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "apilib.h"
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

#include "baygui/lang/Object.h"
#include "baygui/util/ArrayList.h"
#include "baygui/lang/String.h"
#include "baygui/lang/Integer.h"
#include "baygui/lang/Math.h"
#include "baygui/awt/AWTEvent.h"
#include "baygui/awt/event/KeyEvent.h"
#include "baygui/awt/event/KeyListener.h"
#include "baygui/awt/event/MouseEvent.h"
#include "baygui/awt/event/MouseListener.h"
#include "baygui/awt/event/MouseMotionListener.h"
#include "baygui/awt/Rectangle.h"
#include "baygui/awt/FontMetrics.h"
#include "baygui/awt/Color.h"
#include "baygui/awt/Graphics.h"
#include "baygui/awt/Component.h"
#include "baygui/awt/Button.h"
#include "baygui/awt/Checkbox.h"
#include "baygui/awt/CheckboxGroup.h"
#include "baygui/awt/Label.h"
#include "baygui/awt/Listbox.h"
#include "baygui/awt/Scrollbar.h"
#include "baygui/awt/TextComponent.h"
#include "baygui/awt/TextField.h"
#include "baygui/awt/Container.h"
#include "baygui/awt/Frame.h"
#include "baygui/awt/Application.h"

//using namespace baygui::lang;
//using namespace baygui::util;
//using namespace baygui::awt;
//using namespace baygui::awt::event;

#endif

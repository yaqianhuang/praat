#ifndef _GuiP_h_
#define _GuiP_h_
/* GuiP.h
 *
 * Copyright (C) 1993-2004 Paul Boersma
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*
 * pb 2004/11/22
 */

#include "Gui.h"

/*
 * In GUI implementations, we order everything by ease of programming: Unix, Windows, Macintosh.
 */
#if defined (UNIX)
	#define uni 1
	#define win 0
	#define mac 0
#endif
#if defined (_WIN32)
	#define uni 0
	#define win 1
	#define mac 0
#endif
#if defined (macintosh)
	#define uni 0
	#define win 0
	#define mac 1
#endif

#if mac
	#include "macport_on.h"
	#include <Quickdraw.h>
	#include <Appearance.h>
	#include <AppleEvents.h>
	#include <Controls.h>
	#include <ControlDefinitions.h>
	#include <MacWindows.h>
	#include <TextEdit.h>
	#include <MacTextEditor.h>
	#include <Lists.h>
	#include <Menus.h>
	#include <Fonts.h>
	#include <Dialogs.h>
	#ifndef __MACH__
		#include <Balloons.h>
	#endif
	#include <Scrap.h>
	#include <ToolUtils.h>
	#include <Devices.h>
	#if ! TARGET_API_MAC_CARBON
		#include <DiskInit.h>
	#endif
	#include <Gestalt.h>
	#include <Sound.h>   /* SysBeep */
	#ifdef __MACH__
		#include <AEMach.h>
		/*extern OSErr AEProcessAppleEvent (EventRecord *event);
		extern OSErr AEInteractWithUser (SInt32 timeOutInTicks, void *nmReqPtr, void *idleProc);*/
	#endif
	#include "macport_off.h"
#elif win
	#include <windows.h>
	#include <commctrl.h>
#endif
#if mac
	#if TARGET_API_MAC_CARBON
		#define carbon 1
		/* The following line is an optimization. The compiler will throw away most non-appearance code. */
		#define haveAppearance 1
	#else
		#define carbon 0
		#define haveAppearance MOTIF_EMULATOR_HAS_APPEARANCE
		#define GetQDGlobalsScreenBits(bits)  (*(bits) = qd.screenBits, bits)
		#define GetPortBounds(port,dum)  (& (port) -> portRect)
		#define GetRegionBounds(rgn,rect)  (*(rect) = (**(rgn)). rgnBBox, rect)
		#define InvalWindowRect(win,rect)  InvalRect (rect)
		#define ValidWindowRect(win,rect)  ValidRect (rect)
		#define IsControlVisible(control)  ((**(control)). contrlVis)
		#define EnableMenuItem  EnableItem
		#define DisableMenuItem  DisableItem
		#define SetListSelectionFlags(list,flags)  (**(list)). selFlags = flags
		#define SetControlPopupMenuHandle(control,menu)  (**(control)). dataHandle = menu;
	#endif
#endif

#if win || mac

/*#define MEMBER(widget,klas)  (widget -> widgetClass == xm##klas##WidgetClass)
#define MEMBER2(widget,klas1,klas2)  (MEMBER (widget, klas1) || MEMBER (widget, klas2))
#define MEMBER3(widget,klas1,klas2,klas3)  (MEMBER2 (widget, klas1, klas2) || MEMBER (widget, klas3))
#define MEMBER4(widget,klas1,klas2,klas3,klas4)  (MEMBER3 (widget, klas1, klas2, klas3) || MEMBER (widget, klas4))
#define MEMBER5(widget,klas1,klas2,klas3,klas4,klas5)  (MEMBER4 (widget, klas1, klas2, klas3, klas4) || MEMBER (widget, klas5))*/
#define MEMBER(widget,klas)  ((widget -> widgetClass & xm##klas##WidgetClass) != 0)
#define MEMBER2(widget,klas1,klas2)  ((widget -> widgetClass & (xm##klas1##WidgetClass | xm##klas2##WidgetClass)) != 0)
#define MEMBER3(widget,klas1,klas2,klas3)  ((widget -> widgetClass & (xm##klas1##WidgetClass | xm##klas2##WidgetClass | xm##klas3##WidgetClass)) != 0)
#define MEMBER4(widget,klas1,klas2,klas3,klas4)  ((widget -> widgetClass & (xm##klas1##WidgetClass | xm##klas2##WidgetClass | xm##klas3##WidgetClass | xm##klas4##WidgetClass)) != 0)
#define MEMBER5(widget,klas1,klas2,klas3,klas4,klas5)  ((widget -> widgetClass & (xm##klas1##WidgetClass | xm##klas2##WidgetClass | xm##klas3##WidgetClass | xm##klas4##WidgetClass | xm##klas5##WidgetClass)) != 0)

#define MAXNUM_CALLBACKS  3   /* E.g., maximum number of activate callbacks for a PushButton. */

typedef struct {
	struct { XtCallbackProc proc; XtPointer closure; } pairs [MAXNUM_CALLBACKS];
} XtCallbackList;

struct structWidget {
	long magicNumber;
	unsigned long widgetClass;
	Widget parent, previousSibling, nextSibling, firstChild;
	char *name;
	char inMenu, nativized, managed, insensitive;
	Widget textFocus;   /* For shells. */
	Widget shell;   /* My shell ancestor. */

	/* Native. */

	#if win
		HWND window;
		union {
			/* XtShell: */
			struct { Widget menuBar; int uniqueItemID, duringMoveWindow; } shell;

			/* XmPushButton (if in menu), XmToggleButton (if in menu), XmCascadeButton (if in menu): */
			struct { HMENU handle; int id; } entry;

			/* XmMenuBar, XmPulldownMenu: */
			struct { HMENU handle; int id; } menu;
		} nat;
	#elif mac
		Rect rect;   /* Window coordinates. */
		WindowPtr macWindow;
		int isControl;
		struct {
			/* XtShell: */
			struct { WindowPtr ptr; ControlRef rootControl; } window;

			/* XmPushButton (if not in menu), XmToggleButton (if not in menu), XmScrollBar, XmLabel (sometimes), XmCascadeButton (if not in menu or bar): */
			struct { ControlHandle handle; char isBevel, isPopup; } control;

			/* XmPushButton (if in menu), XmToggleButton (if in menu), XmCascadeButton (if in menu): */
			struct { MenuHandle handle; int item; } entry;

			/* XmPulldownMenu: */
			struct { MenuHandle handle; int item /* if cascading */; int id; } menu;

			/* XmText: */
			struct { TEHandle handle; } text;

			/* XmList: */
			struct { ListHandle handle; } list;
		} nat;
	#endif

	/* Motif */

	union {
		struct { Widget horizontalBar, verticalBar, clipWindow, workWindow; } scrolledWindow;
		struct { XtCallbackList moveCallbacks; } drawingArea;
		struct { int editable; XtCallbackList motionVerifyCallbacks, valueChangedCallbacks; } text;
		struct { int active, isDialog;
			unsigned long lowAccelerators [8]; XtCallbackProc goAwayCallback; XtPointer goAwayClosure; } shell;
		struct { Widget okButton, cancelButton, helpButton; XtCallbackList okCallbacks, cancelCallbacks, helpCallbacks; } messageBox;
		struct { unsigned char acceleratorChar; int acceleratorModifiers; } pushButton;
		struct { int inBar; } cascadeButton;
		struct { int indicatorType; XtCallbackList valueChangedCallbacks; } toggleButton;
		struct { XtCallbackProc defaultActionCallback; XtPointer defaultActionClosure; } list;
		struct { XtCallbackList valueChangedCallbacks, dragCallbacks; } scrollBar;
	} motif;

	/* Resources. */

	int x, y, width, height;
	int isRadioButton;   /* For radio buttons and check buttons. */
	int visibleItemCount, selectionPolicy;   /* For lists. */
	int radioBehavior, packing, rowColumnType;   /* For row-columns. */
	int orientation;   /* For row-columns and scroll bars. */
	int alignment;   /* For labels. */
	Widget defaultButton, cancelButton;   /* For forms and shells. */
	int dialogStyle;   /* For forms and shells. */
	int dialogType;   /* For message boxes and shells. */
	Widget messageText;   /* For message boxes. */
	int autoUnmanage;   /* For bulletin boards. */
	Widget subMenuId, popUpButton;   /* For cascade buttons and their menus. */
	long increment, pageIncrement, sliderSize;   /* For scroll bars. */
	long minimum, maximum, value;   /* For scales and scroll bars. */

	XtCallbackProc activateCallback, destroyCallback, exposeCallback,
		extendedSelectionCallback, inputCallback, resizeCallback;
	XtPointer activateClosure, destroyClosure, exposeClosure,
		extendedSelectionClosure, inputClosure, resizeClosure;
	int leftAttachment, rightAttachment, topAttachment, bottomAttachment;
	int leftOffset, rightOffset, topOffset, bottomOffset;
	int deleteResponse;   /* For shells. */

	#if mac
		TXNObject macMlteObject;
		TXNFrameID macMlteFrameId;
		unsigned long changeCount;
	#endif
};

#define my  me ->

extern struct Gui {
	Widget textFocus;
	int duringUpdate;
	#if win
		HINSTANCE instance;   /* First argument of WinMain. */
	#elif mac
		WindowPtr modalDialog;
	#endif
} theGui;

void _Gui_callCallbacks (Widget w, XtCallbackList *callbacks, XtPointer call);
#if mac
	void _GuiMac_clipOn (Widget me);
	void _GuiMac_clipOffValid (Widget me);
#endif
Widget _Gui_initializeWidget (int widgetClass, Widget parent, const char *name);
void _Gui_invalidateWidget (Widget me);
void _Gui_validateWidget (Widget me);
void _GuiNativeControl_check (Widget me, Boolean value);
void _GuiNativeControl_destroy (Widget me);
void _GuiNativeControl_show (Widget me);
void _GuiNativeControl_hide (Widget me);
void _GuiNativeControl_setSensitive (Widget me);

/********** GuiText.c **********/
/* Keyboard focus */
void _GuiText_handleFocusReception (Widget me);
void _GuiText_handleFocusLoss (Widget me);
#if mac
void _GuiMac_clearTheTextFocus (void);
#endif
void _GuiText_setTheTextFocus (Widget me);
/* Change notification */
void _GuiText_handleValueChanged (Widget me);
/* Existence */
void _GuiText_nativizeWidget (Widget me);
void _GuiText_destroyWidget (Widget me);
/* Management */
void _GuiText_unmanage (Widget me);
#if mac
	void _GuiMacText_move (Widget me);
	void _GuiMacText_shellResize (Widget me);
	void _GuiMacText_resize (Widget me);
	void _GuiMacText_map (Widget me);
	void _GuiMacText_update (Widget me);
	int _GuiMacText_tryToHandleKey (Widget me, unsigned char keyCode, unsigned char charCode, EventRecord *event);
	int _GuiMacText_tryToHandleReturnKey (Widget me, EventRecord *event);
	int _GuiMacText_tryToHandleClipboardShortcut (Widget me, unsigned char charCode, EventRecord *event);
	void _GuiMacText_handleClick (Widget me, EventRecord *event);
	void _GuiMac_makeTextCaretBlink (void);
#endif
void _GuiText_init (void);
void _GuiText_exit (void);

#endif

/* End of file GuiP.h */
#endif

TOOLPATH = ../z_tools/
INCPATH  = ../z_tools/haribote/

MAKE     = $(TOOLPATH)make.exe -r
NASK     = $(TOOLPATH)nask.exe
CC1      = $(TOOLPATH)cc1.exe -I$(INCPATH) -Os -Wall -quiet
CPP      = $(TOOLPATH)c++.exe -I../z_tools/haribote -Os -Wall -nostdlib -fno-builtin -fno-exceptions -fno-rtti -B../z_tools -c
GAS2NASK = $(TOOLPATH)gas2nask.exe -a
OBJ2BIM  = $(TOOLPATH)obj2bim.exe
MAKEFONT = $(TOOLPATH)makefont.exe
BIN2OBJ  = $(TOOLPATH)bin2obj.exe
BIM2HRB  = $(TOOLPATH)bim2hrb.exe
BIM2BIN  = $(TOOLPATH)bim2bin.exe
RULEFILE = $(TOOLPATH)haribote/haribote.rul
EDIMG    = $(TOOLPATH)edimg.exe
IMGTOL   = $(TOOLPATH)imgtol.com
GOLIB    = $(TOOLPATH)golib00.exe
MKISOFS  = $(TOOLPATH)mkisofs.exe
COPY     = copy
DEL      = del

##################################################
# デフォルト動作
##################################################

default :
	$(MAKE) img

##################################################
# ファイル生成規則
##################################################

OBJS_BAYOS = \
	bayos.obj \
	system/descriptor.obj \
	system/console.obj \
	system/ihandler.obj \
	system/jpegls.obj \
	system/memory.obj \
	system/message.obj \
	system/scheduler.obj \
	system/sheet.obj \
	driver/beep.obj \
	driver/clock.obj \
	driver/dtk5s.obj \
	driver/fat12.obj \
	driver/file.obj \
	driver/ide.obj \
	driver/iso9660.obj \
	driver/keyboard.obj \
	driver/mouse.obj \
	driver/pci.obj \
	driver/pic.obj \
	driver/timer.obj \
	system/alloca.obj \
	naskfunc.obj

ipl.bin : ipl.nas Makefile
	$(NASK) ipl.nas ipl.bin ipl.lst

asmhead.bin : asmhead.nas Makefile
	$(NASK) asmhead.nas asmhead.bin asmhead.lst

hankaku.bin : hankaku.txt Makefile
	$(MAKEFONT) hankaku.txt hankaku.bin

hankaku.obj : hankaku.bin Makefile
	$(BIN2OBJ) hankaku.bin hankaku.obj _hankaku

bayos.bim : $(OBJS_BAYOS) Makefile
	$(OBJ2BIM) @$(RULEFILE) out:bayos.bim stack:3136k map:bayos.map werr:1 wredef:0 $(OBJS_BAYOS)
# 3MB+64KB=3136KB

bayos.hrb : bayos.bim Makefile
	$(BIM2HRB) bayos.bim bayos.hrb 0

haribote.sys : asmhead.bin bayos.hrb Makefile
	copy /B asmhead.bin+bayos.hrb haribote.sys

haribote.img : ipl.bin haribote.sys hello.hrb cat.hrb bball.hrb guitest.hrb noiz2bg.hrb Makefile
	$(EDIMG) imgin:../z_tools/fdimg0at.tek \
		wbinimg src:ipl.bin len:512 from:0 to:0 \
		copy from:haribote.sys to:@: \
		copy from:bin/BAYOS.BM5 to:@: \
		copy from:bin/SHGOTH12.UF5 to:@: \
		copy from:bin/license.txt to:@: \
		copy from:bin/hello.hrb to:@: \
		copy from:bin/cat.hrb to:@: \
		copy from:bin/bball.hrb to:@: \
		copy from:bin/guitest.hrb to:@: \
		copy from:bin/noiz2bg.hrb to:@: \
		imgout:bin/haribote.img

#		copy from:bin/bball.hrb to:@: \
#		copy from:bin/guitest.hrb to:@: \
#		copy from:bin/noiz2bg.hrb to:@: \

##################################################
# アプリケーションライブラリ
##################################################

API_OBJS = \
	apilib/api_putchar.obj \
	apilib/api_putstr0.obj \
	apilib/api_putstr1.obj \
	apilib/api_end.obj \
	apilib/api_openwin.obj \
	apilib/api_putstrwin.obj \
	apilib/api_boxfilwin.obj \
	apilib/api_initmalloc.obj \
	apilib/api_malloc.obj \
	apilib/api_free.obj \
	apilib/api_point.obj \
	apilib/api_refreshwin.obj \
	apilib/api_linewin.obj \
	apilib/api_closewin.obj \
	apilib/api_getkey.obj \
	apilib/api_alloctimer.obj \
	apilib/api_inittimer.obj \
	apilib/api_settimer.obj \
	apilib/api_freetimer.obj \
	apilib/api_beep.obj \
	apilib/api_fopen.obj \
	apilib/api_fclose.obj \
	apilib/api_fseek.obj \
	apilib/api_fsize.obj \
	apilib/api_fread.obj \
	apilib/api_cmdline.obj \
	apilib/api_getlang.obj \
	apilib/tomo_getmouse.obj \
	apilib/tomo_gettick.obj \
	apilib/tomo_rdmsr.obj \
	apilib/tomo_setlang.obj \
	apilib/tomo_sysinfo.obj \
	apilib/tomo_systime.obj \
	apilib/tomo_wrmsr.obj \
	apilib/tomo_cpuid.obj \
	apilib/tomo_rdtsc.obj \
	apilib/bayos_thread_id.obj \
	apilib/bayos_thread_join.obj \
	apilib/bayos_thread_kill.obj \
	apilib/bayos_thread_yield.obj \
	apilib/bayos_msg_send.obj \
	apilib/bayos_msg_receive.obj \
	apilib/bayos_get_wstr_info.obj \
	apilib/memcpy.obj \
	apilib/printf.obj \
	apilib/alloca.obj \
	apilib/new.obj \
	apilib/delete.obj

apilib.lib : Makefile $(API_OBJS)
	$(GOLIB) $(API_OBJS) out:apilib/apilib.lib

##################################################
# BayGUI ライブラリ
##################################################

OBJS_BAYGUI = \
	baygui/lang/Integer.obj \
	baygui/lang/Math.obj \
	baygui/lang/Object.obj \
	baygui/lang/String.obj \
	baygui/util/ArrayList.obj \
	baygui/awt/Application.obj \
	baygui/awt/AWTEvent.obj \
	baygui/awt/Button.obj \
	baygui/awt/Checkbox.obj \
	baygui/awt/CheckboxGroup.obj \
	baygui/awt/Component.obj \
	baygui/awt/Container.obj \
	baygui/awt/Frame.obj \
	baygui/awt/FontMetrics.obj \
	baygui/awt/Graphics.obj \
	baygui/awt/Label.obj \
	baygui/awt/Listbox.obj \
	baygui/awt/Rectangle.obj \
	baygui/awt/Scrollbar.obj \
	baygui/awt/TextComponent.obj \
	baygui/awt/TextField.obj \
	baygui/awt/event/KeyEvent.obj \
	baygui/awt/event/MouseEvent.obj \

baygui.lib : Makefile $(OBJS_BAYGUI)
	$(GOLIB) $(OBJS_BAYGUI) out:baygui/baygui.lib

##################################################
# hello
##################################################

hello.bim : apps/hello.obj apilib.lib Makefile
	$(OBJ2BIM) @$(RULEFILE) out:apps/hello.bim map:apps/hello.map stack:1k apps/hello.obj werr:1 wredef:0 apilib/apilib.lib

hello.hrb : hello.bim Makefile
	$(BIM2HRB) apps/hello.bim apps/hello.bin 0
	$(BIM2BIN) in:apps/hello.bin out:bin/hello.hrb -osacmp -tek5 BS:0 eprm:z0

##################################################
# cat
##################################################

cat.bim : apps/cat.obj apilib.lib Makefile
	$(OBJ2BIM) @$(RULEFILE) out:apps/cat.bim map:apps/cat.map stack:1k apps/cat.obj werr:1 wredef:0 apilib/apilib.lib

cat.hrb : cat.bim Makefile
	$(BIM2HRB) apps/cat.bim apps/cat.bin 0
	$(BIM2BIN) in:apps/cat.bin out:bin/cat.hrb -osacmp -tek5 BS:0 eprm:z0

##################################################
# bball
##################################################

bball.bim : apps/bball.obj apilib.lib baygui.lib Makefile
	$(OBJ2BIM) @$(RULEFILE) out:apps/bball.bim map:apps/bball.map stack:10k apps/bball.obj werr:1 wredef:0 apilib/apilib.lib baygui/baygui.lib

bball.hrb : bball.bim Makefile
	$(BIM2HRB) apps/bball.bim apps/bball.bin 512k
	$(BIM2BIN) in:apps/bball.bin out:bin/bball.hrb -osacmp -tek5 BS:0 eprm:z0

##################################################
# guitest
##################################################

guitest.bim : apps/guitest.obj apilib.lib baygui.lib Makefile
	$(OBJ2BIM) @$(RULEFILE) out:apps/guitest.bim map:apps/guitest.map stack:10k apps/guitest.obj werr:1 wredef:0 apilib/apilib.lib baygui/baygui.lib

guitest.hrb : guitest.bim Makefile
	$(BIM2HRB) apps/guitest.bim apps/guitest.bin 512k
	$(BIM2BIN) in:apps/guitest.bin out:bin/guitest.hrb -osacmp -tek5 BS:0 eprm:z0

##################################################
# noiz2bg
##################################################

noiz2bg.bim : apps/noiz2bg.obj apilib.lib baygui.lib Makefile
	$(OBJ2BIM) @$(RULEFILE) out:apps/noiz2bg.bim map:apps/noiz2bg.map stack:10k apps/noiz2bg.obj werr:1 wredef:0 apilib/apilib.lib baygui/baygui.lib

noiz2bg.hrb : noiz2bg.bim Makefile
	$(BIM2HRB) apps/noiz2bg.bim apps/noiz2bg.bin 512k
	$(BIM2BIN) in:apps/noiz2bg.bin out:bin/noiz2bg.hrb -osacmp -tek5 BS:0 eprm:z0

##################################################
# infones
##################################################

INFONES_OBJS = \
	infones/K6502.obj \
	infones/InfoNES.obj \
	infones/InfoNES_Mapper.obj \
	infones/InfoNES_pAPU.obj \
	infones/InfoNES_System_HariboteOS.obj

infones.bim : $(INFONES_OBJS) apilib/apilib.lib Makefile
	$(OBJ2BIM) @$(RULEFILE) out:infones/infones.bim map:infones/infones.map stack:1k $(INFONES_OBJS) werr:1 wredef:0 apilib/apilib.lib

infones.hrb : infones.bim Makefile
	$(BIM2HRB) infones/infones.bim infones/infones.bin 1024k
	$(BIM2BIN) in:infones/infones.bin out:bin/infones.hrb -osacmp -tek5 BS:0 eprm:z0

##################################################
# 一般規則
##################################################

%.gas : %.c Makefile
	$(CC1) -o $*.gas $*.c

%.nas : %.gas Makefile
	$(GAS2NASK) $*.gas $*.nas

%.obj : %.nas Makefile
	$(NASK) $*.nas $*.obj $*.lst

%.obj : %.cpp Makefile
	$(CPP) -o $*.obj $*.cpp

##################################################
# コマンド
##################################################

img :
	$(MAKE) haribote.img

iso :
	$(MAKE) img
	$(MKISOFS) -v -iso-level 1 -b haribote.img -o haribote.iso bin
	$(COPY) haribote.iso ..\z_tools\qemu\haribote.iso
	$(MAKE) -C ../z_tools/qemu
#	bochs.bat

run :
	$(MAKE) img
	$(COPY) bin\haribote.img ..\z_tools\qemu\fdimage0.bin
	$(MAKE) -C ../z_tools/qemu

clean :
	-$(DEL) *.bim
	-$(DEL) *.bin
	-$(DEL) *.hrb
	-$(DEL) *.lib
	-$(DEL) *.lst
	-$(DEL) *.map
	-$(DEL) *.obj
	-$(DEL) *.log
	-$(DEL) *.nvram
	-$(DEL) *.vmsd
	-$(DEL) apps\*.bim
	-$(DEL) apps\*.bin
	-$(DEL) apps\*.hrb
	-$(DEL) apps\*.map
	-$(DEL) apps\*.obj
	-$(DEL) bin\*.hrb
	-$(DEL) bin\*.log
	-$(DEL) bin\*.nvram
	-$(DEL) bin\*.vmsd
	-$(DEL) baygui\*.lib
	-$(DEL) baygui\awt\event\*.obj
	-$(DEL) baygui\awt\*.obj
	-$(DEL) baygui\lang\*.obj
	-$(DEL) baygui\util\*.obj
	-$(DEL) apilib\*.lib
	-$(DEL) apilib\*.lst
	-$(DEL) apilib\*.obj
	-$(DEL) driver\*.obj
	-$(DEL) system\*.obj
#	-$(DEL) haribote.img
	-$(DEL) haribote.sys

depend : 
	gcc -MM bayos.cpp driver/*.cpp system/*.cpp apps/*.cpp apilib/*.cpp baygui/lang/*.cpp baygui/util/*.cpp baygui/awt/*.cpp baygui/awt/event/*.cpp > dependencies

include dependencies

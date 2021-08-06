/*
 ____       ____
/ ___|_   _|  _ \ _ __
\___ \ \ / / | | | '_ \
 ___) \ V /| |_| | |_) |
|____/ \_/ |____/| .__/
                 |_|
*/

/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const Gap default_gap        = {.isgap = 1, .realgap = 5, .gappx = 5};
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {	"Fira Sans SemiBold:size=12:antialias=true:autohint=true" ,
                                        "Fira Sans Book:size=9:antialias=true:autohint=true" ,
					"Roboto Regular:size=10:antialias=true:autohint=true" ,
					"Fira Mono Regular:size=10:antialias=true:autohint=true" ,
					"Noto Color Emoji:size=10:antialias=true:autohint=true" ,
					"Noto Sans:size=12:antialias=true:autohint=true" };				
#include "/home/svdp/.cache/wal/colors-wal-dwm.h"
/* static const char col_gray1[]    = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_urgborder[]   = "#ff0000";
static const char *colors[][3]      = {
	*               fg         bg         border   *
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeUrg]  = { col_gray4, col_cyan,  col_urgborder  },
};*/

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-g", "120x34", "-e", "ranger", NULL };
const char *spcmd3[] = {"st", "-n", "volume", "-g", "120x34", "-e", "pulsemixer", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
	{"volume",      spcmd3},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class        instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",       NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox",    NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "st-256color",NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,         NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
	{ NULL,		"spterm", NULL,		  SPTAG(0),  1,		 1,	      0,        -1 },
	{ NULL,		"spfm",   NULL,		  SPTAG(1),  1,		 0,	      -1,       -1 },
	{ NULL,		"volume", NULL,		  SPTAG(2),  1,		 0,	      -1,       -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]    = { "dmenu_run", "-p", "Run: ", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *cmdprintscreen[]  = { "scrot", "-d3", "/home/svdp/Pictures/Screenshots/%Y-%m-%d-%s_$wx$h.png", NULL };
static const char *cmdprintscreenf[]  = { "scrot", "-u", "/home/svdp/Pictures/Screenshots/%Y-%m-%d-%s_$wx$h.png", NULL };
static const char *cmdprintscreens[]  = { "scrot", "-s", "/home/svdp/Pictures/Screenshots/%Y-%m-%d-%s_$wx$h.png", NULL };

#define TERMINAL "st"
#define PrintScreenDWM 0x0000ff61
#include"shiftview.c"
#include <X11/XF86keysym.h>


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,	        XK_e,      spawn,	   SHCMD("dmenuunicode") },		
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_p,  	   setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_p,      togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
        { MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
        { MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
        { MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
        { MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
        { MODKEY,            		XK_grave,  togglescratch,  {.ui = 0 } },
	{ MODKEY,			XK_r,	   togglescratch,  {.ui = 1 } },
	{ MODKEY,            		XK_v,	   togglescratch,  {.ui = 2 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY,			XK_w,	   spawn,	   SHCMD("$BROWSER") },
	{ MODKEY|ShiftMask,             XK_q,      spawn,          SHCMD("xkill") },
	{ MODKEY,	     XK_bracketright,	   shiftview,      {.i = +1}},
	{ Mod1Mask,		      XK_Tab,      shiftview,	   {.i = +1}},
	{ MODKEY,	      XK_bracketleft,	   shiftview,      {.i = -1}},
	{ Mod1Mask,	            XK_grave,	   shiftview,	   {.i = -1}},
	{ 0,          XF86XK_MonBrightnessUp,      spawn,          SHCMD("xbacklight -inc 5.000000") }, 
	{ MODKEY,		       XK_F6,	   spawn,	   SHCMD("xbacklight -inc 5.000000") },
        { 0,        XF86XK_MonBrightnessDown,      spawn,          SHCMD("xbacklight -dec 5.000000") }, 
	{ MODKEY,                      XK_F5,      spawn,          SHCMD("xbacklight -dec 5.000000") },  
	{ 0,         XF86XK_AudioLowerVolume,      spawn,          SHCMD("pamixer -d 5") },
	{ MODKEY,		      XK_F11,	   spawn,	   SHCMD("pamixer -d 5") },    
	{ 0,                XF86XK_AudioMute,      spawn,          SHCMD("pamixer -t") },
	{ MODKEY,                     XK_F10,      spawn,          SHCMD("pamixer -t") },  
	{ 0,         XF86XK_AudioRaiseVolume,      spawn,          SHCMD("pamixer -i 5") },
	{ MODKEY,                     XK_F12,      spawn,          SHCMD("pamixer -i 5") },
	{ MODKEY|ShiftMask,		XK_w,	   spawn,	   SHCMD("brave || brave-beta") },
	{ MODKEY,             PrintScreenDWM,      spawn,          SHCMD("flameshot") },
	{ 0,                  PrintScreenDWM,      spawn,          {.v = cmdprintscreen } },
        { ShiftMask,          PrintScreenDWM,      spawn,          {.v = cmdprintscreens } },
        { Mod1Mask,           PrintScreenDWM,      spawn,          {.v = cmdprintscreenf } },
	{ 0,		  XF86XK_ScreenSaver,	   spawn,          SHCMD("slock") },
	{ MODKEY|ShiftMask,	        XK_t,      spawn,          SHCMD("thunar") },
	{ MODKEY,		       XK_F7,      spawn,	   SHCMD("slock")},
        { MODKEY,                  XK_Escape,      spawn,          SHCMD("sysact") },
	{ MODKEY,		        XK_c,      spawn,          SHCMD("clipmenu") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

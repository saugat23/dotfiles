#include "./XF86keysym.h"
#include "./colorschemes/catppuccin.h"
#include <X11/keysym.h>

#define NUMTAGS 9


/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const unsigned int stairpx   = 20;       /* depth of the stairs layout */
static const int stairdirection     = 1;        /* 0: left-aligned, 1: right-aligned */
static const int stairsamesize      = 1;        /* 1 means shrink all the staired windows to the same size */
#define ICONSIZE 22   /* icon size */
#define ICONSPACING 6 /* space between icon and title */
static const char *fonts[]          = { "Inter:weight=Medium:size=11:antialias=true:hinting=true" };
static const char *colors[][3]      = {
	[SchemeNorm] = { col_gray3, col_gray2, col_gray2 },
	[SchemeSel]  = { col_cyan, col_gray4,  col_cyan },
  [SchemeTitle]  = { col_title, col_gray4, col_gray4 },
};

/* tagging */
static const char *tags[] = { " 󰣇 ", "  ", "  ", " ", "  ","  ", "  ", "  " };

static const Rule rules[] = {
	/*       class                instance     title         tags mask     isfloating   monitor */
       {   "kitty",                   NULL,       NULL,          1 << 1,       0,           -1 },
       {   "Chromium",                NULL,       NULL,          1 << 2,       0,           -1 },
       {   "idea",                    NULL,       NULL,          1 << 3,       0,           -1 },
};

/* shiftview patch */
void
shiftview(const Arg *arg) {
    Arg a = { .ui = selmon->tagset[selmon->seltags] };
    if (arg->i > 0) {
        a.ui = (a.ui << arg->i) | (a.ui >> (NUMTAGS - arg->i));
    } else {
        a.ui = (a.ui >> (-arg->i)) | (a.ui << (NUMTAGS + arg->i));
    }
    a.ui &= (1 << NUMTAGS) - 1;
    view(&a);
}


/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  
#include "vanitygaps.c"

 static const Layout layouts[] = {
 	/* symbol     arrange function */
	{ "| [T]",      tile }, 
  { "| 󰓍 ",      stairs },
  { "| @ ",      spiral },
	{ "| 󰉧 ",      NULL },    
 	{ "| 󰊓 ",      monocle },
	{ "| [\\]",     dwindle },
	{ "| H[]",      deck },
	{ "| TTT",      bstack },
	{ "| ===",      bstackhoriz },
	{ "| HHH",      grid },
	{ "| ###",      nrowgrid },
	{ "| ---",      horizgrid },
	{ "| :::",      gaplessgrid },
	{ "| |M|",      centeredmaster },
	{ "| >M>",      centeredfloatingmaster },
	{ "| ><>",      NULL },    
	{ NULL,       NULL },
 };

/* key definitions */
#define MODKEY Mod4Mask
#define MOD2KEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *roficmd[] = { "rofi", "-show", "drun", "-show-icons", NULL }; 
static const char *termcmd[]  = { "kitty", NULL };
static const char *flameshot[]  = { "flameshot", "gui", NULL };
static const char *powermenu[] = { "/home/sb23/.config/suckless/dwm/scripts/powermenu.sh", NULL};
static const char *configscript[] = { "/home/sb23/.config/suckless/dwm/scripts/config.sh", NULL};
static const char *browserbookmarksscript[] = { "/home/sb23/.config/suckless/dwm/scripts/browserbookmarks.sh", NULL};
static const char *chromiumcmd[] = {"chromium", NULL };
static const char *lockcmd[] = {"i3lock-fancy", NULL };

static const Key keys[] = {
	/* modifier                     key                          function           argument */
	{ MODKEY,			XK_Return,		     spawn,		{.v = termcmd } },
	{ MODKEY,                       XK_space,                    spawn,             {.v = roficmd } },
	{ MODKEY,			XK_b,			     spawn,		{.v = chromiumcmd } },
	{ MODKEY,			XK_c,			     spawn,		SHCMD("_JAVA_AWT_WM_NONREPARENTING=1 idea") },
	{ MODKEY,			XK_l,			     spawn,		SHCMD("python3 ~/.local/bin/logout-popup.py") },
	{ MODKEY|ShiftMask,             XK_b,                        togglebar,         {0} },
	{ MOD2KEY,			XK_Up,      		     spawn, 	        SHCMD("/usr/bin/pactl set-sink-volume @DEFAULT_SINK@ +10%") },
	{ MOD2KEY,			XK_Down,    		     spawn,           	SHCMD("/usr/bin/pactl set-sink-volume @DEFAULT_SINK@ -10%") },
	{ MOD2KEY,			XK_Right,     		     spawn,           	SHCMD("/usr/bin/brightnessctl set +10%") },
	{ MOD2KEY,			XK_Left,     		     spawn,           	SHCMD("/usr/bin/brightnessctl set 10%-") },
	{ MODKEY|ShiftMask,             XK_t,      		     spawn,             SHCMD("~/.dwm/toggle_layout.sh") },
	{ MODKEY,                       XK_Print,                    spawn,      	{.v = flameshot} },
	{ MODKEY|ControlMask, 		XK_Delete,		     spawn, 	        {.v = powermenu} },
	{ MODKEY|ShiftMask,             XK_j,                        rotatestack,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,                        rotatestack,       {.i = -1 } },
	{ MODKEY,                       XK_j,                        focusstack,        {.i = +1 } },
	{ MODKEY,                       XK_k,                        focusstack,        {.i = -1 } },
	{ MODKEY,                       XK_i,                        incnmaster,        {.i = +1 } },
	{ MODKEY,                       XK_d,                        incnmaster,        {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,                        setmfact,          {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,                        setmfact,          {.f = +0.05} },
	{ MODKEY,                       XK_z,                        zoom,              {0} },
	{ MODKEY,                       XK_Tab,                      view,              {0} },
	{ MODKEY,                       XK_q,                        killclient,        {0} },
	{ MODKEY,                       XK_s,                        setlayout,         {.v = &layouts[0]} },
	{ MODKEY,                       XK_t,                        setlayout,         {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,                        setlayout,         {.v = &layouts[2]} },
	{ MODKEY,                       XK_m,                        setlayout,         {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_space,                    togglefloating,    {0} },
	{ MODKEY,                       XK_0,                        view,              {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                        tag,               {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                    focusmon,          {.i = -1 } },
	{ MODKEY,                       XK_period,                   focusmon,          {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                    tagmon,            {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                   tagmon,            {.i = +1 } },
	{ MODKEY,			XK_Left,		     shiftview,		{.i = -1 } },
	{ MODKEY,			XK_Right,		     shiftview,		{.i = +1 } },
	TAGKEYS(                        XK_1,                                           0)
	TAGKEYS(                        XK_2,                                           1)
	TAGKEYS(                        XK_3,                                           2)
	TAGKEYS(                        XK_4,                                           3)
	TAGKEYS(                        XK_5,                                           4)
	TAGKEYS(                        XK_6,                                           5)
	TAGKEYS(                        XK_7,                                           6)
	TAGKEYS(                        XK_8,                                           7)
	TAGKEYS(                        XK_9,                                           8)
	TAGKEYS(			XK_KP_1,					0)
	TAGKEYS(			XK_KP_2,					1)
	TAGKEYS(			XK_KP_3,					2)
	TAGKEYS(			XK_KP_4,					3)
	TAGKEYS(			XK_KP_5,					4)
	TAGKEYS(			XK_KP_6,					5)
	TAGKEYS(			XK_KP_7,					6)
	TAGKEYS(			XK_KP_8,					7)
	TAGKEYS(			XK_KP_9,					8)
	{ MODKEY|ShiftMask,             XK_q,			    quit,               {0} },
	{ MODKEY|ShiftMask,		XK_r,			    quit,               {1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
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

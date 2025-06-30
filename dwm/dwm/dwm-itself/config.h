/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 15;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 0;        /* horizontal padding for statusbar */
static const int vertpadbar         = 0;        /* vertical padding for statusbar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	//{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 }, //this makes firefox always open in workspace 9
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[Y]",      monocle },
	{ "|U|",      centeredmaster },
	{ ">I>",      centeredfloatingmaster },
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

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *roficmd[] = { "rofi", "-show", "drun", "-show-icons", NULL };
static const char *termcmd[]  = { "konsole", NULL };

//Volume
static const char *mutecmd[] = { "amixer", "-q", "set", "Master", "toggle", NULL };
static const char *voldowncmd[] = { "amixer", "-q", "set", "Master", "5%-", "unmute", NULL, "pkill", "-RTMIN+10", "dwmblocks", NULL };
static const char *volupcmd[] = { "amixer", "-q", "set", "Master", "5%+", "unmute", NULL, "pkill", "-RTMIN+10", "dwmblocks", NULL };
static const char *updatevol[] = { "pkill", "-RTMIN+10", "dwmblocks", NULL };


//Brightness
static const char *brdowncmd[] = { "light", "-U", "5", NULL };
static const char *brupcmd[] = { "light", "-A", "5", NULL };
static const char *broffcmd[] = { "xset", "dpms", "force", "suspend", NULL };

static const char *suspendcmd[] = { "systemctl", "suspend", NULL };

//this is a custom script present in /usr/local/bin
static const char *keyboardbrtogcmd[] = { "keyboard-brightness-toggle", NULL };

//Opacity
static const char *opactogglecmd[] = { "picom-trans", "-c", "-t", NULL};  

//Turn off brightness - monitor specific
// xset dpms always applie to all displays, for display specific solutions we need other tools. Due to hardware/driver specifications of my current devices neither the external monitor (via ddcutil) or the laptop screen (via light command) can completely turn off the backlight
//So here we just use xrandr to put brightness to 0, even if it glows black
static const char *brofflaptop[] = { "xrandr", "--output", "eDP", "--brightness", "0", NULL};
static const char *bronlaptop[] = { "xrandr", "--output", "eDP", "--brightness", "1", NULL};

static const char *broffmonitor[] = { "xrandr", "--output", "HDMI-A-0", "--brightness", "0", NULL};
static const char *bronmonitor[] = { "xrandr", "--output", "HDMI-A-0", "--brightness", "1", NULL};


#include "movestack.c"

//XK_Right, XK_Left for arrow keys right and left

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = roficmd } },
	{ MODKEY,						XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_k,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,				XK_k,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,				XK_j,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_k,      setmfact,       {.f = +0.05} },
	{ MODKEY|ControlMask,			XK_j,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,				XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_w,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,						XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,						XK_i,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_f,      fullscreen,     {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_h,	   focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_l,	   focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_h,	   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_l,	   tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_plus,   setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_plus,   setgaps,        {.i = 60  } },
	{ MODKEY|ShiftMask,				XK_minus,  setgaps,	   {.i = -60 } },
	{ MODKEY,						XK_F1,     spawn,          {.v = mutecmd } },
	{ MODKEY,						XK_F1,     spawn,          {.v = updatevol } },
	{ MODKEY,						XK_F2,     spawn,          {.v = voldowncmd } },
	{ MODKEY,						XK_F2,     spawn,          {.v = updatevol } },
	{ MODKEY,						XK_F3,     spawn,          {.v = volupcmd } },
	{ MODKEY,						XK_F3,     spawn,          {.v = updatevol } },
	{ MODKEY,						XK_F4,     spawn,          {.v = brdowncmd } },
	{ MODKEY,						XK_F5,     spawn,          {.v = brupcmd } },
	{ NULL,							XK_F6,     spawn,          {.v = broffcmd } },
	{ MODKEY,						XK_F6,     spawn,          {.v = suspendcmd } },
	{ MODKEY,						XK_F7,     spawn,          {.v = keyboardbrtogcmd } },
	{ MODKEY,						XK_F8,     spawn,          {.v = opactogglecmd } },
	{ MODKEY,						XK_F9,	   spawn,		   {.v = brofflaptop } },
	{ MODKEY|ShiftMask,				XK_F9,	   spawn,		   {.v = bronlaptop } },
	{ MODKEY,						XK_F10,	   spawn,		   {.v = broffmonitor } },
	{ MODKEY|ShiftMask,				XK_F10,	   spawn,		   {.v = bronmonitor } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ControlMask,		XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


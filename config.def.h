/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx  = 1;        /* border pixel of windows */
static unsigned int gappx, default_gappx     = 5;        /* gaps between windows */
static unsigned int snap      = 32;       /* snap pixel */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static char font[]            = "monospace:size=10";
static char font2[]           = "monospace:size=10";
static char dmenufont[]       = "monospace:size=10";
static const char *fonts[]          = { font, font2 };
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	/*{ "Gimp",     NULL,       NULL,       0,            0,           -1 },*/
	{ "Xawtv",     NULL,       NULL,       0,            1,           -1 },
	{ "qutebrowser",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "font",                   STRING,     &font },
		{ "font2",                  STRING,     &font2 },
		{ "dmenu.font",             STRING,     &dmenufont },
		{ "normal.background",      STRING,     &normbgcolor },
		{ "normal.boder",           STRING,     &normbordercolor },
		{ "normal.foreground",      STRING,     &normfgcolor },
		{ "selected.background",    STRING,     &selbgcolor },
		{ "selected.border",        STRING,     &selbordercolor },
		{ "selected.foreground",    STRING,     &selfgcolor },
		{ "borderpx",          	    INTEGER,    &borderpx },
		{ "snap",          		    INTEGER,    &snap },
		{ "showbar",          	    INTEGER,    &showbar },
		{ "topbar",          	    INTEGER,    &topbar },
		{ "nmaster",          	    INTEGER,    &nmaster },
		{ "resizehints",       	    INTEGER,    &resizehints },
		{ "mfact",      	 	    FLOAT,      &mfact },
		{ "gappx",      	 	    INTEGER,    &default_gappx },
		{ "gappx",      	 	    INTEGER,    &gappx },
};


static const Key keys[] = {
	/* modifier                     key        function        argument */

    // Letter keys
	//{ MODKEY,                       XK_b,      spawn,          SHCMD( "dmenu-bluetooth" ) },
	{ MODKEY|ShiftMask,             XK_c,      spawn,          SHCMD( "pkill -USR1 xnotify" ) },
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_e,      spawn,          SHCMD( "dmenu-emoji" ) },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_m,      spawn,          SHCMD( "dmenus" ) },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_o,      spawn,          SHCMD( "open-latex-proj" ) },
	//{ MODKEY,                       XK_m,      spawn,          SHCMD( "dmenu-monitor" ) },
	{ MODKEY,                       XK_q,      spawn,          SHCMD( "dmenu-pkill" ) },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	//{ MODKEY,                       XK_n,      spawn,          SHCMD( "dmenu-networkmanager" ) },
	{ MODKEY,                       XK_n,      spawn,          SHCMD( "dmenu-notify-on-end" ) },
	{ MODKEY,                       XK_Return, spawn,          SHCMD( "st" ) },
	{ MODKEY,                       XK_r,      spawn,          SHCMD( "toggle-record-screen" ) },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD( "systemctl suspend" ) },
	//{ MODKEY,                       XK_t,      spawn,          SHCMD( "dmenu-translate" ) },
	//{ MODKEY,                       XK_w,      spawn,          SHCMD( "qutebrowser" ) },

    // Special keys
	{ 0,                       XF86XK_MonBrightnessUp,      spawn,      SHCMD( "incbacklight +5 && kill -38 $(pidof dwmblocks)" )},
	{ 0,                       XF86XK_MonBrightnessDown,    spawn,      SHCMD( "incbacklight -5 && kill -38 $(pidof dwmblocks)" )},
	{ 0,                       XF86XK_AudioRaiseVolume,     spawn,      SHCMD( "pulseaudio-ctl up && kill -39 $(pidof dwmblocks) ") },
	{ 0,                       XF86XK_AudioLowerVolume,     spawn,      SHCMD( "pulseaudio-ctl down && kill -39 $(pidof dwmblocks) ") },
	{ 0,                       XF86XK_AudioMute,            spawn,      SHCMD( "pulseaudio-ctl mute && kill -39 $(pidof dwmblocks) ") },
	{ 0,                       XF86XK_AudioMicMute,         spawn,      SHCMD( "pulseaudio-ctl mute-input @DEFAULT_SOURCE@ toggle" ) },
	{ 0,                       XF86XK_AudioPlay,            spawn,      SHCMD( "playerctl play-pause" ) },
	{ 0,                       XF86XK_AudioPrev,            spawn,      SHCMD( "playerctl previous" ) },
	{ 0,                       XF86XK_AudioNext,            spawn,      SHCMD( "playerctl next" ) },

    // Arrow keys
	{ MODKEY,                       XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,           XK_Up,     moveresizeedge, {.v = "t"} },
	{ MODKEY|ControlMask,           XK_Down,   moveresizeedge, {.v = "b"} },
	{ MODKEY|ControlMask,           XK_Left,   moveresizeedge, {.v = "l"} },
	{ MODKEY|ControlMask,           XK_Right,  moveresizeedge, {.v = "r"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Up,     moveresizeedge, {.v = "T"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Down,   moveresizeedge, {.v = "B"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Left,   moveresizeedge, {.v = "L"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Right,  moveresizeedge, {.v = "R"} },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_plus,   setgaps,        {.i = +1 } },
	{ MODKEY,             XK_0,      setgaps,        {.i = 0 } },
	//{ MODKEY,                       XK_b,      togglebar,      {0} },
	//{ MODKEY,                     XK_i,      incnmaster,     {.i = +1 } },
	//{ MODKEY,                     XK_d,      incnmaster,     {.i = -1 } },
	//{ MODKEY,                       XK_Return, zoom,           {0} },
	//{ MODKEY,                       XK_Tab,    view,           {0} },
	//{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	//{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	//{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	//{ MODKEY,                       XK_space,  setlayout,      {0} },
	//{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	//{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	//{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	//{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	//{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	//{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_x,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	//{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


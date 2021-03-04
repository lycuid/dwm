/* See LICENSE file for copyright and license details. */

/* appearance */ static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const int bar_height         = 22;
static const char *fonts[]          = { "Fira Code:size=10" };
static const char col_gray1[]       = "#131313";
static const char col_gray2[]       = "#353535";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_teal[]        = "#00ffff";
static const char col_amethyst[]    = "#9b59b6";
static const char *colors[][3]      = {
	/*                          fg         bg         border   */
	[SchemeNorm]          = { col_gray3, col_gray1,     col_gray2 },
	[SchemeSel]           = { col_gray4, col_gray2,     col_amethyst },
	[SchemeTagNorm]       = { col_gray2, col_gray1,     col_gray2 },
	[SchemeTagSel]        = { col_gray4, col_gray2,     col_gray4 },
	[SchemeTagOccNorm]    = { col_gray4, col_gray1,     col_gray2 },
	[SchemeTagOccSel]     = { col_gray4, col_gray2,     col_gray4 },
	[SchemeLayoutSymbol]  = { col_gray1, col_amethyst,  col_gray4 },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };

static const Rule rules[] = {
	/* xprop(1):
		*	WM_CLASS(STRING) = instance, class
		*	WM_NAME(STRING) = title
		*/
	/* class          instance        title           tags mask  isfloating  monitor  scratchkey */
	{ "Gimp",           NULL,       NULL,                 0,          1,        -1,       0 },
	{ "Firefox",        NULL,       NULL,               1 << 2,       0,        -1,       0 },
	{ "Brave-browser",  NULL,       NULL,               1 << 2,       0,        -1,       0 },

	/* make scratchpads floating. */
	{ NULL,             NULL,       "scratchpad-term",    0,          1,        -1,       't' },
	{ NULL,             NULL,       "scratchpad-fm",      0,          1,        -1,       'f' },
	{ NULL,             NULL,       "scratchpad-nm",      0,          1,        -1,       'n' },
};

/* layout(s) */
static const float mfact     = 0.5;   /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;     /* number of clients in master area */
static const int resizehints = 1;     /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */
static const char *termcmd[]  = { "st", NULL };

/* First arg only serves to match against key in rules */
static const char *scratchpad_term[]  = {"t", "st", "-t", "scratchpad-term", "-g", "110x30", NULL};
static const char *scratchpad_fm[]    = {"f", "st", "-t", "scratchpad-fm", "-g", "110x30", "-e", "vifm", NULL};
static const char *scratchpad_nm[]    = {"n", "st", "-t", "scratchpad-nm", "-g", "110x30", "-e", "nmtui", NULL};


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask,           XK_Return, togglescratch,  {.v = scratchpad_term } },
	{ MODKEY|ControlMask,           XK_f,      togglescratch,  {.v = scratchpad_fm } },
	{ MODKEY|ControlMask,           XK_n,      togglescratch,  {.v = scratchpad_nm } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
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


/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 2;        /* horizontal padding for statusbar */
static const int vertpadbar         = 0;        /* vertical padding for statusbar */
static const char *fonts[]          = { "mononoki:size=10" };
static const char dmenufont[]       = "mononoki:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { "#ebdbb2", "#1d2021", "#989b06" },
	[SchemeSel]  = { "#ebdbb2", "#484848", "#b8bb26"  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tagsalt[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	//{ "Firefox",   NULL,       NULL,       (1 << 3),       0,          -1 },
	{  NULL,      NULL,       NULL,       0,            False,         -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "<><",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define XF86MonBrightnessDown		0x1008ff03
#define XF86MonBrightnessUp			0x1008ff02
#define XF86AudioMute				0x1008ff12
#define XF86AudioLowerVolume		0x1008ff11
#define XF86AudioRaiseVolume	    0x1008ff13
#define XF86Display                 0x1008FF59   /* Output switch key */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "rofi", "-modi", "drun", "-show", "drun", "-theme", "gruvbox-dark-soft", NULL };
static const char *wincmd[] = { "rofi", "-modi", "window", "-show", "window", "-theme", "gruvbox-dark-soft", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
//static const char *iconcmd[] = {"/home/maxim/github/rofi-fontawesome/fontawesome-menu/fontawesome-menu", "-f", "/home/maxim/github/rofi-fontawesome/fontawesome-menu/fa5-icon-list.txt", NULL};
//static const char *surf[] = {"surf", NULL};
// Brightness
static const char *cmdbrightnessup[]    = { "/home/maxim/.config/brup.sh", NULL };
static const char *cmdbrightnessdown[]    = { "/home/maxim/.config/brdw.sh", NULL };
// Sound
static const char *cmdsoundup[]     = { "amixer", " -q", "sset", "Master", "-5%+" , NULL };
static const char *cmdsounddown[]   = { "amixer", " -q", "sset", "Master", "-5%-" , NULL };
//static const char *cmdsoundtoggle[] = { "amixer", "-q", "sset", "Master", "toggle", NULL };
// Screenshot
static const char *cmdscrot[] = { "/bin/bash", "scrot", "'%Y-%m-%d-%s_screenshot_$wx$h.jpg'", "-e", "'mv $f /home/maxim/bilder/shots/'", NULL};
// Shutdown
static const char *cmdpow[] = {"/home/maxim/.config/down_script.sh", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = wincmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	//{ MODKEY,                       XK_s,      spawn,          {.v = surf } },
	//{ MODKEY,                       XK_i,      spawn,          {.v = iconcmd } },
    { 0,                            XF86MonBrightnessDown,     spawn,   {.v = cmdbrightnessdown } },
	{ 0,                            XF86MonBrightnessUp,       spawn,   {.v = cmdbrightnessup } },
	//{ 0,                            XF86AudioMute,             spawn,   {.v = cmdsoundtoggle } },
	{ 0,                            XF86AudioRaiseVolume,      spawn,   {.v = cmdsoundup } },
    { 0,                            XF86AudioLowerVolume,      spawn,   {.v = cmdsounddown } },
    { 0,                            XK_Print,                  spawn,   {.v = cmdscrot } },
	{ 0,                            XF86Display,               spawn,   {.v = cmdscrot} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },

    // Resize stuff
    { MODKEY,					    XK_Down,	moveresize,		{.v = (int []){ 0, 25, 0, 0 }}},
    { MODKEY,					    XK_Up,		moveresize,	    {.v = (int []){ 0, -25, 0, 0 }}},
    { MODKEY,					    XK_Right,	moveresize,		{.v = (int []){ 25, 0, 0, 0 }}},
    { MODKEY,					    XK_Left,	moveresize,		{.v = (int []){ -25, 0, 0, 0 }}},
    { MODKEY|ShiftMask,			    XK_Down,	moveresize,		{.v = (int []){ 0, 0, 0, 25 }}},
    { MODKEY|ShiftMask,			    XK_Up,		moveresize,		{.v = (int []){ 0, 0, 0, -25 }}},
    { MODKEY|ShiftMask,			    XK_Right,	moveresize,		{.v = (int []){ 0, 0, 25, 0 }}},
    { MODKEY|ShiftMask,			    XK_Left,	moveresize,		{.v = (int []){ 0, 0, -25, 0 }}},

	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_m,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_n,      togglealttag,   {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = cmdpow} },
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


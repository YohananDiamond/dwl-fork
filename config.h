/* appearance */
static const int sloppyfocus               = 0;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const unsigned int borderpx         = 1;  /* border pixel of windows */
static const float bordercolor[]           = {0.5, 0.5, 0.5, 1.0};
static const float focuscolor[]            = {1.0, 1.0, 1.0, 1.0};
/* To conform the xdg-protocol, set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]         = {0.1, 0.1, 0.1, 1.0};

static const char *const autostart[] = {
        "dotf.common.deskinit", NULL,
        NULL /* terminate */
};

/* tagging - tagcount must be no greater than 31 */
static const int tagcount = 9;

static const Rule rules[] = {
	/* app_id     title                tags_mask, center, float, monitor */
	{ "float",    NULL,                0 << 8,    1,      1,     -1 },
	{ NULL,       "Task Manager",      0 << 8,    1,      1,     -1 },
	{ NULL,       "Sharing Indicator", 0 << 8,    1,      1,     -1 },
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* monitors */
static const MonitorRule monrules[] = {
	/* name       mfact nmaster scale layout       rotate/reflect                x    y */
	/* example of a HiDPI laptop monitor:
	{ "eDP-1",    0.5,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
	*/
	/* defaults */
	{ NULL,       0.55, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
};

/* keyboard config */
static const struct xkb_rule_names xkb_rules = {
	/* fields: rules, model, layout, variant, options */
	.layout = "br",
	.options = NULL,
};

static const int repeat_rate = 45;
static const int repeat_delay = 250;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 1;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;

/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;
/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

#define MSUPER WLR_MODIFIER_LOGO
#define MCTRL WLR_MODIFIER_CTRL
#define MALT WLR_MODIFIER_ALT
#define MSHIFT WLR_MODIFIER_SHIFT

#define MODKEY MSUPER

#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,SKEY,toggletag, {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static const Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* format: { modmask, keycode, function, argument } */

	/* basic manipulation */
	{ MODKEY,            XKB_KEY_q,     killclient,       {0} },
	{ MODKEY|MSHIFT,     XKB_KEY_space, togglefloating,   {0} },
	{ MODKEY|MSHIFT,     XKB_KEY_F,     togglefullscreen, {0} },
	{ MODKEY|MALT|MCTRL, XKB_KEY_e,     quit,             {0} }, /* TODO: is this working? and it should be SUPER+ALT+CTRL) */

	/* set layout */
	{ MODKEY,        XKB_KEY_Tab,   setlayout,      {.v = &layouts[0]} },
	{ MODKEY,        XKB_KEY_m,     setlayout,      {.v = &layouts[2]} },

	/* stack manipulation */
	{ MODKEY,        XKB_KEY_j,     focusstack,     {.i = +1} },
	{ MODKEY,        XKB_KEY_k,     focusstack,     {.i = -1} },
	{ MODKEY|MSHIFT, XKB_KEY_J,     movestack,      {.i = +1} },
	{ MODKEY|MSHIFT, XKB_KEY_K,     movestack,      {.i = -1} },
	{ MODKEY,        XKB_KEY_h,     setmfact,       {.f = -0.05} },
	{ MODKEY,        XKB_KEY_l,     setmfact,       {.f = +0.05} },
	{ MODKEY|MSHIFT, XKB_KEY_H,     incnmaster,     {.i = -1} },
	{ MODKEY|MSHIFT, XKB_KEY_L,     incnmaster,     {.i = +1} },

	/* monitor manipulation */
	/* TODO: try this out */
	{ MODKEY|MALT,        XKB_KEY_j, focusmon, {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|MALT,        XKB_KEY_k, focusmon, {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|MSHIFT|MALT, XKB_KEY_J, tagmon,   {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|MSHIFT|MALT, XKB_KEY_K, tagmon,   {.i = WLR_DIRECTION_LEFT} },

	/* terminals / editors */
	{ MODKEY,        XKB_KEY_Return, spawn, SHCMD("$TERMINAL") },
	{ MODKEY|MSHIFT, XKB_KEY_Return, spawn, SHCMD("$TERMINAL -c float") },
	{ MODKEY, XKB_KEY_e, spawn, SHCMD("graphedit") },

	/* menus */
	{ MODKEY,        XKB_KEY_space, spawn, SHCMD("runnsend error-and-output fzrun") },
	{ MODKEY,        XKB_KEY_c,     spawn, SHCMD("runnsend error-and-output dotf.screenshot") },
	{ MODKEY|MSHIFT, XKB_KEY_C,     spawn, SHCMD("runnsend error-and-output dotf.screenshot --full") },
	{ MODKEY,        XKB_KEY_F10,   spawn, SHCMD("termup -f runread fzmount -m") },
	{ MODKEY|MSHIFT,  XKB_KEY_F10,   spawn, SHCMD("termup -f runread fzmount -u") },
	{ MODKEY|MALT,   XKB_KEY_o,     spawn, SHCMD("runnsend error-and-output fzpow") },

	/* popups */
	{ MODKEY|MALT,   XKB_KEY_m,     spawn, SHCMD("$TERMINAL -c float -e pulsemixer") },
	{ MODKEY|MALT,   XKB_KEY_c,     spawn, SHCMD("$TERMINAL -c float -g 65x10 -e runread cal -3") },
	{ MODKEY|MALT,   XKB_KEY_p,     spawn, SHCMD("$TERMINAL -c float -e calc") },

	/* minor utils */
	{ MODKEY,      XKB_KEY_w,      spawn, SHCMD("setbg") },
	{ MODKEY,      XKB_KEY_comma,  spawn, SHCMD("volumectl dec") },
	{ MODKEY,      XKB_KEY_period, spawn, SHCMD("volumectl inc") },
	{ MODKEY,      XKB_KEY_y,      spawn, SHCMD("volumectl togglemute") },
	{ MODKEY|MALT, XKB_KEY_comma,  spawn, SHCMD("playerctl previous") },
	{ MODKEY|MALT, XKB_KEY_period, spawn, SHCMD("playerctl next") },
	{ MODKEY|MALT, XKB_KEY_y,      spawn, SHCMD("playerctl play-pause") },
	{ MODKEY,      XKB_KEY_minus,  spawn, SHCMD("backlightctl mod -5") },
	{ MODKEY,      XKB_KEY_equal,  spawn, SHCMD("backlightctl mod 5") },
	{ MODKEY,      XKB_KEY_F12,    spawn, SHCMD("wl-redscr toggle") },

	/* apps */
	{ MODKEY, XKB_KEY_b, spawn, SHCMD("runnsend error $BROWSER") },

	{ MODKEY,          XKB_KEY_0,           view, {.ui = ~0} },
	{ MODKEY|MSHIFT,   XKB_KEY_parenright,  tag,  {.ui = ~0} },
	TAGKEYS(XKB_KEY_1, XKB_KEY_exclam,      0),
	TAGKEYS(XKB_KEY_2, XKB_KEY_at,          1),
	TAGKEYS(XKB_KEY_3, XKB_KEY_numbersign,  2),
	TAGKEYS(XKB_KEY_4, XKB_KEY_dollar,      3),
	TAGKEYS(XKB_KEY_5, XKB_KEY_percent,     4),
	TAGKEYS(XKB_KEY_6, XKB_KEY_asciicircum, 5),
	TAGKEYS(XKB_KEY_7, XKB_KEY_ampersand,   6),
	TAGKEYS(XKB_KEY_8, XKB_KEY_asterisk,    7),
	TAGKEYS(XKB_KEY_9, XKB_KEY_parenleft,   8),

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit, {0} },
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ MODKEY,        BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ MODKEY,        BTN_MIDDLE, togglefloating, {0} },
	{ MODKEY|MSHIFT, BTN_LEFT,   moveresize,     {.ui = CurResize} },
};

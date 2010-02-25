#
# Regular cron jobs for the maeremote package
#
0 4	* * *	root	[ -x /usr/bin/maeremote_maintenance ] && /usr/bin/maeremote_maintenance

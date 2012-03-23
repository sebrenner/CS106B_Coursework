# we close pipes to finish out console, gdb's default behavior is to
# stop/print on SIGPIPE, we want it to just get handed to app and ignore
handle SIGPIPE nostop noprint pass



# web_procasination_tools

Tools used for preventing browser-related procrastination problems

## Why?

I watched too much anime and simple website blocker isn't enough(since I can just uninstall them with couple of clicks), having a background process that is hard to trace make the barrier to stopping the process much higher

## How it works

The principle is really simple, depending on how I feel, the program will check for signs of packages to certain websites and after certain threshold(0 if I have finals that week), shutdown the browser

I used libpcap as well as pkill to inspect and then shutdown the browser when needed, and uses a startup command to launch the programm with a randomized process name or a process name that makes it hard to find(like hide it among the vscode processes)

## References

https://eecs.wsu.edu/~sshaikot/docs/lbpcap/libpcap-tutorial.pdf (libpcap usage)
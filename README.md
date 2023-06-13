# ncurses-controller-monitor
A controller input monitor meant to be displayed in a Terminal User Interface. Comes complete with button configuration / mapping too.

# How to download & compile

1. Open a terminal
2. git clone https://github.com/sd103/ncurses-controller-monitor.git
3. cd ncurses-controller-monitor
4. make

At this point, you can use the controller input monitor at any time by entering the ncurses-controller-monitor directory (You should still be in it after compiling) and using the following command:

```
./input-monitor
```

You can also configure a controller you have connected by running the config program with the following command:

```
./config
```

The config program will erase your control settings then ask you to map button inputs to buttons on the monitor.

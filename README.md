# Command-Assistant
A C++ program to suggest commands when you mistype in a linux terminal

## Building

1) Pull this repository
2) Run `make` to compile the executable

## Using

First you will need to grant the `command-not-found` file execution permission. To do this, run

```
chmod +x command-not-found
```

Then, move the executable to `/usr/lib`. You may want to copy the original `command-not-found` executable first.

```
sudo mv /usr/lib/command-not-found /usr/lib/command-not-found-old
sudo mv command-not-found /usr/lib-command-not-found
```

Try typing an incorrect command and you should now be met with suggestions for commands you have installed.

NOTE: This ONLY works on Linux, and has only been tested on Ubuntu using bash.
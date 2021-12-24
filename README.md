# pamalert

Linux PAM module which sends a Slack/Discord webhook alert upon a successful `sshd` login.

![Example alert](https://i.imgur.com/nZ2p2IU.png)

## Build

Requires libpam dev package (Ubuntu: `libpam0g-dev`) and curl dev packages (Ubuntu: `libcurl4-openssl-dev`) 

```sh
mkdir build
cd build
cmake ..
cmake --build .
```

## Setup

Put built `libpamalert.so` file somewhere and add this as the last line to `/etc/pam.d/sshd`:
```
account optional /path/to/libpamalert.so SLACK_OR_DISCORD_WEBHOOK_HERE
```

Note: If using Discord webhook, append `/slack` to end of URL

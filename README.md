## Purpose
Made to connect *n* number of bots to a Mincraft server, in offline mode though.
Then those bots all have the possibility to send simultaneously a command.


## Requirements
- Boost
- OpenSSL

## How to install

```bash
git clone --recurse-submodules https://github.com/Urpagin/McConnectBot.git
```

```bash
cd McConnectBot && mdkir build
```

```bash
cmake ..
```

```bash
make . -j$(nproc)
```
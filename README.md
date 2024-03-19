## Purpose
Made to connect *n* number of bots to a Mincraft server, in offline mode though.
Then those bots all have the possibility to send simultaneously a command.

## Disclaimer
This is, for now, a quick project done swiftly to get to learn C++.
So this is no good-looking repo.

## Requirements
### Building
- Git
- CMake & Make
### Dependencies
- Boost
- OpenSSL

## How to install

```bash
git clone --recurse-submodules https://github.com/Urpagin/McConnectBot.git
```

```bash
cd McConnectBot && mkdir build && cd build
```

```bash
cmake ..
```

```bash
make . -j$(nproc)
```
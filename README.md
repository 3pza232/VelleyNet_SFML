# VolleyNet

A 2D beach volleyball multiplayer game built with SFML 2.6.2 and Box2D 3.1.0.

### Prerequisites
- **Windows**: All libraries are included in the `libs/` folder.
- **Linux**: System packages are required (see below).

### Project Structure
```
VolleyNet/
├── client/          # Client application
├── server/          # Server application
└── libs/            # SFML and Box2D libraries (precompiled for Windows)
```

### Build & Run
```bash
cd client      # or cd srever
mkdir build
cd build
cmake -G "Ninja" ..
ninja -j8
./bin/client   # or ./bin/server
```

### Platform-Specific Notes
- **Windows**: Uses the precompiled libraries in `libs/`. The main CMakeLists.txt is configured for Windows.
- **Linux**: Uses system-installed libraries. Remember to copy `CMakeLists_Linux.txt` to `CMakeLists.txt` before building.

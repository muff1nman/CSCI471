To Build
-------
```
mkdir build
cd build
cmake ..
make
```

To Clean
--------
rm -rf build

To Run
-------
```
# The following path is relative to the build directory
./lib/Main
```

Files are served from the current working directory and you dont have
to run it from the build directory. 

Misc
-------

### Logging

Logging was done using the google glog logging library. To enable it
pass a switch to cmake:

```
rm -rf build
mkdir build
cd build
cmake -DLOGGING=ON ..
make
```

Unfortunately its not installed on Isengard, so it is disabled by
default.

### Other configuration
To change the port, manually edit the file in
`include/httpmuncher/config.h.cmake` and rebuild the project.

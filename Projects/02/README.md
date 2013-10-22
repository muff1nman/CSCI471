Building
----------
```
mkdir build
cd build
cmake ..
```

#### Other options
By default when building these options are turned on (See top level
`CMakeLists.txt` file)

- DEBUG
	- Keeps gdb symbols in the executable and does not optimize. This option
	  should be enabled until I figure out why I cant turn on the -O2 switch.
- CACHING
	- Enables caching of dns responses.

Other options include

- LOGGING
	- If you have google's logging library installed (glog) on your system path
	  you can enable in depth logging.
- TEST
	- If you want to run the included tests, you will need to turn this option
	  on.  Note that you do not need to install anything as all the required
	  test libraries are bundled in with the source (gtest is being used)

To change which are enabled (but really the defaults should be fine):

```
rm -rf build
mkdir build
cd build
cmake .. -DDEBUG=ON -DLOGGING=ON -DCACHING=OFF
```


Running
-------
```
cd build # if you aren't there already
./lib/dnsmuncher --help
```


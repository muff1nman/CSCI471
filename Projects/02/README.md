Although not the best way about things, if you don't want to read the rest of
this document just run `make` with the included Makefile. Otherwise to do things
the proper way, read on.

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

Extra Credit
----------
Caching should be working fine. The best way to test it is to run in daemon mode
and check that no queries are sent the second time.

Querying for other types (SOA, NS, etc) are supported internally and at one
point worked, but this feature fell by the way side as I started trying to hurry
to get things done and you can no longer use the --type switch. So unless having
some code counts for partial credit, theres not much there.


Bugs
------
You can't put a nameserver into the server ip query field, it needs to be an ip
address. Although the docs seem to imply this is fine, I thought it was
annoying.

There is an issue when trying to query for the root domain. I didn't have enough
time to look into this however.



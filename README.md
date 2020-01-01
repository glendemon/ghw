# Generalized Hamming Weights for Linear Codes

## Installation

You must install [flint-2.4](http://flintlib.org/) first

```
#!bash
$ wget http://flintlib.org/flint-2.4.tar.gz
$ tar xzf flint-*.tar.gz
$ cd flint-*
$ ./configure --prefix=../ghw/ --reentrant
$ make
$ make check
$ make install
```

Then install GHW

```
#!bash
$ hg clone ssh://hg@bitbucket.org/glendemon/ghw
$ cd ghw
$ make
$ ln -s dist/Release/GNU-Linux-x86/ghw
```

## Usage

### Launching
```
#!bash
$ time ./ghw [path to file]
```

### Rebuild

Rebuild program and create link.
```
#!bash
$ bash rebuild.sh
```

### Run from ./codes directory

Compute weight hierarchy for codes in ./codes directory.
Write results to ./results directory.
```
#!bash
$ bash run.sh
```

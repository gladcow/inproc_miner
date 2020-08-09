## Dependancies
    Boost, OpenSSL

## Build And Usage
```
git clone git@github.com:gladcow/inproc_miner.git
cd inproc_miner
cmake .
make
miner_test/miner_test
```
`miner_test` connects to sample pool (supportxmr.com) and starts mining targeting 20% of CPU usage. It prints hashrate and CPU usage statistics every time it gets job from the pool (this values are zero for the first job from pool). Press `Enter` key to exit miner_test. It prints integral CPU usage stat before exit. 

## Python Wrapper
Available for Python2. Usage is the same:
```
git clone git@github.com:gladcow/inproc_miner.git
cd inproc_miner
cmake .
make
python2 py_wrapper/test.py
```
`test.py` is equivalent to the `miner_test`

 Current version is for Linux only. 

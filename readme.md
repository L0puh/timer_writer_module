# timer writer kernel module
linux kernel module that writes messages to a file periodically via timer.

the file is saved in `/var/tmp/test_module` directory.
write intervals are specified in _seconds_.

requirements: 
- linux kernel 6.12
- gcc, Make
- kernel headers

# usage:

## build and load 
```bash
cd kernel_module
make            
make load       
```

## configure with setup app
```bash
cd setup_app
make            
./setup_app ../kernel_module/timer_writer.ko "output.txt" 3
# where: module_path, filename, period_seconds
```

## monitor 
```bash
dmesg | tail -10
tail -f /var/tmp/output.txt
```

## cleanup
```bash
# kernel_module/
make unload     
make clean      

# setup_app/
make clean      
```

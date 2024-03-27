## `sysfs` modules for studying NVIDIA kernel modules

- `$ make; sudo insmod counter_kobject.ko; sudo ./a.out`
- Reads to `/sys/kernel/uvm_counters_group/uvm_dummy_target` reset all counters to 0.
- Remember to seek to 0 before reading and after writing.
- Faced an error with making the module for a variable number of counters: currently has 15.
- Ignore the zeroeth value in the output
- To increment a counter: `write (file_fd, "dummy buffer", <counter_index>)`.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main () {
	int fd;
	fd = open ("/sys/kernel/uvm_counters_group/uvm_dummy_target", O_RDWR);
	if (fd < 0)
		exit (fd);
	char rwbuf[4096];

	// read and print the whole buffer once
	printf ("Initial values\n");
	int retval;
	retval = read (fd, (char*) rwbuf, 4096);
	lseek (fd, 0, SEEK_SET);
	printf ("read returned %d bytes\n", retval);
	int i;
	printf ("%s\n", rwbuf);
	rwbuf[0] = 0;

	if (write (fd, rwbuf, 2) != 2) printf ("line 24 mismatch\n");
	if (write (fd, rwbuf, 2) != 2) printf ("line 25 mismatch\n");
	if (write (fd, rwbuf, 5) != 5) printf ("line 26 mismatch\n");
	if (write (fd, rwbuf, 5) != 5) printf ("line 27 mismatch\n");
	if (write (fd, rwbuf, 5) != 5) printf ("line 28 mismatch\n");
	if (write (fd, rwbuf, 5) != 5) printf ("line 29 mismatch\n");
	if (write (fd, rwbuf, 5) != 5) printf ("line 30 mismatch\n");
	if (write (fd, rwbuf, 5) != 5) printf ("line 31 mismatch\n");
	if (write (fd, rwbuf, 5) != 5) printf ("line 32 mismatch\n");
	if (write (fd, rwbuf, 5) != 5) printf ("line 33 mismatch\n");
	if (write (fd, rwbuf, 5) != 5) printf ("line 34 mismatch\n");
	if (write (fd, rwbuf, 5) != 5) printf ("line 35 mismatch\n");
	if (write (fd, rwbuf, 5) != 5) printf ("line 36 mismatch\n");
	if (write (fd, rwbuf, 5) != 5) printf ("line 37 mismatch\n");
	if (write (fd, rwbuf, 3) != 3) printf ("line 38 mismatch\n");
	if (write (fd, rwbuf, 3) != 3) printf ("line 39 mismatch\n");
	if (write (fd, rwbuf, 3) != 3) printf ("line 40 mismatch\n");
	lseek (fd, 0, SEEK_SET);
	i = read (fd, (char*) rwbuf, 4096);
	lseek (fd, 0, SEEK_SET);
	printf ("NEW values, retval %d\n", i);
	printf ("%s\n", rwbuf);
	i = read (fd, (char*) rwbuf, 4096);
	printf ("after reading values: retval %d\n", i);
	printf ("%s\n", rwbuf);

	close (fd);
	return 0;
}


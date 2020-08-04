function cflags = find_libcflags(name)

[status, cflags] = system(sprintf("pkg-config --cflags %s", name));
assert(status == 0);

cflags = strip(cflags);

end
function lflags = find_liblflags(name)

[status, lflags] = system(sprintf("pkg-config --libs %s", name));
assert(status == 0);
lflags = strip(lflags);

end
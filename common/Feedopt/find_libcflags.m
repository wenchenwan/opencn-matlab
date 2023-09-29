function cflags = find_libcflags(name)

[status, cflags] = system(sprintf("pkg-config --cflags %s", name));
ocn_assert( status == 0, "Fails to find the libraries", mfilename);

cflags = strip(cflags);

end
function lflags = find_liblflags(name)

[status, lflags] = system(sprintf("pkg-config --libs %s", name));
ocn_assert( status == 0, "Fails to find the libraries", mfilename);

lflags = strip(lflags);

end
# FileDump
Assignment for class. Reads in an input file within the current directory specified by the user, then outprints the binary or hex (depending on users desire) for that file along with the human readable ascii characters.

Sample Compilation:
      g++ -o johnj filedump.cpp 
      ./johnj desiredFileToRead.bin (for hex output) 
      or 
      ./johnj -b desiredFileToRead.txt (for binary output)

The file type does not matter for the samples above, only the presence of the '-b' binary specifier.

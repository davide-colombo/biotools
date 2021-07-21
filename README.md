# biotools

In this repository you can find useful bioinformatics tools for manipulating DNA strings and, in particular FASTA files.

The core of the program is composed by:
- biotypes.h, define datatypes used for higher level operations;
- biovar.h,   defines global variables used by others files (if you need to use them);
- bioconst.h, defines useful constant;
- bioerr.h,   defines functions for error handling;

These files MUST BE INCLUDED ALWAYS to run the program and YOU MUST INCLUDE THEM IN THAT PRECISE ORDER.

The other files are:
- allocator.h,  define a set of functions for handling memory allocation;
- biostr.h,     define a set of functions for manipulating strings;
- revcomp.h,    define a function for computing the reverse complement of a sequence object;
- dna2rna.h,    define a function for computing the transcription of a sequence object (DNA -> mRNA);
- getseq.h,     define a function for creating a SEQ object from a FILE;

Each file is isolated, in this way you can take one script and include within your personal project without troubles.

If you want to try, 'biotools.c' contains a simple implementation example.

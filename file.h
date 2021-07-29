#ifndef __FILE_H__
#define __FILE_H__
typedef struct TList_file {
	struct TList_file *next;
	struct File *file;
} TList_file;

typedef struct Tlist_direct {
	struct Tlist_direct *next;
	struct Directory *directory;
} Tlist_direct;

typedef struct Directory {
    // The name of the directory
	char *name;

    // TODO: The list of files of the current directory
	TList_file *fisiere;

    // TODO: The list of directories of the current directory
	Tlist_direct *directoare;

    // The parent directory of the current
	// directory (NULL for the root directory)
	struct Directory *parentDir;
} Directory;

typedef struct File {
    // The name of the file
	char *name;

    // The size of the file
	int size;

    // The content of the file
	char *data;

    // The directory in which the file is located
	Directory *dir;
} File;

#endif /* __FILE_H__ */

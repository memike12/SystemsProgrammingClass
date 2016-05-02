#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#define INIT_SIZE 5

/**
 * Structure for a file
 **/
typedef struct{

  char * fname; //name of file
  time_t last; //last modified

} file_t;


/**
 * Structure for a diretory
 **/
typedef struct{
  
  file_t ** flist; //list of file pointers
  int nfiles; //number of files
  int size; //size of flist array
  
  

} dir_t;  

/**
 *Create a new directory structure initialized properly
 *
 *@return: pointer to newly allocated directory
 **/
dir_t * myfs_mkdir();

/**
 *Remove and deallocate the directory structure at dir.  
 *
 *@arg dir:  pointer to a directory structure
 **/
void myfs_rmdir(dir_t * dir);

/**
 *Update the timestamp for the file fname or create the file fname if
 *it doesn't exist
 *
 *@arg dir: pointer to a directory structure
 *@arg fname: string, the name of the file
 *@return file_t *: Pointer to recently touched file
 **/
file_t * myfs_touch(dir_t * dir, char *fname);

/**
 *Remove a file
 *
 *@arg dir: pointer to a directory structure
 *@arg fname: string, the name of the file
 *@return int: positive integer if remove success, else negative on failur
 **/
int myfs_rm(dir_t * dir, char * fname);

/**
 * List the contents of the directory dir
 *
 *@arg dir: pointer to a directory structure
 **/
void myfs_ls(dir_t * dir);

/**
 *List the contents of the directory in time sorted order
 *
 *@arg dir: pointer to a directory structure
 **/
void myfs_ls_sorttime(dir_t * dir);

/**
 *List the contents of the directory in file name sorted order
 *
 *@arg dir: pointer to a directory structure
 **/
void myfs_ls_sortname(dir_t * dir);


#endif

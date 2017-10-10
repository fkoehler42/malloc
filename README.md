# Malloc

A personal implementation of the allocation functions from the C standard library. Each function is protected from a multi-thread access.

## Implemented functions

```
void	*malloc(size_t size);
void	*calloc(size_t count, size_t size);
void	*realloc(void *ptr, size_t size);
void	*reallocf(void *ptr, size_t size);
void	free(void *ptr);
void	show_mem(t_display_flag flag);
```

### Free
### Realloc
### Reallocf
### Calloc
### Show_mem

## Usage

To execute these functions, you need to export the created library in order to override the real functions of the standard library. Use the following commands to do so.

```
make
cc 'your_file.c' ./libft_malloc.so
./test/run.sh 'your_executable'
```

### show_mem usage

This function is a custom one that displays informations about the allocated memory.
You must call it with one these flags :
- ALLOC : show allocated blocks informations.
- FREE : show free blocks informations.
- ALL : show allocated and free blocks informations.
- DUMP : show the hexadecimal value of each byte of data inside allocated blocks.

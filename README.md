# GET_Next_Line
Whether it is a file, the standard input or, later on, a network connection, you will always need to read content line by line. It is therefore time to tackle this function, which is essential for a number of your future projects.

![succeded with 123](graded.png "Succeded with 123")

## Description
Luckily, this project came after **Libft**, and using/submitting the library was not only allowed, but encouraged ([DRY](https://en.wikipedia.org/wiki/Don%27t_repeat_yourself)). As a result, I tried to write `get_next_line` reusing as many **Libft** functions as possible. First of all, let's remember the given **prototype** of the function we have to write:
```
int get_next_line(const int fd, char **line)
```

This function uses the [file descriptor](https://en.wikipedia.org/wiki/File_descriptor) received as first **argument**, and will `read` from it as many bytes as the `BUFFER_SIZE` **macro** determines (check `libft.h` for macro definitions). It must return one of three values:

- `1`, in case we successfully read a line from the file.
- `0`, if we reach the **end of file**.
- `-1`, which indicates there was some **error**.

It also receives `line` (the address of a pointer to `char`), which points to the address of the memory area where we want to write our line. Needless to say, `get_next_line` must allocate memory space for the line. It will be responsibility of the caller (maybe a `main` function) to release back that memory once the line has been used.

## How I went about it
When I started the project, I decided to take it as a chance to learn and practice [data structures](https://en.wikipedia.org/wiki/Data_structure). After several development iterations I ended up with four functions:

1. `get_next_line` to control the whole process.
1. `set_buf` to set the **head** on a [circular linked-list](https://en.wikipedia.org/wiki/Linked_list#Circular_linked_list).
2. `read_ln` to read to buffer in the current **head** of the circular linked list.
3. `build_ln`, to allocate memory in the heap for the `line`, based on the **length of the strings** in the nested linked list (if any) plus the **remaining contents of the buffer** (up to a `\n` or the final `\0`). Then it fixes the buffer for the next call.
4. `init_bfd` is just a silly helper function to initialize the values in the structure used as `content` in the nodes of the circular linked list.

Since we may have to perform multiple `read` operations, we'll need some place to put all the bytes we're reading. We need a data structure capable of growing dynamically, so a **linked-list** sounds like a perfect fit!

### Setting the buffer
The prototype of this function is as follows:
```c
static int	set_buf(int fd, t_list **b)
```
It receives a [file descriptor](https://en.wikipedia.org/wiki/File_descriptor) as an argument, which is used to set the value of `b`, which should point to the current **head** of the circular linked list.

1. The first thing this function does is to traverse the circular list to check if there's any node whose `fd` member is the same as the `fd` of the current call. If there's one, `b` is set to that node.

2. If there's not such a node, the `if` statement will create a new node using the `ft_clst_add` function, which is a new addition to `libft`. This function adds a new node to the circular list, and sets its head to this newly added node.

#### Content of the circular list nodes
For this purpose I declared the following structure in my `get_next_line.h`:
```c
typedef struct s_bfd
{
	char	bf[BUFF_SIZE + 1];
	int		fd;
	t_list	*lst;
	size_t	len;
}	t_bfd;
```

The members in this structure are self-explanatory:

* `bf` for the **buffer**; note how I chose to add an extra byte for the **null character** (we want our buffer to be able to store a proper string).
* `fd` for the **file descriptor**.
* `lst` for a nested linked list. This will be a [singly linked-list](https://en.wikipedia.org/wiki/Linked_list#Singly_linked_list) that will only be populated if the buffer is not big enough to acommodate a whole line (ended by a `\n`) after a `read` operation.
* `len`, for the amount of characters in the just mentioned linked list.

The only purpose of the call to `init_bfd` is to initialize a local structure named `tmp_cont`, which will be used as the values for the content of the node. I would have used a **designated initializer** but they were forbidden by the **Norm** (the style guide used at 42).

### Read from the file descriptor onto the buffer
The `read_ln` function has the following prototype:
```c
static int	read_ln(int fd, t_list *b)
```
This function will use the file descriptor passed in the argument `fd` to `read` from it and store the data in the other argument, which is the **current head** in the circular linked list (`b`).

The first thing it does is to declare and assign a local variable named `buf`, that points to the `bf` member of the current circular list head.

The return value of the `read` operation, is assigned to `ret`, which can have 3 values:

- A **positive number** which indicates how many bytes were read.
- `0`, if the `read` operation reached the **end of the file**. In this case, we also have to check if the buffer is empty. In that case, we are done.
- `-1`, which indicates an **error**, so we won't enter the next `while` loop, and the test of line 62 will deal with the return value of this function, which in turn will be properly handled in `get_next_line`.

> If the `read` operation yields `0` or `-1`, we won't enter the following loop.

For the **positive number** scenario, we are gonna use a `while` **loop**. Once we go inside, we'll keep adding nodes to the nested linked-list, and **clearing the buffer** right after (we don't want garbage from a previous read messing the buffer contents after a `\n` character.

### Storing buffer content in a linked-list
For the scenario where our `buffer` is not big enough to accomodate a line, we'll store as many `read` chunks as needed in the **nested singly linked-list** of `b`. So after each `read` operation, if the buffer doesn't contain a `\n`, we have to flush the buffer onto the mentioned list. At the same time, we'll increase by `BUF_SIZE` bytes the `len` member, which at the end should contain the amount of bytes in our linked list.

> Everytime we flush the whole `buffer` onto a newly allocated **node**, we have to `ft_strclr` it, just in case a later `read` only fills *half of it* (we don't want garbage in the 2nd half of our `buffer`).

Once we reach the **newline** or **end of file**, we'll `break` out of this loop.

## Building the line
The `build_ln` function has the following prototype:
```c
static int	build_ln(char **ln, t_list *b)
```

Within this function we declare three variables:

* `tmp_lst`, which we'll use to iterate through the nested linked_list.
* `b_len` to measure the remaining characters in the buffer.
* `buf` which is used to make more comfy to access the `content` member of the **selected node** in the circular list.

Then we allocate space in memory for a string using the value of the `len` member, and we assign that memory area to the `ln` parameter; now we have to traverse the list, concatenating the node contents to the `ln` string.

Then we have to **delete the list**. Finally, we'll concatenate the contents of the `buffer` (a string that contains a `\n` or a `\0`.

### Fixing the buffer
The last two lines of this function (before the last `return` statement) are used to leave the buffer (`buf`) ready for later calls to `get_next_line`. We do that with two calls:

* One to `ft_memmove`, which copy the contents after the `\n` to the beginning of the buffer.
* Another one to `ft_strclr`, which **clears** (setting all positions to `\0`) from the position of the just shifted `\n` to the end of the buffer.

## TODO
- [x] Move the call to `init_bfd` within the `if` statement.

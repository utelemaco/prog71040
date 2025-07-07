## Commands for User and Group Management

1.  **`whoami`**: Prints your username.

2. **`users`**: Lists all users currently logged into the system.

3.  **`groups`**: Lists the groups you belong to, as well as their IDs and member count.


## Commands for Exploring File System and Directory Structure

1. **`pwd`**: Prints the current working directory.

2.  **`ls`**: Lists all files in the current directory, showing permissions, number of bytes, ownership, and timestamps.
    *   `ls -l`: Long listing format.
    *   `ls -a`: Show hidden files.

3.  **`cd`**: Changes the current working directory.
```bash
cd <directory_name>
```

4. **`mkdir`**: Creates a new directory with the specified name.
```bash
mkdir <directory_name>
```

5.  **`touch`**: Creates an empty file with the specified name, or updates the timestamp of an existing file if it's already present.
```bash
touch <file_name>
```

## Commands for File and Directory Management

1. **`cp`**: Copies files from one location to another.

   * `cp <source_file> <destination_file>`: Copy a single file.
   * `cp -r <source_directory> <destination_directory>`: Recursively copy a directory.

2. **`mv`**: Moves or renames files.
   * `mv <file_name1> <file_name2>`

3.  **`rm`**: Removes files.
    * `rm <file_name>`: Remove a single file.
    * `rm -r <directory_name>`: Recursively remove an entire directory.

## Commands for Viewing File Contents

1.  **`cat`**: Displays the contents of one or more files.
    * `cat <file_name>`

2. **`echo`**: Outputs text to the console, which can be redirected to a file using redirection operators (>).
   * `echo "Hello, World!" > output.txt`

## Redirection and Piping Operators

1.  **`>`**: Redirects output from one command to another or to a file.
```bash
cat input.txt > output.txt
```

2. **`>>`**: Appends new data to the end of an existing file instead of overwriting it.
```bash
echo "Additional text" >> output.txt
```

3.  **`|`**: Pipes output from one command as input for another, allowing you to chain commands together.
```bash
cat input.txt | grep keyword
```

## Permissions and Ownership

1. **`chmod`**: Changes file permissions or ownership.

2. **`chown`**: Changes the owner of a file or directory.
   
To understand how these commands interact with each other, practice using them in different scenarios. This will give you hands-on experience working with files and directories on Linux systems.


4.  **`history`**: Lists and searches through previous commands entered by you or any user on your system.
```bash
history
```

```bash
history | grep ls
```

6.  **`man`**: Displays detailed documentation for a command or function.

```bash
man ls
```

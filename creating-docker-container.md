## Creating a Docker Container

You can use a docker container to compile and execute C programs using the follwing command.

```bash
docker container run --name gcc_15_1_0 -v ./:/home/user -d -t gcc:15.1.0
```

This command creates a new container named `gcc_15_1_0` and maps the current working directory (`.`) to `/home/user` inside the container. 
The `-v` flag is used for volume mapping, which allows sharing files between the host machine and the Docker container.

A directory named `/home/user` will be created within the container, which is a mirror of the current working directory on the host machine.
Any changes made to files in the current working directory on the host will be reflected inside the `/home/user` directory in the container.
Conversely, any changes made to files in the `/home/user` directory within the container will also affect the original files in the current working directory on the host.

This strategy allows for easy file sharing and synchronization between the host machine and the Docker container, making it a convenient way to work with containers.

## Image Argument (gcc:15.1.0):

The `gcc:15.1.0` argument specifies the image to be used as a base for the new container. 
In this case, the image is based on GCC 15.1.0, which implies that the container will have access to the GCC compiler and related tools. 
This means that any commands or applications run within the container will be able to utilize the GCC compiler and its features. 











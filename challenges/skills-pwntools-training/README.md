# pwntools-training
- General Skills
- Easy
- 100 Points

## Description

It's extremely helpful to be able to interface with websites or servers using code!

Feel free to use your favorite language if you already have one. You'll need to be able to connect to this server either by running ssh using your language, or by connecting directly with a library that can work with the SSH protocol.

If you don't know what any of that means, don't worry! I've given you a Python file to get you started.

So here's the challenge: use pwntools, a library for Python, to connect to our training server and solve a challenge. You can try to connect to the server yourself if you wish:

`ssh connect@pwntools-training.ctf.umanitobacssa.ca -p 10101`

And enter the password `ctf2025!` when prompted.

The server will ask you to add 2 numbers together. Sounds easy enough. The catch? You only have 500 milliseconds to do it, far too fast for a human to add together and type!

So instead, try to write some code to handle it for you.

**We strongly recommend using a proper installation of Python 3.** This can be inside a VM, on a remote server, or on your local machine. Note that pwntools works best on Linux, so if you aren't running Linux it's best to use a Linux virtual machine, WSL, or a remote machine like Aviary.

If you already have Python 3 setup and are familiar with it, go ahead and install the `pwntools` package with `pip`.

If you don't, we first recommend looking online for instructions to:
1. Install Python for your machine (if you are on Windows, you should try to use WSL to use Python inside Linux rather than install Python for Windows if you can)
2. Setup a pyenv or venv for your CTF scripts
3. Install the `pwntools` package using pip

Alternatively, if you want to just get started, you can use pwntools with Docker: <https://github.com/Gallopsled/pwntools/blob/dev/DOCKER.md>

Once you have a working Python 3 environment, download the `connect.py` script, place it in the directory you created, and see if you can automate adding the numbers together to get the flag!

Good luck!

## Solution

Modify the template to add numbers together and send the result. See solution.py

## Flag
`cssactf{u17R@-f4$T-m47H3M4t1c5-df518b0c}`
# Components of a CTF Challenge

There are several components that come together to create a good CTF challenge:

1. Category - What domain of digital security does the challenge focus on?
2. Problem - What specific problem is the challenge testing in the player? This usually manifests as a specific vulnerability built into the challenge to be exploited, but it could be more broad than that to allow for multiple solutions.
3. Difficulty - How hard is the challenge? There are a lot of different pieces to what can make a challenge easy for some but very hard for others.
4. Scenario & Presentation - What is the purpose of the challenge, why is the player solving it, and how does it fit into an overarching theme or story? How is the problem presented? This usually involves creating a mock version of a real-world application to exploit - something more interesting than an abstract question on an exam.

---

# Challenge Categories

### General Skills

An introductory category which teaches basic skills for CTF by walking the player through simple challenges and concepts. This is a good time to link new players to some of the most basic tools they might find helpful, for example:

- [CyberChef](https://gchq.github.io/CyberChef/#input=SGVsbG8)
- [emn178 Online Tools](https://emn178.github.io/online-tools/)

**Examples**

- Learn how to connect to a remote server using ncat.
- Learn how to interact with a remote server or web API using a scripting language like Python.
- Learn how to convert between number bases including binary, decimal and hex.
- Learn how to convert between encoding formats like base64 or URI

---

### Forensics

A general catch-all category for challenges related to security analysis.

**Examples**

- Analyze a log file to extract information about a remote attacker.
- Analyze a pcap network trace to identify suspicious network traffic and extract information.
- Extract hidden information embedded in file metadata.
- Extract hidden information embedded in a photo or video using steganography.
- Analyze the change log of a version control system for suspicious activity.

---

### Binary Exploitation

Identify and exploit a vulnerability in a program executable.

- Binary exploitation usually involves exploiting an executable file such as an EXE, JAR, DLL or some other assembly.
- Usually the player is given the exploitable binary to run locally for testing and exploit discovery, although this is not required.
- This often has overlap with reverse engineering as often the player must reverse engineer the code or binary to discover the vulnerability, however binary exploitation usually focuses on fundamental vulnerabilities caused by improper usage of a programming language, framework or improper resource management.

**Examples**

- Exploit a memory management vulnerability in an executable such as a buffer overflow, use-after-free, or double-free to leak data, construct and execute a ROP-chain, or perform an ASLR bypass.
- Exploit a common library vulnerability such as a string format vulnerability.
- Exploit an arbitrary memory write vulnerability to construct and execute a ROP-chain or overwrite a program’s v-table.
- Exploit dynamic linking to load player-controlled code and bypass a software security mechanism.
- Modify configuration or save data for a program to bypass a security mechanism.

---

### Reverse Engineering

Reverse engineer the logic flow of a given program binary or code to extract hidden information or discover a flaw which allows the player to bypass a security measure. 

- The reverse engineering target is often either the source code of a program, or a compiled binary such as an EXE, ELF, JAR, DLL or other assembly which must first be decompiled using a tool like Ghidra or dotPeek.
- Reverse engineering challenges may involve exploiting a vulnerability similar to Binary or Web Exploitation, however in these types of challenges reverse engineering often focuses on a flaw in the high level logic or process design of a given program or algorithm.

**Examples**

- Reverse engineer a license key validation algorithm and craft a valid license key which passes the verification.
- Reverse engineer multi-threaded code to identify an exploitable race condition.
- Reverse engineer obfuscated code to extract a hidden passphrase or input sequence.

---

### Cryptography

Locate a vulnerability in the encryption of a file or data.

- Cryptography challenges often involve discovering a flaw in a given encryption algorithm implementation, exploiting specific characteristics of an insecure encryption algorithm, reconstructing data given partial plaintext, partial ciphertext or partial key material, or using a side channel vulnerability to leak information about the plaintext from the ciphertext.
- Brute-forcing is a valid way to break encryption, but it’s encouraged to avoid creating challenges which require significant computational power as competitors are not expected to have access to a GPU or server to perform brute-forcing attempts at high speed.

**Examples**

- Decrypt a ciphertext created using common human-decryptable cipher such as a Caesar cipher, substitution cipher, or rail fence cipher.
- Extract the encryption key for a one-time-pad XOR ciphertext using a partial known plaintext vulnerability.
- Leak information about a ciphertext or extract an encryption key using a controlled-plaintext vulnerability.
- Decrypt a ciphertext by exploiting a weak prime selection used in RSA encryption.
- Decrypt a ciphertext given the RSA public key of a known public-private keypair.
- Leak information about the structure of plaintext encrypted using AES ECB.
- Brute-force a ZIP file password using a known leaked password dictionary (eg. rockyou)
- Identify a flaw in an encryption algorithm implementation which reduces the keyspace to a very small range of possible keys.

---

### Web Exploitation

Locate a vulnerability in a website, API or other internet service.

- Web exploitation is a very broad category with many potential challenge approaches: bad API implementations, exposed unrestricted developer APIs, hidden files, missing or misconfigured authentication, SQL injection, HTML template injection, Javascript reverse engineering, and many more.

**Examples**

- Analyze a websites source code or Javascript to find hidden information.
- Identify an unrestricted API endpoint parameters which can be modified to request sensitive information which was not intended to be exposed, eg. Firebase, GraphQL or JSON Resource endpoints.
- Identify an API endpoint which returns more data than necessary for the frontend, including private sensitive data not intended to be exposed.
- Modify a browser cookie to change your authenticated user.
- Identify a user controlled input vulnerability which allows for arbitrary code execution, SQL injection, template injection or otherwise unintended behavior.
- Locate hidden files available in public web directories.

---

# Challenge Problem Ideation

Two common ways to come up with a challenge concept are either to first pick an abstract exploit and build a narrative around it, or draw inspiration from real-world scenarios and create a mock that emulates that scenario.

---

### Start with an Exploit

This is often the best way to create easier challenges that guide new players into tackling a CTF. You can easily start with a very basic exploit and iteratively create harder and harder follow-up challenges for players to build their skills.

For example, you could create a chain of binary exploitation problems focused on poor memory management. An example for a series of buffer overflow challenges:

1. Exploit a buffer overflow to replace a value on the stack with a known correct value to pass a check
2. Exploit the same buffer overflow, but now stack canaries are enabled and the player must find a way to programatically brute-force the canary.
3. Now remove the original value check and make players replace a function return pointer to jump to a different solution function.
4. Now make the player create a ROP chain.

Iterative challenges like this are often the easiest to come up with and the most fun for new players to CTF to explore as they can slowly work their way up from minimal knowledge about security exploits to having a good grasp of the fundamentals.

---

### Start with a Scenario

For more intricate challenges, it can be good to use based on real-world scenarios as inspiration. Some of the most interesting security challenges in the real-world involve systems or attack vectors you might not expect:

- Train maintenance company SPS hired a group of polish hackers to crack DRM in metro trains manufactured by Newag, which was intended to block third-party repair centers from repairing their trains and force municipal governments to only sign repair contracts with Newag themselves. [37C3 Presentation](https://www.youtube.com/watch?v=XrlrbfGZo2k) (highly recommended watch its hilarious)
- The UAE government exploited the international trust chain of the 3G cellular network protocol SS7 to trace the location of Princess Sheikha Latifa who had escaped Dubai and was on a boat headed for India. The same vulnerability can be used to intercept SMS two-factor authentication. [Veritasium Video](https://www.youtube.com/watch?v=wVyu7NB7W6Y)
- A Computer Science student in Berlin reverse engineered and exploited a satellite command protocol to recover BeeSat-1, a satellite which had lost communication 12 years prior and was thought to be forever unrecoverable due to a previously unknown software failure. [38C3 Presentation](https://www.youtube.com/watch?v=KdTcd94pVlY)
- Hackers discovered an unpatchable RSA vulnerability in the factory maintenance mode of the Nintendo 3DS which allowed bypassing all security mechanisms of the 3DS using a DS flashcart and a magnet. [33C3 Presentation](https://www.youtube.com/watch?v=8C5cn_Qj0G8)

It’s a great idea to use real-world security vulnerabilities as inspiration for designing challenges. Many security vulnerabilities in the real world are simple enough that the exact vulnerability can be deployed and used as a challenge with minimal modification (eg. Heartbleed, XZ Utils Backdoor, Log4Shell), or you can create simplified clones or mocks of more complex real-world vulnerabilities. The challenges that are grounded in the real world are often the ones that leave players feeling like they are real hackers. Chaos Communication Congress (C3) and DEFCON presentations are good places to look.

# Challenge Difficulty

It’s important to get challenge difficulty right, especially for short CTFs that don’t last more than a day or two. Here are good questions to ask to evaluate how difficult a challenge is:

- Does the challenge description give the player a good sense of where to start looking for the vulnerability?
- How much prior knowledge of the class of vulnerability is expected? Will someone with little knowledge of the exploit domain know what to look for or what to research if they aren’t already aware of the solution?
- How difficult is it to discover the vulnerability? Can the player find it just by poking around at the challenge, or is the player expected to black-box the challenge to find the solution?
- How long does it take to discover the vulnerability? For someone who already has the skills needed to solve the challenge, how much attack surface is there to comb through to find the exploitable mechanism?
- How long does it take to exploit the vulnerability after discovery? Is it finicky, unreliable, or require brute-forcing? Can it be solved by hand or does it need to be scripted?
- How many vulnerabilities need to be exploited? Does the player need to repeat this cycle and discover multiple vulnerabilities and find a way to chain them together, or is it just one or two steps to the solution?

It’s okay for one or two of these things to be difficult but just keep them all in mind when assigning a difficulty rating and points to the challenge. It’s really easy for just one component to spike the difficulty of the challenge. For example, a challenge might seem easy because the vulnerability is easy to exploit, but that doesn’t mean much if it takes the best players hours to even find it.

For a short CTF, it’s best to keep each challenge concise - just one or two vulnerabilities that need to be exploited to solve the challenge. It’s also good to reduce the attack surface so the player doesn’t waste a lot of time just trying to find the specific component they need to attack - although hiding in plain sight is totally valid.

It’s also a good idea to have many different challenges for each level of difficulty. You are likely to have players with a variety of experience levels with CTFs and computer security concepts. It’s a good idea to ensure there is enough content for people of all skill levels to be occupied for they day, and that means making sure a pro who can blast through the easy stuff has enough difficult challenges to work on, and beginners have enough easy content to keep them occupied without getting stuck for hours on a single harder challenge they can’t overcome. 

# Immersive Scenario Design and Presentation

Immersion is a major factor that contributes to how fun a challenge is, and the scenario you create for the challenge and the way you present that scenario is a major part of this immersion. You can think of these components as building the narrative for the challenge.

A challenge should provide a narrative to help the player contextualize the problem they need to solve. On top of that, a player is more likely to find a challenge fun if it’s presented in a way that’s related to something they are already familiar with, as it gives the player an opportunity to learn more about the software and systems they already interact with in their everyday life.

<aside>
🔔

For example, students frequently interact with course registration software like Aurora. A well designed challenge may build upon that familiarity by creating a simplified mock of that system and challenge the player to identify a vulnerability with the software’s login mechanism or course search API to find details about a malicious course entry or admin account. This ensures the player is more likely to engage with the concept of the challenge.

</aside>

These narratives don’t *need* to be intricate. Don’t take things too seriously, and don’t be afraid to create a challenge first then figure out how it integrates into the narrative later. Players will be fine with a corny or nonsensical explanation. But make sure there is some kind of effort put into making the challenge make sense, especially in the broader theme of the CTF, and make sure the narrative and presentation are consistent for the challenge. That said, 

<aside>
💡

A simple narrative about shutting down a botnet with a themed interface to match.

![floorp_2025-02-11_13-32-34.png](attachment:0dee571b-701f-43fa-8b56-b012bac91d3f:floorp_2025-02-11_13-32-34.png)

![floorp_2025-02-11_13-35-18.png](attachment:30547d96-0ce9-4829-9773-a7614687ef54:floorp_2025-02-11_13-35-18.png)

</aside>

<aside>
💡

A binary exploitation challenge in the style of a classic text adventure game. The narrative is corny, that’s okay!

![floorp_2025-02-11_13-37-49.png](attachment:82a6af79-8b04-4f23-bb7e-a7c757cde218:floorp_2025-02-11_13-37-49.png)

![WindowsTerminal_2025-02-11_13-37-13.png](attachment:2b1b36d0-d164-44f6-946a-beb2cdcd2b24:WindowsTerminal_2025-02-11_13-37-13.png)

</aside>

# Challenge Inspiration Resources

### General Sources

- [All challenges from the 2023 CSSA CTF are available on GitHub](https://github.com/umanitoba-cssa/CSSA-CTF-2023-Challenges)
    - It’s a good idea to reuse some of these, especially the easier ones, though maybe change up the narratives so they aren’t completely identical.
    - Since the easier challenges serve as a learning resource to guide players into the harder problems, don’t worry too much if the solution is practically identical to an old challenge.
- [PicoCTF is one of the largest CTFs in the world, and most previous challenges are available on picoGym](https://picoctf.org/index.html#picogym)
- [Exploit-DB](https://www.exploit-db.com/) hosts a giant repository of software vulnerabilities, many of which include proof-of-concept exploit implementations or the relevant vulnerable software.
- [OWASP Top Ten security vulnerabilities](https://owasp.org/www-project-top-ten/)
- [CTF 101 Handbook](https://ctf101.org/)
- Google “common web vulnerabilities”, “common binary exploitation vulnerabilities”, “common ctf vulnerabilities”, etc. There are lots of resources online

### Real-world Inspiration

- [C3 presentations are hosted on YouTube](https://www.youtube.com/@mediacccde)
- [DEFCON presentations are hosted on YouTube](https://www.youtube.com/@DEFCONConference)

# Tools and Resources for Players

It’s a good idea to give players a list of resources they should expect to need ahead of time for short CTFs, so people aren’t stuck waiting for software to download during the competition.

1. **Linux VM**: The truth is a lot of useful CTF software is only available for Linux. It’s a good idea to ask players to have a Linux VM ready to go just in case.
    - Any distro is fine, such as Ubuntu. Alternatively Kali will have a lot of useful software preinstalled: https://www.kali.org/get-kali/#kali-platforms
    - Windows users can use [WSL2 (free, optimized for CLI usage)](https://learn.microsoft.com/en-us/windows/wsl/install), [VirtualBox (free)](https://www.virtualbox.org/), [VMWare Workstation Pro (free but requires an account)](https://www.vmware.com/products/desktop-hypervisor/workstation-and-fusion) or [HyperV (Windows 10/11 Pro or higher tier only)](https://learn.microsoft.com/en-us/windows-server/virtualization/hyper-v/get-started/install-hyper-v?pivots=windows)
    - MacOS users can use [UTM (free)](https://mac.getutm.app/), [VMWare Fusion (free but requires an account)](https://www.vmware.com/products/desktop-hypervisor/workstation-and-fusion) or [Parallels (paid)](https://www.parallels.com/)
    - Access to Aviary might be enough, but its difficult to install software there and not everyone will be in a course that gives them access to the CS labs.
2. Software tools
    - A hex editor like [ImHex](https://imhex.werwolv.net/) or [HxD](https://mh-nexus.de/en/hxd/)
    - A text editor like [VSCode](https://code.visualstudio.com/)
    - A binary decompiler like [Ghidra](https://ghidra-sre.org/), IDA, or Binary Ninja
    - A Java decompiler like [jd-gui](https://github.com/java-decompiler/jd-gui) (if we make any Java RE challenges)
    - A .NET decompiler like [ilSpy (VSCode extension)](https://marketplace.visualstudio.com/items?itemName=icsharpcode.ilspy-vscode), [dnSpy](https://github.com/dnSpyEx/dnSpy) or [dotPeek](https://www.jetbrains.com/decompiler/) (if we make any .NET RE challenges)
    - A debugger like GDB or LLDB
    - The [pwntools Python library](https://docs.pwntools.com/en/stable/)
    - [ROPgadget](https://github.com/JonathanSalwan/ROPgadget) (if we make any ROPchain challenges)
    - A pcap analysis tool like [Wireshark](https://www.wireshark.org/)
    - A web API debugger tool like [Insomnia](https://insomnia.rest/), [Hoppscotch](https://hoppscotch.io/), or [Postman](https://www.postman.com/)
    - Netcat or [ncat](https://nmap.org/ncat/)
3. Learning and Practice Resources
    - The best place to practice before the CTF is [picoGym](https://picoctf.org/index.html#picogym)
    - It could be worth hosting a copy of the 2023 CSSA CTF challenges as well. This can help test the deployment ahead of the competition.
    - [CTF 101 Handbook](https://ctf101.org/)
    - A workshop or two ahead of the event would be good.
# Use a minimal, secure Linux base image
FROM ubuntu:noble

# Install only essential packages
RUN apt-get update && apt-get install -y \
    openssh-server \
    libseccomp2 \
    libncurses6 \
    && rm -rf /var/lib/apt/lists/*

# Create necessary directories
RUN mkdir -p /var/run/sshd /challenge

# Create a restricted user "detective"
RUN useradd -m -d /home/detective -s /bin/sh detective

# Copy the challenge binary and data files into /challenge (owned by root)
COPY bin/ /challenge/
RUN chmod -R 755 /challenge && chown -R root:root /challenge

# Make /challenge read/execute-only for player
RUN chmod -R 755 /challenge && chown -R root:root /challenge
RUN chmod -R o-w /challenge  # Prevent "detective" from writing

# Create an entry script to prevent escape via signals
RUN echo '#!/bin/sh\ncd /challenge\nexec /challenge/client' > /challenge/start.sh
RUN chmod +x /challenge/start.sh

# SSH Configuration: Restrict user access
RUN echo 'Match User detective' >> /etc/ssh/sshd_config && \
    echo '    ForceCommand /challenge/start.sh' >> /etc/ssh/sshd_config && \
    echo '    AllowTcpForwarding no' >> /etc/ssh/sshd_config && \
    echo '    X11Forwarding no' >> /etc/ssh/sshd_config && \
    echo '    PermitRootLogin no' >> /etc/ssh/sshd_config && \
    echo '    PasswordAuthentication yes' >> /etc/ssh/sshd_config && \
    echo '    PermitEmptyPasswords yes' >> /etc/ssh/sshd_config && \
    echo '    ChallengeResponseAuthentication no' >> /etc/ssh/sshd_config

# Set a simple password for detective (optional, can be removed)
RUN echo "detective:CSSActf2025!" | chpasswd

# Restrict process visibility (hides other processes from detective)
RUN echo "kernel.yama.ptrace_scope = 2" >> /etc/sysctl.conf

# Disable core dumps
RUN echo "* hard core 0" >> /etc/security/limits.conf

# Expose SSH port
EXPOSE 22

# Start SSH service
CMD ["/usr/sbin/sshd", "-D"]

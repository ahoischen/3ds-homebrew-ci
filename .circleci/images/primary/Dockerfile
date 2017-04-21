# thewtex/opengl provides opengl functionality, which citra depends on.
FROM thewtex/opengl:latest
USER user
ENV HOME="/home/user"
ENV DEVKITPRO="/opt/devkitPro"
ENV DEVKITARM="${DEVKITPRO}/devkitARM"
ENV CITRA_SDMC="${HOME}/.local/share/citra-emu/sdmc"

ADD ["etc/apt/", "/etc/apt/"]

# Install:
RUN sudo apt-get update && sudo apt-get install -y \
    # libsdl2 for citra
    libsdl2-2.0-0 \

    # Required packages for CircleCI
    git \
    ssh \
    tar \
    gzip \
    ca-certificates \
    zip \
    libstdc++6/testing \
    cmake/testing \
    && sudo apt-get -y clean

# Install the latest libstdc++6, which is only available through a ppa.
#ADD libstdc++.so.6.0.22 /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.22
#RUN sudo rm /usr/lib/x86_64-linux-gnu/libstdc++.so.6 && \
#    sudo ln -s /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.22 /usr/lib/x86_64-linux-gnu/libstdc++.so.6

# The devkitARM archive contains the folder, so it has to be extracted in $DEVKITPRO, not ARM.
ARG devkit_arm_url="https://downloads.sourceforge.net/project/devkitpro/devkitARM/devkitARM_r46/devkitARM_r46-x86_64-linux.tar.bz2"
RUN sudo mkdir -p /tmp/citra /usr/bin/ "${DEVKITPRO}/libctru" && \
    curl -L ${devkit_arm_url} | \
    sudo tar xpjC "${DEVKITPRO}"

# Libctru's archive has all files directly at it's root, so it'l be extracted into the libctru folder.
ARG libctru_url="https://github.com/smealum/ctrulib/releases/download/v1.2.1/libctru-1.2.1.tar.bz2"
RUN curl -L ${libctru_url} | \
    sudo tar xpvj -C "${DEVKITPRO}/libctru"

# Install makerom from source.
RUN git -C /tmp/ clone "https://github.com/profi200/Project_CTR.git" && \
    make -C /tmp/Project_CTR/makerom && \
    sudo mv /tmp/Project_CTR/makerom/makerom /usr/bin && \
    rm -rf /tmp/Project_CTR

# Install bannertool from source
RUN git -C /tmp/ clone --recursive "https://github.com/Steveice10/bannertool.git" && \
    make -C /tmp/bannertool && \
    sudo mv /tmp/bannertool/output/linux-x86_64/bannertool /usr/bin && \
    rm -rf /tmp/bannertool

# Install citra. Citra's archive contains one folder named after it's current build number. Inside are two executables,
# a license and a readme. We only care about `citra`, so we'll just copy it into /usr/bin and remove the rest.
# This should stay a separate layer, since citra has nightly builds and new features are frequently added.
ARG citra_build="citra-linux-20170418-941a3dd"
ARG citra_url="https://github.com/citra-emu/citra-nightly/releases/download/nightly-111/${citra_build}.tar.xz"
RUN curl -L ${citra_url} | \
    sudo tar xpvJC /tmp/ && \
    sudo mv "/tmp/${citra_build}/citra" /usr/bin && \
    sudo rm -rf "/tmp/${citra_build}"

# Override supervisord. thewtex/opengl was intended to run $APP in a noVNC session at startup.
# However, we want to run and build the project and then run citra. To enable us to run this
# script, we need to start bash and then manually run
#   $ sudo /usr/bin/supervisord -c /etc/supervisor/supervisord.conf &
# before running citra.
CMD ["/bin/bash"]
